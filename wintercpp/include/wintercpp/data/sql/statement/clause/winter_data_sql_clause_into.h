//
// Created by Samuel Azcona on 07/06/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_INTO_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_INTO_H

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

namespace winter::data::sql_impl {
    class Into : public virtual Clause {
       public:
        explicit Into(const Predicate& predicate);
        explicit Into(const StatementValue& predicate);
        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

       private:
        const Predicate   predicate_;
        const std::string query_template_ = "INTO $table";
        const std::string query_param_ = "$table";
    };
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_INTO_H
