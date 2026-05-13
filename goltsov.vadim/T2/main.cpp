#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

namespace goltsov
{
  struct DataStruct
  {
    UllLit key1;
    UllOct key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& is, DataStruct& ds);
  std::ostream& operator<<(std::ostream& os, DataStruct& ds);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);

  struct UllLit
  {
    unsigned long long a;
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
    std::vector< char > expected;
    char last;
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

  char check(std::istream& is, std::vector< char > expected);

  enum Key
  {
    KEY1, KEY2, KEY3, UNKNOW
  };

  Key getKeyType(std::string s_key);
}


int main()
{}

namespace goltsov
{
  Key getKeyType(std::string s_key)
  {
    if (s_key == "key1")
    {
      return KEY1;
    }
    else if (s_key == "key2")
    {
      return KEY2;
    }
    else if (s_key == "key3")
    {
      return KEY3;
    }
    else
    {
      return UNKNOW;
    }
  }

  char check(std::istream& is, std::vector< char > expected)
  {
    char c;
    is >> c;
    if (std::find(expected.begin(), expected.end(), c) == expected.end())
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
    std::istream::sentry s (is);
    if (!s)
    {
      return is;
    }
    IOGuard g (is);
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
    catch (...)
    {
      is.setstate(std::ios_base::failbit);
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, UllOct& uo)
  {
    IOGuard guard (os); 
    os << '0';
    os << std::oct << uo.a;
    return os;
  }

  std::istream& operator>>(std::istream& is, UllLit& ul)
  {
    std::istream::sentry s (is);
    if (!s)
    {
      return is;
    }
    IOGuard g (is);
    char last;
    using d_t = delimeter_t;
    unsigned long long numb = 0;
    is >> numb >> d_t{{'u', 'U'}, last} >> d_t{{'l', 'L'}, last} >> d_t{{'l', 'L'}, last};
    ul.a = numb;
    return is;
  }
  std::ostream& operator<<(std::ostream& os, UllLit& ul)
  {
    IOGuard guard (os);
    os << ul.a << "ull";
    return os;
  }

  std::istream& operator>>(std::istream& is, DataStruct& ds)
  {
    std::istream::sentry s (is);
    if (!s)
    {
      return is;
    }
    IOGuard g (is);
    char last;
    using d_t = delimeter_t;
    UllLit k1;
    UllOct k2;
    std::string k3;
    is >> d_t{{'('}, last} >> d_t{{':'}, last};
    for (size_t i = 0; i < 3; ++i)
    {
      std::string key;
      is >> key;
      switch (getKeyType(key))
      {
      case KEY1:
        UllLit value1;
        is >> value1;
        ds.key1 = value1;
        break;
      case KEY2:
        UllOct value2;
        is >> value2;
        ds.key2 = value2;
        break;
      case KEY3:
        std::string value3;
        is >> value3;
        ds.key3 = value3;
        break;
      default:
        is.setstate(std::ios::failbit);
        break;
      }
      is >> d_t{{':'}, last};
    }
    is >> d_t{{')'}, last};
    return is;
  }
  std::ostream& operator<<(std::ostream& os, DataStruct& ds);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

