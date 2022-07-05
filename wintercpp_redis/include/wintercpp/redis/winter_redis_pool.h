//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-21.
//

#ifndef WINTERCPP_WINTER_REDIS_POOL_H
#define WINTERCPP_WINTER_REDIS_POOL_H

#include <wintercpp/redis/winter_redis_connection.h>
#include <wintercpp/template/winter_connection_pool_singleton_template.h>
#include <wintercpp/template/winter_connection_pool_template.h>
#include <wintercpp/util/winter_pool_descriptor.h>

#include <cpp_redis/cpp_redis>
#include <string>

namespace winter::redis {

    class Pool final :
        public virtual winter::templates::
            SinglePool<Pool, winter::redis::Connection, Config> {
        friend class SinglePool<Pool, winter::redis::Connection, Config>;

       private:
        explicit Pool(winter::descriptor::PoolDescriptor pool_descriptor,
                      std::optional<Config>              redis_config);
        winter::redis::Connection* CreateConn() override;
        ~Pool() override = default;
    };
}  // namespace winter::redis

typedef winter::redis::Pool RedisPool;

#endif  // WINTERCPP_WINTER_REDIS_POOL_H
