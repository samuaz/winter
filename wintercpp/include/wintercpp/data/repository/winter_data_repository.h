//
// Created by Samuel Azcona on 27/03/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_REPOSITORY_H
#define WINTERCPP_WINTER_DATA_SQL_REPOSITORY_H

#include <wintercpp/data/response/winter_data_response.h>
#include <wintercpp/data/winter_data_pageable.h>

#include <memory>
#include <string>
#include <vector>

namespace winter::data {

using namespace winter::data::response;

template <typename TEntityClass, typename TIDType, typename TResultSetType>
class Repository {
 public:
  virtual Response<TEntityClass> FindById(TIDType id) = 0;

  virtual Pageable<TEntityClass>
  Page(int page_size, int page_number, const std::string &order_by) = 0;

  virtual int Count() = 0;

 protected:
  virtual Response<TEntityClass> Save(const TEntityClass &entity) = 0;

  virtual Response<TEntityClass> Generate(const TResultSetType &) = 0;

  virtual std::optional<TEntityClass> CreateEntity(const TResultSetType &) = 0;

  virtual Response<TEntityClass> Single(const TResultSetType &) = 0;

  virtual std::vector<TEntityClass> All(const TResultSetType &) = 0;
};

}  // namespace winter::data

#endif	// WINTERCPP_WINTER_DATA_SQL_REPOSITORY_H
