//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>
#include <wintercpp/util/winter_string_util.h>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::util::string;

winter::data::sql_impl::Predicate::Predicate(
    const winter::data::sql_impl::StatementValue&                                  statement_value,
    const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>& field,
    winter::data::sql_impl::Condition                                              conditionOperator) :
    statement_value_(statement_value),
    field_(field), condition_(conditionOperator) {}

const winter::data::sql_impl::StatementValue&
winter::data::sql_impl::Predicate::statementValue() const {
    return statement_value_;
}

const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>&
winter::data::sql_impl::Predicate::field() const {
    return field_;
}

winter::data::sql_impl::Condition winter::data::sql_impl::Predicate::condition()
    const {
    return condition_;
}