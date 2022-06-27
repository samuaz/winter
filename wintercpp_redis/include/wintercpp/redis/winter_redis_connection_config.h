//
// Created by samuaz on 6/1/21.
//

#ifndef WINTERCPP_WINTER_REDIS_CONNECTION_CONFIG_H
#define WINTERCPP_WINTER_REDIS_CONNECTION_CONFIG_H

#include <string>
namespace winter::redis {

    class Config final {
       public:
        Config(std::string host, const size_t &port, std::string password);

        const std::string &host() const;

        size_t port() const;

        const std::string &password() const;

       private:
        const std::string host_;
        const size_t port_;
        const std::string password_;
    };
}  // namespace winter::redis

typedef winter::redis::Config RedisConfig;

#endif  // WINTERCPP_WINTER_REDIS_CONNECTION_CONFIG_H
