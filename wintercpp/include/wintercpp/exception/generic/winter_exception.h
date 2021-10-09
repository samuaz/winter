/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef WINTER_EXCEPTION_H
#define WINTER_EXCEPTION_H

#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;
namespace winter {

class WinterException : public std::logic_error {
 public:
  explicit WinterException(const string &message) noexcept;

  static WinterException
  Create(const std::string &file, const std::string &function_name, int line, const std::string &err, int err_code) {
    std::stringstream ss;
    ss << "Exception " << err << " in file " << file << " function " << function_name << " on line " << line << " with err code " << err_code;
    return WinterException(ss.str());
  }

  static WinterException
  Create(const std::string &file, const std::string &function_name, int line, const std::string &err) {
    std::stringstream ss;
    ss << "Exception " << err << " in file " << file << " function " << function_name << " on line " << line;
    return WinterException(ss.str());
  }
};
}  // namespace winter

#endif	// WINTER_EXCEPTION_H
