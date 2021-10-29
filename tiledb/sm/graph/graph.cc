/**
 * @file   graph.cc
 *
 * @section LICENSE
 *
 * The UST License
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
 * This file implements class graph.
 */


#include "graph.h"
#include "tiledb/common/logger.h"
#include "tiledb/sm/array_schema/dimension.h"
#include "tiledb/sm/buffer/buffer.h"
#include "tiledb/sm/buffer/const_buffer.h"
#include "tiledb/sm/enums/datatype.h"
#include "tiledb/sm/misc/utils.h"

#include <cassert>
#include <iostream>
#include <list>

//using namespace tiledb::sm;

namespace tiledb {
namespace sm {

/* ****************************** */
/*   CONSTRUCTORS & DESTRUCTORS   */
/* ****************************** */

Graph::Graph(){
    dim_num=0;
    size=0

    Graph(dim_num,size);
}

Graph::Graph(int dim_num,int size)
    :dim_num(dim_num),size(size)
    // {
    //     for(int v = 0; v < adjacent_metrix.size(); v++) {
	// 	adjacent_metrix[v].push_back(0);
	// }
    std::vector<uint_32> row;
    row.assign(size,0);
    std::vector<std::vector<unit_32>> adj_m;
    adjacent_metrix=adj_m;
      
}

Graph::~Graph() =default;

Graph::Graph(const Graph& vtx):Graph(){
  auto clone = vtx.clone();
  swap(clone);
}

 /** Move constructor. */
Graph::Graph(Graph&& vtx) noexcept
    : Graph() {
  swap(vtx);
}

Graph& Graph::operator=(const Graph& vtx) {
  auto clone = vtx.clone();
  swap(clone);

  return *this;
}

Graph& Graph::operator=(Graph&& vtx) noexcept {
  swap(vtx);

  return *this;
}


/* ********************************* */
/*                 API               */
/* ********************************* */

int Graph::find_common_ancestor(Vertex* v){
    std::vector<int> parents=v->get_parent();
    std::vector<int> parents_list0;
    std::vector<int> parents_list1;
    //int i,j=0;

    int ver=parents[0]->get_parent()[0];
    while (ver!=root->get_version())
    {
        parents_list0.push_back(ver)
        ver=get_parents_from_ver(ver);
    }

    ver=parents[1]->get_parent()[0];
    while (ver!=root->get_version())
    {
        // parents_list1.push_back(ver)
        

        if (std::find(parents_list0.begin(), parents_list0.end(), ver) != parents_list0.end()) {
            return ver;
        }
        // else {
        //     std::cout << "Element not found";
        // }
        ver=get_parents_from_ver(ver);
    }
}

//Vertex* base 
bool Graph::insert(initializer_list<Vertex> bases, Vertex* n){

    if(initializer_list.size()==1){
        if(n->if_contain(base)){
            if(!base->has_fragment()){
                Vertex* ca=find_common_ancestor(base));
                insert(ca,n);
            }else{
                if(base->has_parent()){
                    std::vector<int> parents=base->get_parent();
                    //for (int i = 0; i < parents.size(); i++)
                    //{
                        //if(   ){
                        insert(parents[i],n);
                    //}
                }else{
                    shared_ptr<Vertex> new_root;
                    root = new_root;
                    add_child(new_root, base);
                    add_child(new_root, n);
                }
            //insert(base's parents,n);
            }
        }else{// 
            add_child(base,n);
        }
    }else{
        for (int i = 0; i < initializer_list.size(); i++)
        {
            add_child(initializer_list[i],n);
        }
    }
}

bool Graph::insert_recreated_version(){

}


vector<int> Graph::get_parents_from_ver(int ver){
    std::vector<int> Parents;
    for (int i = 0; i < adjacent_matrix.size(); i++)
    {
        if(adjacent_matrix[i][ver]!=0){
        Parents.push_back(i);
        }
    }
    return Parents;
}



void Graph::add_child(Vertex* newParent, Vertex* n){
    // for(int v = 0; v < adjacent_metrix.size(); v++) {
	// 	adjacent_metrix[v].push_back(0);
	// }

    // if(n->has_parent()){

    //     std::vector<int> OldParents=n->get_parents();

    //     for (in i = 0; i < OldParents.size(); i++)
    //     {
    //         if(OldParents[i]->if_contain(newParent)){return;}
    //     }

    // }
    //if(previous parents contain new parent){return;}

    int parentVer=newParent->get_version();

	adjacent_metrix[parentVer][adjacent_metrix[parentVer].size()-1] = n->no_of_cells();

    n->add_parent(newParent);

	// if (parent.has_parent())
	// {
	// 	vertex* parents_of_parent = parent.get_parent();
	// 	// Only get the "true" parent in the matrix

	// 	if (parents_of_parent->domain <)
	// 	{
	// 		/* code */
	// 	}
    return;
	}

    void Graph::check_materialization(int sum_of_weight,int thresh){


        if(sum_of_weight > thresh){
            return true;
        }
        return false;
    }

void Graph::DFS(int v,int sum_of_weight)
{
    //std::map<int, bool> visited;
   // vector<int> visited;

    //std::vector<std::vector<bool>> visited;
    
    //visited[v][i] = true;
    //cout << v << " ";

    //vector<int>::iterator i;
    //int sum_of_weight=0;
    //for (i = adjacent_matrix[v].begin(); i != adjacent_matrix[v].end(); ++i){
    for (int i = 0; i < adjacent_matrix[v].size(); i++)
    {
        if(adjacent_matrix[v][i]!=0){

            if(!visited[v][i]){

                sum_of_weight=sum_of_weight+adjacent_matrix[v][i];

                if(sum_of_weight>thresh){
                    //materialization(v,i);
                    materialization(i);
                    set_materialzed();
                    sum_of_weight=0;
                }

                // DFS(*i);   
                visited[v][i] = true;

                DFS(i,sum_of_weight);             
            }
        }
        //DFS(i);  
    }
    
        // if(*i!=0){

        // if (!visited[*i]){ //if not visited

        //     sum_of_weight=sum_of_weight+adjacent_matrix[v][i];
        //     if(check_materialization(sum_of_weight,thresh)){
        //         materialization(v);
        //     }
        //     DFS(*i);
        // }
        // }
        
}
        


    Vertex* Graph::get_vertex_from_ver(int ver){

    }

   void Graph::materialization(int v,int i){

       std::vector<int> parents = get_parents_from_ver(i);

        get_vertex_from_ver();


        parents+ver;

        return;

   }




