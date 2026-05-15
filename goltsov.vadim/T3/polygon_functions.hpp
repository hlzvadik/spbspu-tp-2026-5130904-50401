#ifndef POLYGON_FUNCTIONS_HPP
#define POLYGON_FUNCTIONS_HPP
#include <iostream>
#include <ios>
#include "structs.hpp"

namespace goltsov
{
  void area(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons);
  void max(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons);
  void min(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons);
  void count(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons);
  void maxseq(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons);
  void inframe(std::istream& is, std::ostream& os, const std::vector< Polygon >& all_polygons);

  struct EvenPredicate
  {
    bool operator()(const Polygon& p);
  };

  struct OddPredicate
  {
    bool operator()(const Polygon& p);
  };

  struct CountVertexesPredicate
  {
    size_t count_vertexes;
    bool operator()(const Polygon& p);
  };

  struct CountVertexes
  {
    size_t operator()(const Polygon& p);
  };

  struct AreasTriangleOfPolygon
  {
    const std::vector< Point >& points;
    size_t i = 0;
    double operator()(const Point& p1);
  };

  struct AreaPolygon
  {
    double operator()(const Polygon& p);
  };

  struct NowMax
  {
    size_t now;
    const Polygon& templ;
    size_t operator()(const Polygon& p);
  };

  struct GetX
  {
    int operator()(const Point& p);
  };

  struct GetY
  {
    int operator()(const Point& p);
  };

  struct GetMinX
  {
    int operator()(const Polygon& p);
  };

  struct GetMaxX
  {
    int operator()(const Polygon& p);
  };

  struct GetMinY
  {
    int operator()(const Polygon& p);
  };

  struct GetMaxY
  {
    int operator()(const Polygon& p);
  };
}
#endif
