//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_or.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

winter::data::sql_impl::Or::Or(const Predicate &predicate) :
    predicate_(predicate) {}

winter::data::sql_impl::Or::Or(const StatementValue &statement_value) :
    predicate_(statement_value) {}

winter::data::sql_impl::Or::Or(const StatementValue             &statement_value,
                               winter::data::sql_impl::Condition condition) :
    predicate_(statement_value, condition) {}

std::vector<PreparedStatementField> winter::data::sql_impl::Or::Or::Fields() const {
    return predicate_.fields();
}

std::string
winter::data::sql_impl::Or::Query() const {
    std::ostringstream builder;
    std::string        lstatement = predicate_.lstatementStr();
    std::string        rstatement = predicate_.rstatementStr();
    std::string        condition = predicate_.conditionStr();

    std::string result;
    if (predicate_.has_fields()) {
        for (auto &field : predicate_.fields()) {
            if (field.IsCustomValue()) {
                builder << lstatement
                        << Space() << condition << Space()
                        << field.custom_value().value();
            } else {
                builder << lstatement
                        << Space() << condition << Space()
                        << PlaceHolder();
            }
        }
    } else if (predicate_.has_rstatement()) {
        builder << lstatement
                << Space() << condition << Space()
                << rstatement;
    } else {
        builder << lstatement
                << Space() << condition;
    }

    return replace_value(query_template_, query_param_, builder.str());
}