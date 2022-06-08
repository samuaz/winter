//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

using namespace winter::data::sql_impl::mysql::connection;
using namespace winter::exception;

template <typename TConnection, typename TConfig>
Pool<TConnection, TConfig>::Pool(
    const PoolDescriptor& pool_descriptor,
    std::optional<TConfig> mysql_config) :
    Pool<TConnection, TConfig>::SinglePool(pool_descriptor, std::move(mysql_config)) {}

template <typename TConnection, typename TConfig>
TConnection*
Pool<TConnection, TConfig>::CreateConn() {
  if (Pool<TConnection, TConfig>::connection_config_) {
    return TConnection::Create(Pool<TConnection, TConfig>::connection_config_.value());
  }
  throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, "MYSQL connection_config not present");
}
