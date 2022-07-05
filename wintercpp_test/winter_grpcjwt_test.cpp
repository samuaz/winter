//
// Created by samuaz on 3/10/21.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <wintercpp/winter.h>
#include <wintercpp/winter_grpc.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <thread>

#include "jwt/jwt.hpp"
#include "wintercpp/security/winter_security_token_status.h"

namespace {

class WinterGRPCJWTFixture : public ::testing::Test {
 public:
  WinterGRPCJWTFixture() = default;
  ~WinterGRPCJWTFixture() = default;

 protected:
  void SetUp() override {
    winter::security::GrpcJwt::init("user_id", "secretKey", 5s, 5s);
  }
};

TEST_F(WinterGRPCJWTFixture, canCreateToken) {
  std::string token = winter::security::GrpcJwt::instance().CreateToken("myUserId");
  EXPECT_THAT(token, Not(testing::IsEmpty()));
}

TEST_F(WinterGRPCJWTFixture, canEncode) {
  std::string password = winter::security::GrpcJwt::instance().Encode("mypassword");
  EXPECT_THAT(password, Not(testing::IsEmpty()));
}

TEST_F(WinterGRPCJWTFixture, candecode) {
  std::string password = winter::security::GrpcJwt::instance().Encode("mypassword");
  jwt::jwt_object decode = winter::security::GrpcJwt::instance().DecodeToken(password);
  EXPECT_EQ(decode.payload().get_claim_value<std::string>("password"), "mypassword");
}

TEST_F(WinterGRPCJWTFixture, userFromToken) {
  std::string token = winter::security::GrpcJwt::instance().CreateToken("myUserId");
  std::string user = winter::security::GrpcJwt::instance().UserFromToken(token);
  EXPECT_EQ(user, "myUserId");
}

TEST_F(WinterGRPCJWTFixture, validateToken) {
  std::string token = winter::security::GrpcJwt::instance().CreateToken("myUserId");
  winter::security::TokenStatus tokenInfo = winter::security::GrpcJwt::instance().ValidateToken(token);
  EXPECT_EQ(tokenInfo.isValid(), true);
  EXPECT_EQ(tokenInfo.status(), winter::security::TokenStatusType::VALID);
}

TEST_F(WinterGRPCJWTFixture, expiredToken) {
  std::string token = winter::security::GrpcJwt::instance().CreateToken("myUserId");
  std::chrono::seconds waitTme(6);
  std::this_thread::sleep_for(waitTme);
  winter::security::TokenStatus tokenInfo = winter::security::GrpcJwt::instance().ValidateToken(token);
  EXPECT_FALSE(tokenInfo.isValid());
  EXPECT_EQ(tokenInfo.status(), winter::security::TokenStatusType::EXPIRED);
}
}  // namespace