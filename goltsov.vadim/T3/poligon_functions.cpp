#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "poligon_functions.hpp"

namespace goltsov
{
  void area(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons)
  {
    std::string parametr;
    is >> parametr;
    if (isdigit(parametr[0]))
    {
      unsigned long long count_vertexes = std::stoull(parametr);
      std::vector< Polygon > vert_p;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (vert_p), CountVertexesPredicate {count_vertexes});
      std::vector< double > areas;
      std::transform(vert_p.begin(), vert_p.end(), areas, AreaPolygon {});
      os << std::accumulate(areas.begin(), areas.end(), 0) << '\n';
      return;
    }
    else if (parametr == "EVEN")
    {
      std::vector< Polygon > even_v;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (even_v), EvenPredicate {});
      std::vector< double > areas;
      std::transform(even_v.begin(), even_v.end(), areas, AreaPolygon {});
      os << std::accumulate(areas.begin(), areas.end(), 0) << '\n';
      return;
    }
    else if (parametr == "ODD")
    {
      std::vector< Polygon > odd_v;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (odd_v), OddPredicate {});
      std::vector< double > areas;
      std::transform(odd_v.begin(), odd_v.end(), areas, AreaPolygon {});
      os << std::accumulate(areas.begin(), areas.end(), 0) << '\n';
      return;
    }
    else if (parametr == "MEAN")
    {
      std::vector< double > areas;
      std::transform(all_polygons.begin(), all_polygons.end(), areas, AreaPolygon {});
      os << std::accumulate(areas.begin(), areas.end(), 0) / (static_cast< double >(all_polygons.size())) << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  void max(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons)
  {
    std::string parametr;
    is >> parametr;
    if (parametr == "AREA")
    {
      std::vector< double > areas;
      std::transform(all_polygons.begin(), all_polygons.end(), areas, AreaPolygon {});
      os << (* std::max_element(areas.begin(), areas.end())) << '\n';
      return;
    }
    else if (parametr == "VERTEXES")
    {
      std::vector< size_t > counts_vertexes;
      std::transform(all_polygons.begin(), all_polygons.end(), counts_vertexes, CountVertexes {});
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
    std::string parametr;
    is >> parametr;
    if (parametr == "AREA")
    {
      std::vector< double > areas;
      std::transform(all_polygons.begin(), all_polygons.end(), areas, AreaPolygon {});
      os << * std::min_element(areas.begin(), areas.end()) << '\n';
      return;
    }
    else if (parametr == "VERTEXES")
    {
      std::vector< size_t > counts_vertexes;
      std::transform(all_polygons.begin(), all_polygons.end(), counts_vertexes, CountVertexes {});
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
    std::string parametr;
    is >> parametr;
    if (isdigit(parametr[0]))
    {
      unsigned long long count_vertexes = std::stoull(parametr);
      std::vector< Polygon > vert_p;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (vert_p), CountVertexesPredicate {count_vertexes});
      os << vert_p.size() << '\n';
      return;
    }
    else if (parametr == "EVEN")
    {
      std::vector< Polygon > even_v;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (even_v), EvenPredicate {});
      os << even_v.size() << '\n';
      return;
    }
    else if (parametr == "ODD")
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
    std::vector< size_t > now_max (all_polygons.size());
    Polygon p;
    is >> p;
    std::transform(all_polygons.begin(), all_polygons.end(), now_max.begin(), NowMax {0, p});
    os << * std::max_element(now_max.begin(), now_max.end()) << '\n';
    return;
  }

  void inframe(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons)
  {
    std::vector< int > min_x_v (all_polygons.size());
    std::vector< int > max_x_v (all_polygons.size());
    std::transform(all_polygons.begin(), all_polygons.end(), min_x_v.begin(), GetMinX {});
    std::transform(all_polygons.begin(), all_polygons.end(), max_x_v.begin(), GetMaxX {});
    std::vector< int > min_y_v (all_polygons.size());
    std::vector< int > max_y_v (all_polygons.size());
    std::transform(all_polygons.begin(), all_polygons.end(), min_y_v.begin(), GetMinY {});
    std::transform(all_polygons.begin(), all_polygons.end(), max_y_v.begin(), GetMaxY {});
    Polygon p;
    is >> p;
    int minY = GetMinY {} (p);
    int maxY = GetMaxY {} (p);
    int minX = GetMinX {} (p);
    int maxX = GetMaxX {} (p);
    if ((* std::min_element(min_x_v.begin(), min_x_v.end())) > minX
        && (* std::min_element(min_y_v.begin(), min_y_v.end())) > minY
        && (* std::max_element(max_x_v.begin(), max_x_v.end())) < maxX
        && (* std::min_element(max_y_v.begin(), max_y_v.end())) < maxY)
    {
      os << "<TRUE>";
      return;
    }
    else
    {
      os << "<FALSE>";
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
    static size_t i = 0;
    const Point& p2 = points[(i + 1) % points.size()];
    double result = p1.x * p2.y - p2.x * p1.y;
    ++i;
    return result;
  }

  double AreaPolygon::operator()(const Polygon& p)
  {
    std::vector< double > temp_areas(p.points.size());
    std::transform(p.points.begin(), p.points.end(), temp_areas.begin(), AreasTriangleOfPolygon {p.points});
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
    std::vector< int > all_x (p.points.size());
    std::transform(p.points.begin(), p.points.end(), all_x, GetX {});
    return * std::min_element(all_x.begin(), all_x.end());
  }

  int GetMaxX::operator()(const Polygon& p)
  {
    std::vector< int > all_x (p.points.size());
    std::transform(p.points.begin(), p.points.end(), all_x, GetX {});
    return * std::max_element(all_x.begin(), all_x.end());
  }

  int GetMinY::operator()(const Polygon& p)
  {
    std::vector< int > all_y (p.points.size());
    std::transform(p.points.begin(), p.points.end(), all_y, GetY {});
    return * std::min_element(all_y.begin(), all_y.end());
  }

  int GetMaxY::operator()(const Polygon& p)
  {
    std::vector< int > all_y (p.points.size());
    std::transform(p.points.begin(), p.points.end(), all_y, GetY {});
    return * std::max_element(all_y.begin(), all_y.end());
  }
}
