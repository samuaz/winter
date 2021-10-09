/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_DATABASE_EXCEPTION_H
#define WINTER_DATABASE_EXCEPTION_H

#include <wintercpp/exception/generic/winter_exception.h>

namespace winter {

class DataException final : public WinterException {
 public:
  explicit DataException(const string &message) noexcept;
};

}  // namespace winter

#endif	// WINTER_DATABASE_EXCEPTION_H
