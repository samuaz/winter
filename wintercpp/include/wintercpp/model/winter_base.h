/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef USER_BASE_H
#define USER_BASE_H

#include <wintercpp/util/winter_date.h>

#include <ctime>
#include <string>

/**
 * @class Base
 * base entity class
 */

namespace winter {

class Base {
 public:
  Base();
  const std::string &id() const;

  void id(const std::string &id);

  const Date &creationDate() const;

  void creationDate(const Date &creationDate);

  const Date &modificationDate() const;

  void setModificationDate(const Date &modificationDate);

  bool operator==(const Base &rhs) const;

  bool operator!=(const Base &rhs) const;

  bool operator<(const Base &rhs) const;

  bool operator>(const Base &rhs) const;

  bool operator<=(const Base &rhs) const;

  bool operator>=(const Base &rhs) const;

  virtual bool equals(Base *ref) const = 0;

  virtual ~Base();

  explicit Base(std::string id);

 protected:
  std::string _id;
  Date _creationDate;
  Date _modificationDate;
};
}  // namespace winter

#endif	// USER_BASE_H
