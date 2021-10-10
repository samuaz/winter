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
#include "wintercpp/exception/generic/winter_exception.h"

namespace winter::templates {

template <typename TConnectionImpl, typename TConnectionType>
class Connection {
 public:
  explicit Connection(TConnectionType *conn): conn_(conn) {}

  Connection(const Connection&) = delete;
  Connection& operator=(const Connection&) = delete;

  constexpr const std::string &
  id() const {
    return id_;
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
  
  constexpr TConnectionType &
  conn() const {
    if(conn_ == nullptr) {
        throw WinterException::Create(__FILE__, __FUNCTION__, __LINE__, "cant connect to database, conn_ is null");
    }
    return *conn_;
  }

  std::recursive_mutex &conn_mtx() {
    return conn_mtx_;
  }

 private:
  const std::string id_ {winter::random::generateHex(10)};
  const std::unique_ptr<TConnectionType> conn_;
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
