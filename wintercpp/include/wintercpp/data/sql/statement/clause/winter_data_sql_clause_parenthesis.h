//
// Created by Samuel Azcona on 18/06/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_PARENTHESIS_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_PARENTHESIS_H

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/util/winter_string_util.h>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

namespace winter::data::sql_impl {

    class Parenthesis : public virtual Clause {
       public:
        explicit Parenthesis(const StatementValue &clause);
        std::string                         Query() const override;
        std::vector<PreparedStatementField> Fields() const override;

       private:
        const Predicate   predicate_;
        const std::string query_template_ = "$clause";
        const std::string query_param_ = "$clause";
    };

    template<typename T>
    Parenthesis withParenthesis(T clause) {
        return Parenthesis(clause.Prepare().set_statement_template());
    }
}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_PARENTHESIS_H
