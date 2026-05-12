#include <iostream>
#include <string>

namespace goltsov
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& is, DataStruct& ds);
  std::ostream& operator<<(std::ostream& is, DataStruct& ds);

  struct UllLit
  {
    unsigned long long& a;
  };
  std::istream& operator>>(std::istream& is, UllLit& ul);
  std::ostream& operator<<(std::ostream& is, UllLit& ul);

  struct UllOct
  {
    unsigned long long a;
  };
  std::istream& operator>>(std::istream& is, UllOct& uo);
  std::ostream& operator<<(std::ostream& is, UllOct& uo);

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

  char check(std::istream& is, char expected)
  {
    char c;
    is >> c;
    if (c != expected)
    {
      is.setstate(std::ios_base::failbit);
    }
    return c;
  }

  struct delimeter_t
  {
    char expected;
    char& last;
  };
  std::istream& operator>>(std::istream& is, delimeter_t& del)
  {
    del.last = check(is, del.expected);
    return is;
  }


}


int main()
{}
