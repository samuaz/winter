//#include <wintercpp/template/winter_connection_pool_singleton_template.h>

namespace winter::templates {

using namespace winter::exception;

template <
    typename TImplementation,
    typename TConnectionType,
    typename TConnectionConfig>
SinglePool<TImplementation, TConnectionType, TConnectionConfig> &
SinglePool<TImplementation, TConnectionType, TConnectionConfig>::Instance() {
  if (instance_ == nullptr) {
    throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, "first need to initialize the pool using the init fun");
    return *instance_;
  }

  template <
      typename TImplementation,
      typename TConnectionType,
      typename TConnectionConfig>
  SinglePool<TImplementation, TConnectionType, TConnectionConfig> &
  SinglePool<TImplementation, TConnectionType, TConnectionConfig>::Init(
      const winter::descriptor::PoolDescriptor &pool_descriptor,
      const std::optional<TConnectionConfig> &connection_config) {
    std::call_once(m_once_, [&]() {
      std::cout << "starting: " << typeid(SinglePool).name() << "\n";
      instance_.reset(new TImplementation(pool_descriptor, connection_config));
    });
    instance_->InitPool();
    return *instance_;
  };

  template <
      typename TImplementation,
      typename TConnectionType,
      typename TConnectionConfig>
  std::shared_ptr<TConnectionType>
  SinglePool<TImplementation, TConnectionType, TConnectionConfig>::Connection() {
    return Instance().Conn();
  };

  template <
      typename TImplementation,
      typename TConnectionType,
      typename TConnectionConfig>
  SinglePool<TImplementation, TConnectionType, TConnectionConfig>::SinglePool(
      winter::descriptor::PoolDescriptor pool_descriptor,
      std::optional<TConnectionConfig> connection_config) : winter::templates::ConnectionPool<TConnectionType>(std::move(pool_descriptor)),
							    connection_config_(std::move(connection_config)){};

}  // namespace winter::templates
