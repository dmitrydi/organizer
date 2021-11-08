#pragma once

#include <string>
#include <exception>
#include <memory>
#include "date.h"

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum class LogicalOperation {
  And,
  Or
};

class Node {
public:
  virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
  virtual ~Node() = default;
};

class EmptyNode: public Node {
public:
  bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode: public Node {
public:
  DateComparisonNode(const Comparison& comparison, const Date& value);
  bool Evaluate(const Date& date, const std::string& event) const override;
private:
  const Comparison comparison_;
  const Date value_;
};

class EventComparisonNode: public Node {
public:
  EventComparisonNode(const Comparison& comparison, const std::string& event);
  bool Evaluate(const Date& date, const std::string& event) const override;
private:
  const Comparison comparison_;
  const std::string event_;
};

class LogicalOperationNode: public Node {
public:
  LogicalOperationNode(const LogicalOperation& op,
                       std::shared_ptr<const Node> lhs,
                       std::shared_ptr<const Node> rhs);
  bool Evaluate(const Date& date, const std::string& event) const override;
private:
  const LogicalOperation op_;
  std::shared_ptr<const Node> lhs_, rhs_;

};
