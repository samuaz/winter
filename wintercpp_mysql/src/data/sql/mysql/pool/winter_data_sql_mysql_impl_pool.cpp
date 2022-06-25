//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#include <wintercpp/data/sql/mysql/pool/winter_data_sql_mysql_impl_pool.h>

using namespace winter::data::mysql::connection;

using namespace winter::exception;

Pool::Pool(
    const PoolDescriptor& pool_descriptor,
    std::optional<Config> mysql_config) :
    winter::templates::SinglePool<
	winter::data::mysql::connection::Pool,
	winter::data::mysql::connection::Connection,
	winter::data::mysql::connection::Config>(pool_descriptor, std::move(mysql_config)) {}

winter::data::mysql::connection::Connection*
Pool::CreateConn() {
  if (Pool::connection_config_) {
    ::sql::ConnectOptionsMap connectionProperties;
    connectionProperties["hostName"] = Pool::connection_config_->host();
    connectionProperties["user"] = Pool::connection_config_->user_name();
    connectionProperties["password"] = Pool::connection_config_->password();
    connectionProperties["schema"] = Pool::connection_config_->schema();
    connectionProperties["port"] = std::to_string(Pool::connection_config_->port());
    connectionProperties["OPT_RECONNECT"] = std::to_string(Pool::connection_config_->is_opt_reconnect());
    connectionProperties["OPT_CONNECT_TIMEOUT"] = std::to_string(Pool::connection_config_->opt_connect_timeout());

    std::string url = Pool::connection_config_->host() + ":" + std::to_string(Pool::connection_config_->port()) + "/" + Pool::connection_config_->schema();

    return new winter::data::mysql::connection::Connection(Pool::connection_config_->driver()->connect("jdbc:mariadb://" + url, connectionProperties));
  }
  throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, "MYSQL connection_config not present");
}