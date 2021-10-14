#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
  return true;
};

DateComparisonNode::DateComparisonNode(const Comparison& comparison, const Date& value):
    comparison_(comparison),
    value_(value) {};

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
  switch (comparison_) {
  case Comparison::Less:
    return date < value_;
  case Comparison::LessOrEqual:
    return date <= value_;
  case Comparison::Greater:
    return date > value_;
  case Comparison::GreaterOrEqual:
    return date >= value_;
  case Comparison::Equal:
    return date == value_;
  case Comparison::NotEqual:
    return date != value_;
  default:
    //throw domain_error("Unexpected date comparison operation");
    return 0;
  }
};

EventComparisonNode::EventComparisonNode(const Comparison& comparison, const string& event) :
    comparison_(comparison),
    event_(event) {};
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
  switch (comparison_) {
  case Comparison::Less:
    return event < event_;
  case Comparison::LessOrEqual:
    return event <= event_;
  case Comparison::Greater:
    return event > event_;
  case Comparison::GreaterOrEqual:
    return event >= event_;
  case Comparison::Equal:
    return event == event_;
  case Comparison::NotEqual:
    return event != event_;
  default:
    //throw domain_error("Unexpected event comparison operation");
    return 0;
  }
};

LogicalOperationNode::LogicalOperationNode(const LogicalOperation & op,
                                           shared_ptr<const Node> lhs,
                                           shared_ptr<const Node> rhs):
                                               op_(op),
                                               lhs_(lhs),
                                               rhs_(rhs) {};
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
  switch(op_) {
    case LogicalOperation::And:
      return lhs_->Evaluate(date, event) && rhs_->Evaluate(date, event);
    case LogicalOperation::Or:
      return lhs_->Evaluate(date, event) || rhs_ -> Evaluate(date, event);
    default:
      //throw domain_error("Unexpected logical operation");
      return 0;
  }
}




