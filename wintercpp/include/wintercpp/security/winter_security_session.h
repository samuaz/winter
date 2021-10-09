#ifndef __WINTER_SECURITY_SESSION_H__
#define __WINTER_SECURITY_SESSION_H__

#include <wintercpp/security/winter_security_user_info.h>

namespace winter::security {
class Session {
 public:
  virtual void CreateSession(const UserSecurityInfo &user_security_info) const = 0;

  virtual void RemoveSession(const UserSecurityInfo &user_security_info) const = 0;

  virtual bool IsValid(const UserSecurityInfo &user_security_info) const = 0;
};
}  // namespace winter::security
#endif	// __WINTER_SECURITY_SESSION_H__