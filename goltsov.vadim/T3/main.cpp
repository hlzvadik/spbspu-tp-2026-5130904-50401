#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <ios>
#include <map>
#include "structs.hpp"
#include "polygon_functions.hpp"

void readData(std::istream& is, std::vector< goltsov::Polygon >& all_polygons)
{
  std::copy(std::istream_iterator< goltsov::Polygon > (is), std::istream_iterator< goltsov::Polygon > {}, std::back_inserter(all_polygons));
}

struct command
{
  static std::vector< goltsov::Polygon >* all_polygons;
  command() = default;
};

std::vector< goltsov::Polygon >* command::all_polygons = nullptr;

std::istream& operator>>(std::istream& is, command& c)
{
  std::string name_command;
  is >> name_command;
  static std::map< std::string, void (*)(std::istream&, std::ostream&, const std::vector< goltsov::Polygon >&) > commands;
  commands["AREA"] = & goltsov::area;
  commands["MAX"] = & goltsov::max;
  commands["MIN"] = & goltsov::min;
  commands["COUNT"] = & goltsov::count;
  commands["MAXSEQ"] = & goltsov::maxseq;
  commands["INFRAME"] = & goltsov::inframe;
  try
  {
    commands.at(name_command)(is, std::cout, *command::all_polygons);
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << '\n';
  }
  return is;
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    return 1;
  }
  std::fstream f_is (argv[1]);
  std::vector< goltsov::Polygon > all_polygons;
  readData(f_is, all_polygons);

  command::all_polygons = &all_polygons;

  std::vector< command > c;
  std::copy(std::istream_iterator< command > {std::cin}, std::istream_iterator< command > {}, std::back_inserter(c));

  return 0;
}
