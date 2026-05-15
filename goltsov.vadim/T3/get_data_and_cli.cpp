#include "get_data_and_cli.hpp"
#include <map>
#include <limits>
#include "polygon_functions.hpp"

namespace goltsov
{
  void readData(std::istream& is, std::vector< goltsov::Polygon >& all_polygons)
  {
    if (is.eof())
    {
      return;
    }
    goltsov::Polygon p;
    if (is >> p)
    {
      all_polygons.push_back(p);
      readData(is, all_polygons);
      return;
    }
    if (is.eof())
    {
      return;
    }
    is.clear();
    std::string garbage;
    if (is >> garbage)
    {
      readData(is, all_polygons);
    }
  }

  std::vector< goltsov::Polygon >* command::all_polygons = nullptr;

  std::istream& operator>>(std::istream& is, command&)
  {
    std::string name_command;
    is >> name_command;
    if (!is)
    {
      return is;
    }
    static std::map< std::string, void (*)(std::istream&, std::ostream&,
      const std::vector< goltsov::Polygon >&) > commands;
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
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return is;
  }
}
