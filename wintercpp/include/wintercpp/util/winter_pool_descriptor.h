//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2020-01-30.
//

#ifndef WINTERCPP_WINTER_POOL_DESCRIPTOR_H
#define WINTERCPP_WINTER_POOL_DESCRIPTOR_H

#include <string>

namespace winter::descriptor {

class PoolDescriptor {
 private:
  std::string _name;
  unsigned int _initialPoolSize;
  unsigned int _maxPoolSize;
  unsigned int _poolTimeout;
  bool _usePool;

 public:
  PoolDescriptor();
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
};

}  // namespace winter::descriptor

#endif	// WINTERCPP_WINTER_POOL_DESCRIPTOR_H
