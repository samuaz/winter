//
// Created by Samuel Azcona on 14/03/2020.
//

#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <optional>
#include <vector>

#include "wintercpp/data/sql/column/winter_data_sql_column.h"
#include "wintercpp/exception/generic/winter_internal_exception.h"

using namespace winter::data::sql_impl;

Table::Table(std::string  name,
             TableType    table_type,
             DatabaseType database_type) :
    name_(std::move(name)),
    type_(table_type), database_type_(database_type) {}

Table::Table(std::string name, DatabaseType database_type) :
    name_(std::move(name)), type_(TableType::kTable),
    database_type_(database_type) {}

const std::string &Table::name() const {
    return name_;
}

const std::vector<Column> &Table::columns() const {
    return columns_;
}

const Column &Table::RegisterColumn(const Column &col) {
    // check if the columns corresponds to the current table
    if (col.TableName() != this->name()) {
        throw exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            ("column " + col.name() + " from table " + col.TableName()
             + " Cannot register in a different table " + this->name()));
    }

    /**
     **  Todo:
     ** For now as we are not registering the column when is created, let's
     *throw an exception if you try to register a column that already exists
     ** If I move to register the column at creation time, this function should
     *return the existing one if you try to register a column that already exist
     *instead of throw
     **/
    // throw if the column already exists
    if (std::find(columns_.begin(), columns_.end(), col) != columns_.end()) {
        throw exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            ("column " + col.name() + " from table " + col.TableName()
             + " already exists"));
        // return columns_.at(std::distance(columns_.begin(),
        // std::find(columns_.begin(), columns_.end(), col)));
    }

    // add the new column
    columns_.push_back(col);

    // Find the recent column to return
    // Easily this can be equals to current size... but I feel more safe
    // searching by the column == operator
    return columns_.at(std::distance(
        columns_.begin(), std::find(columns_.begin(), columns_.end(), col)));
}

const Column &Table::RegisterColumn(const std::string &name,
                                    FieldType          fieldType) {
    return RegisterColumn(Column(*this, name, fieldType));
}

std::optional<const Column *> Table::FindColumnByName(
    const std::string &column_name) const {
    auto existing = std::find_if(columns_.begin(),
                                 columns_.end(),
                                 [&column_name](const Column &column) -> bool {
                                     return column.name() == column_name;
                                 });

    if (existing != columns_.end()) {
        return std::optional(
            &columns_.at(std::distance(columns_.begin(), existing)));
    }

    return nullopt;
};

const Column &Table::Char(const std::string &name) {
    return RegisterColumn(name, FieldType::kChar);
}

const Column &Table::SignedChar(const std::string &name) {
    return RegisterColumn(name, FieldType::kSchar);
}

const Column &Table::UnsignedChar(const std::string &name) {
    return RegisterColumn(name, FieldType::kUchar);
}

const Column &Table::String(const std::string &name) {
    return RegisterColumn(name, FieldType::kString);
}

const Column &Table::Short(const std::string &name) {
    return RegisterColumn(name, FieldType::KShort);
}

const Column &Table::UShort(const std::string &name) {
    return RegisterColumn(name, FieldType::kUshort);
}

const Column &Table::Int(const std::string &name) {
    return RegisterColumn(name, FieldType::kInt);
}

const Column &Table::UInt(const std::string &name) {
    return RegisterColumn(name, FieldType::KUint);
}

const Column &Table::BigInt(const std::string &name) {
    return RegisterColumn(name, FieldType::kBigInt);
}

const Column &Table::Long(const std::string &name) {
    return RegisterColumn(name, FieldType::kLong);
}

const Column &Table::ULong(const std::string &name) {
    return RegisterColumn(name, FieldType::kUlong);
}

const Column &Table::Decimal(const std::string &name) {
    return RegisterColumn(name, FieldType::KDecimal);
}

const Column &Table::Float(const std::string &name) {
    return RegisterColumn(name, FieldType::kFloat);
}

const Column &Table::Double(const std::string &name) {
    return RegisterColumn(name, FieldType::kDouble);
}

const Column &Table::Boolean(const std::string &name) {
    return RegisterColumn(name, FieldType::kBoolean);
}

const Column &Table::Date(const std::string &name) {
    return RegisterColumn(name, FieldType::kDate);
}

const Column &Table::DateTime(const std::string &name) {
    return RegisterColumn(name, FieldType::kDateTime);
}

const Column &Table::TimeStamp(const std::string &name) {
    return RegisterColumn(name, FieldType::kTimeStamp);
}

const Column &Table::Enum(const std::string &name) {
    return RegisterColumn(name, FieldType::kEnum);
}

const Column &Table::Blob(const std::string &name) {
    return RegisterColumn(name, FieldType::kBlob);
}

bool Table::operator< (const Table& table) const {
    std::stringstream left, right;
    left << this->name();
    right << table.name();
    return left.str() < right.str();
}


Table::~Table() {}

TableType Table::tableType() const {
    return type_;
}

bool Table::operator==(const Table &table) const {
    return this->name() == table.name();
}

bool TableComparator::operator()(const std::shared_ptr<Table> &lhs,
                                 const std::shared_ptr<Table> &rhs) const {
    std::stringstream s1, s2;
    s1 << lhs->name();
    s2 << rhs->name();
    return s1.str() < s2.str();
}

bool TableComparator::operator()(Table *lhs, Table *rhs) const {
    std::stringstream s1, s2;
    s1 << lhs->name();
    s2 << rhs->name();
    return s1.str() < s2.str();
}

bool TableComparator::operator()(const Table &lhs, const Table &rhs) const {
    std::stringstream s1, s2;
    s1 << lhs.name();
    s2 << rhs.name();
    return s1.str() < s2.str();
}
