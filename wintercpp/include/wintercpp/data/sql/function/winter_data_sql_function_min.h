//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTER_DATA_SQL_FUNCTION_MIN
#define WINTER_DATA_SQL_FUNCTION_MIN

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>

#include <queue>
#include <string>

namespace winter::data::sql_impl {

    class Min : public virtual Clause {
       public:
        explicit Min(const StatementValue &statement_value);
        virtual ~Min() = default;

        std::string                         Query() const override;
        std::vector<PreparedStatementField> Fields() const override;

        // PreparedStatement Prepare() override;

        std::string name() const;

        // FieldType fieldType() override;

       private:
        const StatementValue statement_value_;
        // const PreparedStatementField field_;
        const std::string query_template_ = "MIN($min) AS min_$columnName";
        const std::string query_param_ = "$min";
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_FUNCTION_MIN */
