#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
    if (((int)floor(x / 20) + (int)floor(y / 20)) % 2 == 0)
        return HSLAPixel(0,1,1);
  return HSLAPixel(0,1,0);
}
