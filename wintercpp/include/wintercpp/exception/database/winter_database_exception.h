/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_DATABASE_EXCEPTION_H
#define WINTER_DATABASE_EXCEPTION_H

#include <wintercpp/exception/generic/winter_exception.h>

namespace winter::exception {

class DataException final : public WinterExceptionTemplate<DataException> {
 public:
  explicit DataException(const string &message) noexcept;
};

}  // namespace winter::exception

#endif	// WINTER_DATABASE_EXCEPTION_H
