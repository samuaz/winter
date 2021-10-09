/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_UNAUTHENTICATED_EXCEPTION_H
#define WINTER_UNAUTHENTICATED_EXCEPTION_H

#include <wintercpp/exception/generic/winter_exception.h>

namespace winter {

class UnauthenticatedException final : public WinterException {
 public:
  explicit UnauthenticatedException(const string &message) noexcept;
};
}  // namespace winter

#endif	// WINTER_UNAUTHENTICATED_EXCEPTION_H
