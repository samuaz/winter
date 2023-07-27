//
// Created by Samuel Azcona on 23/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_NOT_IN_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_NOT_IN_H

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/winter_data_sql_select.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_type.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "wintercpp/data/sql/field/winter_data_sql_data_type.h"

namespace winter::data::sql_impl {

    class NotIn : public virtual Clause {
       public:
        explicit NotIn(const StatementValue& statement_value);
        explicit NotIn(const Predicate& predicate);
        std::string                                                                          Query() const override;
        std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const override;

        static NotIn Values(const std::vector<DataType>& values) {
            return NotIn(Predicate::Make(values));
        }

       private:
        const Predicate   predicate_;
        const std::string query_template_ = "NOT IN $NOT_IN_VALUE";
        const std::string query_param_ = "$NOT_IN_VALUE";
    };

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_NOT_IN_H