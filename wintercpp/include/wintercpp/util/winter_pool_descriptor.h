//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2020-01-30.
//

#ifndef WINTERCPP_WINTER_POOL_DESCRIPTOR_H
#define WINTERCPP_WINTER_POOL_DESCRIPTOR_H

#include <string>

namespace winter::descriptor {

class PoolDescriptor {
 public:
  // PoolDescriptor();
  PoolDescriptor(
      std::string name,
      unsigned int initialPoolSize,
      unsigned int maxPoolSize,
      unsigned int poolTimeout,
      bool usePool);

  const std::string &name() const;

  unsigned int initialPoolSize() const;

  unsigned int maxPoolSize() const;

  unsigned int poolTimeout() const;

  bool usePool() const;

 private:
  const std::string _name;
  const unsigned int _initialPoolSize;
  const unsigned int _maxPoolSize;
  const unsigned int _poolTimeout;
  const bool _usePool;
};

}  // namespace winter::descriptor

#endif	// WINTERCPP_WINTER_POOL_DESCRIPTOR_H
