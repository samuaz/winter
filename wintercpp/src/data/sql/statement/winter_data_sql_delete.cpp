//
// Created by Samuel Azcona on 27/03/2020.
//

#include <wintercpp/data/sql/statement/winter_data_sql_delete.h>
#include <wintercpp/util/winter_string_util.h>

using namespace winter::data::sql;

Delete::Delete() :
    Statement<Delete>("Delete $columns", StatementType::kDelete) {
  winter::util::string::replace(statement_template_, "$columns", "");
}

void Delete::BuildStatement() {
  prepared_statement_->set_statement_template(statement_template_);
}
