//
// Created by Samuel Azcona on 23/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_H

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>

#include <string>
#include <vector>

namespace winter::data::sql_impl {

    class Clause {
       public:
        virtual std::string                                                                          Query() const = 0;
        virtual std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> Fields() const = 0;
    };

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_CLAUSE_H