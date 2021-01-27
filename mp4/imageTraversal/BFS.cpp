#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    bfs.push(start);
    w = png.width();
    h = png.height();
    visited.resize(w * h, false);
    tolerance_ = tolerance;
    visited[start.y * w + start.x] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
    BFS* bfs_traversal = new BFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*bfs_traversal);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
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
    bfs.push(point);
    visited[point.y * w + point.x] = true;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point point = bfs.front();
  bfs.pop();
  return point;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return empty() ? Point() : bfs.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return bfs.empty();
}
