#ifndef GET_DATA_AND_CLI_HPP
#define GET_DATA_AND_CLI_HPP
#include <vector>
#include "structs.hpp"
namespace goltsov
{
  struct command
  {
    static std::vector< goltsov::Polygon >* all_polygons;
    command() = default;
  };
  std::istream& operator>>(std::istream& is, command& c);
  void readData(std::istream& is, std::vector< goltsov::Polygon >& all_polygons);
}

#endif