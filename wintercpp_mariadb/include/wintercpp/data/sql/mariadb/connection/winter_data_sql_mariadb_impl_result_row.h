//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H

#include <wintercpp/winter_mysql_core.h>

#include <mariadb/conncpp.hpp>
#include <memory>

namespace winter::data::mariadb::connection {

    class ResultRow :
        public virtual winter::data::sql_impl::mysql::ResultRow<
            ::sql::ResultSet> {
       public:
        ResultRow(const data::sql_impl::PreparedStatement& preparedStatement,
                  const std::shared_ptr<sql::ResultSet>&   resultSet) :
            winter::data::sql_impl::mysql::ResultRow<::sql::ResultSet>(
                preparedStatement, resultSet) {}
    };
}  // namespace winter::data::mariadb::connection
#endif  // WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H
