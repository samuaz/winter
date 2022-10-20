//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2020-01-30.
//

#include <wintercpp/util/winter_pool_descriptor.h>

using namespace winter::descriptor;

/* PoolDescriptor::PoolDescriptor() : _name("GENERIC_POOL_DESCRIPTOR"),
                                   _initialPoolSize(5),
                                   _maxPoolSize(10),
                                   _poolTimeout(60),
                                   _usePool(true) {} */

PoolDescriptor::PoolDescriptor(std::string  name,
                               unsigned int initialPoolSize,
                               unsigned int maxPoolSize,
                               unsigned int waitTimeMs,
                               unsigned int intents,
                               bool         usePool) :
    _name(std::move(name)),
    _initialPoolSize(initialPoolSize), _maxPoolSize(maxPoolSize),
    _waitTimeMs(waitTimeMs), _intents(intents) ,_usePool(usePool) {}

const std::string& PoolDescriptor::name() const {
    return _name;
}

unsigned int PoolDescriptor::initialPoolSize() const {
    return _initialPoolSize;
}

unsigned int PoolDescriptor::maxPoolSize() const {
    return _maxPoolSize;
}

unsigned int PoolDescriptor::waitTimeMs() const {
    return _waitTimeMs;
}

unsigned int PoolDescriptor::intents() const {
    return _intents;
}

bool PoolDescriptor::usePool() const {
    return _usePool;
}
