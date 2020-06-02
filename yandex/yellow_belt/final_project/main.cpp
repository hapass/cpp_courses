#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream &is)
{
    string result;
    while (is.peek() == ' ') is.ignore();
    if (!getline(is, result, '\n')) throw invalid_argument("stream doesn't contain event");
    return result;
}

void RunProgram(istream& input, ostream& output)
{
    Database db;

    for (string line; getline(input, line);)
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add")
        {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        else if (command == "Print")
        {
            db.Print(output);
        }
        else if (command == "Del")
        {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            output << "Removed " << count << " entries" << endl;
        }
        else if (command == "Find")
        {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto &entry : entries)
            {
                output << entry << endl;
            }
            output << "Found " << entries.size() << " entries" << endl;
        }
        else if (command == "Last")
        {
            try
            {
                output << db.Last(ParseDate(is)) << endl;
            }
            catch (invalid_argument &)
            {
                output << "No entries" << endl;
            }
        }
        else if (command.empty())
        {
            continue;
        }
        else
        {
            throw logic_error("Unknown command: " + command);
        }
    }
}

void TestParseCondition()
{
    {
        istringstream is("date != 2017-11-18");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 1");
        Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
    }
    {
        istringstream is(R"(event == "sport event")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
        Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
    }
    {
        istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 5");
        Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
        Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
        Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
        Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
    }
    {
        istringstream is(R"(event != "sport event" AND event != "Wednesday")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
        Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
        Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
    }
    {
        istringstream is(R"(event == "holiday AND date == 2017-11-18")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
        Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
        Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
    }
    {
        istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
        Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
    }
    {
        istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
        Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
        Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
    }
    {
        istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
        Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
        Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
    }
    {
        istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
        Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
    }
    {
        istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
        Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
        Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
    }
}

void TestParseEvent()
{
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestDelete()
{
    istringstream is("Add 2017-06-01 1st of June\nAdd 2017-07-08 8th of July\nAdd 2017-07-08 Someone's birthday\nDel date == 2017-07-08");
    ostringstream os;
    RunProgram(is, os);
    AssertEqual(os.str(), "Removed 2 entries", "Delete test case.");
}

void TestPrint()
{
    istringstream is("Add 2017-01-01 Holiday\nAdd 2017-03-08 Holiday\nAdd 2017-1-1 New Year\nAdd 2017-1-1 New Year\nPrint");
    ostringstream os;
    RunProgram(is, os);
    AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday", "Print test case.");
}

void TestFind()
{
    istringstream is("Add 2017-01-01 Holiday\nAdd 2017-03-08 Holiday\nAdd 2017-01-01 New Year\nFind event != \"working day\"\nAdd 2017-05-09 Holiday");
    ostringstream os;
    RunProgram(is, os);
    AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\nFound 3 entries", "Find test case.");
}

void TestLast()
{
    istringstream is("Add 2017-01-01 New Year\nAdd 2017-03-08 Holiday\nAdd 2017-01-01 Holiday\nLast 2016-12-31\nLast 2017-01-01\nLast 2017-06-01\nAdd 2017-05-09 Holiday");
    ostringstream os;
    RunProgram(is, os);
    AssertEqual(os.str(), "No entries\n2017-01-01 Holiday\n2017-03-08 Holiday", "Last test case.");
}

void TestIntegration()
{
    istringstream is("Add 2017-11-21 Tuesday\nAdd 2017-11-20 Monday\nAdd 2017-11-21 Weekly meeting\nPrint\nFind event != \"Weekly meeting\"\nLast 2017-11-30\nDel date > 2017-11-20\nLast 2017-11-30\nLast 2017-11-01");
    ostringstream os;
    RunProgram(is, os);
    AssertEqual(os.str(), "2017-11-20 Monday\n2017-11-21 Tuesday\n2017-11-21 Weekly meeting\n2017-11-20 Monday\n2017-11-21 Tuesday\nFound 2 entries\n2017-11-21 Weekly meeting\nRemoved 2 entries\n2017-11-20 Monday\nNo entries", "Integration test case.");
}

void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDelete, "TestDelete");
    tr.RunTest(TestPrint, "TestPrint");
    tr.RunTest(TestFind, "TestFind");
    tr.RunTest(TestLast, "TestLast");
    tr.RunTest(TestIntegration, "TestIntegration");
}

int main()
{
    TestAll();
    RunProgram(cin, cout);
    return 0;
}
