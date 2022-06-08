//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_H

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_result_row.h>
#include <wintercpp/data/sql/mariadb/response/winter_data_sql_mariadb_impl_response.h>
#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection_config.h>

#include <wintercpp/winter_mysql.h>

#include <mariadb/conncpp.hpp>

namespace winter::data::sql_impl::mysql::connection::mariadb_impl {

#define MARIADB_CONNECTION_IMPL winter::data::sql_impl::mysql::connection::Connection<::sql::Driver,                                                      \
											winter::data::sql_impl::mysql::connection::mariadb_impl::Config,    \
											int32_t,                                                            \
											::sql::Connection,                                                  \
											winter::data::sql_impl::mysql::mariadb_impl::Response,              \
											::sql::PreparedStatement,                                           \
											::sql::ResultSet,                                                   \
											winter::data::sql_impl::mysql::connection::mariadb_impl::ResultRow, \
											::sql::SQLException>

// template <typename TDriver, typename TConfig, typename TIsolationType, typename TSqlConnection, typename TResponse, typename TpreparedStatement, typename TResultSet, typename TResultRow, typename TSqlException>
class Connection : public virtual MARIADB_CONNECTION_IMPL {
 public:
};
}  // namespace winter::data::sql_impl::mysql::connection::mariadb_impl
#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_H
