/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/exception/sql/winter_sql_exception.h>
using namespace winter::exception;

SqlException::SqlException(const string &message) noexcept :
    WinterExceptionTemplate<SqlException>(message) {}