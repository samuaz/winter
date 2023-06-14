//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_AND
#define WINTER_DATA_SQL_CLAUSE_AND

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>

#include <queue>

namespace winter::data::sql_impl {

    class And : public virtual Clause {
       public:
        explicit And(const Predicate &predicate);

        std::string Query() const override;

        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

       private:
        const Predicate   predicate_;
        const std::string query_template_ = "AND $and";
        const std::string query_param_ = "$and";
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_AND */
