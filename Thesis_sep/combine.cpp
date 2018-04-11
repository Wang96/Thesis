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
#include <limits>

bool compare(std::string line1, std::string line2){
  std::istringstream iss1(line1);
  std::istringstream iss2(line2);
  int cur1;
  int cur2;
  while(iss1 >> cur1 && iss2 >> cur2){
    if(cur1 > cur2) return true;
    else if (cur1 < cur2) return false;
  }
  printf("sub1 line: %s\n", line1.c_str());
  printf("sub2 line: %s\n", line2.c_str());
  printf("duplicate lines!!!!\n");
  return false;
}

void combine(std::string const &sub1, std::string const &sub2){
  std::ofstream outputFile;
  outputFile.open("combine.graph");

  std::fstream file1(sub1.c_str());
  std::fstream file2(sub2.c_str());

  std::string line1;
  std::string line2;
  bool end = std::getline(file1,line1);
  bool stop = std::getline(file2,line2);
  while( end && stop){
    if(!compare(line1,line2)){
      outputFile << line1 << std::endl;
      end = std::getline(file1,line1);
    }
    else{
      outputFile << line2 << std::endl;
      stop = std::getline(file2,line2);
    }
  }
  if(end){
    while(std::getline(file1,line1)){
      outputFile << line1 << std::endl;
    }
  }
  if(stop){
    while(std::getline(file2,line2)){
      outputFile << line2 << std::endl;
    }
  }
}

bool check(std::string const &sub1, std::string const &sub2, std::string const &origin){
  combine(sub1,sub2);

  std::fstream file1("combine.graph");
  std::fstream file2(origin.c_str());

  std::string line1;
  std::string line2;
  int cur1;
  int cur2;

  while(std::getline(file1,line1) && std::getline(file2,line2)){
    std::istringstream iss1(line1);
    std::istringstream iss2(line2);
    if(line1.length() != line2.length()){
      printf("created: %s\n", line1.c_str());
      printf("original: %s\n", line2.c_str());
      return false;
    }
    while(iss1 >> cur1 && iss2 >> cur2){
      if(cur1 != cur2){
        printf("created: %s\n", line1.c_str());
        printf("original: %s\n", line2.c_str());
        printf("cur1 is %d, cur2 is %d\n", cur1,cur2);
        //return false;
      }
    }
  }
  return true;
}

int main(){
  bool result = check("subgraph_sort0.graph","subgraph_sort1.graph","origin_sort.graph");
  printf("%s\n", result ? "True" : "False");
}
