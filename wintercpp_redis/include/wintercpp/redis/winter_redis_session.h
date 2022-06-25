/**
 * @author Samuel Azcona
 * @email samuel@theopencompany.dev
 * @create date 2021-06-26 01:45:23
 * @modify date 2021-06-26 01:45:23
 * @desc [description]
 */

#ifndef __WINTER_REDIS_SESSION_H__
#define __WINTER_REDIS_SESSION_H__

#include <wintercpp/redis/winter_redis_pool.h>
#include <wintercpp/security/winter_security_session.h>
#include <wintercpp/security/winter_security_user_info.h>

namespace winter::redis {

class Session final : virtual public winter::security::Session {
 public:
  Session(std::function<std::shared_ptr<RedisConnection>()> redis_connection);

  void CreateSession(const winter::security::UserSecurityInfo &user_security_info) const override;

  void RemoveSession(const winter::security::UserSecurityInfo &user_security_info) const override;

  bool IsValid(const winter::security::UserSecurityInfo &user_security_info) const override;

 private:
  const std::function<std::shared_ptr<RedisConnection>()> redis_connection_;
};

}  // namespace winter::redis

#endif	// __WINTER_REDIS_SESSION_H__