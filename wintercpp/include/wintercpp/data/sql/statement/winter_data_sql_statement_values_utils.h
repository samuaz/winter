//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_STATEMENT_VALUES_UTILS
#define WINTERCPP_WINTER_DATA_SQL_STATEMENT_VALUES_UTILS

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <cstddef>
#include <memory>
#include <string>
#include <variant>

namespace winter::data::sql_impl {

    inline std::string StatementValueType(size_t index) {
        switch (index) {
            case 0:
                return "Column";
            case 1:
                return "std::shared_ptr<Column>";
            case 2:
                return "Table";
            case 3:
                return "std::shared_ptr<Table>";
            case 4:
                return "std::shared_ptr<IStatement>";
            case 5:
                return "std::shared_ptr<Clause";
            default:
                return "UNKNOWN";
        }
    }

    inline std::string StatementValueType(const StatementValue& statementValue) {
        return StatementValueType(statementValue.index());
    }

    inline std::string GetStatementName(const StatementValue& statement_value) {
        if (auto sharedColumn = std::get_if<std::shared_ptr<Column>>(&statement_value)) {
            return sharedColumn->get()->FullName();
        } else if (auto column = std::get_if<Column>(&statement_value)) {
            return column->FullName();
        } else if (auto table = std::get_if<Table>(&statement_value)) {
            return table->name();
        } else if (auto sharedTable = std::get_if<std::shared_ptr<Table>>(&statement_value)) {
            return sharedTable->get()->name();
        } else if (auto clause = std::get_if<std::shared_ptr<Clause>>(&statement_value)) {
            auto alias = clause->get()->Alias();
            if (alias.has_value()) {
                return alias.value();
            }
            throw winter::exception::WinterInternalException::Create(
                __FILE__,
                __FUNCTION__,
                __LINE__,
                "clause alias not implemented");

            return clause->get()->Alias().value();
        }

        throw winter::exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            "invalid statementvalue or not implemented");
    };

    inline std::string GetStatementValue(const StatementValue& statement_value) {
        if (auto sharedColumn = std::get_if<std::shared_ptr<Column>>(&statement_value)) {
            return sharedColumn->get()->FullName();
        } else if (auto column = std::get_if<Column>(&statement_value)) {
            return column->FullName();
        } else if (auto table = std::get_if<Table>(&statement_value)) {
            return table->name();
        } else if (auto sharedTable = std::get_if<std::shared_ptr<Table>>(&statement_value)) {
            return sharedTable->get()->name();
        } else if (auto clause = std::get_if<std::shared_ptr<Clause>>(&statement_value)) {
            return clause->get()->Query();
        } else if (auto statement = std::get_if<std::shared_ptr<IStatement>>(&statement_value)) {
            return statement->get()->prepared_statement().statement_template();
        }
        throw winter::exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            "invalid statementvalue or not implemented");
    };

    inline std::string GetStatementValue(const std::optional<StatementValue>& opt_statement_value) {
        if (opt_statement_value.has_value()) {
            return GetStatementValue(opt_statement_value.value());
        }
        return "";
    };

}  // namespace winter::data::sql_impl
#endif
