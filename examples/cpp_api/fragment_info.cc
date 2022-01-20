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
#include <chrono>
//#include "tiledb/sm/misc/types.h"
//#include "../../tiledb/sm/misc/types.h"
using namespace tiledb;
typedef std::vector<std::vector<std::pair<int, std::pair<int, int>>>> non_empty;
// Name of array.
std::string array_name("fragment_info_array");

int range=5000;

void create_array() {//Domain &domain, Context &ctx
  // Create a TileDB context.
  Context ctx; ///modiified

  // The array will be 4x4 with dimensions "rows" and "cols", with domain [1,4]
  // and space tiles 2x2
  Domain domain(ctx); ///modified
std::cout<<"------line41----"<<std::endl;
  domain.add_dimension(Dimension::create<int>(ctx, "rows", {{1, range}}, 20))
        .add_dimension(Dimension::create<int>(ctx, "cols", {{1, range}}, 20));
std::cout<<"------line44----"<<std::endl;
  // domain.add_dimension(Dimension::create<int>(ctx, "rows", {{1, 400}}, 2))
  //     .add_dimension(Dimension::create<int>(ctx, "cols", {{1, 400}}, 2));

  // The array will be dense.
  ArraySchema schema(ctx, TILEDB_SPARSE);
  
  //schema.set_domain(domain).set_order({{TILEDB_ROW_MAJOR, TILEDB_ROW_MAJOR}}); //// Pair of {tile order, cell order}
  schema.set_domain(domain).set_order({{TILEDB_ROW_MAJOR, TILEDB_HILBERT}}); //// Pair of {tile order, cell order}

// Parameters

// layout: For a write query, this specifies the order of the cells provided by the user in the buffers. For a read query, this specifies the order of the cells that will be retrieved as results and stored in the user buffers. The layout can be one of the following:

// TILEDB_COL_MAJOR: This means column-major order with respect to the subarray.

// TILEDB_ROW_MAJOR: This means row-major order with respect to the subarray.

// TILEDB_GLOBAL_ORDER: This means that cells are stored or retrieved in the array global cell order.

// TILEDB_UNORDERED: This is applicable only to writes for sparse arrays, or for sparse writes to dense arrays. It specifies that the cells are unordered and, hence, TileDB must sort the cells in the global cell order prior to writing.



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
  const std::vector<int> subarray = {1, range, 1, range};

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

void time_travel_only(uint64_t timestamp){
  // ... create context ctx
Context ctx;

// Open at a timestamp
//uint64_t timestamp = 1561492235844; // In ms
Array array(ctx, array_name, TILEDB_READ, timestamp);
// Slice only rows 1, 2 and cols 2, 3, 4
  const std::vector<int> subarray = {1, range, 1, range};

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

  // // Print out the results.
  // auto result_num = (int)query.result_buffer_elements()["a"].second;

  // for (int r = 0; r < result_num; r++) {
  //   int i = coords_rows[r];
  //   int j = coords_cols[r];
  //   int a = data[r];
  //   std::cout << "Cell (" << i << ", " << j << ") has data " << a << "\n";

  // }

}

void materialization(uint64_t timestamp){

Context ctx;
Config config;
config["sm.consolidation.timestamp_end"]=timestamp;
//Array array(ctx, array_name, TILEDB_READ, timestamp);
//config["sm.consolidation.steps"] = 3;
//array.consolidate(ctx, array_name, config);
Array::consolidate(ctx, array_name, &config);
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

int x_min[]={
4347, 3548, 3523, 3150, 2975, 2962, 2914, 2767, 2669, 2660, 2634, 2616, 2419, 2391, 2387, 2243, 2193, 2189, 2112, 2071, 2068, 2060, 2005, 1984, 1978, 1956, 1878, 1816, 1787, 1674, 1656, 1643, 1617, 1602, 1588, 1579, 1577, 1574, 1550, 1544, 1483, 1425, 1351, 1334, 1321, 1314, 1302, 1288, 1274, 1236, 1210, 1192, 1187, 1147, 1122, 1040, 1035, 1033, 1007, 1001, 997, 996, 991, 973, 936, 860, 859, 844, 843, 772, 731, 722, 704, 659, 640, 639, 635, 631, 620, 579, 532, 517, 514, 513, 507, 499, 419, 415, 408, 396, 385, 383, 368, 349, 295, 237, 203, 137, 118, 72
};

int x_max[]={
4585, 4843, 4909, 4757, 4355, 4740, 4655, 4717, 4609, 3736, 4473, 4685, 3043, 4177, 3868, 3899, 4386, 3918, 4683, 4197, 2578, 4814, 4799, 4935, 4906, 4832, 4101, 3947, 4928, 3998, 3724, 4840, 4385, 4017, 3568, 3752, 4187, 2665, 3019, 4486, 4264, 4324, 3075, 3592, 3890, 4713, 3847, 4882, 4589, 2927, 3387, 3918, 3745, 3491, 4700, 3936, 3969, 2053, 2461, 3362, 3598, 3879, 3352, 2816, 4129, 3386, 2523, 2959, 2998, 3309, 3817, 3281, 4147, 3495, 2498, 4018, 2366, 1755, 2363, 3062, 4431, 3577, 3841, 3984, 4583, 3307, 3500, 3146, 2857, 3755, 3436, 1905, 2719, 4460, 1608, 1787, 2647, 2492, 1549, 2165
};

int y_min[]={
4199, 3480, 3472, 3127, 2952, 2808, 2764, 2760, 2657, 2603, 2568, 2540, 2453, 2434, 2403, 2351, 2302, 2285, 2283, 2266, 2213, 2183, 2164, 2155, 2154, 2108, 2070, 2050, 1982, 1938, 1898, 1893, 1847, 1805, 1753, 1740, 1666, 1652, 1610, 1577, 1470, 1423, 1394, 1338, 1337, 1326, 1302, 1293, 1292, 1281, 1261, 1251, 1231, 1225, 1220, 1167, 1158, 1134, 1114, 1109, 1105, 1097, 1089, 1088, 1082, 1032, 957, 916, 870, 847, 773, 752, 679, 665, 662, 659, 645, 620, 583, 580, 566, 555, 548, 544, 520, 489, 466, 465, 435, 388, 379, 367, 332, 196, 195, 181, 161, 128, 54, 2
};

int y_max[]={
4642, 4814, 4972, 4291, 4850, 4551, 4795, 4670, 4749, 4956, 4720, 4375, 3453, 4306, 4849, 4548, 3379, 4575, 4330, 4163, 4744, 4329, 4678, 3994, 4295, 4490, 3392, 4506, 3892, 3980, 4026, 4587, 4680, 4729, 4321, 4903, 4034, 4126, 3771, 3646, 4876, 3982, 4371, 4594, 4301, 4167, 3920, 2807, 4829, 3542, 4961, 4864, 3416, 3030, 4656, 3318, 3248, 2582, 4947, 4994, 3693, 4301, 4146, 4894, 4634, 3433, 4470, 3421, 1591, 3653, 3534, 2536, 2375, 4236, 2576, 2806, 2923, 2938, 3645, 4258, 2768, 2623, 3071, 3590, 2761, 3456, 2803, 1586, 3658, 2622, 3575, 4128, 2214, 2774, 1990, 2286, 1326, 3412, 3168, 1760
};


int main() {
  range=5000;
  using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::nanoseconds;

  int dimension_size = 100;
  int threshold = 2 * range * range;

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
  graph.DFS(0,0,threshold,maxHeight,0);
  //graph.reset_materialization_list();
  //graph.print_vertexs();

  std::cout<<"Maxheigh:"<<maxHeight << std::endl << std::endl;

  // graph.print_graph();


  // int iSecret;
  // int visited=0;
  // /* initialize random seed: */
  // srand (time(NULL));

  // iSecret = rand() % dimension_size + 1;
  // graph.visit(0,iSecret,visited);
  //  visited=0;
  // iSecret = rand() % dimension_size + 1;
  // graph.visit(0,iSecret,visited);
  //  visited=0;
  // iSecret = rand() % dimension_size + 1;
  // graph.visit(0,iSecret,visited);

// std::vector<int> Totalmaterializednumberofvertices;
// std::vector<int> thresholdList;

// for(float i = 0.1; i < 10 ; i = i + 0.1){
//   threshold = i * 1000 * 1000;
//   std::cout << "For "<<  i <<" x times, ";
//   graph.DFS(0,0,threshold,maxHeight,0);

//   thresholdList.push_back(threshold);
  
//   int numOfMedV=graph.materialization_list();

//   Totalmaterializednumberofvertices.push_back(numOfMedV);

//   //graph.reset_materialization_list();
// }


// for (auto v :Totalmaterializednumberofvertices){
//  std::cout << v <<",";
// }

// std::cout<< std::endl;

// for (auto v :thresholdList){
//   std::cout << v <<",";
// }

// std::cout<< std::endl;

std::vector<int> timeNeededForCreateEachVertex;

for (int i = 0; i < timestamps_vector.size(); i++)
{
  auto t1 = high_resolution_clock::now();

  time_travel_only(timestamps_vector[i]);

  auto t2 = high_resolution_clock::now();
  auto ms_int = duration_cast<nanoseconds>(t2 - t1);
  timeNeededForCreateEachVertex.push_back(ms_int.count());
}


std::cout <<  "timeNeededForCreateEachVertex: "<<std::endl;

for (auto v :timeNeededForCreateEachVertex){
  std::cout << v <<",";
}

std::cout<<std::endl;
std::cout <<  "hihi: "<<std::endl;



std::cout<<"-------------------------------------------------"<<std::endl;



auto mat_list= graph.return_materialize();

std::cout<<"timestemplist to be materialized:"<<std::endl;

for (int i = 0; i < mat_list.size(); i++)
{
  std::cout<<mat_list[i]<<","<<std::endl;
}

std::cout<<"-------------------------------------------------"<<std::endl;
std::vector<int> timeNeededForMAtEachVertex;
for (int i = 0; i < mat_list.size(); i++)
{
  auto t1 = high_resolution_clock::now();

  materialization(mat_list[i]);

  auto t2 = high_resolution_clock::now();
  auto ms_int = duration_cast<nanoseconds>(t2 - t1);

  timeNeededForMAtEachVertex.push_back(ms_int.count());
}

std::cout <<  "Time Needed For Materialising Each Vertex: "<<std::endl;

for (auto v :timeNeededForMAtEachVertex){
  std::cout << v <<",";
}
std::cout<<"-------------------------------------------------"<<std::endl;

std::vector<int> timeNeededForReadingVertexAfterMaterialization;
for (int i = 0; i < timestamps_vector.size(); i++)
{
  auto t1 = high_resolution_clock::now();

  time_travel_only(timestamps_vector[i]);

  auto t2 = high_resolution_clock::now();

  auto ms_int = duration_cast<nanoseconds>(t2 - t1);

  timeNeededForReadingVertexAfterMaterialization.push_back(ms_int.count());
}
std::cout <<  "time Needed For Reading Vertex After Materialization: "<<std::endl;

for (auto v :timeNeededForReadingVertexAfterMaterialization){
  std::cout << v <<",";
}
std::cout<<std::endl<<"-------------------------------------------------"<<std::endl;
  return 0;
}


