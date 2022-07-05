/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_SECURITY_EXCEPTION_H
#define WINTER_SECURITY_EXCEPTION_H

#include <wintercpp/exception/generic/winter_exception.h>

namespace winter::exception {

    class SecurityException final :
        public WinterExceptionTemplate<SecurityException> {
       public:
        explicit SecurityException(const string &message) noexcept;
    };

}  // namespace winter::exception

#endif  // WINTER_SECURITY_EXCEPTION_H
