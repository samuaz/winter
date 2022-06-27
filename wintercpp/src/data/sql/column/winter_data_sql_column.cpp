//
// Created by Samuel Azcona on 14/03/2020.
//

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <utility>

using namespace winter::data::sql_impl;

Column::Column(Table &table, std::string column_name, FieldType column_type) :
    table_(std::move(table)), name_(std::move(column_name)),
    type_(column_type) {
    /**
     **  Todo:
     **  I need to analyze if is good idea to register the column at the time
     *you create it.
     **  The use case is that you have a column that is handled by the database,
     *and you don't want to expose inside winter because is going to be
     *available.
     **  But maybe for some reason you need to make it visible for specific
     *function/query, if you register the column it would be available for all
     *places and keep in memory affecting all the queries.
     **  So, if I don't register it automatically, it is all to you if you want
     *to register it globally or just use it in that function scope.
     **  For now lets say that register the column need manual call to the
     *table.RegisterColumn function.
     **/
    // table.RegisterColumn(*this);
}

Column::Column(const Column &column) :
    table_(column.table_), name_(column.name_), type_(column.type_) {};

Column::Column(const Column *column) :
    table_(column->table_), name_(column->name_), type_(column->type_) {};

const std::string &Column::name() const {
    return name_;
}

const FieldType &Column::type() const {
    return type_;
}

const Table &Column::table() const {
    return table_;
}

const std::string &Column::TableName() const {
    return table_.name();
}

bool Column::operator==(const Column &column) const {
    return this->TableName() == column.TableName()
           && this->name_ == column.name_;
}

bool ColumnComparator::operator()(const std::shared_ptr<Column> &lhs,
                                  const std::shared_ptr<Column> &rhs) const {
    std::stringstream s1, s2;
    s1 << lhs->TableName() << lhs->name();
    s2 << rhs->TableName() << rhs->name();
    return s1.str() < s2.str();
}

bool ColumnComparator::operator()(Column *lhs, Column *rhs) const {
    std::stringstream s1, s2;
    s1 << lhs->TableName() << lhs->name();
    s2 << rhs->TableName() << rhs->name();
    return s1.str() < s2.str();
}

bool ColumnComparator::operator()(const Column &lhs, const Column &rhs) const {
    std::stringstream s1, s2;
    s1 << lhs.TableName() << lhs.name();
    s2 << rhs.TableName() << rhs.name();
    return s1.str() < s2.str();
}