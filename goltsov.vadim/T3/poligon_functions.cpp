#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include "poligon_functions.hpp"

namespace goltsov
{
  template< size_t A >
  struct EvenOddPredicate
  {
    bool operator()(const Polygon& p)
    {
      return p.points.size() % 2 == A;
    }
  };

  struct countVertexesPredicate
  {
    size_t count_vertexes;
    bool operator()(Polygon p)
    {
      return p.points.size() == count_vertexes;
    }
  };

  struct getAreas
  {
    double operator()(const Polygon& p)
    {
      return areaPolygon(p);
    }
  };

  struct getVertexes
  {
    size_t operator()(const Polygon& p)
    {
      return p.points.size();
    }
  };

  struct getAreaPolygon
  {
    std::vector< Point >& points;
    double operator()(const Point& p1)
    {
      static size_t i = 0;
      const Point& p2 = points[(i + 1) % points.size()];
      double result = p1.x * p2.y - p2.x * p1.y;
      ++i;
      return result;
    }
  };

  double areaPolygon(Polygon p)
  {
    std::vector< double > temp_areas(p.points.size());
    getAreaPolygon aeraer {p.points};
    std::transform(p.points.begin(), p.points.end(), temp_areas.begin(), aeraer);
    double sum = std::accumulate(temp_areas.begin(), temp_areas.end(), 0.0);
    return std::abs(sum) / 2.0;
  }

  void area(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons)
  {
    std::string parametr;
    is >> parametr;
    if (isdigit(parametr[0]))
    {
      unsigned long long count_vertexes = std::stoull(parametr);
      std::vector< Polygon > vert_p;
      std::function< bool(Polygon&) > predicate = countVertexesPredicate {count_vertexes};
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (vert_p), predicate);
      std::vector< double > areas;
      getAreas areaer_p;
      std::transform(vert_p.begin(), vert_p.end(), areas, areaer_p);
      os << std::accumulate(areas.begin(), areas.end(), 0) << '\n';
      return;
    }
    else if (parametr == "EVEN")
    {
      std::vector< Polygon > even_v;
      EvenOddPredicate< 0 > predicate;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (even_v), predicate);
      std::vector< double > areas;
      getAreas areaer_p;
      std::transform(even_v.begin(), even_v.end(), areas, areaer_p);
      os << std::accumulate(areas.begin(), areas.end(), 0) << '\n';
      return;
    }
    else if (parametr == "ODD")
    {
      std::vector< Polygon > odd_v;
      EvenOddPredicate< 1 > predicate;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (odd_v), predicate);
      std::vector< double > areas;
      getAreas areaer_p;
      std::transform(odd_v.begin(), odd_v.end(), areas, areaer_p);
      os << std::accumulate(areas.begin(), areas.end(), 0) << '\n';
      return;
    }
    else if (parametr == "MEAN")
    {
      std::vector< double > areas;
      getAreas areaer_p;
      std::transform(all_polygons.begin(), all_polygons.end(), areas, areaer_p);
      os << std::accumulate(areas.begin(), areas.end(), 0) / (static_cast< double >(all_polygons.size())) << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  void max(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons)
  {
    std::string parametr;
    is >> parametr;
    if (parametr == "AREA")
    {
      std::vector< double > areas;
      getAreas areaer_p;
      std::transform(all_polygons.begin(), all_polygons.end(), areas, areaer_p);
      os << * std::max_element(areas.begin(), areas.end()) << '\n';
      return;
    }
    else if (parametr == "VERTEXES")
    {
      std::vector< size_t > counts_vertexes;
      getVertexes vertexer_p;
      std::transform(all_polygons.begin(), all_polygons.end(), counts_vertexes, vertexer_p);
      os << * std::max_element(counts_vertexes.begin(), counts_vertexes.end()) << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  void min(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons)
  {
    std::string parametr;
    is >> parametr;
    if (parametr == "AREA")
    {
      std::vector< double > areas;
      getAreas areaer_p;
      std::transform(all_polygons.begin(), all_polygons.end(), areas, areaer_p);
      os << * std::min_element(areas.begin(), areas.end()) << '\n';
      return;
    }
    else if (parametr == "VERTEXES")
    {
      std::vector< size_t > counts_vertexes;
      getVertexes vertexer_p;
      std::transform(all_polygons.begin(), all_polygons.end(), counts_vertexes, vertexer_p);
      os << * std::min_element(counts_vertexes.begin(), counts_vertexes.end()) << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  void count(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons)
  {
    std::string parametr;
    is >> parametr;
    if (isdigit(parametr[0]))
    {
      unsigned long long count_vertexes = std::stoull(parametr);
      std::vector< Polygon > vert_p;
      std::function< bool(Polygon&) > predicate = countVertexesPredicate {count_vertexes};
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (vert_p), predicate);
      os << vert_p.size() << '\n';
      return;
    }
    else if (parametr == "EVEN")
    {
      std::vector< Polygon > even_v;
      EvenOddPredicate< 0 > predicate;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (even_v), predicate);
      os << even_v.size() << '\n';
      return;
    }
    else if (parametr == "ODD")
    {
      std::vector< Polygon > odd_v;
      EvenOddPredicate< 1 > predicate;
      std::copy_if(all_polygons.begin(), all_polygons.end(), std::back_inserter (odd_v), predicate);
      os << odd_v.size() << '\n';
      return;
    }
    else
    {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }

  struct nowMax
  {
    size_t now;
    Polygon templ;
    size_t operator()(const Polygon& p)
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
  };

  void maxseq(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons)
  {
    std::vector< size_t > now_max (all_polygons.size());
    Polygon p;
    is >> p;
    nowMax predicate {0, p};
    std::transform(all_polygons.begin(), all_polygons.end(), now_max.begin(), predicate);
    os << * std::max_element(now_max.begin(), now_max.end()) << '\n';
    return;
  }

  struct getX
  {
    int operator()(const Point& p)
    {
      return p.x;
    }
  };

  struct getY
  {
    int operator()(const Point& p)
    {
      return p.y;
    }
  };

  struct getMinX
  {
    int operator()(const Polygon& p)
    {
      std::vector< int > all_x (p.points.size());
      std::transform(p.points.begin(), p.points.end(), all_x, getX {});
      return * std::min_element(all_x.begin(), all_x.end());
    }
  };

  struct getMaxX
  {
    int operator()(const Polygon& p)
    {
      std::vector< int > all_x (p.points.size());
      std::transform(p.points.begin(), p.points.end(), all_x, getX {});
      return * std::max_element(all_x.begin(), all_x.end());
    }
  };

  struct getMinY
  {
    int operator()(const Polygon& p)
    {
      std::vector< int > all_y (p.points.size());
      std::transform(p.points.begin(), p.points.end(), all_y, getY {});
      return * std::min_element(all_y.begin(), all_y.end());
    }
  };

  struct getMaxY
  {
    int operator()(const Polygon& p)
    {
      std::vector< int > all_y (p.points.size());
      std::transform(p.points.begin(), p.points.end(), all_y, getY {});
      return * std::max_element(all_y.begin(), all_y.end());
    }
  };

  void inframe(std::istream& is, std::ostream& os, std::vector< Polygon >& all_polygons)
  {
    std::vector< int > min_x_v (all_polygons.size());
    std::vector< int > max_x_v (all_polygons.size());
    std::transform(all_polygons.begin(), all_polygons.end(), min_x_v.begin(), getMinX {});
    std::transform(all_polygons.begin(), all_polygons.end(), max_x_v.begin(), getMaxX {});
    std::vector< int > min_y_v (all_polygons.size());
    std::vector< int > max_y_v (all_polygons.size());
    std::transform(all_polygons.begin(), all_polygons.end(), min_y_v.begin(), getMinY {});
    std::transform(all_polygons.begin(), all_polygons.end(), max_y_v.begin(), getMaxY {});
    Polygon p;
    is >> p;
    int minY = getMinY {} (p);
    int maxY = getMaxY {} (p);
    int minX = getMinX {} (p);
    int maxX = getMaxX {} (p);
    if ((* std::min_element(min_x_v.begin(), min_x_v.end())) > minX && (* std::min_element(min_y_v.begin(), min_y_v.end())) > minY
        && (* std::max_element(max_x_v.begin(), max_x_v.end())) < maxX && (* std::min_element(max_y_v.begin(), max_y_v.end())) < maxY)
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
}
