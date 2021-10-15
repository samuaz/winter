//
// Created by samuel on 08/08/19.
//

#ifndef WINTER_USER_SECURITY_INFO_H
#define WINTER_USER_SECURITY_INFO_H

#include <wintercpp/security/winter_security_token_status.h>

#include <string>

namespace winter::security {

class UserSecurityInfo {
 public:
  UserSecurityInfo(std::string key, std::string user_id, std::string token, TokenStatus token_status);
  const std::string &key() const;
  const std::string &user_id() const;
  const std::string &token() const;
  TokenStatus &token_status() const;

 private:
  const std::string key_;
  const std::string user_id_;
  const std::string token_;
  const TokenStatus token_status_;
};

}  // namespace winter::security

#endif	// WINTER_USER_SECURITY_INFO_H
