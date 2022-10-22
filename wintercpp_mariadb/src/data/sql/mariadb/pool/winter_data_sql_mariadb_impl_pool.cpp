//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#include <wintercpp/data/sql/mariadb/pool/winter_data_sql_mariadb_impl_pool.h>

using namespace winter::data::mariadb::connection;

using namespace winter::exception;

Pool::Pool(const PoolDescriptor& pool_descriptor,
           std::optional<Config> mysql_config) :
    winter::templates::SinglePool<winter::data::mariadb::connection::Pool,
                                  winter::data::mariadb::connection::Connection,
                                  winter::data::mariadb::connection::Config>(
        pool_descriptor, std::move(mysql_config)) {}

winter::data::mariadb::connection::Connection* Pool::CreateConn() {
    if (Pool::connection_config_) {
        ::sql::ConnectOptionsMap connectionProperties;
        connectionProperties["hostName"] = Pool::connection_config_->host();
        connectionProperties["password"] = Pool::connection_config_->password();
        connectionProperties["schema"] = Pool::connection_config_->schema();
        connectionProperties["port"] = std::to_string(Pool::connection_config_->port());
        connectionProperties["OPT_RECONNECT"] = std::to_string(Pool::connection_config_->is_opt_reconnect());
        connectionProperties["OPT_CONNECT_TIMEOUT"] = std::to_string(Pool::connection_config_->opt_connect_timeout());
        auto otherProps = Pool::connection_config_->properties();
        connectionProperties.insert(otherProps.begin(), otherProps.end());

        std::string base_url;

        std::string url = Pool::connection_config_->host() + ":"
                          + std::to_string(Pool::connection_config_->port())
                          + "/" + Pool::connection_config_->schema();

        if (Pool::connection_config_->use_mysql_connection()) {
            connectionProperties["userName"] = Pool::connection_config_->user_name();
            return new winter::data::mysql::connection::Connection(Pool::connection_config_->driver()->connect(connectionProperties));
        } else {
            connectionProperties["user"] = Pool::connection_config_->user_name();
            base_url = "jdbc:mariadb://";
            return new winter::data::mariadb::connection::Connection(Pool::connection_config_->driver()->connect(base_url + url, connectionProperties));
        }


    }
    throw WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        "MYSQL connection_config not present");
}