
//
// Created by samuel on 06/08/19.
//

#ifndef WINTER_REDIS_CONNECTION
#define WINTER_REDIS_CONNECTION

#include <wintercpp/redis/winter_redis_connection_config.h>
#include <wintercpp/template/winter_connection_template.h>

#include <cpp_redis/core/client.hpp>

namespace winter::redis {

// REDIS
#define REDIS_CONN(_FUNCTION_)                                         \
    std::invoke([&]() {                                                \
        auto redis = winter::redis_impl::RedisPool::instance().conn(); \
        redis->_FUNCTION_;                                             \
    })

#define REDIS_SET(_KEY_, _VALUE_) REDIS_CONN(set(_KEY_, _VALUE_))

#define REDIS_DEL(_KEY_) REDIS_CONN(delKey(_KEY_))

#define REDIS_GET_STRING(_KEY_) REDIS_CONN(getString(_KEY_))

    class Connection final :
        public virtual winter::templates::Connection<cpp_redis::client> {
       public:
        static Connection *Create(const Config &redisConfig);

        /**
         * set key and value to Save in redis
         */
        void Set(const std::string &key, const std::string &value);

        /**
         * get int value from key sync
         * @param key
         * @return
         */
        int Int(const std::string &key);

        /**
         *
         * get string value from key sync
         * @param key
         * @return
         */
        std::string String(const std::string &key);

        /**
         *
         * get string value from key with callback async
         * @param key
         * @return
         */
        void StringCallback(
            const std::string                       &key,
            std::function<void(cpp_redis::reply &)> &reply_callback);

        /**
         * remove key from redis
         * @param key
         */
        void DelKey(const std::string &key);

        void DelKey(const std::vector<std::string> &key);

       protected:
        void Reconnect();

       private:
        const Config redis_config_;
        explicit Connection(cpp_redis::client *conn, Config redis_config);
    };
}  // namespace winter::redis
typedef winter::redis::Connection RedisConnection;
#endif /* WINTER_REDIS_CONNECTION */
