//
// Created by Samuel Azcona on 23/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_IN_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_IN_H

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/winter_data_sql_select.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_type.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <deque>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace winter::data::sql_impl {

    template<typename T>
    class In : public virtual Clause {
       public:
        explicit In(std::vector<T> values);
        explicit In(const winter::data::sql_impl::Select &select);
        PreparedStatement Prepare() override;

       private:
        std::vector<T> values_;
        Select select_;
        bool has_clause_ = false;
    };

}  // namespace winter::data::sql_impl

#include "winter_data_sql_clause_in.tpp"

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_IN_H