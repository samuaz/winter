//
// Created by Samuel Azcona on 23/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_IN_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_IN_H

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_type.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

namespace winter::data::sql_impl {

    class In : public virtual Clause {
       public:
        explicit In(const StatementValue& statement_value);
        explicit In(const Predicate& predicate);
        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

        template<typename T>
        static In Values(const std::vector<T>& values_) {
            return In(Predicate::MakePredicate(values_));
        }

       private:
        const Predicate   predicate_;
        const std::string query_template_ = "IN $IN_VALUE";
        const std::string query_param_ = "$IN_VALUE";
    };

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_IN_H