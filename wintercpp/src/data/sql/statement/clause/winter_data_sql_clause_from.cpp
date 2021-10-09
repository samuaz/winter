//
// Created by Samuel Azcona on 24/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

using namespace winter::util::string;

winter::data::sql::From::From(std::set<std::shared_ptr<Table>, TableComparator> tables) : Clause("FROM $tables", "$tables"),
											  tables_(std::move(tables)) {}

winter::data::sql::From::From(const std::shared_ptr<Table> &table) : Clause("FROM $tables", "$tables") {
  tables_.insert(table);
}

winter::data::sql::PreparedStatement
winter::data::sql::From::Prepare() {
  GenerateStatement();
  return winter::data::sql::PreparedStatement(
      StatementType::kClause,
      statement_template(),
      columns_);
}

void winter::data::sql::From::GenerateStatement() {
  std::vector<std::string> tablesNames;
  for (auto const &table : tables_) {
    tablesNames.push_back(table->name());
    columns_.insert(table->columns().begin(), table->columns().end());
  }
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      param(),
      winter::data::sql::CommaSeparatedValue(tablesNames)));
}
