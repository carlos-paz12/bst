#ifndef DEGREE_HPP
#define DEGREE_HPP

#include <cstdint>

namespace ds
{
enum class Degree : std::uint8_t
{
  LEAF,
  UNARY,
  BINARY
};
} // namespace ds

#endif
