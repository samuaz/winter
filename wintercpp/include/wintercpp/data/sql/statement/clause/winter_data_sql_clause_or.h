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

namespace winter::data::sql_impl {

    class Or : public virtual Clause {
       public:
        explicit Or(const Predicate &predicate);

        explicit Or(Column column);

        explicit Or(Column column, Condition);
        std::string name() const override;

        PreparedStatement Prepare() override;

        template<typename T>
        static Predicate MakePredicate(const Column &column,
                                       Condition     condition,
                                       T             value) {
            return Predicate(column,
                             std::make_shared<PreparedStatementField<T> >(
                                 column->name(), value),
                             condition);
        }

        template<typename T>
        static Predicate MakePredicate(const Column      &column,
                                       Condition          condition,
                                       T                  value,
                                       const std::string &customValue) {
            return Predicate(column,
                             std::make_shared<PreparedStatementField<T> >(
                                 column->name(), value, customValue),
                             condition);
        }

       private:
        Column                                          column_;
        std::shared_ptr<AbstractPreparedStatementField> field_;
        Condition                                       condition_ {};
        bool                                            is_predicate_ = false;
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_OR */
