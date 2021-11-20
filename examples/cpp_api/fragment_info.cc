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
3485, 3392, 3032, 3003, 2891, 2778, 2659, 2478, 2410, 2327, 2319, 2263, 2263, 2246, 2176, 2146, 2124, 2121, 2116, 2101, 2084, 2059, 2009, 1900, 1837, 1811, 1747, 1728, 1721, 1719, 1679, 1655, 1576, 1510, 1491, 1479, 1471, 1470, 1462, 1458, 1456, 1445, 1441, 1441, 1436, 1383, 1381, 1373, 1307, 1229, 1226, 1221, 1159, 1158, 1113, 1090, 1079, 1065, 1058, 1006, 964, 963, 893, 866, 788, 786, 773, 750, 733, 707, 673, 635, 634, 622, 590, 550, 509, 497, 440, 428, 424, 422, 370, 357, 273, 266, 254, 231, 181, 149, 134, 131, 105, 91, 65, 55, 37, 26, 26, 24
};

int x_max[]={
4859, 4724, 4318, 4867, 4418, 4641, 4536, 3966, 4851, 4885, 3562, 4852, 4814, 4718, 3657, 4821, 4605, 4973, 4237, 4777, 4491, 4233, 4515, 4606, 3576, 3612, 4217, 3141, 3465, 4216, 4087, 3653, 3673, 3641, 3923, 4894, 4821, 4842, 3060, 3662, 3432, 4023, 4159, 3390, 2672, 3670, 4967, 3490, 2485, 2996, 3734, 3242, 3442, 4609, 3755, 4486, 3958, 4051, 4516, 4840, 4325, 3536, 2680, 4849, 4779, 4305, 4994, 3468, 3488, 2711, 3890, 2903, 1413, 2804, 3325, 3946, 3352, 2187, 4702, 3173, 4281, 4440, 2692, 3167, 3162, 2053, 1668, 2057, 2740, 3796, 2896, 2458, 1598, 2243, 2595, 3633, 3429, 4998, 3562, 3206
};

int y_min[]={
3484, 3442, 2974, 2940, 2818, 2782, 2678, 2622, 2579, 2559, 2557, 2280, 2240, 2201, 2130, 2065, 2057, 2034, 2016, 1957, 1917, 1907, 1894, 1890, 1841, 1809, 1759, 1680, 1630, 1588, 1541, 1514, 1501, 1385, 1348, 1321, 1311, 1285, 1284, 1270, 1265, 1241, 1205, 1180, 1114, 1092, 1083, 1046, 989, 960, 940, 924, 923, 905, 848, 822, 795, 746, 740, 735, 704, 655, 643, 594, 553, 534, 518, 509, 501, 499, 478, 477, 446, 438, 430, 418, 417, 411, 398, 397, 368, 361, 317, 311, 234, 214, 213, 188, 180, 160, 155, 135, 119, 99, 97, 82, 51, 49, 27, 17
};

int y_max[]={
4120, 4725, 4146, 4953, 4860, 3710, 4504, 4986, 4758, 4983, 4142, 3631, 4399, 4958, 3575, 2880, 2900, 4661, 4537, 4430, 4562, 3773, 4578, 3508, 4882, 3113, 3922, 4159, 3754, 2731, 4828, 4961, 2702, 4759, 3677, 4146, 2192, 3835, 3641, 4044, 3725, 3337, 4454, 4336, 4535, 3893, 4312, 3032, 3757, 4236, 3170, 3255, 3072, 3168, 4748, 3651, 4357, 4175, 4247, 4518, 3360, 2916, 4260, 4980, 4441, 4606, 2081, 3259, 3902, 1884, 3335, 2738, 2719, 1798, 2260, 3164, 2983, 2055, 2458, 2218, 3352, 3303, 4241, 3576, 2384, 2856, 2546, 4961, 3297, 3020, 2108, 2717, 3937, 2410, 2261, 2272, 2157, 3099, 2412, 2264
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



// int[dimension_size] SOWList;
// SOWList=graph.DFS(0,0,threshold,maxHeight,0);
// std::cout <<  "SOWList: "<<std::endl;
// for (auto v :SOWList){
//   std::cout << v <<",";
// }
// std::cout<<std::endl;



std::cout<<"-------------------------------------------------"<<std::endl;



auto mat_list= graph.return_materialize();

std::cout<<"timestemplist to be materialized:"<<std::endl;

for (int i = 0; i < mat_list.size(); i++)
{
  std::cout<<mat_list[i]<<",";
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

std::cout <<  "timeNeededForMAtEachVertex: "<<std::endl;

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
std::cout <<  "timeNeededForReadingVertexAfterMaterialization: "<<std::endl;

for (auto v :timeNeededForReadingVertexAfterMaterialization){
  std::cout << v <<",";
}
std::cout<<"-------------------------------------------------"<<std::endl;
  return 0;
}


