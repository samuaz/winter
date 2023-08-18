//
// Created by Samuel Azcona on 14/03/2020.
//

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>

#include <algorithm>
#include <utility>
#include <vector>

using namespace winter::exception;
using namespace winter::data::sql_impl;

PreparedStatement::PreparedStatement(const StatementType &statement_type,
                                     const std::string   &statement_template,
                                     const std::string   &id) :
    id_(id),
    type_(statement_type), statement_template_(statement_template) {}

PreparedStatement::PreparedStatement(const StatementType               &statement_type,
                                     const std::string                 &statement_template,
                                     const std::vector<StatementValue> &columns,
                                     const std::string                 &id) :
    id_(id),
    type_(statement_type), statement_template_(statement_template),
    statement_values_(columns) {}

PreparedStatement::PreparedStatement(
    const StatementType                       &statement_type,
    const std::string                         &query,
    const std::vector<PreparedStatementField> &values,
    const std::string                         &id) :
    id_(id),
    type_(statement_type),
    statement_template_(query),
    fields_(values) {}

PreparedStatement::PreparedStatement(
    const StatementType          &statement_type,
    const std::string            &statement_template,
    const PreparedStatementField &value,
    const std::string            &id) :
    id_(id),
    type_(statement_type), statement_template_(statement_template) {
    fields_.push_back(value);
}

void PreparedStatement::set_id(const std::string &id) {
    id_ = id;
}

PreparedStatement &PreparedStatement::AddValue(const PreparedStatementField &field) {
    fields_.push_back(field);
    return *this;
}

const std::string &PreparedStatement::statement_template() const {
    return statement_template_;
}

void PreparedStatement::set_statement_template(
    const std::string &statement_template) {
    statement_template_ = statement_template;
}

const std::vector<PreparedStatementField>
    &PreparedStatement::values() const {
    return fields_;
}

void PreparedStatement::set_values(
    const std::vector<PreparedStatementField> &values) {
    fields_ = values;
}

const StatementType &PreparedStatement::type() const {
    return type_;
}

void PreparedStatement::set_type(const StatementType &statement_type) {
    type_ = statement_type;
}

const std::string &PreparedStatement::id() const {
    return id_;
}

bool PreparedStatement::operator==(const PreparedStatement &rhs) const {
    return id_ == rhs.id_;
}

bool PreparedStatement::operator!=(const PreparedStatement &rhs) const {
    return ! (rhs == *this);
}

/*

void PreparedStatement::entityId(AbstractPreparedStatementField *field) {
  if (fieldIsPresent(field->name())) {
    values_.erase(findValue(field->name()));
  }
  _entityId = std::shared_ptr<AbstractPreparedStatementField>(field);
  values_.push_front(_entityId);
}

void PreparedStatement::entityId(std::shared_ptr<AbstractPreparedStatementField>
field) { if (FieldIsPresent(field->name())) {
    values_.erase(FindValue(field->name()));
  }
  _entityId = field;
  values_.push_front(field);
}

const AbstractPreparedStatementField &Prepare::entityId() const {
  return *_entityId;
}
*/

std::vector<PreparedStatementField>::iterator
PreparedStatement::FindValue(const std::string &name) {
    return std::find_if(
        fields_.begin(),
        fields_.end(),
        [&name](const PreparedStatementField &obj) {
            return obj.name() == name;
        });
}

const PreparedStatementField &PreparedStatement::FindByName(
    const std::string &name) {
    auto it = FindValue(name);
    if (it != fields_.end()) { return *it; }

    throw WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("preparedstatement field not found " + name));
}

PreparedStatementField PreparedStatement::FindByField(
    const string &name) {
    auto it = FindValue(name);
    if (it != fields_.end()) { return *it; }
    throw WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("preparedstatement field not found " + name));
}

bool PreparedStatement::FieldIsPresent(const std::string &name) {
    return FindValue(name) != fields_.end();
}

int PreparedStatement::SearchFieldIndex(const std::string &name) {
    auto it = FindValue(name);

    if (it != fields_.end()) {
        auto index = std::distance(fields_.begin(), it);
        return index;
    }

    throw WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("preparedstatement field not found " + name));
}

const std::vector<StatementValue> &PreparedStatement::statementValues() const {
    return statement_values_;
}

void PreparedStatement::statementValues(std::vector<StatementValue> statement_values) {
    statement_values_ = std::move(statement_values);
}

PreparedStatement &PreparedStatement::AddStatementValue(const StatementValue &statement_value) {
    statement_values_.push_back(statement_value);
    return *this;
}

PreparedStatement &PreparedStatement::AddStatementValue(
    const std::vector<StatementValue> &statement_values) {
    for (const StatementValue &col : statement_values) { statement_values_.push_back(col); }
    return *this;
}
