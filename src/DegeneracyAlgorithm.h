#ifndef _DJS_DEGENERACY_ALGORITHM_H_
#define _DJS_DEGENERACY_ALGORITHM_H_

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

// local includes
#include "Algorithm.h"
#include "Tools.h"
#include "MemoryManager.h"
#include "DegeneracyTools.h"

// system includes
#include <list>
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <unordered_set>
#include <unordered_map>
/*! \file DegeneracyAlgorithm.h

    \brief see DegeneracyAlgorithm.cpp

    \author Darren Strash (first name DOT last name AT gmail DOT com)

    \copyright Copyright (c) 2011 Darren Strash. This code is released under the GNU Public License (GPL) 3.0.

    \image html gplv3-127x51.png

    \htmlonly
    <center>
    <a href="gpl-3.0-standalone.html">See GPL 3.0 here</a>
    </center>
    \endhtmlonly
*/

class DegeneracyAlgorithm : public Algorithm
{
public:
    DegeneracyAlgorithm(std::vector<std::list<int>> const &adjacencyList, std::unordered_map<int,int> &ordering, std::unordered_map<int,int> &backmap, std::unordered_set<int> &partition, std::unordered_map<int,int> &remapping, int flag);
    virtual ~DegeneracyAlgorithm();

    virtual long Run(std::list<std::list<int>> &cliques);

    DegeneracyAlgorithm           (DegeneracyAlgorithm const &) = delete;
    DegeneracyAlgorithm& operator=(DegeneracyAlgorithm const &) = delete;

    void listAllMaximalCliquesDegeneracyRecursive(long* cliqueCount,
                                               std::list<int> &partialClique,
                                               int* vertexSets, int* vertexLookup,
                                               int** neighborsInP, int* numNeighbors,
                                               int beginX, int beginP, int beginR);

    long listAllMaximalCliquesDegeneracy(std::vector<std::list<int>> const &adjList, int size, std::unordered_map<int,int> &degeneracyOrdering, std::unordered_map<int,int> &backmap, std::unordered_set<int> &partition, std::unordered_map<int,int> &remapping, int flag);

private:
    std::vector<std::list<int>> const &m_AdjacencyList;
    std::unordered_map<int,int> &m_ordering;
    std::unordered_map<int,int> &m_backmap;
    std::unordered_set<int> &m_partition;
    std::unordered_map<int,int> &m_remapping;
    int m_flag;
};

#endif
