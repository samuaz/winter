/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_SQL_EXCEPTION
#define WINTER_SQL_EXCEPTION

#include <wintercpp/exception/generic/winter_exception.h>

namespace winter::data::sql::exception {

class SqlException final : public virtual WinterException {
 public:
  explicit SqlException(const string &message) noexcept;
};

}  // namespace winter::data::sql::exception

#endif /* WINTER_SQL_EXCEPTION */
