//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_OR
#define WINTER_DATA_SQL_CLAUSE_OR

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>

#include <queue>
#include <utility>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

namespace winter::data::sql_impl {

    class Or : public virtual Clause {
       public:
        explicit Or(const Predicate &predicate);

        explicit Or(const StatementValue &statement_value);

        explicit Or(const StatementValue &statement_value, Condition);

        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

       private:
        const Predicate   predicate_;
        const std::string query_template_ = "OR $or";
        const std::string query_param_ = "$or";
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_OR */
