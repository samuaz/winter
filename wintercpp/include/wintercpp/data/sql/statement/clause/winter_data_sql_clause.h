//
// Created by Samuel Azcona on 23/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_H

#include <memory>
#include <string>
#include <vector>

#include "wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement.h"

namespace winter::data::sql_impl {

    class Clause {
       public:
        virtual std::string                         Query() const = 0;
        virtual std::vector<PreparedStatementField> Fields() const = 0;

        std::string operator()(const Clause &clause) {
            return "(" + clause.Query() + ")";
        }

        std::string operator()(const std::shared_ptr<Clause> clause) {
            return "(" + clause->Query() + ")";
        }

        std::string operator()(const std::shared_ptr<IStatement> statement) {
            return "(" + statement->prepared_statement().statement_template() + ")";
        }
    };

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_H