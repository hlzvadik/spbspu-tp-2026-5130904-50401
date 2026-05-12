#include <iostream>
#include <string>
#include <cctype>

namespace goltsov
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& is, DataStruct& ds);
  std::ostream& operator<<(std::ostream& os, DataStruct& ds);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);

  struct UllLit
  {
    unsigned long long& a;
  };
  std::istream& operator>>(std::istream& is, UllLit& ul);
  std::ostream& operator<<(std::ostream& os, UllLit& ul);

  struct UllOct
  {
    unsigned long long a;
  };
  std::istream& operator>>(std::istream& is, UllOct& uo);
  std::ostream& operator<<(std::ostream& os, UllOct& uo);

  struct delimeter_t
  {
    char expected;
    char& last;
  };
  std::istream& operator>>(std::istream& is, delimeter_t& del);

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

  char check(std::istream& is, char expected);
}


int main()
{}

namespace goltsov
{
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

  std::istream& operator>>(std::istream& is, delimeter_t& del)
  {
    del.last = check(is, del.expected);
    return is;
  }

  std::istream& operator>>(std::istream& is, UllOct& uo)
  {
    std::string oct_str;
    std::istream::sentry s(is);
    if (!s)
    {
      return is;
    }
    IOGuard g(is);
    is >> oct_str;
    if (oct_str.empty() || oct_str[0] != '0')
    {
      is.setstate(std::ios_base::failbit);
      return is;
    }
    try
    {
      uo.a = std::stoull(oct_str, nullptr, 8);
    }
    catch (const std::exception&)
    {
      is.setstate(std::ios_base::failbit);
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, UllOct& uo)
  {
    IOGuard guard(os); 
    os << '0';
    os << std::oct << uo.a;
    return os;
  }

  std::istream& operator>>(std::istream& is, UllLit& ul)
  {
    std::string lit_str;
    std::istream::sentry s(is);
    if (!s)
    {
      return is;
    }
    IOGuard g(is);
    is >> lit_str;
    if (lit_str.size() < 4)
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    std::string lit = lit_str.substr(lit_str.size() - 4, 3);
    if (std::tolower(lit[0]) != 'u' || std::tolower(lit[1]) != 'l' || std::tolower(lit[2]) != 'l')
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    try
    {
      ul.a = std::stoull(lit_str.substr(0, lit_str.size() - 3));
    }
    catch (...)
    {
      is.setstate(std::ios::failbit);
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, UllLit& ul)
  {
    IOGuard guard(os);
    os << ul.a << "ull";
    return os;
  }
}
