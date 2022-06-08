//
// Created by samuaz on 5/31/21.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H

#include <functional>
#include <map>
#include <string>

namespace winter::data::sql_impl::mysql::connection {

typedef std::map<std::string, std::string> ConnectionProperties;

template <typename TDriver>
class Config {
 public:
  Config(
      std::function<TDriver()>,
      std::string host,
      int port,
      std::string user_name,
      std::string password,
      std::string schema,
      bool opt_reconnect,
      int opt_connect_timeout,
      ConnectionProperties other_properties = {});

  const std::string &host() const;

  int port() const;

  const std::string &user_name() const;

  const std::string &password() const;

  const std::string &schema() const;

  bool is_opt_reconnect() const;

  int opt_connect_timeout() const;

  const ConnectionProperties &properties() const;

 private:
  TDriver *_driver;
  const std::string _host;
  const int _port;
  const std::string _user_name;
  const std::string _password;
  const std::string _schema;
  const bool _opt_reconnect;
  const int _opt_connect_timeout;
  const ConnectionProperties _other_properties;

  TDriver &driver() const;
};
}  // namespace winter::data::sql_impl::mysql::connection
// typedef winter::data::sql_impl::mysql::connection::Config MysqlConfig;

#include "winter_data_sql_mysql_connection_config.tpp"

#endif	// WINTERCPP_WINTER_DATA_SQL_MYSQL_CONNECTION_CONFIG_H
