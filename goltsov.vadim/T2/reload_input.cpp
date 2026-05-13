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
      is.setstate(std::ios::failbit);
      return is;
    }
    unsigned long long numb;
    is >> numb;
    try
    {
      std::string oct_str = std::string(1, '0') + std::to_string(numb);
      uo.a = std::stoull(oct_str, nullptr, 8);
    }
    catch (...)
    {
      is.setstate(std::ios_base::failbit);
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
    char last;
    using d_t = delimeter_t;
    is >> d_t{{'('}, last} >> d_t{{':'}, last};
    bool filled[3] = {false};
    for (int i = 0; i < 3; ++i)
    {
      std::string key;
      is >> key;
      Key k = getKeyType(key);
      if (k == UNKNOWN || filled[k])
      {
        is.setstate(std::ios::failbit);
        return is;
      }
      filled[k] = true;
      switch (k)
      {
      case KEY1:
      {
        is >> ds.key1;
        break;
      }
      case KEY2:
      {
        is >> ds.key2;
        break;
      }
      case KEY3:
      {
        std::getline(is >> d_t{{'"'}, last}, ds.key3, '"');
        break;
      }
      default:
        is.setstate(std::ios::failbit);
        return is;
      }
      char next;
      is >> next;
      if (next != ':')
      {
        is.setstate(std::ios::failbit);
        return is;
      }
    }
    is >> d_t{{')'}, last};
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
      return UNKNOWN;
    }
  }
}

