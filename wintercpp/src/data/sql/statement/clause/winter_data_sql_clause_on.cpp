//
// Created by Samuel Azcona on 17/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_on.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>

#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

winter::data::sql_impl::On::On(const StatementValue             &l_statement_value,
                               winter::data::sql_impl::Condition condition,
                               const StatementValue             &r_statement_value) :
    l_statement_value_(l_statement_value),
    r_statement_value_(r_statement_value), condition_(condition) {}

winter::data::sql_impl::On::On(const StatementValue             &l_statement_value,
                               winter::data::sql_impl::Condition condition) :
    l_statement_value_(l_statement_value),
    condition_(condition) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> winter::data::sql_impl::On::Fields() const {
    return {};
};

std::string
winter::data::sql_impl::On::Query() const {
    auto getStatementValue = [](const StatementValue &statement_value) -> std::string {
        if (auto sharedColumnValue = std::get_if<std::shared_ptr<Column>>(&statement_value)) {
            return sharedColumnValue->get()->FullName();
        } else if (auto columnValue = std::get_if<Column>(&statement_value)) {
            return columnValue->FullName();
        } else if (auto clauseValue = std::get_if<std::shared_ptr<Clause>>(&statement_value)) {
            return clauseValue->get()->Query();
        } else {
            std::string typeName = StatementValueType(statement_value.index());
            std::string error = "invalid statement_value " + typeName + "not supported";
            throw ::winter::exception::WinterInternalException::Create(
                __FILE__,
                __FUNCTION__,
                __LINE__,
                (error));
        }
    };

    std::string result = winter::util::string::replace_value(
        query_template_,
        query_param_l,
        getStatementValue(l_statement_value_));

    if (r_statement_value_.has_value() && r_statement_value_.value().index() != std::variant_npos) {
        result = winter::util::string::replace_value(
            result,
            query_param_r,
            getStatementValue(r_statement_value_.value()));
    }

    return winter::util::string::replace_value(
        result, query_param_condition, sql_impl::condition(condition_));
}
