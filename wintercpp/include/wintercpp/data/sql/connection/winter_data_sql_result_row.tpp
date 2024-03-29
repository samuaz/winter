#include <wintercpp/exception/generic/winter_internal_exception.h>

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "wintercpp/data/sql/field/winter_data_sql_field_type.h"
//#include "winter_data_sql_result_row.h"

namespace winter::data::sql_impl {

    using namespace winter::exception;

    template<typename T>
    T DataTypeResult::as() const {
        try {
            if (res_) {
                return std::get<T>(res_.Value());
            }
            throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, res_.message());
        } catch (const std::bad_variant_access &ex) {
            std::string message = "wrong return type for T " + std::string(typeid(T).name()) + " error is " + ex.what();
            throw WinterInternalException::Create(__FILE__, __FUNCTION__, __LINE__, message);
        }
    }

    template<typename TResultSet>
    DataTypeResult ResultRow<TResultSet>::operator[](
        const winter::data::sql_impl::Column &column) const {
        auto         column_name = column.name();
        return this->operator[](column_name);
    }

    template<typename TResultSet>
    DataTypeResult ResultRow<TResultSet>::operator[](
        const std::string &column_name) const {
        if (rows_.find(column_name) == rows_.end()) {
            return DataTypeResult(
                winter::data::response::Response<DataType>::Error(
                    "value for column " + column_name + " not found"));
        } else {
            return DataTypeResult(
                winter::data::response::Response<DataType>::Success(
                    rows_.at(column_name)));
        }
    }

    template<typename TResultSet>
    template<typename T>
    winter::data::response::Response<T> ResultRow<TResultSet>::Value(
        const winter::data::sql_impl::Column &column) const {
        auto column_name = column.name();
        return Value(column_name);
    }

    template<typename TResultSet>
    template<typename T>
    winter::data::response::Response<T> ResultRow<TResultSet>::Value(
        const std::string &column_name) const {
        return this[column_name].template as<T>();
    }

    template<typename TResultSet>
    const Rows &ResultRow<TResultSet>::rows() const {
        return rows_;
    }

    template<typename TResultSet>
    const Rows &ResultRow<TResultSet>::set_rows(const Rows &rows) {
        return rows_ = rows;
    }

    template<typename TResultSet>
    void ResultRow<TResultSet>::AddRow(const std::string             &name,
                                       const std::optional<DataType> &sqlType) {
        rows_.insert(std::pair(name, sqlType));
    }

    template<typename TResultSet>
    void ResultRow<TResultSet>::AddRow(std::string name) {
        rows_.insert(std::pair(name, std::nullopt));
    }

}  // namespace winter::data::sql_impl
