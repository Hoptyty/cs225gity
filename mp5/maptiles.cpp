/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> points;
    map<Point<3>, unsigned> color2index;
    for (unsigned i = 0; i < theTiles.size(); i++) {
        LUVAPixel pixel = theTiles[i].getAverageColor();
        Point<3> point = convertToXYZ(pixel);
        points.push_back(point);
        color2index.insert(pair<Point<3>, unsigned>(point, i));
    }
    KDTree<3>* kdtree = new KDTree<3>(points);

    int h = theSource.getRows();
    int w = theSource.getColumns();
    MosaicCanvas* mosaic = new MosaicCanvas(h, w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            LUVAPixel pixel = theSource.getRegionColor(i, j);
            Point<3> color = convertToXYZ(pixel);
            Point<3> nearest = kdtree -> findNearestNeighbor(color);
            unsigned index = color2index[nearest];
            mosaic -> setTile(i, j, &theTiles[index]);
        }
    }

    return mosaic;
}

