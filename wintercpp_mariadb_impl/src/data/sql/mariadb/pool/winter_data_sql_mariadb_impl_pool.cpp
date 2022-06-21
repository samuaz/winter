//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#include <wintercpp/data/sql/mariadb/pool/winter_data_sql_mariadb_impl_pool.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>

using namespace winter::data::sql_impl::mysql::connection::mariadb_impl;
using namespace winter::exception;

Pool::Pool(
    const PoolDescriptor& pool_descriptor,
    std::optional<Config> mysql_config) :
    winter::templates::SinglePool<
	winter::data::sql_impl::mysql::connection::mariadb_impl::Pool,
	winter::data::sql_impl::mysql::connection::mariadb_impl::Connection,
	winter::data::sql_impl::mysql::connection::mariadb_impl::Config>(pool_descriptor, std::move(mysql_config)) {}

winter::data::sql_impl::mysql::connection::mariadb_impl::Connection*
Pool::CreateConn() {
  if (Pool::connection_config_) {
    return winter::data::sql_impl::mysql::connection::mariadb_impl::Connection::Create(Pool::connection_config_.value());
  }
  throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, "MYSQL connection_config not present");
}
