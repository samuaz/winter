//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/function/winter_data_sql_function_min.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>
#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h"

using namespace winter::util::string;

winter::data::sql_impl::Min::Min(StatementValues column) :
    Clause("MIN($min) AS min_$columnName", "$min"),
    column_(std::move(column)) {
        Prepare();
    }

    std::string winter::data::sql_impl::Min::Min::name() const {
            return "Min";
    };

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Min::Prepare() {
    std::ostringstream builder;

        if (auto columnValue = std::get_if<Column>(&column_)) {
             builder << columnValue->TableName() << Dot() << columnValue->name();
        }
        // Verificamos si el elemento es de tipo std::string
        else if (auto clauseValue = std::get_if<winter::data::sql_impl::IStatementValue>(&column_)) {
            builder << clauseValue->query();
        }

    std::string minFunString = replace_value(statement_template(), param(), builder.str());
    BuildQuery() << replace_value(minFunString, "$columnName", builder.str());

    return PreparedStatement(
        StatementType::KFunction,
        query());
}
