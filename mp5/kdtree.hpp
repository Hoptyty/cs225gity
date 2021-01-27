/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim])
        return first < second;

    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double curr_dist = 0.0;
    double potential_dist = 0.0;
    for (int i = 0; i < Dim; i++) {
       curr_dist += pow((currentBest[i] - target[i]), 2);
       potential_dist += pow((potential[i] - target[i]), 2);
    }
    if (curr_dist == potential_dist)
        return potential < currentBest;

     return potential_dist < curr_dist;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> kdtree(newPoints.begin(), newPoints.end());
    size = kdtree.size();
    root = buildTree(kdtree, 0, size - 1, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
    size = other.size;
    copy(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
    if (this != &rhs) {
        clear(root);
        size = rhs.size;
        copy(rhs.root);
    }

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
    clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    double radius_sqr = INFINITY;
    KDTreeNode* nearest = NULL;
    findNearestNeighbor(root, query, 0, radius_sqr, nearest);

    return nearest -> point;
}

template <int Dim>
void KDTree<Dim>::findNearestNeighbor(typename KDTree<Dim>::KDTreeNode* node, const Point<Dim>& query, int dim, double& radius_sqr, KDTreeNode*& curr_best) const {
    if (node == NULL)
        return;
    bool near_left = smallerDimVal(query, node -> point, dim);
    if (near_left) {
        findNearestNeighbor(node -> left, query, (dim + 1) % Dim, radius_sqr, curr_best);
    } 
    else {
        findNearestNeighbor(node -> right, query, (dim + 1) % Dim, radius_sqr, curr_best);
    }
    if (curr_best == NULL || shouldReplace(query, curr_best -> point, node -> point)) {
        curr_best = node;
        radius_sqr = 0.0;
        for (int i = 0; i < Dim; i++)
            radius_sqr += pow(node -> point[i] - query[i], 2);
    }
    if (pow(node -> point[dim] - query[dim], 2) <= radius_sqr) {
        if (near_left) {
            findNearestNeighbor(node -> right, query, (dim + 1) % Dim, radius_sqr, curr_best);
        }
        else {
            findNearestNeighbor(node -> left, query, (dim + 1) % Dim, radius_sqr, curr_best);
        }
    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* subRoot) {
    if (subRoot == NULL)
        return NULL;
    KDTreeNode* node = new KDTreeNode(subRoot -> point);
    node -> left = copy(subRoot -> left);
    node -> right = copy(subRoot -> right);
    return node;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subRoot) {
    if (subRoot == NULL)
        return;
    clear(subRoot -> left);
    clear(subRoot -> right);
    delete subRoot;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& kdtree, int start, int end, int dim) {
    if (start > end)
        return NULL;
    quickSelect(kdtree, start, end, dim);
    int median = (start + end) / 2;
    KDTreeNode* node = new KDTreeNode(kdtree[median]);
    node -> left = buildTree(kdtree, start, median - 1, (dim + 1) % Dim);
    node -> right = buildTree(kdtree, median + 1, end, (dim + 1) % Dim);
    return node;
}

template <int Dim>
void KDTree<Dim>::quickSelect(vector<Point<Dim>>& kdtree, int start, int end, int dim) {
    int median = (start + end) / 2;
    while (1) {
        if (start == end)
            return;
        Point<Dim> pivot = kdtree[end]; 
        int index = start;
        for (int i = start; i < end; i++) {
            if (smallerDimVal(kdtree[i], pivot, dim)) {
                swap(kdtree[i], kdtree[index]);
                index++;
            }
        }
        swap(kdtree[index], kdtree[end]);
        if (median == index)
            return;
        if (median < index)
            end = index - 1;
        else
            start = index + 1;
    } 
}
