//
// Created by Samuel Azcona on 16/03/2020.
//

#include <wintercpp/data/sql/statement/winter_data_sql_insert.h>
#include <wintercpp/util/winter_string_util.h>
using namespace winter::data::sql_impl;

Insert::Insert(const std::string &query) :
    Statement<Insert>(query, StatementType::kInsert) {}

Insert::Insert() : Statement<Insert>("INSERT", StatementType::kInsert) {}

Insert::Insert(std::shared_ptr<Table> table) :
    Statement<Insert>("INSERT INTO $table", StatementType::kInsert),
    table_(std::move(table)) {}

void Insert::BuildStatement() {
    if (table_) {
        winter::util::string::replace(
            statement_template_, "$table", table_->name());
    }
    prepared_statement_->set_statement_template(statement_template_);
    // GenerateId();
}
