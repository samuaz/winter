/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_INTERNAL_EXCEPTION_H
#define WINTER_INTERNAL_EXCEPTION_H

#include <wintercpp/exception/generic/winter_exception.h>

#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;
namespace winter::exception {

class WinterInternalException final : public WinterException<WinterInternalException> {
 public:
  explicit WinterInternalException(const string &message) noexcept;
};
}  // namespace winter::exception

#endif	// WINTER_INTERNAL_EXCEPTION_H
