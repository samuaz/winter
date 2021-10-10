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
namespace winter::exception {

template <typename T>
class WinterException : public std::logic_error {
 public:
  static T
  Create(const std::string &file, const std::string &function_name, int line, const std::string &err, int err_code) {
    auto msg = message(file, function_name, line, err);
    msg << " with err code " << err_code;
    return T(msg.str());
  }

  static T
  Create(const std::string &file, const std::string &function_name, int line, const std::string &err) {
    return T(message(file, function_name, line, err).str());
  }

 protected:
  explicit WinterException<T>(const string &message) noexcept : std::logic_error(message) {}

 private:
  static std::stringstream message(const std::string &file, const std::string &function_name, int line, const std::string &err) {
    std::stringstream ss;
    ss << "Exception " << typeid(T).name() << " " << err << " in file " << file << " function name " << function_name << " on line number " << line;
    return ss;
  }
};
}  // namespace winter::exception

#endif	// WINTER_EXCEPTION_H
