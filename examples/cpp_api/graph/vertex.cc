/**
 * @file   vertex.cc
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
 * This file implements class vertex.
 */


#include "vertex.h"
// #include "tiledb/common/logger.h"
// #include "tiledb/sm/array_schema/dimension.h"
// #include "tiledb/sm/buffer/buffer.h"
// #include "tiledb/sm/buffer/const_buffer.h"
// #include "tiledb/sm/enums/datatype.h"
// #include "tiledb/sm/misc/utils.h"

#include <cassert>
#include <iostream>
#include <list>

//using namespace tiledb::sm;

//namespace tiledb {
//namespace sm {

/* ****************************** */
/*   CONSTRUCTORS & DESTRUCTORS   */
/* ****************************** */

Vertex::Vertex(){
    domain_=nullptr;
    uri="";
}

Vertex::Vertex(Domain* domain, std::string uri,std::vector<std::pair<std::string, std::pair<int, int>>> non_empty,int ver)
    :domain_(domain),uri(uri),NDRange_(non_empty),versionNo(ver)
    {
      //no_of_cells=domain_->cell_num(ptr->domain_->domain());
      
}

Vertex::~Vertex() =default;

// Vertex::Vertex(const Vertex& vtx):Vertex(){
//   auto clone = vtx.clone();
//   swap(clone);
// }

//  /** Move constructor. */
// Vertex::Vertex(Vertex&& vtx) noexcept
//     : Vertex() {
//   swap(vtx);
// }

// Vertex& Vertex::operator=(const Vertex& vtx) {
//   auto clone = vtx.clone();
//   swap(clone);

//   return *this;
// }

// Vertex& Vertex::operator=(Vertex&& vtx) noexcept {
//   swap(vtx);

//   return *this;
// }


/* ********************************* */
/*                 API               */
/* ********************************* */

std::vector<std::pair<std::string, std::pair<int, int>>> Vertex::get_NDRange(Vertex*vtr){

  return NDRange_;

}

bool Vertex::if_contain(Vertex*vtr){
  //unsigned dim_num_=vtr->domain_->dim_num();
  //int dim_num = NDRange.size();
  

  if(vtr->dim_num() > num_dim){return false;}
  
  auto newNDRange=vtr->get_NDRange();

  
  

  for(int i=0;i<(int)num_dim;i++){
    // Range Outside=vtr->domain_->domain(i);
    // Range Inside=domain_->domain(i);
    if(newNDRange[i].second.first >= NDRange_[i].second.first
    &&
    newNDRange[i].second.second <= NDRange_[i].second.second
    ){
        return false;
    }
  }
    return true;
}

// void Vertex::add_children(Vertex* ptr){

//     if(if_contain(ptr)){
//     int cell_num=ptr->domain_->cell_num(ptr->domain_->domain());

//     child_map.insert(ptr,cell_num);
//     ptr->add_parents(this);
//     }
//     //cell_num(fragments[i].expanded_non_empty_domain());
// }

void Vertex::add_parent(Vertex* ptr){

  parents.push_back(ptr->get_version());

}

bool Vertex::has_parent(){

  if(parents.empty()){return true;}
  return false;
}


int Vertex::no_of_cells(){
  if(num_of_cells){return num_of_cells;}
  return 0;
}

int Vertex::get_version(){

  return versionNo;
}

std::vector<int> Vertex::get_parent(){
    return parents;
}


unsigned Vertex::dim_num() {
  return num_dim;
}

// Domain* Vertex::domain() {
//   return domain_;
// }

// Vertex Vertex::clone() const {
//   Vertex clone;
//   clone.domain_ = domain_;
//   clone.uri=uri;
//   //clone.child_map=child_map;
//   //clone.fanout_ = fanout_;
//   //clone.levels_ = levels_;

//   return clone;
// }

// void Vertex::swap(Vertex& vtx) {
//   std::swap(domain_, vtx.domain_);
//   std::swap(uri, vtx.uri);
//   std::swap(child_map, vtx.child_map);
// }

bool Vertex::if_materialized(){
  return materialized;
}

void Vertex::set_materialized(){
  materialized=1;
}