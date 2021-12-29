//
// Created by 蒋希文 on 2021/12/27.
//

#ifndef BK_PARTITION_BK_H
#define BK_PARTITION_BK_H

#include <vector>
#include <map>
#include <set>
#include "Types.h"

class BK {
private:
    // In the paper, there are two parameters, which is called c and M. The parameter c is a parameter between 0 and 1,
    // in order to control the memory usage. And the parameter M is the total of memory.
    // Here we use a new parameter k instead of c * M.
    double _k;

    // In the paper, phi is the Maximal degree or the average degree number of vertices in the graph.
    unsigned int _phi;

    unsigned int _vertexNum;

    std::map<unsigned int, std::vector<VertexType>> _edges;

    std::vector<CliqueType> _cliques;

public:
    BK(unsigned int vertexNum, const std::vector<EdgeType> &edges, double c);
    std::vector<CliqueType> execute();
private:
    VertexType _selectPivot(const std::vector<VertexType> &P,
                            const std::vector<VertexType> &X);
    std::vector<CliqueType> _executeBK(const std::vector<VertexType> &vertices);
    void _executeBKRecursive(std::vector<VertexType> &R,
                             std::vector<VertexType> &P,
                             std::vector<VertexType> &X,
                             std::vector<CliqueType> &results);

    void _executePartitionBasedBK();
};

#endif //BK_PARTITION_BK_H
