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
#include <wintercpp/data/sql/field/winter_data_sql_abstract_field.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_abstract_prepared_statement_field.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>

#include <optional>
#include <string>

#include "wintercpp/data/sql/statement/winter_data_sql_statement.h"

namespace winter::data::sql_impl {

    class Predicate {
       public:
        explicit Predicate(const StatementValue& statement_value);

        explicit Predicate(const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>& field);

        explicit Predicate(const std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>>& fields);

        Predicate(
            const StatementValue&                                                          statement_value,
            const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>& field);

        Predicate(
            const StatementValue&                                                          statement_value,
            Condition                                                                      conditionOperator,
            const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>& field);

        Predicate(
            const StatementValue& statement_value,
            Condition             conditionOperator);

        Predicate(
            const StatementValue& l_statement_value,
            Condition             conditionOperator,
            const StatementValue& r_statement_value);

        template<typename T>
        static Predicate Make(const Column& column,
                              T             value) {
            return Predicate(column, std::make_shared<PreparedStatementField<T>>(column->FullName(), value));
        }

        template<typename T>
        static Predicate Make(const Column& column,
                              Condition     condition,
                              T             value) {
            return Predicate(column, condition, std::make_shared<PreparedStatementField<T>>(column->FullName(), value));
        }

        template<typename T>
        static Predicate Make(const Column&      column,
                              Condition          condition,
                              T                  value,
                              const std::string& custom_value) {
            return Predicate(column,
                             condition,
                             std::make_shared<PreparedStatementField<T>>(column->FullName(), value, custom_value));
        }

        template<typename T>
        static Predicate Make(
            const Column& column, 
            T value, 
            const std::string& custom_value) {
            return Predicate(std::make_shared<PreparedStatementField<T>>(column->FullName(), value, custom_value));
        }

        template<typename T>
        static Predicate Make(const std::string& valueName,
                              T                  value) {
            return Predicate(std::make_shared<PreparedStatementField<T>>(valueName, value));
        }

        template<typename T>
        static Predicate Make(const StatementValue& statement_value,
                              Condition             condition,
                              T                     value) {
            return Predicate(statement_value,
                             condition,
                             std::make_shared<PreparedStatementField<T>>(value));
        }

        template<typename T>
        static Predicate Make(T value) {
            return Predicate(std::make_shared<PreparedStatementField<T>>(value));
        }

        template<typename T>
        static Predicate Make(const std::vector<T>& values) {
            std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> fields;
            fields.reserve(values.size());
            for (const auto& value : values) {
                fields.push_back(std::make_shared<PreparedStatementField<T>>(value));
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

        const std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>>& fields() const;

        const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>& field() const;

        Condition condition() const;

       private:
        std::string                                                                                statementStr(std::optional<StatementValue> statement_value) const;
        const std::optional<StatementValue>                                                        l_statement_value_;
        const winter::data::sql_impl::Condition                                                    condition_;
        const std::optional<StatementValue>                                                        r_statement_value_;
        const std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> fields_ {};
    };
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_PREDICATE_H
