#pragma once

#include "date.h"

#include <string>
#include <memory>

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
    LogicalOperationNode(LogicalOperation o, std::shared_ptr<Node> l, std::shared_ptr<Node> r);
    bool Evaluate(const Date &d, const std::string &e) const override;
private:
    const LogicalOperation operation;
    const std::shared_ptr<Node> lhs;
    const std::shared_ptr<Node> rhs;
};

class DateComparisonNode : public Node
{
public:
    DateComparisonNode(Comparison c, const Date &d);
    bool Evaluate(const Date &d, const std::string &e) const override;
private:
    const Comparison comparison;
    const Date date;
};

class EventComparisonNode : public Node
{
public:
    EventComparisonNode(Comparison c, const std::string &e);
    bool Evaluate(const Date &d, const std::string &e) const override;
private:
    const Comparison comparison;
    const std::string event;
};