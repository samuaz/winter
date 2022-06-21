//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_CONFIG_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_CONFIG_H
#include <wintercpp/winter_mysql.h>

#include <mariadb/conncpp.hpp>

namespace winter::data::mariadb::connection {

#define MARIADB_RESULT_CONFIG_IMPL = winter::data::mariadb::connection::Config<::sql::Driver>

class Config : public virtual winter::data::sql_impl::mysql::connection::Config<::sql::Driver*> {
 public:
  Config(
      const string& host,
      int port,
      const string& userName,
      const string& password,
      const string& schema,
      bool optReconnect,
      int optConnectTimeout,
      const ConnectionProperties& otherProperties) :
      winter::data::sql_impl::mysql::connection::Config<::sql::Driver*>(
	  []() -> ::sql::Driver* {
	    return ::sql::mariadb::get_driver_instance();
	  },
	  host,
	  port,
	  userName,
	  password,
	  schema,
	  optReconnect,
	  optConnectTimeout,
	  otherProperties) {}
};
}  // namespace winter::data::mariadb::connection
#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_CONNECTION_CONFIG_H
