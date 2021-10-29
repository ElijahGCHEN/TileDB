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


#include "tiledb/sm/graph/vertex.h"
#include "tiledb/common/logger.h"
#include "tiledb/sm/array_schema/dimension.h"
#include "tiledb/sm/buffer/buffer.h"
#include "tiledb/sm/buffer/const_buffer.h"
#include "tiledb/sm/enums/datatype.h"
#include "tiledb/sm/misc/utils.h"

#include <cassert>
#include <iostream>
#include <list>

using namespace tiledb::common;

namespace tiledb {
namespace sm {

/* ****************************** */
/*   CONSTRUCTORS & DESTRUCTORS   */
/* ****************************** */

Vertex::Vertex(){
    domain_=nullptr;
    uri="";
}

Vertex::Vertex(const Domain* domain, std::string uri,NDRange non_empty,int ver)
    :domain_(domain),uri(uri),non_empty_domain_(non_empty),versionNo(ver)
    {
      no_of_cells=domain_->cell_num(ptr->domain_->domain());
      
}

Vertex::~Vertex() =default;

Vertex::Vertex(const Vertex& vtx):Vertex(){
  auto clone = vtx.clone();
  swap(clone);
}

 /** Move constructor. */
Vertex::Vertex(Vertex&& vtx) noexcept
    : Vertex() {
  swap(vtx);
}

Vertex& Vertex::operator=(const Vertex& vtx) {
  auto clone = vtx.clone();
  swap(clone);

  return *this;
}

Vertex& Vertex::operator=(Vertex&& vtx) noexcept {
  swap(vtx);

  return *this;
}


/* ********************************* */
/*                 API               */
/* ********************************* */

bool Vertex::if_contain(vertex*vtr){
  //unsigned dim_num_=vtr->domain_->dim_num();
  //int dim_num = NDRange.size();
  unsigned dim_num=domian_->dim_num();

  if(vtr->domina_->dim_num() > dim_num){return false;}
  
  auto newNDRange=domain_->get_NDRange();

  
  

  for(int i=0;i<(int)dim_num<i++){
    // Range Outside=vtr->domain_->domain(i);
    // Range Inside=domain_->domain(i);
    if(newNDRange[i] > NDRange_[i]){
        return false;
    }
  }
    return true;
}

void Vertex::add_children(vertex* ptr){

    if(if_contain(ptr)){
    int cell_num=ptr->domain_->cell_num(ptr->domain_->domain());

    child_map.insert(ptr,cell_num);
    ptr->add_parents(this);
    }
    //cell_num(fragments[i].expanded_non_empty_domain());
}

void Vertex::add_parent(vertex* ptr){

  parents.push_back(ptr->get_version());

}

bool Vertex::has_parent(){

  if(parents.empty()){return true;}
  return false;
}


int Vertex::no_of_cells(){
  return no_of_cells;
}

int Vertex::get_version(){

  return versionNo;
}

Vector<int> Vertex::get_parent(){
    return parents;
}


unsigned Vertex::dim_num() const {
  return (domain_ == nullptr) ? 0 : domain_->dim_num();
}

const Domain* Vertex::domain() const {
  return domain_;
}

Vertex Vertex::clone() const {
  Vertex clone;
  clone.domain_ = domain_;
  clone.uri=uri;
  clone.child_map=child_map;
  //clone.fanout_ = fanout_;
  //clone.levels_ = levels_;

  return clone;
}

void Vertex::swap(Vertex& vtx) {
  std::swap(domain_, vtx.domain_);
  std::swap(uri, vtx.uri);
  std::swap(child_map, vtx.child_map);
}

bool Vertex::if_materialized(){
  return materialized
}

void Vertex::set_materialized(){
  materialized=1;
}