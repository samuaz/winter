/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_UNAUTHENTICATED_EXCEPTION_H
#define WINTER_UNAUTHENTICATED_EXCEPTION_H

#include <wintercpp/exception/generic/winter_exception.h>

namespace winter::exception {

class UnauthenticatedException final : public WinterException<UnauthenticatedException> {
 public:
  explicit UnauthenticatedException(const string &message) noexcept;
};
}  // namespace winter::exception

#endif	// WINTER_UNAUTHENTICATED_EXCEPTION_H
