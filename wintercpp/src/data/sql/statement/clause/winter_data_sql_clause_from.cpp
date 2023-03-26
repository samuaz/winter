//
// Created by Samuel Azcona on 24/05/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

using namespace winter::util::string;

winter::data::sql_impl::From::From(std::vector<std::shared_ptr<Table>> tables) :
    Clause("FROM $tables", "$tables"), tables_(std::move(tables)) {
        Prepare();
    }

winter::data::sql_impl::From::From(const std::shared_ptr<Table> &table) :
    Clause("FROM $tables", "$tables") {
    tables_.push_back(table);
}

    std::string winter::data::sql_impl::From::From::name() const {
            return "From";
    };

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::From::Prepare() {
    GenerateStatement();
    return winter::data::sql_impl::PreparedStatement(
        StatementType::kClause, statement_template(), columns_);
}

void winter::data::sql_impl::From::GenerateStatement() {
    std::vector<std::string> tablesNames;
    for (auto const &table : tables_) {
        tablesNames.push_back(table->name());
        auto tableColumns = table->columns();
        for (const Column &col : tableColumns) { columns_.push_back(col); }
    }
    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        param(),
        winter::data::sql_impl::CommaSeparatedValue(tablesNames)));
}
