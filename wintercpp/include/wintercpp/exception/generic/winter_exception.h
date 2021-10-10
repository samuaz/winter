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

  template<typename T>
  static T
  Create(const std::string &file, const std::string &function_name, int line, const std::string &err, int err_code) {    
    auto msg = message<T>(file, function_name, line, err);
    msg << " with err code " << err_code;
    return T(msg.str());
  }

  template<typename T>
  static T
  Create(const std::string &file, const std::string &function_name, int line, const std::string &err) {  
    return T(message<T>(file, function_name, line, err).str());
  }

  private:
  template<typename T>
  static std::stringstream message(const std::string &file, const std::string &function_name, int line, const std::string &err) {
        std::stringstream ss;
        ss << "Exception " << typeid(T).name() << " " << err << " in file " << file << " function name " << function_name << " on line number " << line;
        return ss;
  }
};
}  // namespace winter

#endif	// WINTER_EXCEPTION_H
