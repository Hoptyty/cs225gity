#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;
  static std::unordered_map<std::string, int> dist;
  std::unordered_map<std::string, bool> visited;
  std::unordered_map<std::string, std::string> parent;
  struct comp {
      bool operator() (std::string a, std::string b) {
          return dist[a] > dist[b];
      };
  };
  std::priority_queue<string, std::vector<string>, comp> min_pq;
  for (auto v : vertexMap) {
      dist[v.first] = INT_MAX;
      visited[v.first] = false;
      parent[v.first] = "";
      if (v.first == start)
          dist[v.first] = 0;
      min_pq.push(v.first);
  }
  unsigned count = 0;
  while (count < size()) {
      std::string v = min_pq.top();
      min_pq.pop();
      if (visited[v])
          continue;
      count++;
      visited[v] = true;
      auto& edges = adjList[v];
      for (auto& it : edges) {
          const E& e = *it;
          std::string neighbor;
          if (e.source().key() == v)
              neighbor = e.dest().key();
          else
              neighbor = e.source().key();
          if (!visited[neighbor] && dist[v] + e.weight() < dist[neighbor]) {
              dist[neighbor] = dist[v] + e.weight();
              min_pq.push(neighbor);
              parent[neighbor] = v;
          }
      }
  }

  std::string v = end;
  path.push_front(end);
  while (v != start) {
      v = parent[v];
      path.push_front(v);
  }

  return path;
}

