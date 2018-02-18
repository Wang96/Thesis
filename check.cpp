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

// std::fstream& GotoLine(std::fstream& file, int num){
//     file.seekg(std::ios::beg);
//     for(int i=0; i < num - 1; ++i){
//         file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//     }
//     return file;
// }

void sortN(std::string const &filename, std::string const &output){
  std::fstream file(filename.c_str());
  std::string line;
  std::getline(file,line);
  std::getline(file,line);
  std::vector<std::vector<int> > v;
  std::vector<int> temp;
  int num;
  while(std::getline(file,line)){
    std::istringstream iss(line);
    while(iss >> num){
      temp.push_back(num);
      //printf("push_back: %d ", num);
    }
    sort(temp.begin(),temp.end());
    v.push_back(temp);
    temp.clear();
    //printf("\n");
  }
  sort(v.begin(),v.end());

  std::ofstream outputFile;
  outputFile.open(output.c_str());
  std::vector<std::vector<int> >::iterator it;
  std::vector<int>::iterator itr;
  for(it = v.begin(); it != v.end(); it++){
    for(itr = it->begin(); itr != it->end(); itr++){
      outputFile << *itr << " ";
      //printf("subgraph output %d\n", *itr);
    }
    outputFile << std::endl;
  }
}

// std::vector<std::vector<int> > combine(std::vector<std::vector<int> > cliques){
//   std::vector<std::vector<int> >::iterator it = cliques.begin();
//   int current;
//   int previous;
//   std::vector<std::vector<int> > v;
//   std::vector<int> ctemp;
//   std::vector<int> ptemp;
//   while(it != cliques.end()){
//     previous = current;
//     ptemp = ctemp;
//     ctemp.clear();
//     std::vector<int>::iterator itr = it->begin();
//     current = *itr;
//     while(itr != it->end()){
//       ctemp.push_back(*itr);
//       itr++;
//     }
//     if(current == previous){
//       for(itr = ptemp.begin(); itr != ptemp.end(); itr++){
//         ctemp.push_back(*itr);
//       }
//     }
//     else{
//       v.push_back(ptemp);
//     }
//     it++;
//   }
//   return v;
// }
//
// bool check(std::string const &origin, std::string const &subgraph){
//   std::vector<std::vector<int> > vo = (sortN(origin));
//   std::vector<std::vector<int> > vs = (sortN(subgraph));
//   std::vector<std::vector<int> >::iterator it = vs.begin();
//   std::vector<std::vector<int> >::iterator itt = vo.begin();
//   while(it != vs.end()){
//     std::vector<int>::iterator itr;
//     itr = it->begin();
//     std::vector<int>::iterator itrr;
//     itrr = itt->begin();
//     while(*itr != *itrr){
//       itt++;
//       itrr = itt->begin();
//     }
//     for(itr = it->begin(); itr != it->end(); itr++){
//       if(std::find(itt->begin(),itt->end(),*itr) == itt->end()){
//         printf("%d is not in original cliques!!\n", *itr);
//       }
//     }
//     it++;
//   }
//   return true;
// }

bool checkCorrect(std::string const &origin, std::string const &subgraph){
  //sortN(origin, "origin_sort0.graph");
  sortN(subgraph, "subgraph_sort0.graph");
  std::fstream file1("../quick-cliques/origin_sort0.graph");
  std::fstream file2("subgraph_sort0.graph");

  std::string oline;
  std::string sline;
  int current_s;
  int current_o;
  bool stop = std::getline(file1,oline);
  //std::getline(file1,oline);
  //std::getline(file1,oline);
  //std::getline(file2,sline);
  //std::getline(file2,sline);
  bool end = std::getline(file2,sline);
  //printf("oline %s\n", oline.c_str());
  //printf("sline %s\n", sline.c_str());
  //printf("first line %s\n", sline.c_str());

  while(end && stop){
    //printf("reading line %s\n", sline.c_str());
    std::istringstream iss_s(sline);
    std::istringstream iss_o(oline);
    iss_s >> current_s;
    iss_o >> current_o;
    int current = current_s;
    //printf("%d %d\n", current_o, current_s);
    while(current_s != current_o){
      stop = std::getline(file1,oline);
      std::istringstream iss(oline);
      iss >> current_o;
      //printf("skipping line %s\n", oline.c_str());
    }
    //printf("same node now\n");
    std::vector<int> vs;
    std::vector<int> vo;
    int node;
    while(current_s == current and end){
      while(iss_s >> node){
        vs.push_back(node);
        //printf("adding node %d\n", node);
      }
      end = std::getline(file2,sline);
      std::istringstream iss(sline);
      iss >> current_s;
    }


    //printf("original line %s\n", oline.c_str());
    // printf("original node %d\n", current_o);
    while(current_o == current and stop){
      std::istringstream iss1(oline);
      while(iss1 >> node){
        vo.push_back(node);
        //printf("add node %d\n", node);
      }
      stop = std::getline(file1,oline);
      std::istringstream iss2(oline);
      iss2 >> current_o;
      //printf("nextline %s\n", oline.c_str());
    }
    //printf("current_o: %d, current_s: %d, current: %d\n", current_o, current_s,current);
    std::vector<int>::iterator it;
    for(it = vs.begin();it != vs.end();it++){
      //printf("comparing node %d\n", *it);
      if(std::find(vo.begin(), vo.end(), *it) == vo.end()){
        printf("Not a correct clique!! %d is not in original clique\n", *it);
        // printf("original size %lu\n", vo.size());
        //printf("current node is %d\n", current);
        std::vector<int>::iterator it1;
        printf("original line is: \n");
        for(it1 = vo.begin();it1 != vo.end();it1++){
          printf("%d ", *it1);
        }
        printf("\n");
        std::vector<int>::iterator it2;
        printf("subgraph line is: \n");
        for(it2 = vs.begin();it2 != vs.end();it2++){
          printf("%d ", *it2);
        }
        printf("\n");
        return false;
      }
    }
    //printf("finish current line\n");
    vs.clear();
    vo.clear();
  }



  return true;
}

int main(){
  bool result = checkCorrect("../quick-cliques/clique.graph","newsubcliques0_1.graph");
  printf("%s\n", result ? "True" : "False");
}
