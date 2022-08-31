//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_CONNECTION_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_CONNECTION_H

#include <mysql/jdbc.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_connection_config.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_result_row.h>
#include <wintercpp/data/sql/mysql/response/winter_data_sql_mysql_impl_response.h>
#include <wintercpp/winter_mysql_core.h>

namespace winter::data::mysql::connection {

#define MYSQL_CONNECTION_IMPL                              \
    winter::data::sql_impl::mysql::connection::Connection< \
        ::sql::Driver,                                     \
        winter::data::mysql::connection::Config,           \
        ::sql::transaction_isolation,                      \
        ::sql::Connection,                                 \
        winter::data::mysql::Response,                     \
        ::sql::PreparedStatement,                          \
        ::sql::ResultSet,                                  \
        winter::data::mysql::connection::ResultRow,        \
        ::sql::SQLException>

    class Connection final : public virtual MYSQL_CONNECTION_IMPL {
        using MYSQL_CONNECTION_IMPL::Connection;

       private:
        ::sql::transaction_isolation IsolationLevel(
            const sql_impl::TransactionIsolationType &isolation) override;
    };
}  // namespace winter::data::mysql::connection
#endif  // WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_CONNECTION_H
