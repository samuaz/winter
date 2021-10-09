//
// Created by Samuel Azcona on 26/05/2020.
//

#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>

std::string
winter::data::sql::CommaSeparatedValue(
    const std::vector<std::string> &elements) {
  std::string statement{};
  auto elementsSize = elements.size();
  for (size_t i = 0; i < elementsSize; i++) {
    auto e = elements[i];
    statement += e += std::string((i == elementsSize - 1 ? Nothing() : Comma()));
  }
  return statement;
}

std::string
winter::data::sql::CommaSeparatedEqualValue(
    const std::vector<std::string> &elements) {
  std::string statement{};
  auto elementsSize = elements.size();
  for (size_t i = 0; i < elementsSize; i++) {
    auto e = elements[i];
    statement += e += Equal() += PlaceHolder() += std::string((i == elementsSize - 1 ? Nothing() : Comma()));
  }
  return statement;
}

std::string
winter::data::sql::CommaSeparatedEqualValue(
    const winter::data::sql::PreparedStatement &prepared_statement) {
  return commaSeparatedEqualValue(prepared_statement.values());
}

std::string
winter::data::sql::commaSeparatedEqualValue(
    const std::deque<std::shared_ptr<AbstractPreparedStatementField> >
	&columns) {
  std::string values{};
  unsigned long size = columns.size();
  for (unsigned long i = 0; i < size; i++) {
    auto row = columns[i];
    if (row->IsCustomValue()) {
      values += row->name() + Equal() += row->custom_value() + std::string(i == size - 1 ? Nothing() : Comma());
    } else {
      values += row->name() + Equal() += PlaceHolder() += std::string(i == size - 1 ? Nothing() : Comma());
    }
  }
  return values;
}

std::string
winter::data::sql::CommaSeparatedStatement(
    const std::deque<std::shared_ptr<AbstractPreparedStatementField> >
	&columns) {
  std::string values{};
  unsigned long size = columns.size();
  for (unsigned long i = 0; i < size; i++) {
    auto row = columns[i];
    if (row->IsCustomValue()) {
      values += Space() += row->custom_value() + std::string(i == size - 1 ? Nothing() : Comma());
    } else {
      values += PlaceHolder() += std::string(i == size - 1 ? Nothing() : Comma());
    }
  }
  return values;
}

std::string
winter::data::sql::CommaSeparatedStatement(
    const winter::data::sql::PreparedStatement &prepared_statement) {
  std::string values{};
  auto columns = prepared_statement.values();
  unsigned long size = columns.size();
  for (unsigned long i = 0; i < size; i++) {
    auto row = columns[i];
    if (row->IsCustomValue()) {
      values += Space() += row->custom_value() + std::string(i == size - 1 ? Nothing() : Comma());
    } else {
      values += PlaceHolder() += std::string(i == size - 1 ? Nothing() : Comma());
    }
  }
  return values;
}

std::string
winter::data::sql::CommaSeparatedPlaceHolder(size_t size) {
  std::string values{};
  for (size_t i = 0; i < size; i++) {
    values += PlaceHolder() += std::string(i == size - 1 ? Nothing() : Comma());
  }
  return values;
}

std::string
winter::data::sql::Dot() {
  return ".";
}

std::string
winter::data::sql::Space() {
  return " ";
}

std::string
winter::data::sql::Comma() {
  return ",";
}

std::string
winter::data::sql::PlaceHolder() {
  return "?";
}

std::string
winter::data::sql::Equal() {
  return "=";
}

std::string
winter::data::sql::Nothing() {
  return {};
}
