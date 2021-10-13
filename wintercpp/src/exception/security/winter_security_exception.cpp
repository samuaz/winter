/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/exception/security/winter_security_exception.h>
using namespace winter::exception;

SecurityException::SecurityException(const string &message) noexcept : WinterExceptionTemplate<SecurityException>(message) {}