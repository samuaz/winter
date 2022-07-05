//
// Created by Samuel Azcona on 16/03/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_ID_TYPE_H
#define WINTERCPP_WINTER_DATA_SQL_ID_TYPE_H

#include <any>
#include <string>

namespace winter::data::sql_impl {

    enum class IDType : int {
        STRING,
        INT,
        LONG,
        NONE,
    };

    template<typename T>
    struct TypeId {
        static IDType Get();
    };

    template<>
    struct TypeId<int> {
        static IDType Get();
    };

    template<>
    struct TypeId<long> {
        static IDType Get();
    };

    template<>
    struct TypeId<std::string> {
        static IDType Get();
    };

    template<>
    struct TypeId<void> {
        static IDType Get();
    };

}  // namespace winter::data::sql_impl

#endif  // WINTERCPP_WINTER_DATA_SQL_ID_TYPE_H
