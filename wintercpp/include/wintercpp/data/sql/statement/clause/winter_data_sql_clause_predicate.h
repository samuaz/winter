/*******************************************************************************
 * Copyright (c) 2021. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 * Morbi non lorem porttitor neque feugiat blandit. Ut vitae ipsum eget quam
 *lacinia accumsan. Etiam sed turpis ac ipsum condimentum fringilla. Maecenas
 *magna. Proin dapibus sapien vel ante. Aliquam erat volutpat. Pellentesque
 *sagittis ligula eget metus. Vestibulum commodo. Ut rhoncus gravida arcu.
 ******************************************************************************/

//
// Created by samua_6h1tg27 on 6/28/2021.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_PREDICATE_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_PREDICATE_H

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>

#include <optional>
#include <string>

#include "wintercpp/data/sql/field/winter_data_sql_data_type.h"

namespace winter::data::sql_impl {

    class Predicate {
       public:
        explicit Predicate(const StatementValue& statement_value);

        explicit Predicate(const PreparedStatementField& field);

        explicit Predicate(const std::vector<PreparedStatementField>& fields);

        Predicate(
            const StatementValue&         statement_value,
            const PreparedStatementField& field);

        Predicate(
            const StatementValue&         statement_value,
            Condition                     conditionOperator,
            const PreparedStatementField& field);

        Predicate(
            const StatementValue& statement_value,
            Condition             conditionOperator);

        Predicate(
            const StatementValue& l_statement_value,
            Condition             conditionOperator,
            const StatementValue& r_statement_value);

        static Predicate Make(const Column&   column,
                              const DataType& value) {
            return Predicate(column, PreparedStatementField(column->FullName(), value));
        }

        static Predicate Make(const Column&   column,
                              Condition       condition,
                              const DataType& value) {
            return Predicate(column, condition, PreparedStatementField(column->FullName(), value));
        }

        static Predicate Make(const Column&      column,
                              Condition          condition,
                              const DataType&    value,
                              const std::string& custom_value) {
            return Predicate(column,
                             condition,
                             PreparedStatementField(column->FullName(), value, custom_value));
        }

        static Predicate Make(
            const Column&      column,
            const DataType     value,
            const std::string& custom_value) {
            return Predicate(PreparedStatementField(column->FullName(), value, custom_value));
        }

        static Predicate Make(const std::string& valueName,
                              const DataType&    value) {
            return Predicate(PreparedStatementField(valueName, value));
        }

        static Predicate Make(const StatementValue& statement_value,
                              Condition             condition,
                              const DataType&       value) {
            return Predicate(statement_value,
                             condition,
                             PreparedStatementField(value));
        }

        static Predicate Make(const DataType& value) {
            return Predicate(PreparedStatementField(value));
        }

        static Predicate Make(const std::vector<DataType>& values) {
            std::vector<PreparedStatementField> fields;
            fields.reserve(values.size());
            for (const auto& value : values) {
                fields.push_back(PreparedStatementField(value));
            }
            return Predicate(fields);
        }

        static Predicate Make(const StatementValue& statement_value,
                              Condition             condition) {
            return Predicate(statement_value,
                             condition);
        }

        static Predicate Make(const StatementValue& rstatement_value,
                              Condition             condition,
                              const StatementValue& lstatement_value) {
            return Predicate(rstatement_value,
                             condition,
                             lstatement_value);
        }

        const std::optional<StatementValue>& lstatementValue() const;

        const std::optional<StatementValue>& rstatementValue() const;

        std::string lstatementStr() const;

        std::string rstatementStr() const;

        std::string conditionStr() const;

        bool has_lstatement() const;

        bool has_rstatement() const;

        bool has_condition() const;

        bool has_fields() const;

        const std::vector<PreparedStatementField>& fields() const;

        const PreparedStatementField& field() const;

        Condition condition() const;

       private:
        std::string                               statementStr(std::optional<StatementValue> statement_value) const;
        const std::optional<StatementValue>       l_statement_value_;
        const winter::data::sql_impl::Condition   condition_;
        const std::optional<StatementValue>       r_statement_value_;
        const std::vector<PreparedStatementField> fields_ {};
    };
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_PREDICATE_H
