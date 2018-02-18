#include <cassert>
#include <cstdio>
#include <ctime>
#include <fstream> // ifstream
//#include <csys/resource.h>

#include <list>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


#include <set>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <algorithm>
#include <unordered_map>


std::set<int> readInSubgraph(std::string const &fileName, int partition)
{

    std::ifstream instream(fileName.c_str());
    std::ofstream outputFile;
    outputFile.open("partition0.txt");

    std::set<int> subgraph;

    int num;
    int node = 1;
    while(instream.good() && !instream.eof()){
      std::string line;
      std::getline(instream, line);
      std::istringstream iss(line);
      iss >> num;
      //printf("line: %d, partition: %d\n", node,num);
      if (num == partition && !line.empty()){
        subgraph.insert(node);
        outputFile << node << " ";
      }
      node ++;
    }
    outputFile << std::endl;

// #ifdef DEBUG
//     printf("Number of vertices: %d\n", n);
//     printf("Number of edges: %d\n", m);
// #endif
    outputFile.close();
    return subgraph;


}

// void markBoundary(std:;string const &filename, int partition){
//   std::ifstream instream(fileName.c_str());
//   std::ofstream outputFile;
//   outputFile.open("boundaryGraph0.txt");
//   string line;
//   std::getline(instream, line);
//   std::istringstream iss(line);
//   iss >> n >> m;
//   outputFile << n << " " << m << std::endl;
//
//   int current = 1;
//   std::vector<int> temp;
//   while(i < n && std::getline(instream, line)){
//     std::istringstream iss(line);
//     int target;
//     int boundary = 0;
//     temp.clear();
//     while(iss >> target){
//
//     }
//   }
// }

// std::set<int> withNeighbors(std::set<int> partition, std::string const &fileName){
//     //std::set<int> neighbors;
//     std::ifstream instream(fileName.c_str());
//     std::string line;
//     std::getline(instream, line);
//     int node;
//     int current = 1;
//     while(std::getline(instream, line)){
//       if(std::find(partition.begin(), partition.end(), current) != partition.end()){
//         std::istringstream iss(line);
//         //neighbors.insert(current);
//         while(iss >> node){
//           //if(std::find(partition.begin()))
//           partition.insert(node);
//         }
//       }
//       else{
//         std::istringstream iss(line);
//         //neighbors.insert(current);
//         int onboundary = 0;
//         while(iss >> node){
//           //if(std::find(partition.begin()))
//           onboundary = std::find(partition.begin(),partition.end(),node) != partition.end();
//           if(onboundary){
//             partition.insert(node);
//           }
//         }
//         if(onboundary){
//           partition.insert(current);
//         }
//       }
//       current++;
//     }
//     return partition;
// }
//
// std::set<int> second(std::set<int> partition, std::string const &fileName){
//   std::set<int> neighbors;
//   std::ifstream instream(fileName.c_str());
//   std::string line;
//   std::getline(instream, line);
//   int node;
//   int current = 1;
//   while(std::getline(instream, line)){
//     if(std::find(partition.begin(), partition.end(), current) != partition.end()){
//       std::istringstream iss(line);
//       //neighbors.insert(current);
//       while(iss >> node){
//         if(std::find(partition.begin(),partition.end(),node) != partition.end())
//           neighbors.insert(node);
//       }
//     }
//     current++;
//   }
//   return neighbors;
// }

std::map<int, int> remapVertex(std::string const &fileName, std::set<int> partition,
  std::string const &subgraph, std::string const &remap, std::string const &backtrack)
{
    int n, m;

    std::ifstream instream(fileName.c_str());

    std::ofstream outputFile[3];
    outputFile[0].open(subgraph.c_str());
    outputFile[1].open(remap.c_str());
    outputFile[2].open(backtrack.c_str());

    //outputFile[0] << partition.size() << std::endl;

    std::string line;

    if(!instream.good())
    {
        fprintf(stderr, "Problem with line 1 in input file\n");
        exit(1);
    }
    std::getline(instream, line);
    std::istringstream iss(line);
    iss >> n >> m;
    outputFile[0] << n << " " << m << std::endl;

    std::map<int, int> remapping;

    //printf("The partition list size is %lu, and graph size is %lu\n", partition.size(),graph.size());

    int current_id = 1;
    int i = 1;
    int count = 0;
    //std::vector<int> tmp;
    //std::vector<int> bd;
    while(i <= n && std::getline(instream, line))
    {
        std::istringstream iss(line);
        int target;
        //int boundary = std::find(ppartition.begin(), ppartition.end(), i) == ppartition.end();
        //tmp.clear();
        bool insub = (std::find(partition.begin(), partition.end(), i) != partition.end());
        if (insub){
          //outputFile << i << " ";
          //std::vector<int> neighbor;
          //neighbor.push_back(target);
          count++;
          //if (remapping.find(i) == remapping.end()){
            remapping.insert(std::pair<int, int>(i,current_id));
            outputFile[1] << i << " " << current_id << std::endl;
            outputFile[2] << current_id << " " << i << std::endl;
            current_id++;
          //}

          while(iss >> target){
            bool check  = (std::find(partition.begin(), partition.end(), target) != partition.end());
            if(check){
              //tmp.push_back(target);
              outputFile[0] << target << " ";
            }
            // if(remapping.find(target) == remapping.end() && check){
            //   remapping.insert(std::pair<int, int>(target,current_id));
            //   outputFile[1] << target << " " << current_id << std::endl;
            //   outputFile[2] << current_id << " " << target << std::endl;
            //   current_id++;
            // }
            // if(!check){
            //   boundary = 1;
            // }
          }
          // outputFile[0] << boundary << " ";
          // std::vector<int>::iterator it;
          // for(it = tmp.begin();it != tmp.end();it++){
          //     outputFile[0] << *it << " ";
          // }
        }
        i++;
        outputFile[0] << std::endl;
    }
    //     while(iss >> target){
    //       bool check = (std::find(partition.begin(), partition.end(), target) != partition.end());
    //       if(insub){
    //         /**
    //         if (remapping.find(target) == remapping.end()){
    //           remapping.insert(std::pair<int, int>(target,current_id++));
    //           outputFile[1] << target << " " << current_id << std::endl;
    //         }
    //       **/
    //         //count++;
    //         //printf("%d %d\n", i, target);
    //         tmp.push_back(target);
    //         //outputFile[0] << target << " ";
    //       }
    //       if(insub && !check){
    //         boundary = 1;
    //         bd.push_back(target);
    //       }
    //
    //     }
    //     if(insub){
    //       outputFile[0] << boundary << " ";
    //       std::vector<int>::iterator it;
    //       for(it = tmp.begin();it != tmp.end();it++){
    //         outputFile[0] << *it << " ";
    //       }
    //     }
    //     //if (insub){
    //     outputFile[0] << std::endl;
    //     //}
    //
    //     i++;
    // }
    // std::vector<int>::iterator it;
    // for(it = bd.begin(); it != bd.end(); it++){
    //   remapping.insert(std::pair<int, int>(*it,current_id));
    //   outputFile[1] << *it << " " << current_id << std::endl;
    //   outputFile[2] << current_id << " " << *it << std::endl;
    //   current_id++;
    // }
    //outputFile[0].seekp(0);
    //outputFile[0] << partition.size() << " " << count << std::endl;
    outputFile[0].close();
    outputFile[1].close();
    outputFile[2].close();
    printf("count: %d\n", count);
    return remapping;
}

void createSubgraph(std::string const &subgraph, std::set<int> partition, std::map<int, int> remapping, std::string const &newgraph){
  std::ofstream outputFile;
  outputFile.open(newgraph.c_str());
  int edges = 0;

  std::ifstream instream1(subgraph.c_str());
  std::string line;
  std::getline(instream1, line);
  while(instream1.good() && !instream1.eof()){

    std::getline(instream1, line);
    //current++;
    std::istringstream iss(line);
    int target;
    while(!line.empty() && iss >> target){
      edges++;
    }
  }
  edges = edges/2;

  outputFile << remapping.size() << " " << edges << std::endl;
  //int current = 0;
  std::ifstream instream(subgraph.c_str());
  //std::string line;
  std::getline(instream, line);
  int i = 1;
  //printf("first line %s\n", line.c_str());
  //std::vector<int> tmp;
  //int i = 0;
  while(std::getline(instream, line)){
    //tmp.clear();
    //int boundary;
    //current++;
    std::istringstream iss(line);
    int target;
    if(!line.empty() || std::find(partition.begin(), partition.end(), i) != partition.end()){
      //outputFile << i << " ";
      //iss >> boundary;
      //outputFile << boundary << " ";
      while(iss >> target){
        // if(std::find(partition.begin(),partition.end(),target) == partition.end()){
        //   boundary = 1;
        // }
        // else{
        //   tmp.push_back(remapping[target]);
        // }

        outputFile << remapping[target] << " ";
      }
      // outputFile << boundary << " ";
      // std::vector<int>::iterator it;
      // for(it = tmp.begin();it != tmp.end();it++){
      //   outputFile << *it << " ";
      // }
      outputFile << std::endl;
    }
    i++;

  }
  //outputFile.seekp(0);
  //outputFile << remapping.size() << " " << edges << std::endl;
  outputFile.close();
}



int main(){
  std::set<int> tmp = readInSubgraph("../KaHIP/tmppartition2",0);
  //std::set<int> result = withNeighbors(tmp, "../KaHIP/examples/rgg_n_2_15_s0.graph");
  //std::set<int> result = second(second(result0,"../KaHIP/examples/rgg_n_2_15_s0.graph"),"../KaHIP/examples/rgg_n_2_15_s0.graph");
  std::map<int, int> remap = remapVertex("../KaHIP/examples/rgg_n_2_15_s0.graph", tmp, "subgraph0.graph","remapping0.txt","backtrack0.txt");
  createSubgraph("subgraph0.graph", tmp, remap, "newgraph0.graph");
  //printf("%lu\n", result0.size());
  printf("%lu\n", tmp.size());
  //printf("%lu\n", result.size());
  printf("%lu\n", remap.size());
}
