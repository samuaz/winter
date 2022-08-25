//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/data/sql/mariadb/response/winter_data_sql_mariadb_impl_response.h>
#include <wintercpp/winter.h>
#include <wintercpp/winter_mysql_core.h>

namespace winter::data::mariadb {
    typedef winter::data::sql_impl::Transaction<winter::data::mariadb::connection::Connection, winter::data::mariadb::Response> Transaction;

}  // namespace winter::data::mariadb

#endif  // WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
