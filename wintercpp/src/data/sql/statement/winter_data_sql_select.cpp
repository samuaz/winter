//
// Created by Samuel Azcona on 27/03/2020.
//

#include <wintercpp/data/sql/statement/winter_data_sql_select.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <vector>

using namespace winter::data::sql_impl;

Select::Select(const std::string &query) :
    Statement<Select>(query, StatementType::kSelect) {
}

Select::Select() :
    Statement<Select>("SELECT $columns", StatementType::kSelect) {}

Select::Select(const std::vector<StatementValue> &values) :
    Statement<Select>("SELECT $columns", StatementType::kSelect),
    value_(values) {}

void Select::writeColumns() {
    if (value_.empty()) {
        winter::util::string::replace(statement_template_, "$columns", "*");
        return;
    }

    std::vector<std::string> values;
    for (auto const &col : value_) {
        if (auto columnVal = std::get_if<Column>(&col)) {
            values.push_back(columnVal->FullName());
        } else if (auto clauseVal = std::get_if<std::shared_ptr<winter::data::sql_impl::Clause>>(&col)) {
            values.push_back(clauseVal->get()->Query());
        } else if (auto statementVal = std::get_if<std::shared_ptr<winter::data::sql_impl::IStatement>>(&col)) {
            values.push_back(statementVal->get()->prepared_statement().statement_template());
        }
    }
    winter::util::string::replace(
        statement_template_, "$columns", CommaSeparatedValue(values));
    prepared_statement_.statementValues(value_);
}

Select &Select::operator<<(std::vector<StatementValue> columns) {
    value_ = std::move(columns);
    return *this;
}

void Select::BuildStatement() {
    writeColumns();
    prepared_statement_.set_statement_template(statement_template_);
}
