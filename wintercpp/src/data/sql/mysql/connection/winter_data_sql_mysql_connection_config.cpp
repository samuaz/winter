//
// Created by samuaz on 5/31/21.
//

#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection_config.h>

#include "jdbc/mysql_driver.h"

using namespace winter::data::sql::mysql::connection;

MysqlConfig::Config(
    std::string host,
    int port,
    std::string userName,
    std::string password,
    std::string schema,
    bool optReconnect,
    int optConnectTimeout) : _driver(::sql::mysql::get_driver_instance()), _host(std::move(host)), _port(port), _userName(std::move(userName)), _password(std::move(password)), _schema(std::move(schema)), _opt_reconnect(optReconnect), _opt_connect_timeout(optConnectTimeout) {}

const std::string&
MysqlConfig::host() const {
  return _host;
}

int MysqlConfig::port() const {
  return _port;
}

const std::string&
MysqlConfig::user_name() const {
  return _userName;
}

const std::string&
MysqlConfig::password() const {
  return _password;
}

const std::string&
MysqlConfig::schema() const {
  return _schema;
}

bool MysqlConfig::is_opt_reconnect() const {
  return _opt_reconnect;
}

int MysqlConfig::opt_connect_timeout() const {
  return _opt_connect_timeout;
}

::sql::mysql::MySQL_Driver&
MysqlConfig::driver() const {
  return *_driver;
}
