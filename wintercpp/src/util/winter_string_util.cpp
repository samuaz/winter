//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2020-01-30.
//

#include <wintercpp/util/winter_string_util.h>

#include <locale>

std::string
winter::util::string::replace(
    std::string &str,
    const std::string &from,
    const std::string &to) {
  size_t start_pos = str.find(from);
  if (start_pos != std::string::npos) {
    str.replace(start_pos, from.length(), to);
  }
  return str;
}

std::string
winter::util::string::replace_value(
    std::string str,
    const std::string &from,
    const std::string &to) {
  size_t start_pos = str.find(from);
  if (start_pos != std::string::npos) {
    str.replace(start_pos, from.length(), to);
  }
  return str;
}

void winter::util::string::strip_unicode(std::string &str) {
  str.erase(
      remove_if(str.begin(), str.end(), [](char c) -> bool {
	return !(c >= 0 && c < 128);
      }),
      str.end());

  str.erase(
      std::remove_if(
	  str.begin(),
	  str.end(),
	  [l = std::locale{}](auto x) {
	    return std::isspace(x, l);
	  }),
      str.end());
}
