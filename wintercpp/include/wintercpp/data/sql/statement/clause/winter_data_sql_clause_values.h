//
// Created by Samuel Azcona on 07/06/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_VALUES
#define WINTER_DATA_SQL_CLAUSE_VALUES

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>

#include <utility>
#include <vector>

#include "wintercpp/data/sql/field/winter_data_sql_data_type.h"
#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

namespace winter::data::sql_impl {

    class Values : public virtual Clause {
       public:
        explicit Values(const std::vector<PreparedStatementField> &fields);

        std::string                         Query() const override;
        std::vector<PreparedStatementField> Fields() const override;

        static PreparedStatementField Add(
            const Column &column, const DataType &value) {
            return PreparedStatementField(column->FullName(),
                                          value);
        }

        static PreparedStatementField Add(
            const Column &column, const DataType &value, const std::string &custom_value) {
            return PreparedStatementField(
                column->FullName(), value, custom_value);
        }

       private:
        const Predicate   predicate_;
        const std::string query_template_ = "($columns) VALUES ($values)";
        const std::string query_param_columns_ = "$columns";
        const std::string query_param_values_ = "$values";
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_VALUES */
