#include <iostream>
#include "structs.hpp"

namespace goltsov
{
  void area(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons);
  void max(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons);
  void min(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons);
  void count(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons);
  void maxseq(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons);
  void inframe(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons);
}