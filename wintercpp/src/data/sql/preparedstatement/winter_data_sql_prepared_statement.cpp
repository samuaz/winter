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
                                     std::string          statement_template,
                                     std::string          id) :
    id_(std::move(id)),
    type_(statement_type), statement_template_(std::move(statement_template)) {}

PreparedStatement::PreparedStatement(const StatementType &statement_type,
                                     std::string          statement_template,
                                     std::vector<Column>  columns,
                                     std::string          id) :
    id_(std::move(id)),
    type_(statement_type), statement_template_(std::move(statement_template)),
    columns_(std::move(columns)) {}

PreparedStatement::PreparedStatement(
    const StatementType                                         &statement_type,
    std::string                                                  query,
    std::vector<std::shared_ptr<AbstractPreparedStatementField> > values,
    std::string                                                  id) :
    id_(std::move(id)),
    type_(statement_type), statement_template_(std::move(query)),
    values_(std::move(values)) {}

PreparedStatement::PreparedStatement(
    const StatementType                                   &statement_type,
    std::string                                            statement_template,
    const std::shared_ptr<AbstractPreparedStatementField> &value,
    std::string                                            id) :
    id_(std::move(id)),
    type_(statement_type), statement_template_(std::move(statement_template)) {
    values_.push_back(value);
}

void PreparedStatement::set_id(const std::string &id) {
    id_ = id;
}

PreparedStatement &PreparedStatement::AddValue(
    AbstractPreparedStatementField *field) {
    values_.push_back(std::shared_ptr<AbstractPreparedStatementField>(field));
    return *this;
}

PreparedStatement &PreparedStatement::AddValue(
    const std::shared_ptr<AbstractPreparedStatementField> &field) {
    values_.push_back(field);
    return *this;
}

const std::string &PreparedStatement::statement_template() const {
    return statement_template_;
}

void PreparedStatement::set_statement_template(
    const std::string &statement_template) {
    statement_template_ = statement_template;
}

const std::vector<std::shared_ptr<AbstractPreparedStatementField> >
    &PreparedStatement::values() const {
    return values_;
}

void PreparedStatement::set_values(
    const std::vector<std::shared_ptr<AbstractPreparedStatementField> > &values) {
    values_ = values;
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

std::vector<std::shared_ptr<AbstractPreparedStatementField> >::iterator
PreparedStatement::FindValue(const std::string &name) {
    return std::find_if(
        values_.begin(),
        values_.end(),
        [&name](const std::shared_ptr<AbstractPreparedStatementField> &obj) {
            return obj->name() == name;
        });
}

const AbstractPreparedStatementField &PreparedStatement::FindByName(
    const std::string &name) {
    auto it = FindValue(name);
    if (it != values_.end()) { return **it; }

    throw WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("preparedstatement field not found " + name));
}

std::shared_ptr<AbstractPreparedStatementField> PreparedStatement::FindByField(
    const string &name) {
    auto it = FindValue(name);
    if (it != values_.end()) { return *it; }
    throw WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("preparedstatement field not found " + name));
}

bool PreparedStatement::FieldIsPresent(const std::string &name) {
    return FindValue(name) != values_.end();
}

int PreparedStatement::SearchFieldIndex(const std::string &name) {
    auto it = FindValue(name);

    if (it != values_.end()) {
        auto index = std::distance(values_.begin(), it);
        return index;
    }

    throw WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("preparedstatement field not found " + name));
}

const std::vector<Column> &PreparedStatement::columns() const {
    return columns_;
}

void PreparedStatement::columns(std::vector<Column> columns) {
    columns_ = std::move(columns);
}

PreparedStatement &PreparedStatement::AddColumn(const Column &column) {
    columns_.push_back(column);
    return *this;
}

PreparedStatement &PreparedStatement::AddColumn(
    const std::vector<Column> &columns) {
    for (const Column &col : columns) { columns_.push_back(col); }
    return *this;
}
