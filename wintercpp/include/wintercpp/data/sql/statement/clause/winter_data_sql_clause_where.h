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
#include <utility>

namespace winter::data::sql_impl {

    class Where : public virtual Clause {
       public:
        explicit Where(const Predicate &predicate);

        explicit Where(Column column);

        explicit Where(Column column, winter::data::sql_impl::Condition);

        PreparedStatement Prepare() override;

        template<typename T>
        static Predicate make_predicate(const Column &column,
                                        Condition     condition,
                                        T             value) {
            return Predicate(column,
                             std::make_shared<PreparedStatementField<T> >(
                                 column->name(), value),
                             condition);
        }

        template<typename T>
        static Predicate make_predicate(const Column      &column,
                                        Condition          condition,
                                        T                  value,
                                        const std::string &custom_value) {
            return Predicate(column,
                             std::make_shared<PreparedStatementField<T> >(
                                 column->name(), value, custom_value),
                             condition);
        }

       private:
        const Column column_;
        const std::shared_ptr<
            winter::data::sql_impl::AbstractPreparedStatementField>
                                                field_;
        const winter::data::sql_impl::Condition condition_ {};
        const bool                              _is_predicate = false;
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_WHERE */
