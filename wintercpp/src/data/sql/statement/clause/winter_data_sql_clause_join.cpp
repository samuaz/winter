//
// Created by Samuel Azcona on 16/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_join.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>
#include <variant>

using namespace winter::data::sql_impl;

Join::Join(const StatementValue& statement_value,
           JoinType              type) :
    predicate_(statement_value),
    type_(type) {
}

Join::Join(const StatementValue& statement_value) :
    predicate_(statement_value),
    type_(JoinType::DEFAULT) {
}

std::vector<PreparedStatementField> Join::Fields() const {
    return predicate_.fields();
}

std::string
Join::Query() const {
    std::string query = winter::util::string::replace_value(query_template_, "$type", GenerateType());
    return winter::util::string::replace_value(
        query,
        query_param_,
        predicate_.lstatementStr());
}

std::string Join::GenerateType() const {
    switch (type_) {
        case JoinType::INNER: return "INNER";
        case JoinType::LEFT: return "LEFT";
        case JoinType::RIGHT: return "RIGHT";
        case JoinType::CROSS: return "CROSS";
        case JoinType::DEFAULT: return "INNER";
        case JoinType::FULL_JOIN: return "FULL";
    }
    return std::string();
}
