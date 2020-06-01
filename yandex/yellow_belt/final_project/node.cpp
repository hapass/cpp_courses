#include "node.h"

using namespace std;

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
    return false;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation op, shared_ptr<Node> lhs, shared_ptr<Node> rhs) {}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
    return false;
}

DateComparisonNode::DateComparisonNode(Comparison comp, const Date &date) {}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
    return false;
}

EventComparisonNode::EventComparisonNode(Comparison comp, const string &event) {}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {
    return false;
}