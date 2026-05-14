#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

struct IOGuard
{
  explicit IOGuard(std::basic_ios< char >& s):
    s_(s),
    precision_(s.precision()),
    width_(s.width()),
    flags_(s.flags()),
    fill_(s.fill())
  {}
  ~IOGuard()
  {
    s_.precision(precision_);
    s_.width(width_);
    s_.flags(flags_);
    s_.fill(fill_);
  }
private:
  std::basic_ios< char >& s_;
  std::streamsize precision_;
  std::streamsize width_;
  std::basic_ios< char >::fmtflags flags_;
  char fill_;
};

struct Delimeter
{
  char expected;
  char& last;
};
std::istream& operator>>(std::istream& is, Delimeter d);

struct Point
{
  int x, y;
};
std::istream& operator>>(std::istream& is, Point& p);
std::ostream& operator<<(std::ostream& os, const Point& p);

struct Polygon
{
  std::vector< Point > points;
};
std::istream& operator>>(std::istream& is, Polygon& p);
std::ostream& operator<<(std::ostream& os, const Polygon& p);

struct getPoint
{
  std::istream& is;
  Point operator()()
  {
    Point p;
    if (!(is >> p))
    {
      is.setstate(std::ios_base::failbit);
    }
    return p;
  }
};

char check(std::istream& is, char expected);

int main()
{
  Point p;
  std::cin >> p;
  Polygon pp;
  std::cin >> pp;
  std::cout << p << '\n' << pp << '\n';
}

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
  std::copy_n(std::istream_iterator<Point>(is), count_points, std::back_inserter(t.points));
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
