/**
 * @author Samuel Azcona
 * @email samuel@theopencompany.dev
 * @create date 2021-06-26 16:52:46
 * @modify date 2021-06-26 16:52:46
 * @desc winter::Data::Pageable
 */

#ifndef __WINTER_DATA_PAGEABLE_H__
#define __WINTER_DATA_PAGEABLE_H__

#include <any>
#include <vector>

namespace winter::data {
/**
 * @brief Pageable class
 *
 * @tparam T represents the data type of the page_content
 */
template <typename T>
class Pageable {
 public:
  /**
     * @brief Construct a new Pageable object
     *
     * @param page_size Number of elements that you want to request in a single Page
     * @param page_number Actual Page number
     * @param row_total Total elements of all pages
     */
  Pageable(int page_size, int page_number, int row_total);

  /**
     * @brief Construct a new Pageable object
     *
     * @param page_size Number of elements that you want to request in a single Page
     * @param page_number Actual Page number
     * @param row_total Total elements of all pages
     * @param page_content vector with the requested content
     */
  Pageable(
      int page_size,
      int page_number,
      int row_total,
      std::vector<T> page_content);

  void set_page_size(int page_size);
  int page_size() const;

  void set_page_number(int page_number);
  int page_number() const;

  int page_total() const;

  void set_row_total(int row_total);
  int row_total() const;

  const std::vector<T> &page_content() const;
  void set_page_content(const std::vector<T> &Page_content);

  int OffSet() const;

 private:
  int page_size_;
  int page_number_;
  int row_total_;
  std::vector<T> page_content_;
};

}  // namespace winter::data

#include "winter_data_pageable.tpp"

#endif	// __WINTER_DATA_PAGEABLE_H__