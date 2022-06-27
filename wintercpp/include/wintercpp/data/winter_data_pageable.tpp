//
// Created by Samuel Azcona on 03/09/2020.
//

using namespace winter::data;

template<typename T>
Pageable<T>::Pageable(int page_size, int page_number, int row_total) :
    page_size_(page_size), page_number_(page_number), row_total_(row_total) {}

template<typename T>
Pageable<T>::Pageable(int page_size,
                      int page_number,
                      int row_total,
                      std::vector<T> page_content) :
    page_size_(page_size),
    page_number_(page_number), row_total_(row_total),
    page_content_(std::move(page_content)) {}

template<typename T>
void Pageable<T>::set_page_size(int page_size) {
    page_size_ = page_size;
}

template<typename T>
int Pageable<T>::page_size() const {
    return page_size_;
}

template<typename T>
void Pageable<T>::set_page_number(int page_number) {
    page_number_ = page_number;
}

template<typename T>
int Pageable<T>::page_number() const {
    return page_number_;
}

template<typename T>
int Pageable<T>::page_total() const {
    return (row_total_ + page_size_ - 1) / page_size_;
}

template<typename T>
void Pageable<T>::set_row_total(int row_total) {
    row_total_ = row_total;
}

template<typename T>
int Pageable<T>::row_total() const {
    return row_total_;
}

template<typename T>
const std::vector<T> &Pageable<T>::page_content() const {
    return page_content_;
}

template<typename T>
void Pageable<T>::set_page_content(const std::vector<T> &Page_content) {
    page_content_ = Page_content;
}
template<typename T>
int Pageable<T>::OffSet() const {
    return page_size_ * page_number_;
}
