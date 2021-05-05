/**
 * @file   global_stats.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2018-2021 TileDB, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * This file contains definitions of statistics-related code.
 */

#include "tiledb/sm/stats/global_stats.h"

#include <cassert>
#include <sstream>

namespace tiledb {
namespace sm {
namespace stats {

GlobalStats all_stats;

/* ****************************** */
/*   CONSTRUCTORS & DESTRUCTORS   */
/* ****************************** */

GlobalStats::GlobalStats()
    : enabled_(false) {
  reset();
}

/* ****************************** */
/*              API               */
/* ****************************** */

bool GlobalStats::enabled() const {
  return enabled_;
}

void GlobalStats::dump(FILE* out) const {
  if (out == nullptr)
    out = stdout;

  std::string output;
  GlobalStats::dump(&output);
  fprintf(out, "%s", output.c_str());
}

void GlobalStats::dump(std::string* out) const {
  *out = dump_registered_stats();
}

void GlobalStats::raw_dump(FILE* out) const {
  if (out == nullptr)
    out = stdout;

  std::string output;
  GlobalStats::raw_dump(&output);
  fprintf(out, "%s", output.c_str());
}

void GlobalStats::raw_dump(std::string* out) const {
  *out = dump_registered_stats();
}

void GlobalStats::set_enabled(bool enabled) {
  enabled_ = enabled;
}

void GlobalStats::register_stats(const tdb_shared_ptr<Stats>& stats) {
  registered_stats_.emplace_back(stats);
}

/* ****************************** */
/*       PRIVATE FUNCTIONS        */
/* ****************************** */

std::string GlobalStats::dump_registered_stats() const {
  std::stringstream ss;

  for (const auto& stats : registered_stats_) {
    const std::string stats_dump = stats->dump();
    if (!stats_dump.empty())
      ss << stats_dump;
  }

  return ss.str();
}

void GlobalStats::write(
    std::stringstream* ss, const std::string& msg, double secs) const {
  if (secs != 0)
    (*ss) << msg << secs << " secs\n";
}

void GlobalStats::write(
    std::stringstream* ss, const std::string& msg, uint64_t count) const {
  if (count != 0)
    (*ss) << msg << count << "\n";
}

void GlobalStats::write_bytes(
    std::stringstream* ss, const std::string& msg, uint64_t count) const {
  if (count != 0) {
    auto gbs = (double)count / GB_BYTES;
    (*ss) << msg << count << " bytes (" << gbs << " GB) \n";
  }
}

void GlobalStats::write_factor(
    std::stringstream* ss,
    const std::string& msg,
    uint64_t count_a,
    uint64_t count_b) const {
  if (count_a != 0 && count_b != 0)
    (*ss) << msg << (count_a / (double)count_b) << "x\n";
}

void GlobalStats::write_ratio(
    std::stringstream* ss,
    const std::string& msg,
    uint64_t count_a,
    uint64_t count_b) const {
  if (count_a != 0 && count_b != 0)
    (*ss) << msg << (count_a / (double)count_b) * 100.0 << "%\n";
}

void GlobalStats::report_ratio(
    FILE* out,
    const char* msg,
    const char* unit,
    uint64_t numerator,
    uint64_t denominator) const {
  std::stringstream ss;
  ss << msg << ": " << numerator << " / " << denominator << " " << unit;
  fprintf(out, "%s", ss.str().c_str());

  if (denominator > 0) {
    fprintf(out, " (%.1fx)", double(numerator) / double(denominator));
  }
  fprintf(out, "\n");
}

void GlobalStats::report_ratio_pct(
    FILE* out,
    const char* msg,
    const char* unit,
    uint64_t numerator,
    uint64_t denominator) const {
  std::stringstream ss;
  ss << msg << ": " << numerator << " / " << denominator << " " << unit;
  fprintf(out, "%s", ss.str().c_str());

  if (denominator > 0) {
    fprintf(out, " (%.1f%%)", 100.0 * double(numerator) / double(denominator));
  }
  fprintf(out, "\n");
}

}  // namespace stats
}  // namespace sm
}  // namespace tiledb
