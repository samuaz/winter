//
// Created by samuaz on 6/1/21.
//

#include <wintercpp/redis/winter_redis_connection_config.h>

winter::redis::Config::Config(std::string host,
                              const size_t &port,
                              std::string password) :
    host_(std::move(host)),
    port_(port), password_(std::move(password)) {}

const std::string &winter::redis::Config::host() const {
    return host_;
}

size_t winter::redis::Config::port() const {
    return port_;
}

const std::string &winter::redis::Config::password() const {
    return password_;
}
