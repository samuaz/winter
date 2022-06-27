//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/redis/winter_redis_pool.h>

using namespace winter::exception;

winter::redis::Pool::Pool(winter::descriptor::PoolDescriptor pool_descriptor,
                          std::optional<Config> redis_config) :
    SinglePool(std::move(pool_descriptor), std::move(redis_config)) {}

winter::redis::Connection* winter::redis::Pool::CreateConn() {
    if (connection_config_) {
        return Connection::Create(connection_config_.value());
    }
    throw WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        "MYSQL connection_config not present");
}
