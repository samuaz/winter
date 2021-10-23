//
// Created by samuaz on 5/31/21.
//

#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection_config.h>

//#include "jdbc/mysql_driver.h"

using namespace winter::data::sql::mysql::connection;

MysqlConfig::Config(
    std::string host,
    int port,
    std::string user_name,
    std::string password,
    std::string schema,
    bool opt_reconnect,
    int opt_connect_timeout,
    const ConnectionProperties& other_properties) :
#if WITH_MYSQL
    _driver(::sql::mysql::get_driver_instance()),
#endif
#if WITH_MARIADB
    _driver(::sql::mariadb::get_driver_instance()),
#endif
    _host(std::move(host)),
    _port(port),
    _user_name(std::move(user_name)),
    _password(std::move(password)),
    _schema(std::move(schema)),
    _opt_reconnect(opt_reconnect),
    _opt_connect_timeout(opt_connect_timeout),
    _other_properties(other_properties) {
}

const std::string&
MysqlConfig::host() const {
  return _host;
}

int MysqlConfig::port() const {
  return _port;
}

const std::string&
MysqlConfig::user_name() const {
  return _user_name;
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

const ConnectionProperties& MysqlConfig::properties() const {
  return _other_properties;
}

MYSQL_DRIVER&
MysqlConfig::driver() const {
  return *_driver;
}