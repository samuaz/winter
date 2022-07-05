//#include "winter_data_sql_abstract_field.h"

namespace winter::data::sql_impl {

    template<typename T>
    const T& Field<T>::value() const {
        return value_;
    }

    template<typename T>
    const FieldType& Field<T>::type() const {
        return type_;
    }

    template<typename T>
    const std::string& Field<T>::name() const {
        return name_;
    }

    template<typename T>
    void Field<T>::value(T value) {
        value_ = value;
    }

}  // namespace winter::data::sql_impl
