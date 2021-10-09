#ifndef __WINTER_SECURITY_JWT_GRPC_H__
#define __WINTER_SECURITY_JWT_GRPC_H__

//
// Created by samuaz on 3/5/21.
//

#include <grpcpp/impl/codegen/string_ref.h>
#include <grpcpp/server_context.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/security/winter_security_exception.h>
#include <wintercpp/security/winter_security_jwt.h>
#include <wintercpp/security/winter_security_session.h>
#include <wintercpp/security/winter_security_token_status.h>
#include <wintercpp/security/winter_security_user_info.h>

#include <cctype>
#include <chrono>
#include <iostream>
#include <jwt/jwt.hpp>

namespace winter::security {

class GrpcJwt : public virtual Jwt {
 public:
  static GrpcJwt &instance();

  static GrpcJwt &init(
      const string &key,
      const string &secret_key,
      std::chrono::seconds token_exp,
      std::chrono::seconds refresh_token_exp);

  GrpcJwt(GrpcJwt const &) = delete;

  Jwt &operator=(const GrpcJwt &) = delete;

  GrpcJwt(GrpcJwt &&) = delete;

  GrpcJwt &operator=(GrpcJwt &&) = delete;

  std::string CreateToken(const std::string &value) const;

  std::string CreateRefreshToken(const std::string &value) const;

  std::string UserFromToken(const std::string &token) const;

  UserSecurityInfo Secure(const grpc::ServerContext &context) const;

  UserSecurityInfo Secure(const grpc::ServerContext &context, const winter::security::Session &session) const;

  std::string ExtractTokenFromGrpcMetadata(
      const std::multimap<grpc::string_ref, grpc::string_ref> &metadata) const;

 private:
  GrpcJwt(
      const string key,
      string secretKey,
      std::chrono::seconds token_exp,
      std::chrono::seconds refresh_token_exp);
  std::string _key;
  static inline std::unique_ptr<GrpcJwt> instance_;
  static inline std::once_flag m_once_;
};

}  // namespace winter::security

#endif	// __WINTER_SECURITY_JWT_GRPC_H__