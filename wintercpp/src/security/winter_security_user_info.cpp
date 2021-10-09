#include <wintercpp/security/winter_security_user_info.h>

#include <string>
#include <utility>

using namespace winter::security;

UserSecurityInfo::UserSecurityInfo(std::string key, std::string user_id, std::string token, TokenStatus token_status) : key_(std::move(key)), user_id_(std::move(user_id)), token_(std::move(token)), token_status_(std::move(token_status)){};

const std::string&
UserSecurityInfo::key() const {
  return key_;
}

const std::string&
UserSecurityInfo::user_id() const {
  return user_id_;
}

const std::string&
UserSecurityInfo::token() const {
  return token_;
}
