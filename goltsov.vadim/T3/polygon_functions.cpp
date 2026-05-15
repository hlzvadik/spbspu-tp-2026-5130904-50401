#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <ios>
#include <iomanip>
#include "polygon_functions.hpp"

namespace goltsov
{
  void area(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons)
  {
    std::string parameter;
    is >> parameter;
    if (!is)
    {
      if (is.eof())
      {
        is.clear();
        is.setstate(std::ios_base::eofbit);
      }
      else
      {
        is.clear();
      }
      throw std::runtime_error("<INVALID COMMAND>");
    }
    if (isdigit(parameter[0]))
    {
      unsigned long long count_vertexes = std::stoull(parameter);
      if (count_vertexes < 3)
      {
        throw std::runtime_error("<INVALID COMMAND>");
      }
      std::vector< Polygon > vert_p;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (vert_p),
        CountVertexesPredicate {count_vertexes});
      std::vector< double > areas;
      std::transform(vert_p.begin(), vert_p.end(), std::back_inserter(areas), AreaPolygon {});
      os << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
      return;
    }
    else if (parameter == "EVEN")
    {
      std::vector< Polygon > even_v;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (even_v), EvenPredicate {});
      std::vector< double > areas;
      std::transform(even_v.begin(), even_v.end(), std::back_inserter(areas), AreaPolygon {});
      os << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
      return;
    }
    else if (parameter == "ODD")
    {
      std::vector< Polygon > odd_v;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (odd_v), OddPredicate {});
      std::vector< double > areas;
      std::transform(odd_v.begin(), odd_v.end(), std::back_inserter(areas), AreaPolygon {});
      os << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
      return;
    }
    else if (parameter == "MEAN")
    {
      if (all_polygons.size() == 0)
      {
        throw std::runtime_error("<INVALID COMMAND>");
      }
      std::vector< double > areas;
      std::transform(all_polygons.begin(), all_polygons.end(), std::back_inserter(areas), AreaPolygon {});
      os << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0)
        / (static_cast< double >(all_polygons.size())) << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  void max(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons)
  {
    if (all_polygons.size() == 0)
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
    std::string parameter;
    is >> parameter;
    if (!is)
    {
      if (is.eof())
      {
        is.clear();
        is.setstate(std::ios_base::eofbit);
      }
      else
      {
        is.clear();
      }
      throw std::runtime_error("<INVALID COMMAND>");
    }
    if (parameter == "AREA")
    {
      std::vector< double > areas;
      std::transform(all_polygons.begin(), all_polygons.end(), std::back_inserter(areas), AreaPolygon {});
      os << std::fixed << std::setprecision(1) << (* std::max_element(areas.begin(), areas.end())) << '\n';
      return;
    }
    else if (parameter == "VERTEXES")
    {
      std::vector< size_t > counts_vertexes;
      std::transform(all_polygons.begin(), all_polygons.end(),
        std::back_inserter(counts_vertexes), CountVertexes {});
      os << (* std::max_element(counts_vertexes.begin(), counts_vertexes.end())) << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  void min(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons)
  {
    if (all_polygons.size() == 0)
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
    std::string parameter;
    is >> parameter;
    if (!is)
    {
      if (is.eof())
      {
        is.clear();
        is.setstate(std::ios_base::eofbit);
      }
      else
      {
        is.clear();
      }
      throw std::runtime_error("<INVALID COMMAND>");
    }
    if (parameter == "AREA")
    {
      std::vector< double > areas;
      std::transform(all_polygons.begin(), all_polygons.end(), std::back_inserter(areas), AreaPolygon {});
      os << std::fixed << std::setprecision(1) << * std::min_element(areas.begin(), areas.end()) << '\n';
      return;
    }
    else if (parameter == "VERTEXES")
    {
      std::vector< size_t > counts_vertexes;
      std::transform(all_polygons.begin(), all_polygons.end(),
        std::back_inserter(counts_vertexes), CountVertexes {});
      os << * std::min_element(counts_vertexes.begin(), counts_vertexes.end()) << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  void count(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons)
  {
    std::string parameter;
    is >> parameter;
    if (!is)
    {
      if (is.eof())
      {
        is.clear();
        is.setstate(std::ios_base::eofbit);
      }
      else
      {
        is.clear();
      }
      throw std::runtime_error("<INVALID COMMAND>");
    }
    if (isdigit(parameter[0]))
    {
      unsigned long long count_vertexes = std::stoull(parameter);
      if (count_vertexes < 3)
      {
        throw std::runtime_error("<INVALID COMMAND>");
      }
      std::vector< Polygon > vert_p;
      std::copy_if(all_polygons.begin(), all_polygons.end(),
        std::back_inserter (vert_p), CountVertexesPredicate {count_vertexes});
      os << vert_p.size() << '\n';
      return;
    }
    else if (parameter == "EVEN")
    {
      std::vector< Polygon > even_v;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (even_v), EvenPredicate {});
      os << even_v.size() << '\n';
      return;
    }
    else if (parameter == "ODD")
    {
      std::vector< Polygon > odd_v;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (odd_v), OddPredicate {});
      os << odd_v.size() << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  void maxseq(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons)
  {
    std::vector< size_t > now_max;
    Polygon p;
    is >> p;
    if (!is)
    {
      if (is.eof())
      {
        is.clear();
        is.setstate(std::ios_base::eofbit);
      }
      else
      {
        is.clear();
      }
      throw std::runtime_error("<INVALID COMMAND>");
    }
    if (is.peek() != '\n')
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
    std::transform(all_polygons.begin(), all_polygons.end(), std::back_inserter(now_max), NowMax {0, p});
    os << * std::max_element(now_max.begin(), now_max.end()) << '\n';
    return;
  }

  void inframe(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons)
  {
    Polygon p;
    is >> p;
    if (!is)
    {
      if (is.eof())
      {
        is.clear();
        is.setstate(std::ios_base::eofbit);
      }
      else
      {
        is.clear();
      }
      throw std::runtime_error("<INVALID COMMAND>");
    }
    if (is.peek() != '\n')
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
    std::vector< int > min_x_v;
    std::vector< int > max_x_v;
    std::transform(all_polygons.begin(), all_polygons.end(), std::back_inserter(min_x_v), GetMinX {});
    std::transform(all_polygons.begin(), all_polygons.end(), std::back_inserter(max_x_v), GetMaxX {});
    std::vector< int > min_y_v;
    std::vector< int > max_y_v;
    std::transform(all_polygons.begin(), all_polygons.end(), std::back_inserter(min_y_v), GetMinY {});
    std::transform(all_polygons.begin(), all_polygons.end(), std::back_inserter(max_y_v), GetMaxY {});
    int minY = GetMinY {} (p);
    int maxY = GetMaxY {} (p);
    int minX = GetMinX {} (p);
    int maxX = GetMaxX {} (p);
    if ((* std::min_element(min_x_v.begin(), min_x_v.end())) <= minX
        && (* std::min_element(min_y_v.begin(), min_y_v.end())) <= minY
        && (* std::max_element(max_x_v.begin(), max_x_v.end())) >= maxX
        && (* std::max_element(max_y_v.begin(), max_y_v.end())) >= maxY)
    {
      os << "<TRUE>\n";
      return;
    }
    else
    {
      os << "<FALSE>\n";
      return;
    }
  }

  bool EvenPredicate::operator()(const Polygon& p)
  {
    return p.points.size() % 2 == 0;
  }

  bool OddPredicate::operator()(const Polygon& p)
  {
    return p.points.size() % 2 == 1;
  }

  bool CountVertexesPredicate::operator()(const Polygon& p)
  {
    return p.points.size() == count_vertexes;
  }

  size_t CountVertexes::operator()(const Polygon& p)
  {
    return p.points.size();
  }

  double AreasTriangleOfPolygon::operator()(const Point& p1)
  {
    const Point& p2 = points[(i + 1) % points.size()];
    double result = p1.x * p2.y - p2.x * p1.y;
    ++i;
    return result;
  }

  double AreaPolygon::operator()(const Polygon& p)
  {
    std::vector< double > temp_areas;
    std::transform(p.points.begin(), p.points.end(),
      std::back_inserter(temp_areas), AreasTriangleOfPolygon {p.points, 0});
    double sum = std::accumulate(temp_areas.begin(), temp_areas.end(), 0.0);
    return std::abs(sum) / 2.0;
  }

  size_t NowMax::operator()(const Polygon& p)
  {
    if (templ.points == p.points)
    {
      now += 1;
    }
    else
    {
      now = 0;
    }
    return now;
  }

  int GetX::operator()(const Point& p)
  {
    return p.x;
  }

  int GetY::operator()(const Point& p)
  {
    return p.y;
  }

  int GetMinX::operator()(const Polygon& p)
  {
    std::vector< int > all_x;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(all_x), GetX {});
    return * std::min_element(all_x.begin(), all_x.end());
  }

  int GetMaxX::operator()(const Polygon& p)
  {
    std::vector< int > all_x;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(all_x), GetX {});
    return * std::max_element(all_x.begin(), all_x.end());
  }

  int GetMinY::operator()(const Polygon& p)
  {
    std::vector< int > all_y;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(all_y), GetY {});
    return * std::min_element(all_y.begin(), all_y.end());
  }

  int GetMaxY::operator()(const Polygon& p)
  {
    std::vector< int > all_y;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(all_y), GetY {});
    return * std::max_element(all_y.begin(), all_y.end());
  }
}
