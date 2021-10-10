//
// Created by samuaz on 5/31/21.
//

#ifndef WINTERCPP_WINTER_CONNECTION_POOL_SINGLETON_TEMPLATE_H
#define WINTERCPP_WINTER_CONNECTION_POOL_SINGLETON_TEMPLATE_H

#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/template/winter_connection_pool_template.h>

#include <memory>
#include <optional>

namespace winter::templates {

template <
    typename TImplementation,
    typename TConnectionType,
    typename TConnectionConfig>
class SinglePool : public winter::templates::ConnectionPool<TConnectionType> {
  friend class ConnectionPool<TConnectionType>;

 public:
  static SinglePool &Instance();

  static SinglePool &Init(
      const winter::descriptor::PoolDescriptor &pool_descriptor,
      const std::optional<TConnectionConfig> &connection_config);

  static std::shared_ptr<TConnectionType> Connection();

  SinglePool(SinglePool const &) = delete;

  SinglePool &operator=(const SinglePool &) = delete;

  SinglePool(SinglePool &&) = delete;

  SinglePool &operator=(SinglePool &&) = delete;

 protected:
  explicit SinglePool(
      winter::descriptor::PoolDescriptor pool_descriptor,
      std::optional<TConnectionConfig> connection_config);

  static inline std::unique_ptr<SinglePool> instance_;

  static inline std::once_flag m_once_;

  std::optional<TConnectionConfig> connection_config_;

 private:
  TConnectionType *CreateConn() override = 0;
};
}  // namespace winter::templates

#include "winter_connection_pool_singleton_template.tpp"

#endif	// WINTERCPP_WINTER_CONNECTION_POOL_SINGLETON_TEMPLATE_H
