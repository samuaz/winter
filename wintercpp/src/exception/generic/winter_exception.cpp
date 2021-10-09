/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/exception/generic/winter_exception.h>
using namespace winter;

WinterException::WinterException(const string &message) noexcept : std::logic_error(message) {}
