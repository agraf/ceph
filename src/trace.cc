#include "trace.h"

#include <fstream>

namespace rdias {

Trace Trace::ins;

void Trace::trace(uint8_t id) {
  if (Trace::ins.enabled)
    Trace::ins.trace_point(id);
}

Trace::Trace() {
  const char *env_opt = std::getenv("RDIAS_TRACE");
  enabled = env_opt != nullptr;
  points.reserve(1 << 25);
}

Trace::~Trace() {
  dump();
}

void Trace::trace_point(uint8_t id) {
  points.emplace_back(_clock::now(), id);
}

void Trace::dump() {
  if (points.empty()) {
    return;
  }


  std::ofstream file;
  file.open("/tmp/__trace.txt");
  _time begin = points[0].timestamp;
  _time prev = begin;
  for (auto& point : points) {
    uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(
                                            point.timestamp - begin).count();
    uint64_t diff = std::chrono::duration_cast<std::chrono::microseconds>(
                                            point.timestamp - prev).count();
    file << (int) point.id << ": " << us << ": " << diff << std::endl;
    prev = point.timestamp;
  }
  file.close();
}

}

/*
int main() {
  rdias::Trace::trace(1);
  rdias::Trace::trace(2);
  rdias::Trace::trace(3);

  return 0;
}
*/
