//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/function/winter_data_sql_function_min.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>

#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values_utils.h"

using namespace winter::util::string;
using namespace winter::data::sql_impl;

winter::data::sql_impl::Min::Min(const StatementValue& statement_value) :
    statement_value_(statement_value) {
    alias_ = name();
    if (auto columnValue = std::get_if<Column>(&statement_value_)) {
        field_type_ = columnValue->type();
    } else if (auto sharedColumnValue = std::get_if<std::shared_ptr<Column>>(&statement_value_)) {
        field_type_ = sharedColumnValue->get()->type();
    } else if (auto clauseValue = std::get_if<std::shared_ptr<Clause>>(&statement_value_)) {
        field_type_ = clauseValue->get()->FieldType();
    }
}

winter::data::sql_impl::Min::Min(
    const StatementValue&                    statement_value,
    const std::string&                       alias,
    const winter::data::sql_impl::FieldType& field_type) :
    statement_value_(statement_value) {
    alias_ = alias;
    field_type_ = field_type;
}

std::string winter::data::sql_impl::Min::Min::name() const {
    std::ostringstream builder;
    if (auto columnValue = std::get_if<Column>(&statement_value_)) {
        builder << columnValue->TableName() << "_" << columnValue->name();
    } else if (auto sharedColumnValue = std::get_if<std::shared_ptr<Column>>(&statement_value_)) {
        builder << columnValue->TableName() << "_" << columnValue->name();
    } else {
        builder << GetStatementName(statement_value_);
    }
    return replace_value(query_param_min_column_name_, query_param_column_name_, builder.str());
};

std::vector<PreparedStatementField> winter::data::sql_impl::Min::Fields() const {
    return {};
}

std::string
winter::data::sql_impl::Min::Query() const {
    std::string minFunString = replace_value(query_template_, query_param_, GetStatementValue(statement_value_));
    return replace_value(minFunString, query_param_min_column_name_, *Alias());
}

/* winter::data::sql_impl::FieldType winter::data::sql_impl::Min::fieldType() {
    if (auto columnValue = std::get_if<Column>(&statement_value_)) {
        return columnValue->type();
    } else if (auto clauseValue = std::get_if<std::shared_ptr<winter::data::sql_impl::IStatementValue>>(&statement_value_)) {
        return clauseValue->get()->fieldType();
    } else {
        throw exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            ("invalid call to fieldtype function on clause"));
    }
} */
