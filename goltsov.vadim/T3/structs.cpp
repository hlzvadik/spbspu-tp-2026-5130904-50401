#include "structs.hpp"
#include <iostream>
#include <algorithm>
#include <ios>

namespace goltsov
{
  std::istream& operator>>(std::istream& is, Point& p)
  {
    std::istream::sentry s (is);
    if (!s)
    {
      return is;
    }
    IOGuard guard (is);
    char last = 0;
    Point t = {0, 0};
    is >> Delimeter {'(', last} >> t.x >> Delimeter {';', last} >> t.y >> Delimeter {')', last};
    if (is)
    {
      p = std::move(t);
    }
    return is;
  }

  std::ostream& operator<<(std::ostream& os, const Point& p)
  {
    os << '(' << p.x << ';' << p.y << ')';
    return os;
  }

  bool operator==(const Point& lhs, const Point& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }

  std::istream& operator>>(std::istream& is, Polygon& p)
  {
    std::istream::sentry s (is);
    if (!s)
    {
      return is;
    }
    IOGuard guard (is);
    Polygon t;
    size_t count_points = 0;
    is >> count_points;
    if (count_points < 3)
    {
      is.setstate(std::ios_base::failbit);
      return is;
    }
    t.points.reserve(count_points);
    std::copy_n(std::istream_iterator< Point >(is), count_points, std::back_inserter(t.points));
    if (t.points.size() != count_points || !is)
    {
      is.setstate(std::ios_base::failbit);
      return is;
    }
    p = std::move(t);
    return is;
  }

  std::ostream& operator<<(std::ostream& os, const Polygon& p)
  {
    os << p.points.size() << " ";
    std::copy(p.points.begin(), p.points.end() - 1, std::ostream_iterator< Point > {os, " "});
    os << * (p.points.end() - 1);
    return os;
  }

  std::istream& operator>>(std::istream& is, Delimeter d)
  {
    d.last = check(is, d.expected);
    return is;
  }

  char check(std::istream& is, char expected)
  {
    char c = 0;
    is >> c;
    if (c != expected)
    {
      is.setstate(std::ios_base::failbit);
    }
    return c;
  }
}
