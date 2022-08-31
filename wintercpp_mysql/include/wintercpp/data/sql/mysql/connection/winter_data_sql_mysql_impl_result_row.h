//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESULT_ROW_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESULT_ROW_H

#include <mysql/jdbc.h>
#include <wintercpp/winter_mysql_core.h>

#include <memory>

namespace winter::data::mysql::connection {
    typedef winter::data::sql_impl::mysql::ResultRow<::sql::ResultSet> ResultRow;
}  // namespace winter::data::mysql::connection
#endif  // WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_RESULT_ROW_H
