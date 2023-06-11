//
// Created by Samuel Azcona on 24/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>
#include <variant>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"
#include "wintercpp/data/sql/table/winter_data_sql_table.h"
#include "wintercpp/exception/generic/winter_internal_exception.h"

using namespace winter::util::string;

winter::data::sql_impl::From::From(const StatementValue &statement_value) {
    statement_values_.push_back(statement_value);
}

winter::data::sql_impl::From::From(const std::vector<StatementValue> &statement_values) :
    statement_values_(statement_values) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> winter::data::sql_impl::From::Fields() const {
    return {};
}

std::string winter::data::sql_impl::From::Query() const {
    std::vector<std::string> tablesNames;

    for (auto const &statement_value : statement_values_) {
        if (auto sharedTableValue = std::get_if<std::shared_ptr<Table>>(&statement_value)) {
            tablesNames.push_back(sharedTableValue->get()->name());
        } else if (auto tableValue = std::get_if<Table>(&statement_value)) {
            tablesNames.push_back(tableValue->name());
        } else if (auto clauseValue = std::get_if<std::shared_ptr<Clause>>(&statement_value)) {
            tablesNames.push_back(clauseValue->get()->Query());
        } else {
            std::string typeName = StatementValueType(statement_value.index());
            std::string error = "invalid statement_value " + typeName + "not supported";
            throw ::winter::exception::WinterInternalException::Create(
                __FILE__,
                __FUNCTION__,
                __LINE__,
                (error));
        }
    }
    return winter::util::string::replace_value(
        query_template_,
        query_param_,
        winter::data::sql_impl::CommaSeparatedValue(tablesNames));
}
