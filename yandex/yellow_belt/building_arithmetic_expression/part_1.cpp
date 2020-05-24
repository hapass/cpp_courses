#include <iostream>
#include <deque>
#include "test_runner.h"

using namespace std;

void RunProgram(istream& input, ostream& output) {
    string initial_value;
    int operations_count = 0;
    input >> initial_value >> operations_count;

    deque<string> expression;
    expression.push_back(initial_value);
    while(operations_count-- > 0) {
        string operation;
        int value = 0;
        input >> operation >> value;
        expression.push_front("(");
        expression.push_back(") ");
        expression.push_back(operation);
        expression.push_back(" ");
        expression.push_back(to_string(value));
    }

    for (const string& str: expression) {
        output << str;
    }
}

void TestSimpleExpression() {
    {
        istringstream input("8\n1\n* 3\n- 6\n/ 1\n");
        ostringstream output;
        RunProgram(input, output);
        AssertEqual(output.str(), "(8) * 3");
    }

    {
        istringstream input("8\n2\n* 3\n- 6\n/ 1\n");
        ostringstream output;
        RunProgram(input, output);
        AssertEqual(output.str(), "((8) * 3) - 6");
    }

    {
        istringstream input("8\n3\n* 3\n- 6\n/ 1\n");
        ostringstream output;
        RunProgram(input, output);
        AssertEqual(output.str(), "(((8) * 3) - 6) / 1");
    }
}

void TestMultDivNegPlus() {
    istringstream input("18\n4\n* 32\n/ 16\n- 10\n+ 333");
    ostringstream output;
    RunProgram(input, output);
    AssertEqual(output.str(), "((((18) * 32) / 16) - 10) + 333");
}

void TestPlusNegDivMult() {
    istringstream input("18\n4\n+ 32\n- 16\n/ 10\n* 333");
    ostringstream output;
    RunProgram(input, output);
    AssertEqual(output.str(), "((((18) + 32) - 16) / 10) * 333");
}

void TestNoOperation() {
    istringstream input("18\n0\n");
    ostringstream output;
    RunProgram(input, output);
    AssertEqual(output.str(), "18");
}

void TestSignedNumbers() {
    istringstream input("+18\n5\n+ -2\n- -5\n* -50\n/ -13\n+ -0");
    ostringstream output;
    RunProgram(input, output);
    AssertEqual(output.str(), "(((((+18) + -2) - -5) * -50) / -13) + 0");
}

void TestHighLoad() {
    stringstream input;
    int iterations = 10000;
    input << "0\n";
    input << iterations << "\n";
    for (int i = 0; i < iterations; i++) {
        input << "+ 1\n";
    }

    bool success = true;
    try {
        ostringstream output;
        RunProgram(input, output);
    } catch(exception& e) {
        success = false;
    }
    Assert(success, "Does not crash on 10000 inputs.");
}

int main() {
    TestRunner r;
    r.RunTest(TestSimpleExpression, "TestSimpleExpression");
    r.RunTest(TestMultDivNegPlus, "TestMultDivNegPlus");
    r.RunTest(TestPlusNegDivMult, "TestPlusNegDivMult");
    r.RunTest(TestNoOperation, "TestNoOperation");
    r.RunTest(TestSignedNumbers, "TestSignedNumbers");
    r.RunTest(TestHighLoad, "TestHighLoad");
    RunProgram(cin, cout);
    return 0;
}