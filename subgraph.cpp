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
#include <unordered_set>


std::unordered_set<int> readInSubgraph(std::string const &fileName, int partition)
{

    std::ifstream instream(fileName.c_str());
    std::ofstream outputFile;
    std::ostringstream oss;
    oss << partition;
    outputFile.open("../../projects/algo/nwang/partition"+oss.str()+".txt");

    std::unordered_set<int> subgraph;

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

std::unordered_set<int> withNeighbors(std::unordered_set<int> partition, std::string const &fileName){
    //std::set<int> neighbors;
    std::ifstream instream(fileName.c_str());
    std::string line;
    std::getline(instream, line);
    int node;
    int current = 1;
    //std::unordered_set<int> copy = partition;
    int count = 0;
    while(std::getline(instream, line)){
      if(partition.find(current) != partition.end()){
        std::istringstream iss(line);
        //neighbors.insert(current);
        while(iss >> node){
          //if(std::find(partition.begin()))
          partition.insert(node);
	}
      }
      else{
        std::istringstream iss(line);
        //neighbors.insert(current);
        int onboundary = 0;
        while(iss >> node){
          //if(std::find(partition.begin()))
          onboundary = (partition.find(node) != partition.end());
          if(onboundary){
            partition.insert(node);
          }
        }
        if(onboundary){
          partition.insert(current);
      	}
      }
      current++;
    }
    return partition;
}

std::set<int> second(std::unordered_set<int> partition, std::string const &fileName){
  std::set<int> neighbors;
  std::ifstream instream(fileName.c_str());
  std::string line;
  std::getline(instream, line);
  int node;
  int current = 1;
  while(std::getline(instream, line)){
    if(partition.find(current) != partition.end()){
      std::istringstream iss(line);
      //neighbors.insert(current);
      while(iss >> node){
        if(partition.find(node) != partition.end())
          neighbors.insert(node);
      }
    }
    current++;
  }
  return neighbors;
}

std::map<int, int> remapVertex(std::string const &fileName, std::unordered_set<int> ppartition, std::unordered_set<int> partition,
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
    int edges = 0;
    std::vector<int> tmp;
    std::vector<int> bd;

    int count = 0;
    int count1 = 0;

    int highest_degree=0;
    int within = 0;

    while(i <= n && std::getline(instream, line))
    {
        std::istringstream iss(line);
        int target;
        int boundary = (ppartition.find(i) == ppartition.end());
        tmp.clear();
	int degree = 0;
        bool insub = (partition.find(i) != partition.end());
        if (insub){
          //outputFile << i << " ";
          //std::vector<int> neighbor;
          //neighbor.push_back(target);
          if (remapping.find(i) == remapping.end()){
            remapping.insert(std::pair<int, int>(i,current_id));
            outputFile[1] << i << " " << current_id << std::endl;
            outputFile[2] << current_id << " " << i << std::endl;
            current_id++;
          }

          while(iss >> target){
            bool check  = (partition.find(target) != partition.end());
            if(check){
              tmp.push_back(target);
	      degree++;
            }

	    if(!boundary && check && (ppartition.find(target) == ppartition.end())){
		count++;
	    }
	    else if(boundary && check && (ppartition.find(target) != ppartition.end())){
		count1++;
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
          outputFile[0] << boundary << " ";
          std::vector<int>::iterator it;
          for(it = tmp.begin();it != tmp.end();it++){
              outputFile[0] << *it << " ";
	      edges++;
          }

	  if(degree > highest_degree){
		highest_degree = degree;
		within = boundary;
	  }
        }
        i++;
        outputFile[0] << std::endl;
    }

    printf("Number of edges cross blocks: %d\n", count);
    printf("NUmber of edges outside: %d\n",count1);
    printf("Number of total edges: %d\n", edges/2);
    printf("Highest degree of the subgraph: %d, boundary status: %d\n", highest_degree,within);
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
    return remapping;
}

void createSubgraph(std::string const &subgraph, std::map<int, int> remapping, std::string const &newgraph){
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
  //int i = 1;
  //printf("first line %s\n", line.c_str());
  //std::vector<int> tmp;
  while(std::getline(instream, line)){
    //tmp.clear();
    int boundary;
    //current++;
    std::istringstream iss(line);
    int target;
    if(!line.empty()){
      //outputFile << i << " ";
      iss >> boundary;
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
    //i++;

  }
  //outputFile.seekp(0);
  //outputFile << remapping.size() << " " << edges << std::endl;
  outputFile.close();
}


int main(int argc, char *argv[]){
  std::string partition_num = argv[1];
  std::string file_name = argv[2];
  std::string partition_file = argv[3];
  //printf("number of arguments: %d\n",argc);
  std::unordered_set<int> tmp = readInSubgraph(partition_file,atoi(partition_num.c_str()));
  std::unordered_set<int> result = withNeighbors(tmp, file_name.c_str());
  printf("partition_id is %d\n", atoi(partition_num.c_str()));
  //printf("file name is %s\n",file_name.c_str());
  //std::set<int> result = second(result0,"../KaHIP/examples/rgg_n_2_15_s0.graph");
  std::map<int, int> remap = remapVertex(file_name.c_str(), tmp, result, "subgraph"+partition_num+".graph","../../projects/algo/nwang/remapping"+partition_num+".txt","../../projects/algo/nwang/backtrack"+partition_num+".txt");
  createSubgraph("subgraph"+partition_num+".graph", remap, "../../projects/algo/nwang/newgraph"+partition_num+".graph");
  //printf("%lu\n", result0.size());
  printf("%lu\n", tmp.size());
  //printf("%lu\n", result.size());
  printf("%lu\n", remap.size());
}
