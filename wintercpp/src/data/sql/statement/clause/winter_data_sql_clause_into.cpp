//
// Created by Samuel Azcona on 07/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_into.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::data::sql_impl;

Into::Into(const Predicate &predicate) :
    predicate_(predicate) {}

Into::Into(const StatementValue &statementValue) :
    predicate_(statementValue) {}

std::string Into::Query() const {
    return winter::util::string::replace_value(
        query_template_,
        query_param_,
        predicate_.lstatementStr());
}

std::vector<PreparedStatementField> Into::Fields() const {
    return predicate_.fields();
}
