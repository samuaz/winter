/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/exception/security/winter_unauthenticated_exception.h>
using namespace winter;

UnauthenticatedException::UnauthenticatedException(
    const string &message) noexcept : WinterException(message) {}
