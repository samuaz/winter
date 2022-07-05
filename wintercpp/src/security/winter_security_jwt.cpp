/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/security/winter_security_jwt.h>

#include <cctype>
#include <chrono>
#include <iostream>
#include <jwt/jwt.hpp>
#include <utility>

using namespace winter::security;

std::string Jwt::createToken(const std::string   &key,
                             const std::string   &value,
                             std::chrono::seconds expire_time) const {
    using namespace jwt::params;
    jwt::jwt_object obj {algorithm(algorithm_), secret(secret_key_)};
    auto            now = std::chrono::system_clock::now();
    obj.add_claim(key, value)
        .add_claim("iat", now)
        .add_claim("exp", (now + expire_time));
    auto enc_str = obj.signature();
    return enc_str;
}

std::string Jwt::CreateToken(const std::string &key,
                             const std::string &value) const {
    return createToken(key, value, token_exp_);
}

std::string Jwt::CreateRefreshToken(const std::string &key,
                                    const std::string &value) const {
    return createToken(key, value, refresh_token_exp_);
}

std::string Jwt::ValueFromKey(const std::string &key,
                              const std::string &token) const {
    using namespace jwt::params;
    jwt::jwt_object  dec_obj = DecodeToken(token);
    jwt::jwt_payload payload = dec_obj.payload();
    return payload.get_claim_value<std::string>(key);
}

std::string Jwt::Encode(const std::string &password) const {
    using namespace jwt::params;
    // Create JWT object
    jwt::jwt_object obj {algorithm(algorithm_), secret(secret_key_)};
    obj.add_claim("password", password);
    auto enc_str = obj.signature();
    return enc_str;
}

jwt::jwt_object Jwt::DecodeToken(const std::string &token) const {
    using namespace jwt::params;
    jwt::jwt_object dec_obj = jwt::decode(token, algorithms({algorithm_}), secret(secret_key_));
    return dec_obj;
}

TokenStatus Jwt::ValidateToken(const std::string &token) const {
    using namespace jwt::params;

    if (token.empty()) {
        return TokenStatus(TokenStatusType::INVALID,
                           "TOKEN IS MISSING, YOU NEED TO SEND YOUR TOKEN AS "
                           "METADATA example: authorization: Bearer token");
    } else {
        try {
            auto dec_obj = jwt::decode(token,
                                       algorithms({algorithm_}),
                                       secret(secret_key_),
                                       verify(true));
            return TokenStatus(TokenStatusType::VALID, "VALID");
        } catch (const jwt::TokenExpiredError &e) {
            return TokenStatus(TokenStatusType::EXPIRED, e.what());
        } catch (const jwt::SignatureFormatError &e) {
            return TokenStatus(TokenStatusType::INVALID, e.what());
        } catch (const jwt::DecodeError &e) {
            return TokenStatus(TokenStatusType::INVALID, e.what());
        } catch (const jwt::VerificationError &e) {
            return TokenStatus(TokenStatusType::INVALID, e.what());
        } catch (...) {
            return TokenStatus(TokenStatusType::INVALID,
                               "Caught unknown exception");
        }
    }
}

void Jwt::StripUnicode(string &str) const {
    str.erase(remove_if(str.begin(),
                        str.end(),
                        [](char c) -> bool {
                            return ! (c >= 0 && c < 128);
                        }),
              str.end());

    str.erase(std::remove_if(str.begin(),
                             str.end(),
                             [l = std::locale {}](auto x) {
                                 return std::isspace(x, l);
                             }),
              str.end());
}

Jwt::Jwt(string               secretKey,
         std::chrono::seconds tokenExp,
         std::chrono::seconds refreshTokenExp) :
    secret_key_(std::move(secretKey)),
    token_exp_(tokenExp), refresh_token_exp_(refreshTokenExp) {}
