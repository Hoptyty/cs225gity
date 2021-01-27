#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return adjList[v.key()].size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.insert({key, v});
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  vertexMap.erase(key);
  for (auto& it : adjList.at(key)) {
      edgeList.erase(it);
  }
  adjList.erase(key);
  for (auto& pair : adjList) {
      auto edges = pair.second;
      for (auto& it : edges) {
          if ((*it).directed())
              edgeList.erase(it);
          edges.remove(it);
      }
  }
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  edgeListIter it = edgeList.begin();
  adjList[v1.key()].push_front(it);
  if (!e.directed()) 
    adjList[v2.key()].push_front(it);
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  
  // TODO: Part 2
  if (edgeList.empty())
      return;
  bool directed = edgeList.front().get().directed();
  auto& edges = adjList[key1];
  for (auto& it : edges) {
      const E& e = *it;
      if ((e.source().key() == key1 && e.dest().key() == key2) || (e.dest().key() == key1 && e.source().key() == key2)) {
          edgeList.erase(it);
          edges.remove(it);
          break;
      }
  }
  if (!directed) {
      edges = adjList[key2];
      for (auto& it : edges) {
          const E& e = *it;
          if ((e.source().key() == key1 && e.dest().key() == key2) || (e.dest().key() == key1 && e.source().key() == key2)) {
              edges.remove(it);
              break;
          }
      }
  }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  edgeList.erase(it);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
    std::list<std::reference_wrapper<E>> edges;
    const std::list<edgeListIter>& edge_iters = adjList.at(key);
    for (auto it : edge_iters) {
        edges.push_front((*it).get());
    }

    return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  bool empty_1 = false;
  bool empty_2 = false;
  if (adjList.find(key1) == adjList.end())
      empty_1 = true;
  if (adjList.find(key2) == adjList.end())
      empty_2 = true;
  if (empty_1 && empty_2)
      return false;
  if (empty_2 || (!empty_1 && adjList.at(key1).size() < adjList.at(key2).size())) {
    const std::list<edgeListIter>& edges = adjList.at(key1);
    for (auto it : edges) {
        const E& e = *it;
        if (e.directed()) {
            if (e.source().key() == key1 && e.dest().key() == key2)
                return true;
        }
        else {
            if ((e.source().key() == key1 && e.dest().key() == key2) || (e.dest().key() == key1 && e.source().key() == key2))
                return true;
        }
    }
  }
  else {
    const std::list<edgeListIter>& edges = adjList.at(key2);
    for (auto it : edges) {
        const E& e = *it;
        if (e.directed()) {
            if (e.source().key() == key1 && e.dest().key() == key2)
                return true;
        }
        else {
            if ((e.source().key() == key1 && e.dest().key() == key2) || (e.dest().key() == key1 && e.source().key() == key2))
                return true;
        }
    }
  }
  return false;
}
