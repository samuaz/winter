/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.dev/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/security/winter_security_jwt_grpc.h>

#include <chrono>
#include <jwt/jwt.hpp>
#include <utility>

#include "wintercpp/util/winter_string_util.h"
using namespace winter::security;
using namespace winter::exception;

GrpcJwt &
GrpcJwt::init(
    const string &key,
    const string &secret_key,
    std::chrono::seconds token_exp,
    std::chrono::seconds refresh_token_exp) {
  std::call_once(m_once_, [&]() {
    instance_.reset(new GrpcJwt(
	key,
	secret_key,
	token_exp,
	refresh_token_exp));
  });
  return *instance_;
};

GrpcJwt &
GrpcJwt::instance() {
  if (instance_ == nullptr) {
    throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__,
					  "you first need to init this GRPCJWT class using "
					  "the init function");
  }

  return *instance_;
}

GrpcJwt::GrpcJwt(
    string key,
    string secretKey,
    std::chrono::seconds token_exp,
    std::chrono::seconds refresh_token_exp) :
    Jwt(std::move(secretKey), token_exp, refresh_token_exp),
    _key(std::move(key)){};

std::string
GrpcJwt::ExtractTokenFromGrpcMetadata(
    const std::multimap<grpc::string_ref, grpc::string_ref> &metadata) const {
  auto map = metadata;
  std::multimap<grpc::string_ref, grpc::string_ref>::iterator itr;
  for (itr = map.begin(); itr != map.end(); ++itr) {
    if (itr->first == "Authorization" || itr->first == "authorization") {
      try {
	std::string erase = "Bearer ";
	std::size_t pos = itr->second.find(erase);
	if (pos > 0) {
	  erase = "bearer ";
	  pos = itr->second.find(erase);
	}
	std::string value(itr->second.begin(), itr->second.end());
	std::string token = value.erase(pos, erase.length());
	winter::util::string::strip_unicode(token);
	return token;
      } catch (...) {
	throw SecurityException::Create(__FILE__, __FUNCTION__, __LINE__, "TOKEN Format invalid you need tu use Bearer token");
      }
    }
  }

  throw SecurityException::Create(__FILE__, __FUNCTION__, __LINE__,
				  "TOKEN IS MISSING, YOU NEED TO SEND YOUR TOKEN AS METADATA example: "
				  "authorization: Bearer token");
}

UserSecurityInfo
GrpcJwt::Secure(const grpc::ServerContext &context) const {
  std::string token = GrpcJwt::ExtractTokenFromGrpcMetadata(context.client_metadata());

  TokenStatus tokenStatus = GrpcJwt::ValidateToken(token);

  if (!tokenStatus.isValid()) {
    throw SecurityException::Create(__FILE__, __FUNCTION__, __LINE__, tokenStatus.message());
  }

  return UserSecurityInfo(_key, UserFromToken(token), token, tokenStatus);
}

UserSecurityInfo
GrpcJwt::Secure(const grpc::ServerContext &context, const Session &session) const {
  UserSecurityInfo userSecurityInfo = Secure(context);

  if (!session.IsValid(userSecurityInfo)) {
    throw SecurityException::Create(__FILE__, __FUNCTION__, __LINE__, "Session is not valid, re-authentication is needed");
  }
  return userSecurityInfo;
}

std::string
GrpcJwt::CreateToken(const std::string &value) const {
  return Jwt::CreateToken(_key, value);
}

std::string
GrpcJwt::CreateRefreshToken(const std::string &value) const {
  return Jwt::CreateRefreshToken(_key, value);
}

std::string
GrpcJwt::UserFromToken(const std::string &token) const {
  return Jwt::ValueFromKey(_key, token);
}
