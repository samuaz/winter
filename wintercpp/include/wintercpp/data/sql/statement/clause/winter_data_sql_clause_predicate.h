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
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>

namespace winter::data::sql_impl {

    class Predicate {
       public:
        Predicate(
            Column column,
            std::shared_ptr<
                winter::data::sql_impl::AbstractPreparedStatementField> field,
            Condition conditionOperator);

        const Column& column() const;

        const std::shared_ptr<
            winter::data::sql_impl::AbstractPreparedStatementField>&
        field() const;

        Condition condition() const;

       private:
        Column column_;
        std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>
            field_;
        winter::data::sql_impl::Condition condition_ {};
    };
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_PREDICATE_H
