//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#include <wintercpp/redis/winter_redis_pool.h>

winter::redis::Pool::Pool(
    winter::descriptor::PoolDescriptor pool_descriptor,
    std::optional<Config> redis_config) : SinglePool(std::move(pool_descriptor), std::move(redis_config)) {}

winter::redis::Connection*
winter::redis::Pool::CreateConn() {
  if (connection_config_) {
    return Connection::Create(connection_config_.value());
  }
  throw WinterException("MYSQL connection_config not present");
}
