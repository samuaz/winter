//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_STATEMENT_VALUES
#define WINTERCPP_WINTER_DATA_SQL_STATEMENT_VALUES

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <memory>
#include <string>
#include <variant>

namespace winter::data::sql_impl {

    class IStatement;
    class Clause;
    class Column;
    class Table;

    typedef std::variant<Column, std::shared_ptr<Column>, Table, std::shared_ptr<Table>, std::shared_ptr<IStatement>, std::shared_ptr<Clause>> StatementValue;

    inline bool IsColumn(const StatementValue& statement_value) {
        return std::holds_alternative<std::shared_ptr<Column>>(statement_value) || std::holds_alternative<Column>(statement_value);
    }

    inline bool IsTable(const StatementValue& statement_value) {
        return std::holds_alternative<std::shared_ptr<Table>>(statement_value) || std::holds_alternative<Table>(statement_value);
    }

    inline bool IsStatement(const StatementValue& statement_value) {
        return std::holds_alternative<std::shared_ptr<IStatement>>(statement_value);
    }

    inline bool IsClause(const StatementValue& statement_value) {
        return std::holds_alternative<std::shared_ptr<Clause>>(statement_value);
    }

    inline bool IsClause(const std::optional<StatementValue>& statement_value) {
        if (statement_value.has_value()) {
            return std::holds_alternative<std::shared_ptr<Clause>>(statement_value.value());
        }
        return false;
    }

}  // namespace winter::data::sql_impl
#endif