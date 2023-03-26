//
// Created by Samuel Azcona on 27/03/2020.
//

#include <wintercpp/data/sql/statement/winter_data_sql_select.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <vector>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause.h"

using namespace winter::data::sql_impl;

Select::Select(const std::string &query) :
    Statement<Select>(query, StatementType::kSelect) {}

Select::Select() :
    Statement<Select>("SELECT $columns", StatementType::kSelect) {}

Select::Select(std::vector<StatementValues> columns) :
    Statement("SELECT $columns", StatementType::kSelect),
    columns_(std::move(columns)) {}

void Select::writeColumns() {
    if (columns_.empty()) {
        winter::util::string::replace(statement_template_, "$columns", "*");
        return;
    }

    std::vector<std::string> columns;
    for (auto const &col : columns_) {
        if (auto columnVal = std::get_if<Column>(&col)) {
            columns.push_back(columnVal->TableName() + "." + columnVal->name());
        } else if (auto clauseVal = std::get_if<winter::data::sql_impl::IStatementValue>(&col)) {
            columns.push_back(clauseVal->query());
        }
    }
    winter::util::string::replace(
        statement_template_, "$columns", CommaSeparatedValue(columns));
    prepared_statement_->columns(columns_);
}

Select &Select::operator<<(std::vector<StatementValues> columns) {
    columns_ = std::move(columns);
    return *this;
}

void Select::BuildStatement() {
    writeColumns();
    prepared_statement_->set_statement_template(statement_template_);
}
