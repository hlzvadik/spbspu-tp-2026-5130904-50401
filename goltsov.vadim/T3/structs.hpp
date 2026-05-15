#include <iostream>
#include <vector>
#include <iterator>

namespace goltsov
{
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

  char check(std::istream& is, char expected);
}
