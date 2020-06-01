#include "node.h"

using namespace std;

bool EmptyNode::Evaluate(const Date &date, const string &event) const
{
    return false;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation o, shared_ptr<Node> l, shared_ptr<Node> r)
    : operation(o), lhs(l), rhs(r)
{
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const
{
    switch (operation)
    {
    case LogicalOperation::And:
        return lhs->Evaluate(date, event) && rhs->Evaluate(date, event);
    case LogicalOperation::Or:
        return lhs->Evaluate(date, event) || rhs->Evaluate(date, event);
    }
}

DateComparisonNode::DateComparisonNode(Comparison c, const Date &d) : comparison(c), date(d) {}

bool DateComparisonNode::Evaluate(const Date &d, const string &e) const
{
    switch (comparison)
    {
    case Comparison::Less: return d < date;
    case Comparison::LessOrEqual: return d <= date;
    case Comparison::Greater: return d > date;
    case Comparison::GreaterOrEqual: return d >= date;
    case Comparison::Equal: return d == date;
    case Comparison::NotEqual: return d != date;
    }
}

EventComparisonNode::EventComparisonNode(Comparison c, const string &e) : comparison(c), event(e) {}

bool EventComparisonNode::Evaluate(const Date &d, const string &e) const
{
    switch (comparison)
    {
    case Comparison::Less: return e < event;
    case Comparison::LessOrEqual: return e <= event;
    case Comparison::Greater: return e > event;
    case Comparison::GreaterOrEqual: return e >= event;
    case Comparison::Equal: return e == event;
    case Comparison::NotEqual: return e != event;
    }
}