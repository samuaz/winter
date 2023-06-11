//
// Created by Samuel Azcona on 16/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_set.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>
#include <utility>

winter::data::sql_impl::Set::Set(const std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> &fields) :
    fields_(fields) {}

std::string
winter::data::sql_impl::Set::Query() const {
    return winter::util::string::replace_value(
        query_template_,
        query_param_,
        winter::data::sql_impl::commaSeparatedEqualValue(fields_));
}
