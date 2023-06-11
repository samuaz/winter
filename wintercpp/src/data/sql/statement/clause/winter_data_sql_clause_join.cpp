//
// Created by Samuel Azcona on 16/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_join.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>
#include <variant>

winter::data::sql_impl::Join::Join(const StatementValue& statement_value,
                                   JoinType              type) :
    statement_value_(statement_value),
    type_(type) {
}

winter::data::sql_impl::Join::Join(const StatementValue& statement_value) :
    statement_value_(statement_value),
    type_(JoinType::DEFAULT) {
}

std::string
winter::data::sql_impl::Join::Query() const {
    std::string query = winter::util::string::replace_value(query_template_, "$type", GenerateType());

    auto subQuery = [&]() -> std::string {
        if (auto sharedTable = std::get_if<std::shared_ptr<Table>>(&statement_value_)) {
            return sharedTable->get()->name();
        } else if (auto table = std::get_if<Table>(&statement_value_)) {
            return table->name();
        } else if (auto clause = std::get_if<std::shared_ptr<Clause>>(&statement_value_)) {
            return clause->get()->Query();
        }

        std::string typeName = StatementValueType(statement_value_.index());
        std::string error = "invalid statement_value " + typeName + "not supported";
        throw ::winter::exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            (error));
    };

    return winter::util::string::replace_value(
        query,
        query_param_,
        winter::data::sql_impl::CommaSeparatedValue({subQuery()}));
}

std::string winter::data::sql_impl::Join::GenerateType() const {
    switch (type_) {
        case JoinType::INNER: return "INNER";
        case JoinType::LEFT: return "LEFT";
        case JoinType::RIGHT: return "RIGHT";
        case JoinType::CROSS: return "CROSS";
        case JoinType::DEFAULT: return "INNER";
    }
    return std::string();
}
