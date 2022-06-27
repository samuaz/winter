#include <wintercpp/exception/generic/winter_internal_exception.h>

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>

namespace winter::data::sql_impl {

    using namespace winter::exception;

    template<typename T>
    T DataTypeResult::as() const {
        std::cout << "preguntando si hay resultado" << std::endl;
        if (res_) {
            std::cout << "si hay resultado imprimiendo" << std::endl;
            return std::get<T>(res_.Value());
        }
        std::cout << "no hay resultado, tirando excepcion" << std::endl;
        throw WinterInternalException::Create(
            __FILE__, __FUNCTION__, __LINE__, res_.message());
    }

    template<typename TResultSet>
    DataTypeResult ResultRow<TResultSet>::operator[](
        const winter::data::sql_impl::Column &column) const {
        auto column_name = column.name();
        return this->operator[](column_name);
    }

    template<typename TResultSet>
    DataTypeResult ResultRow<TResultSet>::operator[](
        const std::string &column_name) const {
        if (rows_.find(column_name) == rows_.end()) {
            std::cout << "no se encontro la columna " << column_name
                      << std::endl;
            return DataTypeResult(
                winter::data::response::Response<DataType>::Error(
                    "value for column " + column_name + " not found"));
        } else {
            std::cout << "encontrada la columna " << column_name << std::endl;
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
    void ResultRow<TResultSet>::AddRow(const std::string &name,
                                       const std::optional<DataType> &sqlType) {
        rows_.insert(std::pair(name, sqlType));
    }

    template<typename TResultSet>
    void ResultRow<TResultSet>::AddRow(std::string name) {
        rows_.insert(std::pair(name, std::nullopt));
    }

}  // namespace winter::data::sql_impl
