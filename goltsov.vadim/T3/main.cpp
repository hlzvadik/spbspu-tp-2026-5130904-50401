#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "structs.hpp"
#include "polygon_functions.hpp"
#include "get_data_and_cli.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    return 1;
  }
  std::fstream f_is (argv[1]);
  std::vector< goltsov::Polygon > all_polygons;
  readData(f_is, all_polygons);

  goltsov::command::all_polygons = &all_polygons;

  std::vector< goltsov::command > c;
  std::copy(std::istream_iterator< goltsov::command > {std::cin}, std::istream_iterator< goltsov::command > {},
    std::back_inserter(c));

  return 0;
}
