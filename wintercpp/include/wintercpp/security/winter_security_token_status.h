/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_TOKEN_STATUS_H
#define WINTER_TOKEN_STATUS_H

#include <string>

namespace winter::security {

    /**
     * @enum VALID
     * @enum EXPIRED
     * @enum INVALID
     * status response from token
     */
    enum class TokenStatusType { VALID = 0,
                                 EXPIRED = 1,
                                 INVALID = 2 };

    /**
     * @struct TokenStatus
     */
    class TokenStatus {
       public:
        TokenStatus(TokenStatusType status, std::string message);

        const TokenStatusType& status() const;

        const std::string& message() const;

        bool isValid() const;

       private:
        const TokenStatusType status_;
        const std::string     message_;
    };

}  // namespace winter::security

#endif  // WINTER_TOKEN_STATUS_H
