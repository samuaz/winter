//
// Created by samuel on 06/08/19.
//

#ifndef WINTER_CONNECTION_POOL_H
#define WINTER_CONNECTION_POOL_H

#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_pool_descriptor.h>

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

namespace winter::templates {

using namespace winter::descriptor;

template <typename TConnection>
class ConnectionPool {
 public:
  std::shared_ptr<TConnection> Conn();
  void ReleaseConn(TConnection *conn);
  virtual ~ConnectionPool();

 protected:
  explicit ConnectionPool(winter::descriptor::PoolDescriptor pool_descriptor);
  winter::descriptor::PoolDescriptor pool_descriptor_;
  void InitPool();

 private:
  std::recursive_mutex pool_mtx_;
  std::deque<TConnection *> available_connections_;
  std::deque<TConnection *> in_use_connections_;
  void CheckConnections();
  void AddConn(TConnection *conn, bool release = false);
  virtual TConnection *CreateConn() = 0;
};

};  // namespace winter::templates

#include "winter_connection_pool_template.tpp"

#endif	// WINTER_CONNECTION_POOL_H