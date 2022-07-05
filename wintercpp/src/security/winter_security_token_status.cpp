#include <wintercpp/security/winter_security_token_status.h>

using namespace winter::security;

TokenStatus::TokenStatus(TokenStatusType status, std::string message) :
    status_(status), message_(std::move(message)) {}

const TokenStatusType& TokenStatus::status() const {
    return status_;
}

const std::string& TokenStatus::message() const {
    return message_;
}

bool TokenStatus::isValid() const {
    if (status_ == TokenStatusType::VALID) { return true; }
    return false;
}