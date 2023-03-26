//
// Created by Samuel Azcona on 17/06/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_ON
#define WINTER_DATA_SQL_CLAUSE_ON

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>

#include <queue>

namespace winter::data::sql_impl {

    class On : public virtual Clause {
       public:
        explicit On(const Column &l_column,
                    Condition     condition,
                    const Column &r_column);
        explicit On(const Column &l_column, Condition condition);
        PreparedStatement Prepare() override;
        std::string       name() const override;
    };
}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_ON */
