/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/exception/database/winter_database_exception.h>
using namespace winter::exception;

DataException::DataException(const string &message) noexcept :
    WinterExceptionTemplate<DataException>(message) {}