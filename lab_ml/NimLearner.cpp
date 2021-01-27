/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    startingTokens_ = startingTokens;
    Vertex v1_0 = "p1-0";
    Vertex v2_0 = "p2-0";
    g_.insertVertex(v1_0);
    g_.insertVertex(v2_0);
    Vertex v1_1 = "p1-1";
    Vertex v2_1 = "p2-1";
    g_.insertVertex(v1_1);
    g_.insertVertex(v2_1);
    g_.insertEdge(v2_1, v1_0);
    g_.setEdgeWeight(v2_1, v1_0, 0);
    g_.insertEdge(v1_1, v2_0);
    g_.setEdgeWeight(v1_1, v2_0, 0);
    for (unsigned i = 2; i <= startingTokens; i++) {
        Vertex v1_2 = "p1-" + std::to_string(i);
        Vertex v2_2 = "p2-" + std::to_string(i);
        g_.insertVertex(v1_2);
        g_.insertVertex(v2_2);
        g_.insertEdge(v2_2, v1_1);
        g_.setEdgeWeight(v2_2, v1_1, 0);
        g_.insertEdge(v1_2, v2_1);
        g_.setEdgeWeight(v1_2, v2_1, 0);
        g_.insertEdge(v2_2, v1_0);
        g_.setEdgeWeight(v2_2, v1_0, 0);
        g_.insertEdge(v1_2, v2_0);
        g_.setEdgeWeight(v1_2, v2_0, 0);
        v1_0 = v1_1;
        v2_0 = v2_1;
        v1_1 = v1_2;
        v2_1 = v2_2;
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
  int n = startingTokens_;
  Vertex v1 = "p1-" + std::to_string(n);
  unsigned i = 1;
  while (n) {
    n -= (1 + rand() % std::min(n, 2));
    Vertex v2 = "p" + std::to_string(1 + i % 2) + "-" + std::to_string(n);
    path.push_back(g_.getEdge(v1, v2));
    v1 = v2;
    i++;
  } 
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
    int update = 1; 
    for (auto it = path.rbegin(); it != path.rend(); it++) {
        int weight = g_.getEdgeWeight((*it).source, (*it).dest);
        weight += update; 
        update *= -1;
        g_.setEdgeWeight((*it).source, (*it).dest, weight);
    }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
