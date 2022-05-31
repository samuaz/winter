//
// Created by Samuel Azcona on 23/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>

winter::data::sql_impl::Clause::Clause(
    std::string statement_template,
    std::string param) :
    statement_template_(std::move(statement_template)),
    param_(std::move(param)) {}

const std::string &
winter::data::sql_impl::Clause::query() const {
  return query_;
}

winter::data::sql_impl::Clause &
winter::data::sql_impl::Clause::operator<<(
    const std::string &rvalue) {
  query_ += rvalue;
  return *this;
}

winter::data::sql_impl::Clause &
winter::data::sql_impl::Clause::BuildQuery() {
  return *this;
}

std::string
winter::data::sql_impl::Clause::param() {
  return param_;
}

std::string
winter::data::sql_impl::Clause::statement_template() {
  return statement_template_;
}

void winter::data::sql_impl::Clause::set_statement_template(
    const std::string &statement_template) {
  statement_template_ = statement_template;
}
