/**
 * @file   tiledb_dense_read_global.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017-2018 TileDB, Inc.
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
 * It shows how to read a complete dense array in the global cell order.
 *
 * You need to run the following to make it work:
 *
 * $ ./tiledb_dense_create
 * $ ./tiledb_dense_write_global_1
 * $ ./tiledb_dense_read_global
 */

#include <array>
#include <iomanip>
#include <tiledb>

int main() {
  using std::setw;
  tiledb::Context ctx;

  // Find out the minimum bounding rectangle
  tiledb::ArraySchema schema(ctx, "my_dense_array");  // Load schema

  std::unordered_map<std::string, std::pair<uint64_t, uint64_t>> domain;
  domain = tiledb::Array::non_empty_domain<uint64_t>("my_dense_array", schema);
  std::cout << "Non empty domain:\n";
  for (const auto &d : domain) {
    std::cout << d.first << ": (" << d.second.first << ", " << d.second.second
              << ")\n";
  }

  // Init the array & query for the array
  tiledb::Query query(ctx, "my_dense_array", TILEDB_READ);

  // Set the layout of output, desired attributes, and determine buff sizes
  query.set_layout(TILEDB_GLOBAL_ORDER);

  // Make buffers
  auto a1_buff = query.make_buffer<int>("a1");
  auto a2_buff = query.make_var_buffers<char>(
      "a2", 3);  // variable sized attr gets a pair of buffs
  auto a3_buff =
      query.make_buffer<float>("a3", 1000);  // Limit size to 1000 elements
  query.set_buffer("a1", a1_buff);
  query.set_buffer("a2", a2_buff);
  query.set_buffer("a3", a3_buff);
  std::cout << "\nQuery submitted: " << query.submit() << "\n";

  // Get the number of elements filled in by the query
  // Order is by attribute. For variable size attrs, the offset_buff comes
  // first.
  const auto buff_sizes = query.returned_buff_sizes();

  // chunk the continuous buffer by cell
  auto a2 = tiledb::group_by_cell(a2_buff, buff_sizes[1], buff_sizes[2]);
  auto a3 = tiledb::group_by_cell<2>(a3_buff, buff_sizes[3]);

  std::cout << "Result num: " << buff_sizes[0]
            << '\n';  // This assumes all attributes were fully read.
  std::cout << "a1" << setw(10) << "a2" << setw(10) << "a3[0]" << setw(10)
            << "a3[1]\n";
  for (unsigned i = 0; i < buff_sizes[0]; ++i) {
    std::cout << a1_buff[i] << setw(10)
              << std::string(a2[i].data(), a2[i].size()) << setw(10) << a3[i][0]
              << setw(10) << a3[i][1] << '\n';
  }

  return 0;
}