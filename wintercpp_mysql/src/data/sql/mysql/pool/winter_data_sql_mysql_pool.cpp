//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#include <wintercpp/data/sql/mysql/pool/winter_data_sql_mysql_pool.h>

using namespace winter::data::sql::mysql::connection;
using namespace winter::exception;

Pool::Pool(
    PoolDescriptor pool_descriptor,
    std::optional<Config> mysql_config) :
    SinglePool(std::move(pool_descriptor), std::move(mysql_config)) {}

MysqlConnection*
Pool::CreateConn() {
  if (connection_config_) {
    return MysqlConnection::Create(connection_config_.value());
  }
  throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, "MYSQL connection_config not present");
}
