//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H

#include <wintercpp/winter_mysql_core.h>

#include <mariadb/conncpp.hpp>
#include <memory>

namespace winter::data::mariadb::connection {
    typedef winter::data::sql_impl::mysql::ResultRow<::sql::ResultSet> ResultRow;
}  // namespace winter::data::mariadb::connection
#endif  // WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESULT_ROW_H
