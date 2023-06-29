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

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

namespace winter::data::sql_impl {

    class Values : public virtual Clause {
       public:
        explicit Values(const std::vector<std::shared_ptr<AbstractPreparedStatementField>> &fields);

        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

        template<typename T>
        static std::shared_ptr<PreparedStatementField<T>> Add(
            const Column &column, T value) {
            return std::make_shared<PreparedStatementField<T>>(column->FullName(),
                                                               value);
        }

        template<typename T>
        static std::shared_ptr<PreparedStatementField<T>> Add(
            const Column &column, T value, const std::string &custom_value) {
            return std::make_shared<PreparedStatementField<T>>(
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
