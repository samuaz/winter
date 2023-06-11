//
// Created by Samuel Azcona on 07/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_into.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

winter::data::sql_impl::Into::Into(const StatementValue &statement_value) :
    statement_value_(statement_value) {}

std::string winter::data::sql_impl::Into::Query() const {
    std::string statement_query;
    if (auto sharedTableValue = std::get_if<std::shared_ptr<Table>>(&statement_value_)) {
        statement_query = sharedTableValue->get()->name();
    } else if (auto tableValue = std::get_if<Table>(&statement_value_)) {
        statement_query = tableValue->name();
    } else {
        std::string typeName = StatementValueType(statement_value_.index());
        std::string error = "invalid statement_value " + typeName + "not supported";
        throw ::winter::exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            (error));
    }

    return winter::util::string::replace_value(
        query_template_,
        query_param_,
        winter::data::sql_impl::CommaSeparatedValue({statement_query}));
}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() {
    return {};
}
