//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESPONSE_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESPONSE_H

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_result_row.h>
#include <wintercpp/winter_mysql_core.h>
#include <wintercpp/winter.h>
#include <mariadb/conncpp.hpp>

namespace winter::data::mariadb {
    typedef winter::data::sql_impl::Response<winter::data::mariadb::connection::ResultRow> Response;
}  // namespace winter::data::mariadb
#endif  // WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_RESPONSE_H
