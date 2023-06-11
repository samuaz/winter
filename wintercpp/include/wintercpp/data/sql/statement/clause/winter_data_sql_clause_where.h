//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_WHERE2
#define WINTER_DATA_SQL_CLAUSE_WHERE2

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
        explicit Where(const Predicate &predicate);

        explicit Where(StatementValue statement_value);

        explicit Where(StatementValue statement_value, winter::data::sql_impl::Condition);

        std::string Query() const override;

        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

        template<typename T>
        static Predicate make_predicate(const Column &column,
                                        Condition     condition,
                                        T             value) {
            return Predicate(column,
                             std::make_shared<PreparedStatementField<T>>(
                                 column->name(), value),
                             condition);
        }

        template<typename T>
        static Predicate make_predicate(const Column      &column,
                                        Condition          condition,
                                        T                  value,
                                        const std::string &custom_value) {
            return Predicate(column,
                             std::make_shared<PreparedStatementField<T>>(
                                 column->name(), value, custom_value),
                             condition);
        }

       private:
        const StatementValue                                  statement_value_;
        const std::shared_ptr<AbstractPreparedStatementField> field_;
        const winter::data::sql_impl::Condition               condition_ {};
        const bool                                            _is_predicate = false;
        const std::string                                     query_template_ = "WHERE $where";
        const std::string                                     query_param_ = "$where";
    };
}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_WHERE2 */
