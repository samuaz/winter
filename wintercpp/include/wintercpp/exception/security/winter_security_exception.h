/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_SECURITY_EXCEPTION_H
#define WINTER_SECURITY_EXCEPTION_H

#include <wintercpp/exception/generic/winter_exception.h>

namespace winter {

class SecurityException final : public WinterException {
 public:
  explicit SecurityException(const string &message) noexcept;
};

}  // namespace winter

#endif	// WINTER_SECURITY_EXCEPTION_H
