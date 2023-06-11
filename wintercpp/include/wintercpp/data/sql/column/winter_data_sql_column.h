//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_COLUMN
#define WINTER_DATA_SQL_COLUMN

#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>

#include <any>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace winter::data::sql_impl {

    class Table;
    class Column;
    struct ColumnComparator;

    /**
     * Column class represents a column on a database sql table
     */
    class Column final {
       public:
        /**
         * @brief creates column object that represets a sql table column
         * @param Table table
         * @param String column_name
         * @param FieldType column_type
         */
        Column(Table &table, std::string column_name, FieldType column_type);

        /**
         * @brief creates column object that represets a sql table column from
         * reference
         * @param column
         */
        Column(const Column &column);

        /**
         * @brief creates column object that represets a sql table column from
         * pointer
         * @param Column
         */
        Column(const Column *column);

        /**
         * @brief equals override, this function determines if a column is
         * equals to other by check the table name and column name
         * @param Column
         * @return boolean
         */
        bool operator==(const Column &column) const;

        /**
         * @brief returns a reference to the table that contains this column
         * @return const Table
         */
        const Table &table() const;

        /**
         * @brief returns the name of the table that contains this column
         * @return std::string
         */
        const std::string &TableName() const;

        /**
         * @brief returns the name of the column
         * @return std::string
         */
        const std::string &name() const;

        /**
         * @brief returns the full name of the column example tableName.columnName
         * @return std::string
         */
        std::string FullName() const;

        /**
         * @brief returns the datatype this column represents
         * @return const FieldType
         */
        const FieldType &type() const;

        const Column *operator->() const {
            return this;
        }

        bool operator<(const Column &column) const;

       private:
        const Table      &table_;
        const std::string name_;
        const FieldType   type_;
    };

    /**
     * @brief Column comparator
     */
    struct ColumnComparator {
        bool operator()(const std::shared_ptr<Column> &lhs,
                        const std::shared_ptr<Column> &rhs) const;

        bool operator()(Column *lhs, Column *rhs) const;

        bool operator()(const Column &lhs, const Column &rhs) const;
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_COLUMN */
