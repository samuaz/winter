//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_FIELD_TYPE
#define WINTER_DATA_SQL_FIELD_TYPE

#include <iostream>
#include <optional>
#include <string>

#include "wintercpp/data/sql/field/winter_data_sql_data_type.h"
#include "wintercpp/exception/generic/winter_internal_exception.h"

namespace winter::data::sql_impl {

    struct Date {
        std::string value;
    };

    struct DateTime {
        std::string value;
    };

    enum class FieldType : int {
        kNull,
        kUchar,
        kSchar,
        kChar,
        kString,
        kUshort,
        KShort,
        KUint,
        kInt,
        kBigInt,
        kUlong,
        kLong,
        KDecimal,
        kFloat,
        kDouble,
        kBoolean,
        kDate,
        kDateTime,
        kTimeStamp,
        kEnum,
        kBlob
    };

    template<typename T>
    struct TypeField {
        static FieldType Get();
    };

    template<>
    struct TypeField<uint8_t> {
        static FieldType Get();
    };

    template<>
    struct TypeField<int8_t> {
        static FieldType Get();
    };

    template<>
    struct TypeField<uint16_t> {
        static FieldType Get();
    };

    template<>
    struct TypeField<int16_t> {
        static FieldType Get();
    };

    template<>
    struct TypeField<uint32_t> {
        static FieldType Get();
    };

    template<>
    struct TypeField<int32_t> {
        static FieldType Get();
    };

    template<>
    struct TypeField<uint64_t> {
        static FieldType Get();
    };

    template<>
    struct TypeField<int64_t> {
        static FieldType Get();
    };

    template<>
    struct TypeField<long> {
        static FieldType Get();
    };

    template<>
    struct TypeField<double> {
        static FieldType Get();
    };

    template<>
    struct TypeField<float> {
        static FieldType Get();
    };

    template<>
    struct TypeField<bool> {
        static FieldType Get();
    };

    template<>
    struct TypeField<std::string> {
        static FieldType Get();
    };

    template<>
    struct TypeField<char> {
        static FieldType Get();
    };

    template<>
    struct TypeField<char *> {
        static FieldType Get();
    };

    template<>
    struct TypeField<const char *> {
        static FieldType Get();
    };

    template<>
    struct TypeField<std::istream *> {
        static FieldType Get();
    };

    template<>
    struct TypeField<Date> {
        static FieldType Get();
    };

    template<>
    struct TypeField<DateTime> {
        static FieldType Get();
    };

    template<typename T>
    FieldType GetFieldType() {
        if constexpr (std::is_same_v<T, uint8_t>) {
            return FieldType::kUchar;
        } else if constexpr (std::is_same_v<T, uint16_t>) {
            return FieldType::kUshort;
        } else if constexpr (std::is_same_v<T, uint32_t>) {
            return FieldType::KUint;
        } else if constexpr (std::is_same_v<T, uint64_t>) {
            return FieldType::kBigInt;
        } else if constexpr (std::is_same_v<T, int8_t>) {
            return FieldType::kSchar;
        } else if constexpr (std::is_same_v<T, int16_t>) {
            return FieldType::KShort;
        } else if constexpr (std::is_same_v<T, int32_t>) {
            return FieldType::kInt;
        } else if constexpr (std::is_same_v<T, int64_t>) {
            return FieldType::kLong;
        } else if constexpr (std::is_same_v<T, char>) {
            return FieldType::kChar;
        } else if constexpr (std::is_same_v<T, short>) {
            return FieldType::KShort;
        } else if constexpr (std::is_same_v<T, long>) {
            return FieldType::kLong;
        } else if constexpr (std::is_same_v<T, long double>) {
            return FieldType::KDecimal;
        } else if constexpr (std::is_same_v<T, double>) {
            return FieldType::kDouble;
        } else if constexpr (std::is_same_v<T, float>) {
            return FieldType::kFloat;
        } else if constexpr (std::is_same_v<T, bool>) {
            return FieldType::kBoolean;
        } else if constexpr (std::is_same_v<T, std::string>) {
            return FieldType::kString;
        } else if constexpr (std::is_same_v<T, std::istream *>) {
            return FieldType::kBlob;
        } else if constexpr (std::is_same_v<T, nullptr_t>) {
            return FieldType::kNull;
        } else if constexpr (std::is_same_v<T, std::nullopt_t>) {
            return FieldType::kNull;
        } else {
            std::cout << "Type of T is: " << typeid(T).name() << std::endl;
            throw exception::WinterInternalException("Type not supported");
        }
    }

    inline FieldType GetFieldType(const DataType &var) {
        return std::visit([](const auto &value) {
            using T = std::decay_t<decltype(value)>;
            return GetFieldType<T>();
        }, var);
    }

}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_FIELD_TYPE */
