//
// Created by Samuel Azcona on 17/06/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_ON
#define WINTER_DATA_SQL_CLAUSE_ON

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>

#include <optional>
#include <queue>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

namespace winter::data::sql_impl {

    class On : public virtual Clause {
       public:
        explicit On(const StatementValue &l_statement_value,
                    Condition             condition,
                    const StatementValue &r_statement_value);
        explicit On(const StatementValue &l_statement_value, Condition condition);
        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

       private:
        const StatementValue                l_statement_value_;
        const std::optional<StatementValue> r_statement_value_;
        const Condition                     condition_;
        const std::string                   query_template_ = "ON $lcolumn $condition $rcolumn";
        const std::string                   query_param_l = "$lcolumn";
        const std::string                   query_param_r = "$rcolumn";
        const std::string                   query_param_condition = "$condition";
    };
}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_ON */
