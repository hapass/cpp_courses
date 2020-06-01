#pragma once

#include <string>
#include <memory>

class Date;

enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation
{
    And,
    Or
};

class Node
{
public:
    virtual bool Evaluate(const Date &date, const std::string &event) const = 0;
    virtual ~Node() = default;
};

class EmptyNode : public Node
{
public:
    bool Evaluate(const Date &date, const std::string &event) const override;
};

class LogicalOperationNode : public Node
{
public:
    LogicalOperationNode(LogicalOperation op, std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs);
    bool Evaluate(const Date &date, const std::string &event) const override;
};

class DateComparisonNode : public Node
{
public:
    DateComparisonNode(Comparison comp, const Date &date);
    bool Evaluate(const Date &date, const std::string &event) const override;
};

class EventComparisonNode : public Node
{
public:
    EventComparisonNode(Comparison comp, const std::string &event);
    bool Evaluate(const Date &date, const std::string &event) const override;
};