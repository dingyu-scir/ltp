#ifndef __LTP_FRAMEWORK_IO_H__
#define __LTP_FRAMEWORK_IO_H__

#include <iostream>

namespace ltp {
namespace framework {

class Reader {
protected:
  std::istream& is;
public:
  Reader(std::istream& _is): is(_is) {}
};

class LineCountsReader: public Reader {
protected:
  size_t nr_lines;
  size_t cursor;
  size_t interval;
public:
  LineCountsReader(std::istream& _is): cursor(0), Reader(_is) {
    nr_lines = number_of_lines();
    interval = nr_lines / 10;
  }

  size_t number_of_lines() {
    const int size = 1024*1024;
    char buffer[1024*1024];
    size_t retval = 0;

    while (true) {
      is.read(buffer, 1024*1024);
      std::streamsize cc = is.gcount();
      if (0 == cc) { break; }
      for (std::streamsize i = 0; i < cc; ++ i) {
        if (buffer[i] == '\n') { ++ retval; } }
    }
    is.clear();
    is.seekg(0, std::ios_base::beg);
    return retval;
  }
};

} //  namespace framework
} //  namespace ltp

#endif  //  end for __LTP_FRAMEWORK_IO_H__

