//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_TRANSACTION_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_TRANSACTION_H

#include <wintercpp/winter.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_connection.h>
#include <wintercpp/winter_mysql_core.h>

namespace winter::data::mysql {
    typedef winter::data::sql_impl::Transaction<winter::data::mysql::connection::Connection, winter::data::mysql::Response> Transaction;
}  // namespace winter::data::mysql

#endif  // WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_TRANSACTION_H