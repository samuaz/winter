//
// Created by samuel on 06/08/19.
//

#include <wintercpp/redis/winter_redis_connection.h>

using namespace winter;

redis::Connection *
redis::Connection::Create(
    const redis::Config &redisConfig) {
  auto *client = new cpp_redis::client;
  const auto &host = redisConfig.host();
  auto port = redisConfig.port();
  const auto &password = redisConfig.password();
  client->auth(password);
  client->connect(host, port);
  return new winter::redis::Connection(client, redisConfig);
}

redis::Connection::Connection(
    cpp_redis::client *conn,
    Config redis_config) : winter::templates::Connection<winter::redis::Connection, cpp_redis::client>(conn),
			   redis_config_(std::move(redis_config)) {}

int redis::Connection::Int(const std::string &key) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  Reconnect();
  int result = 0;
  conn_->get(key, [&](cpp_redis::reply &reply) {
    if (reply.is_integer()) {
      result = reply.as_integer();
    }
  });
  conn_->sync_commit();
  return result;
}

std::string
redis::Connection::String(const std::string &key) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  Reconnect();
  std::string result;
  conn_->get(key, [&](cpp_redis::reply &reply) {
    if (reply.is_string()) {
      result = reply.as_string();
    }
  });
  conn_->sync_commit();
  return result;
}

void redis::Connection::StringCallback(
    const std::string &key,
    std::function<void(cpp_redis::reply &)> &reply_callback) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  Reconnect();
  conn_->get(key, reply_callback);
  conn_->sync_commit();
}

void redis::Connection::DelKey(const std::string &key) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  std::vector<std::string> keys = {key};
  Reconnect();
  conn_->del(keys);
  conn_->commit();
}

void redis::Connection::DelKey(const std::vector<std::string> &key) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  Reconnect();
  const std::vector<std::string> &keys = {key};
  conn_->del(keys);
  conn_->commit();
}

void redis::Connection::Set(
    const std::string &key,
    const std::string &value) {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  Reconnect();
  conn_->set(key, value);
  conn_->sync_commit();
}

void redis::Connection::Reconnect() {
  std::scoped_lock<std::recursive_mutex> lock(conn_mtx_);
  if (!conn_->is_connected()) {
    conn_->auth(redis_config_.password());
    conn_->connect(redis_config_.host(), redis_config_.port());
  }
}
