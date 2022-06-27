//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2020-01-30.
//

#ifndef WINTERCPP_WINTER_STRING_UTIL_H
#define WINTERCPP_WINTER_STRING_UTIL_H

#include <string>

namespace winter::util::string {

    std::string replace(std::string &str,
                        const std::string &from,
                        const std::string &to);

    std::string replace_value(std::string str,
                              const std::string &from,
                              const std::string &to);

    void strip_unicode(std::string &str);

}  // namespace winter::util::string

#endif  // WINTERCPP_WINTER_STRING_UTIL_H
