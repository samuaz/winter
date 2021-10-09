#include <wintercpp/redis/winter_redis_session.h>

using namespace winter::redis;

Session::Session(std::function<std::shared_ptr<RedisConnection>()> redis_connection) : redis_connection_(std::move(redis_connection)) {}

void Session::CreateSession(const winter::security::UserSecurityInfo &user_security_info) const {
  auto redis = redis_connection_();
  redis->Set(user_security_info.key(), user_security_info.token());
}

void Session::RemoveSession(const winter::security::UserSecurityInfo &user_security_info) const {
  auto redis = redis_connection_();
  redis->DelKey(user_security_info.key());
}

bool Session::IsValid(const winter::security::UserSecurityInfo &user_security_info) const {
  auto redis = redis_connection_();
  std::string redisSessionToken = redis->String(user_security_info.user_id());

  if (redisSessionToken.empty()) {
    return false;
  }

  if (user_security_info.token() != redisSessionToken) {
    return false;
  }

  return true;
}