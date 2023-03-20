#ifndef WINTER_DATA_SQL_DATA_TYPE
#define WINTER_DATA_SQL_DATA_TYPE

#include <map>
#include <optional>
#include <string>
#include <variant>

namespace winter::data::sql_impl {
    typedef std::variant<uint8_t,
                         uint16_t,
                         uint32_t,
                         uint64_t,
                         int8_t,
                         int16_t,
                         int32_t,
                         int64_t,
                         char,
                         short,
                         long long,
                         long,
                         long double,
                         double,
                         float,
                         bool,
                         std::string,
                         std::istream *>
                                                            DataType;
    typedef std::map<std::string, std::optional<DataType> > Rows;
}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_DATA_TYPE */
