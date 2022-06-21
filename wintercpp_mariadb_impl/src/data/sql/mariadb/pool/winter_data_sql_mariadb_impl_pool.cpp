//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#include <wintercpp/data/sql/mariadb/pool/winter_data_sql_mariadb_impl_pool.h>

using namespace winter::data::mariadb::connection;

using namespace winter::exception;

Pool::Pool(
    const PoolDescriptor& pool_descriptor,
    std::optional<Config> mysql_config) :
    winter::templates::SinglePool<
	winter::data::mariadb::connection::Pool,
	winter::data::mariadb::connection::Connection,
	winter::data::mariadb::connection::Config>(pool_descriptor, std::move(mysql_config)) {}

winter::data::mariadb::connection::Connection*
Pool::CreateConn() {
  if (Pool::connection_config_) {
    return winter::data::mariadb::connection::Connection::Create(Pool::connection_config_.value());
  }
  throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, "MYSQL connection_config not present");
}
