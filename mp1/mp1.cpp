#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <cmath>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
    PNG *inputImg = new PNG();
    inputImg -> readFromFile(inputFile);
    int width = inputImg -> width();
    int height = inputImg -> height();
    PNG *outputImg = new PNG(width, height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            HSLAPixel & inputPixel = inputImg -> getPixel(x,y);
            HSLAPixel & outputPixel = outputImg -> getPixel(width - 1 - x, height - 1 - y);
            outputPixel.h = inputPixel.h;
            outputPixel.s = inputPixel.s;
            outputPixel.l = inputPixel.l;
            outputPixel.a = inputPixel.a;
        }
    }
    outputImg -> writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
    PNG png(width, height);
    // TODO: Part 3
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            HSLAPixel & pixel = png.getPixel(x,y);
            pixel.h = 11 + 30 * (fabs(x + y) / (width + height));
            pixel.s = 1.0;
            pixel.l = 0.5;
        }
    }
    return png;
}
