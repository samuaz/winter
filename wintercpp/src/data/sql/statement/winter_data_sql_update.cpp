//
// Created by Samuel Azcona on 13/04/2020.
//

#include <wintercpp/data/sql/statement/winter_data_sql_update.h>

using namespace winter::data::sql_impl;

Update::Update(const std::string &query) :
    Statement<Update>(query, StatementType::kUpdate) {}

Update::Update(std::shared_ptr<Table> table) :
    Statement<Update>("UPDATE $table", StatementType::kUpdate),
    table_(std::move(table)) {}

void Update::BuildStatement() {
  if (table_) {
    winter::util::string::replace(statement_template_, "$table", table_->name());
  }
  prepared_statement_->set_statement_template(statement_template_);
}
