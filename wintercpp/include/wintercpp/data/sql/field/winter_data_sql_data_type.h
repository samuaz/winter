#ifndef WINTER_DATA_SQL_DATA_TYPE
#define WINTER_DATA_SQL_DATA_TYPE

#include <map>
#include <optional>
#include <string>
#include <variant>

namespace winter::data::sql_impl {
    typedef std::variant<char,
                         short,
                         int,
                         long int,
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
