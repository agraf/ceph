#ifndef _RDIAS_TRACE_H_
#define _RDIAS_TRACE_H_

#include <vector>
#include <chrono>

namespace rdias {

class Trace {
private:
  typedef std::chrono::high_resolution_clock _clock;
  typedef std::chrono::time_point<_clock> _time;

  static Trace ins;

  struct Point {
    _time timestamp;
    uint8_t id;
    Point() : id(-1) {}
    Point(_time timestamp, uint8_t id) : timestamp(timestamp), id(id) { }
  };

  bool enabled;
  std::vector<Point> points;
public:
  static void trace(uint8_t id);

  Trace();
  ~Trace();
  void trace_point(uint8_t id);
  void dump();
};

}

#endif // _RDIAS_TRACE_H_
