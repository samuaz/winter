//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTER_DATA_SQL_FUNCTION_MIN
#define WINTER_DATA_SQL_FUNCTION_MIN

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>

#include <queue>
#include <string>

#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h"

namespace winter::data::sql_impl {

    class Min : public virtual Clause {
       public:
        explicit Min(StatementValues column);

        PreparedStatement Prepare() override;

        std::string name() const override;

       private:
        const StatementValues                                 column_;
        const std::shared_ptr<AbstractPreparedStatementField> field_;
        const bool                                            is_predicate_ = false;
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_FUNCTION_MIN */
