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
#include <initializer_list>
#include <tiledb/tiledb>

#include "vertex.h"
//#include "tiledb/common/status.h"
//#include "../array_schema/domain.h"
//#include "tiledb/sm/misc/tile_overlap.h"

//using namespace tiledb::sm;

//namespace tiledb {
//namespace sm {


class Graph{
    public:
  /* ********************************* */
  /*     CONSTRUCTORS & DESTRUCTORS    */
  /* ********************************* */

  /** Constructor. */
  Graph();

  /** Constructor. */
  Graph(int dim_num,int size);

  /** Destructor. */
  ~Graph();

  // /** Copy constructor. This performs a deep copy. */
  // Graph(const Graph& g);

  // /** Move constructor. */
  // Graph(Graph&& g) noexcept;

  // /** Copy-assign operator. This performs a deep copy. */
  // Graph& operator=(const Graph& g);

  // /** Move-assign operator. */
  // Graph& operator=(Graph&& g) noexcept;

  /* ********************************* */
  /*                 API               */
  /* ********************************* */


	void insert(std::initializer_list<Vertex> base_, Vertex* n);
	void add_child(Vertex* newParent, Vertex* n);
	void materialization();
  std::vector<int> get_parents_from_ver(int ver);
  int find_common_ancestor(Vertex* v);
  void DFS(int v,int sum_of_weight);


  //private:

    int dim_num;
    int size;
	  std::vector<std::vector<int>> adjacent_matrix;
    
	  Vertex* root;

    std::vector<std::vector<std::bool>> visited;
    
    std::vector<Vertex> vertexs;
    
    //std::vector<std::vector<Vertex>> vertexs;


  

  Graph clone() const;

  void swap(Graph& vtx);

};

//}  // namespace sm
//}  // namespace tiledb

#endif  // TILEDB_GRAPH_H