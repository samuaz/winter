
#include <wintercpp/data/sql/field/winter_data_sql_field.h>

#include <utility>

namespace winter::data::sql_impl {

    const DataType& Field::value() const {
        return value_;
    }

    const FieldType& Field::type() const {
        return type_;
    }

    const std::string& Field::name() const {
        return name_;
    }

    void Field::value(DataType value) {
        value_ = std::move(value);
    }

}  // namespace winter::data::sql_impl
