#include <cmath>
#include "Image.h"
using namespace cs225;

void Image::lighten() {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.l += 0.1;
            if (pixel.l > 1)
                pixel.l = 1.0;
            else if (pixel.l < 0)
                pixel.l = 0.0;
        }
    }
}

void Image::lighten(double amount) {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.l += amount;
            if (pixel.l > 1)
                pixel.l = 1.0;
            else if (pixel.l < 0)
                pixel.l = 0.0;
        }
    }
}

void Image::darken() {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.l -= 0.1;
            if (pixel.l > 1)
                pixel.l = 1.0;
            else if (pixel.l < 0)
                pixel.l = 0.0;
        }
    }
}

void Image::darken(double amount) {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.l -= amount;
            if (pixel.l > 1)
                pixel.l = 1.0;
            else if (pixel.l < 0)
                pixel.l = 0.0;
        }
    }

}

void Image::saturate() {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.s += 0.1;
            if (pixel.s > 1)
                pixel.s = 1.0;
            else if (pixel.s < 0)
                pixel.s = 0.0;
        }
    }
}

void Image::saturate(double amount) {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.s += amount;
            if (pixel.s > 1)
                pixel.s = 1.0;
            else if (pixel.s < 0)
                pixel.s = 0.0;
        }
    }
}

void Image::desaturate() {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.s -= 0.1;
            if (pixel.s > 1)
                pixel.s = 1.0;
            else if (pixel.s < 0)
                pixel.s = 0.0;
        }
    }
}

void Image::desaturate(double amount) {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.s -= amount;
            if (pixel.s > 1)
                pixel.s = 1.0;
            else if (pixel.s < 0)
                pixel.s = 0.0;
        }
    }
}

void Image::grayscale() {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.s = 0.0;
        }
    }
}

void Image::rotateColor(double degrees) {
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            pixel.h += degrees;
            if (pixel.h > 360)
                pixel.h = fmod(pixel.h, 360.0);
            else if (pixel.h < 0)
                pixel.h = 360 + fmod(pixel.h, 360.0);
        }
    }
}

void Image::illinify() {
    double mid_pt1 = (216 + 11) / 2;
    double mid_pt2 = (216 + 360 + 11) / 2;
    int w = this -> width();
    int h = this -> height();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            if (pixel.h > mid_pt1 && pixel.h < mid_pt2) {
                pixel.h = 216; //blue
            }
            else {
                pixel.h = 11; //orange
            }
        }
    }
}

void Image::scale(double factor) {
    Image temp = Image();
    temp = *this;
    int w = this -> width();
    int h = this -> height();
    int currW = (int)(factor * w);
    int currH = (int)(factor * h);
    this -> resize(currW, currH);
    for (int j = 0; j < currH; j++) {
        for (int i = 0; i < currW; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            int prevI = (int)(i / factor);
            int prevJ = (int)(j / factor);
            pixel = temp.getPixel(prevI, prevJ);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    Image temp = Image();
    temp = *this;
    int width = this -> width();
    int height = this -> height();
    this -> resize(w, h);
    for (unsigned j = 0; j < h; j++) {
        for (unsigned i = 0; i < w; i++) {
            HSLAPixel & pixel = this -> getPixel(i, j);
            int prevI = (int)(i * width / w);
            int prevJ = (int)(j * height / h);
            pixel = temp.getPixel(prevI, prevJ);
        }
    }
}
