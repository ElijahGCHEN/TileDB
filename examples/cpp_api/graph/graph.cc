/**
 * @file   graph.cc
 *
 * @section LICENSE
 *
 * The UST License
 *
 * @copyright Copyright (c) 2017-2021 TileDB, Inc.
 *
 *
 * @section DESCRIPTION
 *
 * This file implements class graph.
 */


#include "graph.h"
// #include "tiledb/common/logger.h"
// #include "tiledb/sm/array_schema/dimension.h"
// #include "tiledb/sm/buffer/buffer.h"
// #include "tiledb/sm/buffer/const_buffer.h"
// #include "tiledb/sm/enums/datatype.h"
// #include "tiledb/sm/misc/utils.h"

#include <cassert>
#include <iostream>
#include <list>
#include <algorithm>

//using namespace tiledb::sm;

//namespace tiledb {
//namespace sm {

/* ****************************** */
/*   CONSTRUCTORS & DESTRUCTORS   */
/* ****************************** */

Graph::Graph(){
    dim_num=0;
    size=0;

    Graph(dim_num,size);
}

Graph::Graph(int dim_num,int size)
    :dim_num(dim_num),size(size){
    // {
    //     for(int v = 0; v < adjacent_metrix.size(); v++) {
	// 	adjacent_metrix[v].push_back(0);
	// }

    //std::vector<int> row;
    //row.assign(size,0);

    


    //std::vector<std::vector<int>> adj_m;


    std::vector<std::vector<int>> vec(size, std::vector<int> (size, 0));
    adjacent_matrix=vec;

    std::vector<std::vector<bool>> vecbool(size, std::vector<bool> (size, 0));
    visited=vecbool;

    //adjacent_metrix=adj_m;

    //root= &Vertex;
}


Graph::~Graph() =default;

// Graph::Graph(const Graph& vtx):Graph(){
//   auto clone = vtx.clone();
//   swap(clone);
// }

//  /** Move constructor. */
// Graph::Graph(Graph&& vtx) noexcept
//     : Graph() {
//   swap(vtx);
// }

// Graph& Graph::operator=(const Graph& vtx) {
//   auto clone = vtx.clone();
//   swap(clone);

//   return *this;
// }

// Graph& Graph::operator=(Graph&& vtx) noexcept {
//   swap(vtx);

//   return *this;
// }


/* ********************************* */
/*                 API               */
/* ********************************* */
std::vector<Vertex> Graph::get_vertexs(){
    return vertexs;
}

void Graph::print_vertexs(){
    //return vertexs;
    for (int i = 0; i < vertexs.size(); i++)
    {
        vertexs[i].print();
    }
    

}

std::vector<std::vector<int>> Graph::get_adj(){
    return adjacent_matrix;
}

int Graph::find_common_ancestor(const Vertex* v){
    std::vector<int> parents=v->get_parent();
    std::vector<int> parents_list0;
    std::vector<int> parents_list1;
    //int i,j=0;


    //int ver=parents[0]->get_parent()[0];
    std::vector<int> vers=get_parents_from_ver(parents[0]);
    int ver=vers[0];
    while (ver!=root->get_version())
    {
        parents_list0.push_back(ver);
        vers=get_parents_from_ver(ver);
        ver=vers[0];
    }

    //ver=parents[1]->get_parent()[0];
    vers=get_parents_from_ver(parents[1]);
    ver=vers[0];
    while (ver!=root->get_version())
    {
        // parents_list1.push_back(ver)
        

        if (std::find(parents_list0.begin(), parents_list0.end(), ver) != parents_list0.end()) {
            return ver;
        }
        // else {
        //     std::cout << "Element not found";
        // }
        vers=get_parents_from_ver(ver);
        ver=vers[0];
    }

    return 0;
}

//Vertex* base 

void Graph::insertRoot(Vertex* n){
    root=n;
    vertexs.push_back(*n);
}

void Graph::registerVertex(Vertex* n){
    int ver=n->get_version();
    if(vertexs.size()-1==ver){return;} //vertex already exist

    vertexs.push_back(*n);
}

void Graph::insert(std::vector<Vertex*> bases, Vertex* n){
std::cout<<"-----line 167"<<std::endl;
    if(bases.size()==1){
        std::cout<<"-----line 169"<<std::endl;

        //if(n->if_contain(&bases[0])){
        if(n->if_contain(bases[0])){
            std::cout<<"-----line 172"<<std::endl;

            if(!bases[0]->has_fragment()){
                std::cout<<"-----line 175"<<std::endl;

                //int ca=find_common_ancestor(&bases[0]);
                int ca=find_common_ancestor(bases[0]);
                std::vector<Vertex*> v(1,&vertexs[ca]);
                //v.push_back(vertexs[ca]);
                insert(v,n);

            }else{
                std::cout<<"-----line 184"<<std::endl;
                if(bases[0]->has_parent()){

                    std::cout<<"-----line 186"<<std::endl;

                    std::vector<int> parents=bases[0]->get_parent();
                    std::cout<<"-----line 189"<<std::endl;
                    //for (int i = 0; i < parents.size(); i++)
                    //{
                        //if(   ){

                        std::cout<<"-----line 195 parents number "<<parents.size()<<std::endl;
                        int p=parents[0];
                        std::cout<<"-----line 197 parent = "<<p<<std::endl;
                        std::vector<Vertex*> ver(1,&vertexs[p]);
                        //ver.push_back(vertexs[p]);
                        insert(ver,n);
                    //}
                }else{

                    std::cout<<"-----line 204"<<std::endl;
                    std::shared_ptr<Vertex> new_root;
                    //std::Vertex new_root;
                    

                    add_child(new_root.get(), root);
                    add_child(new_root.get(), n);
                    root = new_root.get();
                }
            //insert(base's parents,n);
            }

        }else{// 
            std::cout<<"-----line 203"<<std::endl;
            add_child(bases[0],n);
        }
    }else{
        for (int i = 0; i < bases.size(); i++)
        {
            //add_child(bases[i],n);
            /////////////////////// assume there are only 2 bases
            // std::set<int> fragments_list1;
            // std::set<int> fragments_list2;
            std::vector<int> fragments_list1;
            std::vector<int> fragments_list2;
            fragments_to_make_vertex(bases[0]->get_version(),&fragments_list1);
            fragments_to_make_vertex(bases[1]->get_version(),&fragments_list2);

            int num_of_cell1=0;
            for (int j = 0; j < fragments_list2.size(); j++)
            {
                int ver=fragments_list2[j];
                //if(ver not in fragments_list1){
                //if(!std::any_of(fragments_list1.begin(), fragments_list1.end(), compare(ver))){
                //if(std::find(fragments_list1.begin(), fragments_list1.end(), ver) = fragments_list1.end()){
                if (std::count(fragments_list1.begin(), fragments_list1.end(), ver)==0) {
                    num_of_cell1=num_of_cell1+vertexs[ver].no_of_cells();
                }
            }

            int num_of_cell2=0;
            for (int j = 0; j < fragments_list1.size(); j++)
            {
                int ver=fragments_list1[j];
                //if(ver not in fragments_list2){
                //if(!std::any_of(fragments_list2.begin(), fragments_list2.end(), compare(ver))){ 
                //if(std::find(fragments_list2.begin(), fragments_list2.end(), ver) = fragments_list2.end()){  
                if (std::count(fragments_list2.begin(), fragments_list2.end(), ver)==0) {
                    num_of_cell2=num_of_cell2+vertexs[ver].no_of_cells();
                }
            }
            
            add_child_m(bases[0],n,num_of_cell1);
            add_child_m(bases[1],n,num_of_cell2);
        }
    }

    //vertexs.push_back(*n);
    registerVertex(n);
}

// std::vector<int> Graph::fragments_to_make_vertex(Vertex * v){
//     int ver=v->get_version();

//     std::vector<int> fragments_list;

//     fragments_list.push_back(ver);

//     std::vector<int> parents=get_parents_from_ver(ver);

//     int ver=parents[0];

//     while (ver!=root->get_version())
//     {
//         fragments_list.push_back(ver);
//         parents=get_parents_from_ver(ver);
//         ver=parents[0];
//     }
    
//     return fragments_list;
// }

void Graph::Recreation(int ver){

}

void Graph::fragments_to_make_vertex(int ver, std::vector<int> *fragments_list){
    //int ver=v->get_version();

    //std::vector<int> fragments_list;
    if(ver==0){return;}

    //if(ver not in fragments_list){
    //if (std::find(fragments_list->begin(), fragments_list->end(), ver) = fragments_list->end())
    if (std::count(fragments_list->begin(), fragments_list->end(), ver)==0) 
    {
        fragments_list->push_back(ver);
    }

    std::vector<int> parents=get_parents_from_ver(ver);

    for (int i = 0; i < parents.size(); i++)
    {
        fragments_to_make_vertex(parents[i],fragments_list);
    }
    
}

// bool Graph::insert_recreated_version(){

// }

// void Graph::printVertexs(){
//     for (int i = 0; i < vertexs.size(); i++)
//     {
        
//     }
    
// }


std::vector<int> Graph::get_parents_from_ver(int ver){
    std::vector<int> Parents;
    for (int i = 0; i < adjacent_matrix.size(); i++)
    {
        if(adjacent_matrix[i][ver]!=0){
        Parents.push_back(i);
        }
    }
    return Parents;
}


void Graph::add_child_m(Vertex* newParent, Vertex* n,int num_of_cells ){


    int parentVer=newParent->get_version();

    int ver=n->get_version();

    // if(adjacent_matrix.size()-1<ver){
    //     adjacent_matrix.resize(ver,std::vector<int>(ver));
    //     visited.resize(ver,std::vector<int>(ver));
    // }

    adjacent_matrix[parentVer][ver] = num_of_cells;
    n->add_parent(newParent);
    n->add_weight(num_of_cells);
    return;
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

	
    //adjacent_matrix[parentVer][adjacent_matrix[parentVer].size()-1] = n->no_of_cells();
    
    int ver=n->get_version();

//     if(adjacent_matrix.size()-1<ver){
//         //resize matrix

// // //vector<vector<int>> M;
// // //int m = number of rows, n = number of columns;
// // M.resize(m, vector<int>(n));
//         adjacent_matrix.resize(ver,std::vector<int>(ver));
//         visited.resize(ver,std::vector<int>(ver));
//     }

    adjacent_matrix[parentVer][ver] = n->no_of_cells();
    n->add_parent(newParent);
    n->add_weight(n->no_of_cells());
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

    // void Graph::check_materialization(int sum_of_weight,int thresh){


    //     if(sum_of_weight > thresh){
    //         return true;
    //     }
    //     return false;
    // }

void Graph::DFS(int v,int sum_of_weight,int thresh)
{
    //std::map<int, bool> visited;
   // vector<int> visited;

    //std::vector<std::vector<bool>> visited;
    
    //visited[v][i] = true;
    //cout << v << " ";

    //vector<int>::iterator i;
    //int sum_of_weight=0;
    //for (i = adjacent_matrix[v][.begin()]; i != adjacent_matrix[v].end(); ++i){
    for (int i = 0; i < adjacent_matrix[v].size(); i++)
    {
        if(adjacent_matrix[v][i]!=0){

            if(!visited[v][i]){

                sum_of_weight=sum_of_weight+adjacent_matrix[v][i];

                if(sum_of_weight>thresh){
                    //materialization(v,i);
                    materialization(i);
                    //set_materialized();
                    sum_of_weight=0;
                }

                // DFS(*i);   
                visited[v][i] = true;

                DFS(i,sum_of_weight,thresh);             
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

        return;
        
}
        


    // Vertex* Graph::get_vertex_from_ver(int ver){

    // }
    void Graph::set_materialized(int i){
        vertexs[i].set_materialized();
    }


   void Graph::materialization(int i){

    //    std::vector<int> parents = get_parents_from_ver(i);

    //     get_vertex_from_ver();


    //     parents+ver;
        set_materialized(i);

        return;

   }





