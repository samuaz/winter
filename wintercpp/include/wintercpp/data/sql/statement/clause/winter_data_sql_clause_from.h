//
// Created by Samuel Azcona on 24/05/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_FROM
#define WINTER_DATA_SQL_CLAUSE_FROM

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <memory>
#include <vector>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

namespace winter::data::sql_impl {

    class From : public virtual Clause {
       public:
        explicit From(const std::vector<StatementValue>& tables);
        explicit From(const StatementValue& statement_value);
        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

       private:
        std::vector<StatementValue> statement_values_;
        const std::string           query_template_ = "FROM $tables";
        const std::string           query_param_ = "$tables";
    };

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CLAUSE_FROM */
