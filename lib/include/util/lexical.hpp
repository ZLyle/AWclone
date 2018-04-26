#ifndef UTIL_LEXICAL_HPP_
#define UTIL_LEXICAL_HPP_

#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <regex>

namespace util {

template <typename T>
static T lexical_cast(std::string characters) {
  std::stringstream converter;
  converter << characters;

  T to_return;
  converter >> to_return;

  return to_return;
}

static std::string getline_and_strip_comments(std::ifstream& input_stream) {
  std::string to_return;
  std::getline(input_stream >> std::ws, to_return);
  return std::regex_replace(to_return, std::regex(R"(\s*#.*)"), "");
}

}  // namespace util

#endif  // UTIL_LEXICAL_HPP_
