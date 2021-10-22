//
// Created by samuaz on 5/31/21.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H

#include <wintercpp/data/sql/mysql/winter_sql_mysql_driver.h>

#if WITH_MYSQL
#include <mysql/jdbc.h>
typedef ::sql::mysql::MySQL_Driver MYSQL_DRIVER;
#elif WITH_MARIADB
#include <mariadb/conncpp.hpp>
typedef ::sql::Driver MYSQL_DRIVER;
#else
#error "NO WINTER_MYSQL_DRIVER"
#endif

#include <string>

namespace winter::data::sql::mysql::connection {

class Connection;

class Config final {
  friend class Connection;

 public:
  Config(
      std::string host,
      int port,
      std::string userName,
      std::string password,
      std::string schema,
      bool opt_reconnect,
      int opt_connect_timeout);

  const std::string &host() const;

  int port() const;

  const std::string &user_name() const;

  const std::string &password() const;

  const std::string &schema() const;

  bool is_opt_reconnect() const;

  int opt_connect_timeout() const;

 private:
  //::sql::mysql::MySQL_Driver *_driver;
  MYSQL_DRIVER *_driver;
  const std::string _host;
  const int _port;
  const std::string _userName;
  const std::string _password;
  const std::string _schema;
  const bool _opt_reconnect;
  const int _opt_connect_timeout;

  //::sql::mysql::MySQL_Driver &driver() const;
  MYSQL_DRIVER &driver() const;
};
}  // namespace winter::data::sql::mysql::connection
typedef winter::data::sql::mysql::connection::Config MysqlConfig;

#endif	// WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H
