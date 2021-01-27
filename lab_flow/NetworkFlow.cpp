/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {
  // YOUR CODE HERE
    vector<Vertex> vertices = g_.getVertices();
    for (size_t i = 0; i < vertices.size(); i++) {
        residual_.insertVertex(vertices[i]);
        flow_.insertVertex(vertices[i]);
    }
    vector<Edge> edges = g_.getEdges();
    for (size_t i = 0; i < edges.size(); i++) {
        residual_.insertEdge(edges[i].source, edges[i].dest);
        residual_.setEdgeWeight(edges[i].source, edges[i].dest, g_.getEdgeWeight(edges[i].source, edges[i].dest));
        residual_.insertEdge(edges[i].dest, edges[i].source);
        residual_.setEdgeWeight(edges[i].dest, edges[i].source, 0);
        flow_.insertEdge(edges[i].source, edges[i].dest);
        flow_.setEdgeWeight(edges[i].source, edges[i].dest, 0);
    }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  if (path.size() < 2)
      return 0;
  Vertex v1 = path[0];
  Vertex v2 = path[1];
  int curr_min = residual_.getEdgeWeight(v1, v2);
  for (size_t i = 2; i < path.size(); i++) {
      v1 = v2;
      v2 = path[i];
      int weight = residual_.getEdgeWeight(v1, v2);
      if (weight < curr_min)
          curr_min = weight;
  }
  return curr_min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  maxFlow_ = 0;
  vector<Vertex> path;
  while (findAugmentingPath(source_, sink_, path)) {
      int c = pathCapacity(path);
      Vertex v1 = path[0];
      for (size_t i = 1; i < path.size(); i++) {
          Vertex v2 = path[i];
          if (flow_.edgeExists(v1, v2)) {
              int f_weight = flow_.getEdgeWeight(v1, v2);
              flow_.setEdgeWeight(v1, v2, f_weight + c);
          }
          else {
              int f_weight = flow_.getEdgeWeight(v2, v1);
              flow_.setEdgeWeight(v2, v1, f_weight - c);
          }
          int r_forward_weight = residual_.getEdgeWeight(v1, v2);
          residual_.setEdgeWeight(v1, v2, r_forward_weight - c);
          int r_reverse_weight = residual_.getEdgeWeight(v2, v1);
          residual_.setEdgeWeight(v2, v1, r_reverse_weight + c);
          v1 = v2;
      }
      maxFlow_ += c;
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

