#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    dfs.push(start);
    w = png.width();
    h = png.height();
    visited.resize(w * h, false);
    tolerance_ = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
    DFS* dfs_traversal = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*dfs_traversal);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
    if (point.x >= w || point.y >= h || visited[point.y * w + point.x])
        return;
    HSLAPixel p1 = png_.getPixel(point.x, point.y);
    HSLAPixel p2 = png_.getPixel(start_.x, start_.y);
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;
    if (h > 180)
        h = 360 - h;
    h /= 360;
    double diff = sqrt((h * h) + (s * s ) + (l * l));
    if (diff >= tolerance_)
        return;
    dfs.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point point = dfs.top();
  dfs.pop();
  visited[point.y * w + point.x] = true;
  if (empty())
      return point;
  Point p2 = dfs.top();
  while (visited[p2.y * w + p2.x]) {
      dfs.pop();
      if (empty())
          break;
      p2 = dfs.top();
  }
  return point;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return empty() ? Point() : dfs.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return dfs.empty();
}
