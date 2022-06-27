//
// Created by samuel on 06/08/19.
//

#include <wintercpp/redis/winter_redis_connection.h>

using namespace winter;

redis::Connection *redis::Connection::Create(const redis::Config &redisConfig) {
    auto *client = new cpp_redis::client;
    const auto &host = redisConfig.host();
    auto port = redisConfig.port();
    const auto &password = redisConfig.password();
    client->auth(password);
    client->connect(host, port);
    return new winter::redis::Connection(client, redisConfig);
}

redis::Connection::Connection(cpp_redis::client *conn, Config redis_config) :
    winter::templates::Connection<cpp_redis::client>(conn),
    redis_config_(std::move(redis_config)) {}

int redis::Connection::Int(const std::string &key) {
    std::scoped_lock<std::recursive_mutex> lock(conn_mtx());
    Reconnect();
    int result = 0;
    conn().get(key, [&](cpp_redis::reply &reply) {
        if (reply.is_integer()) { result = reply.as_integer(); }
    });
    conn().sync_commit();
    return result;
}

std::string redis::Connection::String(const std::string &key) {
    std::scoped_lock<std::recursive_mutex> lock(conn_mtx());
    Reconnect();
    std::string result;
    conn().get(key, [&](cpp_redis::reply &reply) {
        if (reply.is_string()) { result = reply.as_string(); }
    });
    conn().sync_commit();
    return result;
}

void redis::Connection::StringCallback(
    const std::string &key,
    std::function<void(cpp_redis::reply &)> &reply_callback) {
    std::scoped_lock<std::recursive_mutex> lock(conn_mtx());
    Reconnect();
    conn().get(key, reply_callback);
    conn().sync_commit();
}

void redis::Connection::DelKey(const std::string &key) {
    std::scoped_lock<std::recursive_mutex> lock(conn_mtx());
    std::vector<std::string> keys = {key};
    Reconnect();
    conn().del(keys);
    conn().commit();
}

void redis::Connection::DelKey(const std::vector<std::string> &key) {
    std::scoped_lock<std::recursive_mutex> lock(conn_mtx());
    Reconnect();
    const std::vector<std::string> &keys = {key};
    conn().del(keys);
    conn().commit();
}

void redis::Connection::Set(const std::string &key, const std::string &value) {
    std::scoped_lock<std::recursive_mutex> lock(conn_mtx());
    Reconnect();
    conn().set(key, value);
    conn().sync_commit();
}

void redis::Connection::Reconnect() {
    std::scoped_lock<std::recursive_mutex> lock(conn_mtx());
    if (! conn().is_connected()) {
        conn().auth(redis_config_.password());
        conn().connect(redis_config_.host(), redis_config_.port());
    }
}
