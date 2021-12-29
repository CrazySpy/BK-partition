//
// Created by 蒋希文 on 2021/12/27.
//

#include <algorithm>
#include <numeric>
#include "BK.h"
#include "Types.h"
#include "Utils.h"

BK::BK(unsigned int vertexNum, const std::vector<EdgeType> &edges, double k)
        :_vertexNum(vertexNum), _k(k), _phi(0) {
    for(auto &edge : edges) {
        auto &u = edge.first, &v = edge.second;
        _edges[u].push_back(v);
        _edges[v].push_back(u);
        _phi = std::max<unsigned int>(_phi, std::max(_edges[u].size(), _edges[v].size()));
    }
}

VertexType BK::_selectPivot(const std::vector<VertexType> &P,
                            const std::vector<VertexType> &X) {
    std::vector<VertexType> unionSet;
    std::set_union(P.begin(), P.end(), X.begin(), X.end(), std::back_inserter(unionSet));

    VertexType bestInstance = unionSet[0];
    unsigned int instanceNeighbourNum = 0;
    for(auto &instanceName : unionSet) {
        if(instanceNeighbourNum <= _edges[instanceName].size()) {
            bestInstance = instanceName;
            instanceNeighbourNum = _edges[instanceName].size();
        }
    }

    return bestInstance;
}

std::vector<CliqueType> BK::_executeBK(const std::vector<VertexType> &vertices) {
    auto R = std::vector<VertexType>();
    auto P = vertices;
    auto X = std::vector<VertexType>();
    std::vector<CliqueType> results;
    _executeBKRecursive(R, P, X, results);

    return results;
}

void BK::_executeBKRecursive(std::vector<VertexType> &R,
                             std::vector<VertexType> &P,
                             std::vector<VertexType> &X,
                             std::vector<CliqueType> &results) {
    if(P.empty()) {
        if(X.empty()) {
            results.push_back(R);
        }
        return;
    }

    auto pivot = _selectPivot(P, X);
    auto &pivotNeighbour = _edges[pivot];
    std::vector<VertexType> nonPivotNeighbourP;
    // The candidate should select from the pivot's non-neighbour.
    std::set_difference(P.begin(), P.end(),
                        pivotNeighbour.begin(), pivotNeighbour.end(),
                        std::back_inserter(nonPivotNeighbourP));

    for(auto &candidateInstance : nonPivotNeighbourP) {
        auto &candidateNeighbours = _edges[candidateInstance];

        std::vector<VertexType> tmpR = R, tmpP, tmpX;
        // R = R ∪ candidate
        orderedInsert(tmpR, candidateInstance);
        // P = P ∩ candidate
        std::set_intersection(P.begin(), P.end(), candidateNeighbours.begin(), candidateNeighbours.end(),
                              std::back_inserter(tmpP));
        // X = X ∩ candidate
        std::set_intersection(X.begin(), X.end(), candidateNeighbours.begin(), candidateNeighbours.end(),
                              std::back_inserter(tmpX));

        _executeBKRecursive(tmpR, tmpP, tmpX, results);

        P.erase(std::find(P.begin(), P.end(), candidateInstance));

        orderedInsert(X, candidateInstance);
    }
}

void BK::_executePartitionBasedBK() {
    std::vector<VertexType> S, extendS;
    for(VertexType v = 1; v <= _vertexNum; ++v) {
        S.push_back(v);
        // Add v and neighbours of v into extend S.
        extendS = orderedMerge(extendS, _edges[v]);
        orderedInsert(extendS, v);

        if(_phi * extendS.size() >= _k) {
            auto cliques = _executeBK(extendS);
            for(auto &clique : cliques) {
                if(isIntersected(S, clique) && clique.front() >= S.front()) {
                    _cliques.push_back(clique);
                }
            }

            S.clear();
            extendS.clear();
        }

    }
}


std::vector<CliqueType> BK::execute() {
    _executePartitionBasedBK();
    return _cliques;
}

