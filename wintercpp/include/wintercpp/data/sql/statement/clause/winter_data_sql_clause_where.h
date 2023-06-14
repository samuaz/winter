//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_WHERE
#define WINTER_DATA_SQL_CLAUSE_WHERE

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>

#include <queue>
#include <string>
#include <utility>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

namespace winter::data::sql_impl {

    class Where : public virtual Clause {
       public:
        explicit Where(const Predicate& predicate);

        explicit Where(const StatementValue& statement_value);

        explicit Where(const StatementValue& statement_value, winter::data::sql_impl::Condition);

        std::string Query() const override;

        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

       private:
        const Predicate   predicate_;
        const bool        _is_predicate = false;
        const std::string query_template_ = "WHERE $where";
        const std::string query_param_ = "$where";
    };
}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_WHERE */
