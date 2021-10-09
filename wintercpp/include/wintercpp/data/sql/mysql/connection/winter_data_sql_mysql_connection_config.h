//
// Created by samuaz on 5/31/21.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H

#include <mysql/jdbc.h>

#include <string>

namespace winter::data::sql::mysql::connection {

class Config final {
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

  ::sql::mysql::MySQL_Driver &driver() const;

  bool is_opt_reconnect() const;

  int opt_connect_timeout() const;

 private:
  ::sql::mysql::MySQL_Driver *_driver;
  std::string _host;
  int _port;
  std::string _userName;
  std::string _password;
  std::string _schema;
  bool _opt_reconnect;
  int _opt_connect_timeout;
};
}  // namespace winter::data::sql::mysql::connection
typedef winter::data::sql::mysql::connection::Config MysqlConfig;

#endif	// WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H
