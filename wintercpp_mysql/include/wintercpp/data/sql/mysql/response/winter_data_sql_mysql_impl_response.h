//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESPONSE_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESPONSE_H

#include <mysql/jdbc.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_result_row.h>
#include <wintercpp/winter.h>
#include <wintercpp/winter_mysql_core.h>

namespace winter::data::mysql {
    typedef winter::data::sql_impl::Response<winter::data::mysql::connection::ResultRow> Response;

}  // namespace winter::data::mysql
#endif  // WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESPONSE_H
