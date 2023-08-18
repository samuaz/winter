//
// Created by Samuel Azcona on 24/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>
#include <variant>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

From::From(const Predicate &predicate) {
    predicate_.push_back(predicate);
}

From::From(const std::vector<Predicate> &predicates) :
    predicate_(predicates) {}

From::From(const StatementValue &statement_value) {
    predicate_.push_back(Predicate(statement_value));
}

From::From(const std::vector<StatementValue> &statement_value) {
    for (auto const &statement_value : statement_value) {
        predicate_.push_back(Predicate(statement_value));
    }
}

std::vector<PreparedStatementField> winter::data::sql_impl::From::Fields() const {
    std::vector<PreparedStatementField> fields;
    fields.reserve(predicate_.size());
    for (const auto &predicate : predicate_) {
        auto predicateFields = predicate.fields();
        fields.insert(fields.end(), predicateFields.begin(), predicateFields.end());
    }
    return fields;
}

std::string winter::data::sql_impl::From::Query() const {
    std::vector<std::string> tablesNames;
    tablesNames.reserve(predicate_.size());
    for (const auto &predicate : predicate_) {
        tablesNames.push_back(predicate.lstatementStr());
    }
    return winter::util::string::replace_value(
        query_template_,
        query_param_,
        winter::data::sql_impl::CommaSeparatedValue(tablesNames));
}
