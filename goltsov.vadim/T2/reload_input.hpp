#include <iostream>
#include <vector>
#include <string>

namespace goltsov
{
  struct UllLit
  {
    unsigned long long a;
  };
  std::istream& operator>>(std::istream& is, UllLit& ul);
  std::ostream& operator<<(std::ostream& os, const UllLit& ul);
  bool operator<(const UllLit& lhs, const UllLit& rhs);
  bool operator==(const UllLit& lhs, const UllLit& rhs);

  struct UllOct
  {
    unsigned long long a;
  };
  std::istream& operator>>(std::istream& is, UllOct& uo);
  std::ostream& operator<<(std::ostream& os, const UllOct& uo);
  bool operator<(const UllOct& lhs, const UllOct& rhs);
  bool operator==(const UllOct& lhs, const UllOct& rhs);

  struct DataStruct
  {
    UllLit key1;
    UllOct key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& is, DataStruct& ds);
  std::ostream& operator<<(std::ostream& os, const DataStruct& ds);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);

  struct delimeter_t
  {
    std::vector< char > expected;
    char& last;
  };
  std::istream& operator>>(std::istream& is, delimeter_t del);

  struct KeyValueInp
  {
    std::string key;
    std::vector< bool >& is_been;
    DataStruct& ds;
  };
  std::istream& operator>>(std::istream& is, KeyValueInp inp);

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

  char check(std::istream& is, const std::vector< char >& expected);
  std::istream& getValueByKey(std::istream& is, std::string key, std::vector< bool >& is_been, DataStruct& ds);
}
