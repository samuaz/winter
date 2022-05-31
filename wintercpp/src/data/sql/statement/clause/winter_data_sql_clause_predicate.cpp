//
// Created by Samuel Azcona on 21/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>
#include <wintercpp/util/winter_string_util.h>

using namespace winter::util::string;

winter::data::sql_impl::Predicate::Predicate(
    Column column,
    std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField> field,
    winter::data::sql_impl::Condition conditionOperator) :
    column_(std::move(column)),
    field_(std::move(field)),
    condition_(conditionOperator) {}

const winter::data::sql_impl::Column&
winter::data::sql_impl::Predicate::column()
    const {
  return column_;
}

const std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>&
winter::data::sql_impl::Predicate::field() const {
  return field_;
}

winter::data::sql_impl::Condition
winter::data::sql_impl::Predicate::condition()
    const {
  return condition_;
}