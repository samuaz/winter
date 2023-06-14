//
// Created by Samuel Azcona on 16/06/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_JOIN_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_JOIN_H

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

namespace winter::data::sql_impl {

    enum class JoinType : int { DEFAULT = 0,
                                INNER,
                                LEFT,
                                RIGHT,
                                CROSS,
                                FULL_JOIN
    };

    class Join : public virtual Clause {
       public:
        explicit Join(const StatementValue&, JoinType type);
        explicit Join(const StatementValue& statement_value);
        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

       private:
        const Predicate   predicate_;
        const JoinType    type_;
        std::string       GenerateType() const;
        const std::string query_template_ = "$type JOIN $table";
        const std::string query_param_ = "$table";
    };

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_JOIN_H
