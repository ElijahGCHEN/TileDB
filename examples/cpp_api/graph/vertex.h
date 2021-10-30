/**
 * @file   rtree.h
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017-2021 TileDB, Inc.
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
 * This file defines class RTree.
 */

#ifndef TILEDB_RTREE_H
#define TILEDB_RTREE_H

#include <vector>
#include <unordered_map>

#include <tiledb/tiledb>

//#include "tiledb/common/status.h"
//#include "../../../tiledb/sm/array_schema/domain.h"
//#include "tiledb/sm/misc/tile_overlap.h"

//using namespace tiledb::common;

//namespace tiledb {
//namespace sm {


class Vertex{
    public:
  /* ********************************* */
  /*     CONSTRUCTORS & DESTRUCTORS    */
  /* ********************************* */

  /** Constructor. */
  Vertex();

  /** Constructor. */
  Vertex(const Domain* domain, std::vector<std::pair<std::string, std::pair<int, int>>> non_empty,
          std::string uri,int ver);

  /** Destructor. */
  ~Vertex();

  // /** Copy constructor. This performs a deep copy. */
  // Vertex(const Vertex& vtx);

  // /** Move constructor. */
  // Vertex(Vertex&& vtx) noexcept;

  // /** Copy-assign operator. This performs a deep copy. */
  // Vertex& operator=(const Vertex& vtx);

  // /** Move-assign operator. */
  // Vertex& operator=(Vertex&& vtx) noexcept;

  /* ********************************* */
  /*                 API               */
  /* ********************************* */

  /** The number of dimensions of the R-tree. */
  unsigned dim_num() const;

  /** Returns the domain. */
  const Domain* domain() const;

  bool if_contain(Vertex& vtr);

  void add_children(Vertex * ptr);

  Vertex* get_parent(); 

  std::vector<std::pair<std::string, std::pair<int, int>>> get_NDRange():

  get_fragment_from_uri();
  void if_materialized();
  
  private:

  std::string uri;

  std::unordered_map<Vertex* vtx,std::int num_of_cells> child_map;

  const Domain* domain_;

  //NDRange NDRange_;

  std::vector<std::pair<std::string, std::pair<int, int>>>  NDRange_;

  int versionNo;

  bool materialized;



  std::vector<int> parents;
  //NDRange ndrange;

  Vertex clone() const;

  void swap(Vertex& vtx);

};

//}  // namespace sm
//}  // namespace tiledb

#endif  // TILEDB_VERTEX_H