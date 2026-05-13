#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "reload_input.hpp"

namespace goltsov
{
  std::istream& operator>>(std::istream& is, UllLit& ul)
  {
    std::istream::sentry s (is);
    if (!s)
    {
      return is;
    }
    IOGuard guard (is);
    char last;
    using d_t = goltsov::delimeter_t;
    unsigned long long numb = 0;
    is >> numb >> d_t{{'u', 'U'}, last} >> d_t{{'l', 'L'}, last} >> d_t{{'l', 'L'}, last};
    ul.a = numb;
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const UllLit& ul)
  {
    IOGuard guard (os);
    os << ul.a << "ull";
    return os;
  }
  bool operator<(const UllLit& lhs, const UllLit& rhs)
  {
    return lhs.a < rhs.a;
  }
  bool operator==(const UllLit& lhs, const UllLit& rhs)
  {
    return lhs.a == rhs.a;
  }

  std::istream& operator>>(std::istream& is, UllOct& uo)
  {
    std::istream::sentry s (is);
    if (!s)
    {
      return is;
    }
    IOGuard guard (is);
    char pre;
    is >> pre;
    if (pre != '0')
    {
      is.setstate(std::ios_base::failbit);
      return is;
    }
    unsigned long long numb;
    is >> numb;
    if (!is)
    {
      return is;
    }
    std::string oct_str = std::string(1, '0') + std::to_string(numb);
    if (std::find(oct_str.begin(), oct_str.end(), '8') != oct_str.end()
        || std::find(oct_str.begin(), oct_str.end(), '9') != oct_str.end())
    {
      is.setstate(std::ios_base::failbit);
    }
    else
    {
      uo.a = std::stoull(oct_str, nullptr, 8);
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const UllOct& uo)
  {
    IOGuard guard (os); 
    os << '0';
    os << std::oct << uo.a;
    return os;
  }
  bool operator<(const UllOct& lhs, const UllOct& rhs)
  {
    return lhs.a < rhs.a;
  }
  bool operator==(const UllOct& lhs, const UllOct& rhs)
  {
    return lhs.a == rhs.a;
  }

  std::istream& operator>>(std::istream& is, DataStruct& ds)
  {
    std::istream::sentry s (is);
    if (!s)
    {
      return is;
    }
    IOGuard guard (is);
    DataStruct inp;
    char last;
    using d_t = delimeter_t;
    std::vector< bool > is_been (3, false);
    std::string k1, k2, k3;
    is >> d_t{{'('}, last} >> d_t{{':'}, last}
      >> k1 >> KeyValueInp {k1, is_been, inp} >> d_t{{':'}, last}
      >> k2 >> KeyValueInp {k2, is_been, inp} >> d_t{{':'}, last}
      >> k3 >> KeyValueInp {k3, is_been, inp} >> d_t{{':'}, last}
      >> d_t{{')'}, last};
    if (is)
    {
      ds = inp;
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
  {
    IOGuard g (os);
    os << "(:key1 " << ds.key1 << ":key2 " << ds.key2 << ":key3 \"" << ds.key3 << "\":)";
    return os;
  }
  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    return (lhs.key1 < rhs.key1) || (lhs.key1 == rhs.key1 && lhs.key2 < rhs.key2)
      || (lhs.key1 == rhs.key1 && lhs.key2 == rhs.key2 && lhs.key3 < rhs.key3);
  }

  std::istream& operator>>(std::istream& is, delimeter_t del)
  {
    del.last = check(is, del.expected);
    return is;
  }

  std::istream& operator>>(std::istream& is, KeyValueInp inp)
  {
    return getValueByKey(is, inp.key, inp.is_been, inp.ds);
  }

  char check(std::istream& is, const std::vector< char >& expected)
  {
    char c;
    is >> c;
    if (std::find(expected.begin(), expected.end(), c) == expected.end())
    {
      is.setstate(std::ios_base::failbit);
    }
    return c;
  }

  std::istream& getValueByKey(std::istream& is, std::string key, std::vector< bool >& is_been, DataStruct& ds)
  {
    using d_t = delimeter_t;
    if (key == "key1")
    {
      if (is_been[0])
      {
        is.setstate(std::ios_base::failbit);
        return is;
      }
      is >> ds.key1;
      is_been[0] = true;
    }
    else if (key == "key2")
    {
      if (is_been[1])
      {
        is.setstate(std::ios_base::failbit);
        return is;
      }
      is >> ds.key2;
      is_been[1] = true;
    }
    else if (key == "key3")
    {
      if (is_been[2])
      {
        is.setstate(std::ios_base::failbit);
        return is;
      }
      char q;
      std::getline(is >> d_t {{'"'}, q}, ds.key3, '"');
      is_been[2] = true;
    }
    else
    {
      is.setstate(std::ios_base::failbit);
    }
    return is;
  }
}

