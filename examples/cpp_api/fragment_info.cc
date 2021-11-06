/**
 * @file   fragment_info.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2021 TileDB, Inc.

 *
 * @section DESCRIPTION
 *
 * When run, this program will create a simple 2D dense array, write some data
 * with one query (creating a fragment) and collect information on the fragment.
 */

// #include "../../tiledb/sm/graph/graph.h"
// #include "../../tiledb/sm/graph/vertex.h"
#include "graph/graph.h"
#include "graph/vertex.h"
#include <iostream>
#include <random>
#include <bits/stdc++.h>
#include <algorithm>
#include <tiledb/tiledb>
#include <vector>
//#include "tiledb/sm/misc/types.h"
//#include "../../tiledb/sm/misc/types.h"
using namespace tiledb;
typedef std::vector<std::vector<std::pair<int, std::pair<int, int>>>> non_empty;
// Name of array.
std::string array_name("fragment_info_array");

void create_array() {//Domain &domain, Context &ctx
  // Create a TileDB context.
  Context ctx; ///modiified

  // The array will be 4x4 with dimensions "rows" and "cols", with domain [1,4]
  // and space tiles 2x2
  Domain domain(ctx); ///modified
std::cout<<"------line41----"<<std::endl;
  domain.add_dimension(Dimension::create<int>(ctx, "rows", {{1, 1000}}, 2))
        .add_dimension(Dimension::create<int>(ctx, "cols", {{1, 1000}}, 2));
std::cout<<"------line44----"<<std::endl;
  // domain.add_dimension(Dimension::create<int>(ctx, "rows", {{1, 400}}, 2))
  //     .add_dimension(Dimension::create<int>(ctx, "cols", {{1, 400}}, 2));

  // The array will be dense.
  ArraySchema schema(ctx, TILEDB_SPARSE);
  
  schema.set_domain(domain).set_order({{TILEDB_ROW_MAJOR, TILEDB_ROW_MAJOR}});

  // Add a single attribute "a" so each (i,j) cell can store an integer.
  schema.add_attribute(Attribute::create<int>(ctx, "a"));
  //schema.add_attribute(Attribute::create<int>(ctx, "b"));
  // Create the (empty) array on disk.
  Array::create(array_name, schema);
}

void createData(int x1,int y1,int x2,int y2,std::vector<int> &coords,std::vector<int> &data){

  int iSecret;
  /* initialize random seed: */
  srand (time(NULL));
  /* generate secret number between 1 and 10: */
  //iSecret = rand() % 10 + 1;
  std::pair<int ,int > start;
  start.first=x1;
  start.second=y1;

  std::pair<int ,int > end;
  end.first=x2;
  end.second=y2;

  // std::vector<int> coords;
  // std::vector<int> data;
  for (int i = start.first; i <= end.first; i++)
  {
    for (int j = start.second; j <= end.second; j++)
    {
      coords.push_back(i);
      coords.push_back(j);
      iSecret = rand() % 10 + 1;
      data.push_back(iSecret);
    }
    
  }
}

void write_array_1() {
  Context ctx;

  std::vector<int> coords;
  std::vector<int> data;

  createData(1,1,3,5,coords,data);

  Array array(ctx, array_name, TILEDB_WRITE);
  Query query(ctx, array);
  query.set_layout(TILEDB_UNORDERED)
      .set_buffer("a", data)

      //.set_buffer("b",data2)

      //.set_subarray(subarray);
      .set_coordinates(coords);

  query.submit();
  array.close();
}

void write_array_2() {
  Context ctx;

  std::vector<int> coords;
  std::vector<int> data;

  createData(4,4,5,5,coords,data);

  Array array(ctx, array_name, TILEDB_WRITE);
  Query query(ctx, array);
  query.set_layout(TILEDB_UNORDERED)
      .set_buffer("a", data)
      //.set_subarray(subarray);
      .set_coordinates(coords);

  query.submit();
  array.close();
}

void write_array_3() {
  Context ctx;

  std::vector<int> coords;
  std::vector<int> data;

  createData(1,4,5,5,coords,data);
  Array array(ctx, array_name, TILEDB_WRITE);
  Query query(ctx, array);
  query.set_layout(TILEDB_UNORDERED)
      .set_buffer("a", data)
      //.set_subarray(subarray);
      .set_coordinates(coords);

  query.submit();
  array.close();
}

void write_array_4() {
  Context ctx;

  std::vector<int> coords;
  std::vector<int> data;
  createData(1,1,4,5,coords,data);
  Array array(ctx, array_name, TILEDB_WRITE);
  Query query(ctx, array);
  query.set_layout(TILEDB_UNORDERED)
      .set_buffer("a", data)
      //.set_subarray(subarray);
      .set_coordinates(coords);

  query.submit();
  array.close();
}

void write_array_c(std::vector<std::vector<int>> &result) {
  Context ctx;

  std::vector<int> coords;
  std::vector<int> data;
  //createData(1,1,4,5,coords,data);

  for (int i = 1; i < result.size(); i++)
  {
    for (int j = 1; i < result.size(); i++)
    {
      data.push_back(result[i][j]);
      coords.push_back(i);
      coords.push_back(j);
    }
    
  }
  

  Array array(ctx, array_name, TILEDB_WRITE);
  Query query(ctx, array);
  query.set_layout(TILEDB_UNORDERED)
      .set_buffer("a", data)
      //.set_subarray(subarray);
      .set_coordinates(coords);

  query.submit();
  array.close();
}

void write_array_5() {
  Context ctx;

  std::vector<int> coords;
  std::vector<int> data;

  createData(1,1,5,5,coords,data);

  Array array(ctx, array_name, TILEDB_WRITE);
  Query query(ctx, array);
  query.set_layout(TILEDB_UNORDERED)
      .set_buffer("a", data)
      //.set_subarray(subarray);
      .set_coordinates(coords);

  query.submit();
  array.close();
}




void write_array(int x1,int y1,int x2,int y2) {
  Context ctx;

  std::vector<int> coords;
  std::vector<int> data;

  createData(x1,y1,x2,y2,coords,data);

  Array array(ctx, array_name, TILEDB_WRITE);
  Query query(ctx, array);
  query.set_layout(TILEDB_UNORDERED)
      .set_buffer("a", data)
      //.set_subarray(subarray);
      .set_coordinates(coords);

  query.submit();
  array.close();
}

// void write_array_2() {

//   std::vector<int> coords = {1, 2, 2, 3, 3, 4, 3, 3};
//   std::vector<int> data = {2, 3, 1, 4};

//   Context ctx;
//   Array array(ctx, array_name, TILEDB_WRITE);
//   Query query(ctx, array);
//   query.set_layout(TILEDB_UNORDERED)
//        .set_buffer("a", data)
//        //.set_subarray(subarray);
//        .set_coordinates(coords);

//   query.submit();
//   array.close();

// }

void get_fragment_info(std::vector<std::vector<std::pair<std::string, std::pair<int, int>>>> &non_empty_vector
, std::vector<std::string> &urii, std::vector<int> &num_of_cells,std::vector<uint64_t> &timestamps_vector) {
  // Create TileDB context
  Context ctx;

  Array array(ctx,array_name, TILEDB_READ); ///newadd

  // Create fragment info object
  FragmentInfo fragment_info(ctx, array_name);

  // Load fragment
  fragment_info.load();

  // Get number of written fragments.
  uint32_t num = fragment_info.fragment_num();
  std::cout << "The number of written fragments is " << num << ".\n"
            << std::endl;

  for(int i=0;i<num;i++){
  // Get fragment URI
  

      std::string uri = fragment_info.fragment_uri(i);
      std::cout << "The fragment URI is " << uri.c_str() << ".\n" << std::endl;
      urii.push_back(uri);
      // Get fragment size
      uint64_t size = fragment_info.fragment_size(i);
      std::cout << "The fragment size is " << size << ".\n" << std::endl;

      // Check if the fragment is dense or sparse.
      bool dense = fragment_info.dense(i);
      if (dense == 1)
        std::cout << "The fragment is dense.\n" << std::endl;
      else
        std::cout << "The fragment is sparse.\n" << std::endl;

      // Get the fragment timestamp range
      std::pair<uint64_t, uint64_t> timestamps = fragment_info.timestamp_range(i);
      std::cout << "The fragment's timestamp range is {" << timestamps.first << " ,"
                << timestamps.second << "}.\n"
                << std::endl;

      timestamps_vector.push_back(timestamps.second);

      // Get the number of cells written to the fragment.
      uint64_t cell_num = fragment_info.cell_num(i);
      //uint64_t cell_num = fragment_info.cell_num(); //test
      std::cout << "The number of cells written to the fragment is " << cell_num
                << ".\n"
                << std::endl;
      num_of_cells.push_back(cell_num);




            // Get the format version of the fragment.
      uint32_t version = fragment_info.version(i);
      std::cout << "The fragment's format version is " << version << ".\n"
                << std::endl;
                

      // Check if fragment has consolidated metadata.
      // If not, get the number of fragments with unconsolidated metadata
      //  in the fragment info object.
      bool consolidated = fragment_info.has_consolidated_metadata(i);
      if (consolidated != 0) {
        std::cout << "The fragment has consolidated metadata.\n" << std::endl;
      } else {
        uint32_t unconsolidated = fragment_info.unconsolidated_metadata_num();
        std::cout << "The fragment has " << unconsolidated
                  << " unconsolidated metadata fragments.\n"
                  << std::endl;
      }

        //Get non-empty domain from index
      //uint64_t non_empty_dom[2];

    int num_of_dim= 2;

    std::vector<std::pair<std::string, std::pair<int, int>>> f;

    for(int j=0;j<num_of_dim;j++){
      int non_empty_dom[2];
      fragment_info.get_non_empty_domain(i, j, &non_empty_dom[0]);
      std::cout <<"Fragment "<<i<<" : "<<"dimension "<< j <<" : ("<<non_empty_dom[0]<<" , "<<non_empty_dom[1]<<"). \n"
                <<std::endl;

      std::pair<int, int> range;
      range.first = non_empty_dom[0];
      range.second = non_empty_dom[1];

      std::pair<std::string, std::pair<int, int>> dimension;
      //std::pair<int, int> dimension;
      dimension.first=std::to_string(j);
      dimension.second=range;

      
      f.push_back(dimension);
    
      
    }

    non_empty_vector.push_back(f);
  }
  
  
  // std::cout << "PPPPPPPPPPPPPrinttttttttttttttttttttttttttttttttttttttttttt"<< std::endl;
  // array.print();
  // std::cout << "PPPPPPPPPPPPPrinttttttttttttttttttttttttttttttttttttttttttt"<< std::endl;;=


  auto non_empty = array.non_empty_domain<int>();
  int num_of_dim= non_empty.size();
  for(int i=0;i<num_of_dim;i++){
      std::cout << "Dimension named " << non_empty[i].first << " has cells in [" << non_empty[i].second.first << ", " << 
          non_empty[i].second.second << "]" << std::endl;
  }


      
}

void read_array() {
  Context ctx;

  // Prepare the array for reading
  Array array(ctx, array_name, TILEDB_READ);

  // Slice only rows 1, 2 and cols 2, 3, 4
  const std::vector<int> subarray = {1, 5, 1, 5};

  // Prepare the vector that will hold the result (of size 6 elements)
  std::vector<int> data(25);
  std::vector<int> coords_rows(3);
  std::vector<int> coords_cols(3);
  // Prepare the query
  Query query(ctx, array, TILEDB_READ);
  query.set_subarray(subarray)
      .set_layout(TILEDB_ROW_MAJOR)
      .set_buffer("a", data)
      .set_buffer("rows", coords_rows)
      .set_buffer("cols", coords_cols);
  // Submit the query and close the array.
  query.submit();
  array.close();

  // Print out the results.
  auto result_num = (int)query.result_buffer_elements()["a"].second;
  for (int r = 0; r < result_num; r++) {
    int i = coords_rows[r];
    int j = coords_cols[r];
    int a = data[r];
    std::cout << "Cell (" << i << ", " << j << ") has data " << a << "\n";
  }
}

std::vector<std::vector<int>> time_travel(uint64_t timestamp){
  // ... create context ctx
Context ctx;

// Open at a timestamp
//uint64_t timestamp = 1561492235844; // In ms
Array array(ctx, array_name, TILEDB_READ, timestamp);
// Slice only rows 1, 2 and cols 2, 3, 4
  const std::vector<int> subarray = {1, 5, 1, 5};

  // Prepare the vector that will hold the result (of size 6 elements)
  std::vector<int> data(25);
  std::vector<int> coords_rows(25);
  std::vector<int> coords_cols(25);
  // Prepare the query
  Query query(ctx, array, TILEDB_READ);
  query.set_subarray(subarray)
      .set_layout(TILEDB_ROW_MAJOR)
      .set_buffer("a", data)
      .set_buffer("rows", coords_rows)
      .set_buffer("cols", coords_cols);
  // Submit the query and close the array.
  query.submit();
  array.close();

  // Print out the results.
  auto result_num = (int)query.result_buffer_elements()["a"].second;

  //std::vector<std::vector<int>> result;
  std::vector<std::vector<int>> result(6, std::vector<int> (6, 0));

  for (int r = 0; r < result_num; r++) {
    int i = coords_rows[r];
    int j = coords_cols[r];
    int a = data[r];
    std::cout << "Cell (" << i << ", " << j << ") has data " << a << "\n";
    result[i][j]=a;
  }
  return result;
}

std::vector<std::vector<int>> time_travel_by_subarray(uint64_t timestamp,std::vector<int> subarray){
  // ... create context ctx
Context ctx;

// Open at a timestamp
//uint64_t timestamp = 1561492235844; // In ms
Array array(ctx, array_name, TILEDB_READ, timestamp);
// Slice only rows 1, 2 and cols 2, 3, 4
  //const std::vector<int> subarray = {1, 5, 1, 5};

  // Prepare the vector that will hold the result (of size 6 elements)
  std::vector<int> data(25);
  std::vector<int> coords_rows(25);
  std::vector<int> coords_cols(25);
  // Prepare the query
  Query query(ctx, array, TILEDB_READ);
  query.set_subarray(subarray)
      .set_layout(TILEDB_ROW_MAJOR)
      .set_buffer("a", data)
      .set_buffer("rows", coords_rows)
      .set_buffer("cols", coords_cols);
  // Submit the query and close the array.
  query.submit();
  array.close();

  // Print out the results.
  auto result_num = (int)query.result_buffer_elements()["a"].second;

  //std::vector<std::vector<int>> result;
  std::vector<std::vector<int>> result(6, std::vector<int> (6, 0));

  for (int r = 0; r < result_num; r++) {
    int i = coords_rows[r];
    int j = coords_cols[r];
    int a = data[r];
    std::cout << "Cell (" << i << ", " << j << ") has data " << a << "\n";
    result[i][j]=a;
  }
  return result;
}


std::vector<std::vector<int>> combine_two_vertex(std::vector<std::vector<int>> &VP1, std::vector<std::vector<int>> &VP2){

  std::vector<std::vector<int>> result(VP1.size(), std::vector<int> (VP1.size(), 0));
  for (int i = 0; i < VP1.size(); i++)
  {
    for (int j = 0; j < VP1.size(); j++)
    {
      result[i][j]=VP1[i][j]-VP2[i][j];
    }
    
  }
  ///calculate non_empty_domain

return result;

}


  

void createFragment(int x1,int y1,int x2,int y2,std::vector<std::vector<std::pair<std::string, std::pair<int, int>>>> &non_empty_vector
, std::vector<std::string> &uri, std::vector<int> &num_of_cells,std::vector<uint64_t> &timestamps_vector,Graph &graph){


  write_array(x1,y1,x2,y2);

  non_empty_vector.clear();
  uri.clear();
  num_of_cells.clear();
  timestamps_vector.clear();
  get_fragment_info(non_empty_vector,uri,num_of_cells,timestamps_vector);

  int index=non_empty_vector.size()-1;
  //std::cout<<
  std::cout<<"------index----"<<index<<std::endl;
  //Vertex VerNew(*non_empty_vector.end(),*uri.end(),graph.vertexs.size(),*num_of_cells.end(),*timestamps_vector.end());
  Vertex VerNew(non_empty_vector[index],uri[index],graph.vertexs.size(),num_of_cells[index],timestamps_vector[index]);

  VerNew.print();
  std::cout<<"------line691----"<<std::endl;
  
  // auto parentvertex=graph.vertexs[graph.vertexs.size()-1];
  auto AllVertexs=graph.get_vertexs();

  std::cout<<"------line692----"<<std::endl;
  auto latestV=graph.get_latest_vertex();
  latestV.print();
  //Vertex parentvertex=AllVertexs[AllVertexs.size()-1];

  std::cout<<"------line693----"<<std::endl;
  std::vector<Vertex*> vparent(1,&AllVertexs[AllVertexs.size()-1]);
  std::cout<<"------line695----"<<std::endl;
  graph.insert(vparent,&VerNew);

  std::cout<<"------------------------------------------------------------------------------"<<std::endl;
  graph.print_vertexs();
  std::cout<<"=========================================================================="<<std::endl;

}
void createMergedFragment(Vertex &VP1,Vertex &VP2,std::vector<std::vector<std::pair<std::string, std::pair<int, int>>>> &non_empty_vector
, std::vector<std::string> &uri, std::vector<int> &num_of_cells,std::vector<uint64_t> &timestamps_vector,Graph &graph){


  
  auto V1=time_travel(VP1.get_timestamps());
  auto V2=time_travel(VP2.get_timestamps());
  auto result=combine_two_vertex(V2,V1);
  write_array_c(result);

  //write_array(x1,y1,x2,y2);

  non_empty_vector.clear();
  uri.clear();
  num_of_cells.clear();
  timestamps_vector.clear();
  get_fragment_info(non_empty_vector,uri,num_of_cells,timestamps_vector);
  int index=non_empty_vector.size()-1;
  Vertex VerNew(non_empty_vector[index],uri[index],graph.vertexs.size(),num_of_cells[index],timestamps_vector[index]);

  //auto parentvertex=*Graph::vertexs.end();

  std::vector<Vertex*> vparent;

  vparent.push_back(&VP1);
  vparent.push_back(&VP2);

  graph.insert(vparent,&VerNew);

  std::cout<<"------------------------------------------------------------------------------"<<std::endl;
  graph.print_vertexs();
  std::cout<<"=========================================================================="<<std::endl;

}

int x_min[]={678, 571, 561, 508, 483, 466, 453, 448, 444, 443, 434, 428, 428, 420, 418, 415, 413, 400, 397, 396, 395, 380, 380, 373, 366, 360, 356, 354, 334, 317, 312, 305, 288, 286, 282, 281, 280, 272, 265, 262, 261, 259, 242, 240, 230, 227, 224, 223, 222, 220, 218, 205, 203, 197, 192, 190, 185, 176, 175, 175, 172, 172, 171, 152, 151, 151, 147, 145, 145, 144, 142, 134, 133, 122, 114, 111, 107, 96, 93, 88, 83, 80, 78, 78, 74, 62, 60, 59, 57, 55, 46, 37, 36, 35, 32, 24, 17, 12, 8, 4};

int x_max[]={999, 956, 971, 985, 877, 840, 716, 840, 869, 888, 859, 772, 727, 956, 947, 854, 824, 896, 938, 974, 810, 779, 840, 895, 805, 899, 834, 804, 839, 839, 624, 844, 841, 761, 733, 465, 810, 719, 702, 767, 629, 719, 948, 687, 793, 804, 318, 882, 905, 721, 911, 830, 624, 880, 947, 881, 805, 924, 912, 701, 780, 665, 553, 622, 586, 694, 691, 866, 870, 783, 643, 694, 778, 758, 597, 889, 659, 573, 721, 543, 848, 596, 505, 731, 695, 744, 884, 710, 682, 832, 689, 468, 489, 743, 897, 792, 440, 441, 780, 709};

int y_min[]={682, 623, 575, 572, 538, 532, 510, 491, 490, 487, 458, 454, 437, 428, 424, 423, 406, 398, 383, 383, 378, 339, 323, 318, 303, 299, 289, 284, 276, 276, 276, 274, 270, 267, 267, 265, 263, 260, 260, 259, 257, 253, 251, 244, 239, 232, 228, 220, 213, 210, 208, 206, 188, 186, 180, 174, 173, 167, 165, 161, 159, 141, 138, 133, 133, 131, 130, 125, 122, 121, 115, 111, 104, 101, 101, 100, 81, 80, 80, 78, 76, 75, 66, 58, 57, 55, 52, 48, 45, 41, 39, 38, 33, 31, 30, 19, 17, 16, 11, 9};

int y_max[]={932, 998, 819, 986, 966, 744, 932, 827, 881, 862, 944, 875, 966, 862, 710, 932, 994, 888, 653, 921, 948, 723, 973, 717, 821, 702, 518, 803, 841, 954, 562, 934, 686, 892, 782, 895, 928, 859, 651, 960, 949, 812, 936, 592, 778, 930, 790, 953, 819, 845, 849, 970, 835, 462, 692, 935, 703, 584, 463, 574, 690, 503, 376, 911, 968, 523, 471, 613, 716, 357, 609, 469, 767, 651, 641, 829, 546, 358, 581, 385, 576, 543, 710, 673, 619, 547, 885, 386, 530, 589, 488, 561, 572, 724, 437, 751, 271, 558, 508, 814};


int main() {

  int dimension_size = 100;

  Graph graph(2,dimension_size);
  Context ctx;

  if (Object::object(ctx, array_name).type() == Object::Type::Array) {
    tiledb::Object::remove(ctx, array_name);
  }
  std::vector<std::vector<std::pair<std::string, std::pair<int, int>>>>  non_empty_vector;

  std::vector<std::string>  uri;

  std::vector<int> num_of_cells;

  std::vector<uint64_t> timestamps_vector;

  create_array();

  Vertex V0;

  //std::vector<Vertex> vec;
  //std::cout<<"2222222222222222"<<std::endl;
  //vec.push_back(V0);
  graph.insertRoot(&V0);

  // createFragment(1,1,3,5,non_empty_vector,uri,num_of_cells,timestamps_vector,graph);
  // createFragment(4,4,5,5,non_empty_vector,uri,num_of_cells,timestamps_vector,graph);
  // createFragment(1,4,5,5,non_empty_vector,uri,num_of_cells,timestamps_vector,graph);
  // //createFragment(1,1,4,5,non_empty_vector,uri,num_of_cells,timestamps_vector,graph);
  // createMergedFragment(graph.vertexs[graph.vertexs.size()-2],graph.vertexs[graph.vertexs.size()-1],non_empty_vector,uri,num_of_cells,timestamps_vector,graph);

  
  for (int i = 0; i < dimension_size; i++)
  {
    createFragment(x_min[i],y_min[i], x_max[i], y_max[i],non_empty_vector,uri,num_of_cells,timestamps_vector,graph);
  }

  int maxHeight=0;
  graph.DFS(0,0,200,maxHeight,0);

  graph.print_vertexs();

  std::cout<<"Maxheigh:"<<maxHeight << std::endl << std::endl;

  // graph.print_graph();


  int iSecret;
  /* initialize random seed: */
  srand (time(NULL));

  iSecret = rand() % dimension_size + 1;
  graph.visit(0,iSecret,0);
  iSecret = rand() % dimension_size + 1;
  graph.visit(0,iSecret,0);
  iSecret = rand() % dimension_size + 1;
  graph.visit(0,iSecret,0);


  return 0;
}


