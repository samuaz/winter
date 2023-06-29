//
// Created by Samuel Azcona on 07/06/2020.
//

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_abstract_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_values.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>

winter::data::sql_impl::Values::Values(const std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>>& fields) :
    predicate_(fields) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> winter::data::sql_impl::Values::Fields() const {
    return predicate_.fields();
};

std::string
winter::data::sql_impl::Values::Query() const {
    std::vector<std::string> columns;
    auto                     fields = predicate_.fields();

    for (const auto& field : fields) { columns.push_back(field->name()); }

    std::string query = winter::util::string::replace_value(
        query_template_,
        query_param_columns_,
        winter::data::sql_impl::CommaSeparatedValue(columns));

    return winter::util::string::replace_value(
        query,
        query_param_values_,
        winter::data::sql_impl::CommaSeparatedStatement(fields));
}
