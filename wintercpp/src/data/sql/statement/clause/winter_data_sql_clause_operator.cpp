//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>

using namespace winter::data::sql_impl;

std::string
GetCondition<Condition::EQ>::Get() {
  return "=";
}

std::string
GetCondition<Condition::NOT_EQ>::Get() {
  return "!=";
}

std::string
GetCondition<Condition::GREATER>::Get() {
  return ">";
}

std::string
GetCondition<Condition::GREATER_EQ>::Get() {
  return ">=";
}

std::string
GetCondition<Condition::LESS>::Get() {
  return "<";
}

std::string
GetCondition<Condition::LESS_EQ>::Get() {
  return "<=";
}

std::string
GetCondition<Condition::IN>::Get() {
  return "IN";
}

std::string
GetCondition<Condition::NOT>::Get() {
  return "NOT";
}

std::string
GetCondition<Condition::NOT_IN>::Get() {
  return "NOT IN";
}

std::string
GetCondition<Condition::BETWEEN>::Get() {
  return "BETWEEN";
}

std::string
GetCondition<Condition::IS>::Get() {
  return "IS";
}

std::string
GetCondition<Condition::LIKE>::Get() {
  return "LIKE";
}

std::string
GetCondition<Condition::EXISTS>::Get() {
  return "EXISTS";
}

std::string
GetCondition<Condition::NOT_NULL>::Get() {
  return "NOT NULL";
}

std::string
GetCondition<Condition::IS_NULL>::Get() {
  return "IS NULL";
}

std::string
GetCondition<Condition::IS_NOT_NULL>::Get() {
  return "IS NOT NULL";
}

std::string
GetCondition<Condition::NONE>::Get() {
  return "";
}

std::string
winter::data::sql_impl::condition(enum Condition condition) {
  switch (condition) {
    case Condition::EQ:
      return GetCondition<Condition::EQ>::Get();
    case Condition::NOT_EQ:
      return GetCondition<Condition::NOT_EQ>::Get();
    case Condition::LESS:
      return GetCondition<Condition::LESS>::Get();
    case Condition::LESS_EQ:
      return GetCondition<Condition::LESS_EQ>::Get();
    case Condition::GREATER:
      return GetCondition<Condition::GREATER>::Get();
    case Condition::GREATER_EQ:
      return GetCondition<Condition::GREATER_EQ>::Get();
    case Condition::IN:
      return GetCondition<Condition::IN>::Get();
    case Condition::NOT:
      return GetCondition<Condition::NOT>::Get();
    case Condition::NOT_IN:
      return GetCondition<Condition::NOT_IN>::Get();
    case Condition::BETWEEN:
      return GetCondition<Condition::BETWEEN>::Get();
    case Condition::IS:
      return GetCondition<Condition::IS>::Get();
    case Condition::LIKE:
      return GetCondition<Condition::LIKE>::Get();
    case Condition::EXISTS:
      return GetCondition<Condition::EXISTS>::Get();
    case Condition::NONE:
      return GetCondition<Condition::NONE>::Get();
    case Condition::NOT_NULL:
      return GetCondition<Condition::NOT_NULL>::Get();
    case Condition::IS_NULL:
      return GetCondition<Condition::IS_NULL>::Get();
    case Condition::IS_NOT_NULL:
      return GetCondition<Condition::IS_NOT_NULL>::Get();
  }
}
