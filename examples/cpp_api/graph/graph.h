/**
 * @file   rtree.h
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017-2021 TileDB, Inc.
 *
 
 *
 * @section DESCRIPTION
 *
 * This file defines class RTree.
 */

#ifndef TILEDB_GRAPH_H
#define TILEDB_GRAPH_H

#include <vector>
#include <unordered_map>
#include <initializer_list>
#include <tiledb/tiledb>
#include <memory>
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


	void insert(std::vector<Vertex*> bases, Vertex* n);
	void add_child(Vertex* newParent, Vertex* n);
	void materialization(int i);
  void set_materialized(int i);
  std::vector<int> get_parents_from_ver(int ver);
  int find_common_ancestor(const Vertex* v);
  void DFS(int v,int sum_of_weight);
  void insertRoot(Vertex* n);
  std::vector<Vertex> get_vertexs();
  void print_vertexs();
  std::vector<std::vector<int>> get_adj();
  void registerVertex(Vertex* n);
  void fragments_to_make_vertex(int ver, std::vector<int> *fragments_list);
  void add_child_m(Vertex* newParent, Vertex* n,int num_of_cells);
  void DFS(int v,int sum_of_weight,int thresh);
  void Recreation(int ver);


  //private:

    int dim_num;
    int size;
	  std::vector<std::vector<int>> adjacent_matrix;
    
	  Vertex* root;
    //std::shared_ptr<Vertex> root;

    std::vector<std::vector<bool>> visited;
    
    std::vector<Vertex> vertexs;

    int thresh;
    
    
    //std::vector<std::vector<Vertex>> vertexs;


  

  //Graph clone() const;

  //void swap(Graph& vtx);

};

//}  // namespace sm
//}  // namespace tiledb

#endif  // TILEDB_GRAPH_H