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

class WinterException : public std::logic_error {
 public:
  WinterException(const WinterException &) = delete;
  WinterException &operator=(const WinterException &) = delete;

 protected:
  explicit WinterException(const string &message) noexcept : std::logic_error(message) {}
};

template <typename T>
class WinterExceptionTemplate : public WinterException {
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
  explicit WinterExceptionTemplate<T>(const string &message) noexcept : WinterException(message) {}

 private:
  static std::stringstream message(const std::string &file, const std::string &function_name, int line, const std::string &err) {
    std::stringstream ss;
    ss << "Exception " << typeid(T).name() << " " << err << " in file " << file << " function name " << function_name << " on line number " << line;
    return ss;
  }
};
}  // namespace winter::exception

#endif	// WINTER_EXCEPTION_H
