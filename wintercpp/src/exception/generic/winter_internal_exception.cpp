/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/exception/generic/winter_internal_exception.h>
using namespace winter::exception;

WinterInternalException::WinterInternalException(const string &message) noexcept : WinterException<WinterInternalException>(message) {}