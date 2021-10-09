//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-20.
//

#ifndef WINTERCPP_WINTER_CONNECTION_TEMPLATE_H
#define WINTERCPP_WINTER_CONNECTION_TEMPLATE_H

#include <wintercpp/template/winter_connection_pool_template.h>
#include <wintercpp/util/winter_random.h>

#include <memory>
#include <mutex>
#include <string>

namespace winter::templates {

template <typename TConnectionImpl, typename TConnectionType>
class Connection {
 public:
  explicit Connection(TConnectionType *conn) : id_(winter::random::generateHex(10)),
					       conn_(conn) {}

  constexpr const std::string &
  id() const {
    return id_;
  }

  constexpr TConnectionType &
  conn() const {
    return *conn_;
  }

  bool
  operator==(const TConnectionImpl &rhs) const {
    return id_ == rhs.id_;
  }

  bool
  operator!=(const TConnectionImpl &rhs) const {
    return !(rhs == *this);
  }

 protected:
  std::string id_;
  std::unique_ptr<TConnectionType> conn_;
  std::recursive_mutex conn_mtx_{};
};

template <typename ConnectionImpl, typename ConnectionType>
struct MatchConn {
  explicit MatchConn(const std::string &id) : id_(id) {}

  bool
  operator()(
      const Connection<ConnectionImpl, ConnectionType> &obj) const {
    return obj.id_ == id_;
  }

 private:
  const std::string &id_;
};
}  // namespace winter::templates

#endif	// WINTERCPP_WINTER_CONNECTION_TEMPLATE_H
