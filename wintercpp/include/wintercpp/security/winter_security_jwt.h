//
// Created by samuaz on 3/5/21.
//

#ifndef WINTERCPP_WINTER_JWT_H
#define WINTERCPP_WINTER_JWT_H

#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/security/winter_security_exception.h>
#include <wintercpp/security/winter_security_token_status.h>
#include <wintercpp/security/winter_security_user_info.h>

#include <cctype>
#include <chrono>
#include <iostream>
#include <jwt/jwt.hpp>

namespace winter::security {

class Jwt {
 public:
  Jwt(
      string secretKey,
      std::chrono::seconds tokenExp,
      std::chrono::seconds refreshTokenExp);

  std::string CreateToken(const std::string &key, const std::string &value) const;

  std::string CreateRefreshToken(const std::string &key, const std::string &value) const;

  std::string ValueFromKey(const std::string &key, const std::string &token) const;

  jwt::jwt_object DecodeToken(const std::string &token) const;

  TokenStatus ValidateToken(const std::string &token) const;

  void StripUnicode(std::string &str) const;

  std::string Encode(const std::string &password) const;

 private:
  const std::string secret_key_;
  const std::chrono::seconds token_exp_;
  const std::chrono::seconds refresh_token_exp_;
  const std::string algorithm_ = "HS512";
  std::string createToken(const std::string &key, const std::string &value, std::chrono::seconds expire_time) const;
};

}  // namespace winter::security
#endif	// WINTERCPP_WINTER_JWT_H
