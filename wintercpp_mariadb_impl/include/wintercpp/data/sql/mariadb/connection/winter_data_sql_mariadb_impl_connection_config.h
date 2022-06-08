//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_CONFIG_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_CONFIG_H
#include <wintercpp/winter_mysql.h>

#include <mariadb/conncpp.hpp>

namespace winter::data::sql_impl::mysql::connection::mariadb_impl {

#define MARIADB_RESULT_CONFIG_IMPL = winter::data::sql_impl::mysql::connection::mariadb_impl::Config<::sql::Driver>

class Config : public virtual MARIADB_RESULT_CONFIG_IMPL {
 public:
  Config(const string& host, int port, const string& userName, const string& password, const string& schema, bool optReconnect, int optConnectTimeout, const ConnectionProperties& otherProperties) :
      MARIADB_RESULT_CONFIG_IMPL(::sql::mariadb::get_driver_instance(), host, port, userName, password, schema, optReconnect, optConnectTimeout, otherProperties) {}
};
}  // namespace winter::data::sql_impl::mysql::connection::mariadb_impl
#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_CONFIG_H
