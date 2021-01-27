#include <algorithm>
#include "StickerSheet.h"

using namespace std;

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    base = new Image(picture);
    stickers = new Image*[max]();
    max_layer = max;
    xcoord = new int[max];
    ycoord = new int[max];
}

StickerSheet::~StickerSheet() {
    clear();
}

StickerSheet::StickerSheet(const StickerSheet& other) {
    copy(other);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet& other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return (*this);
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max > max_layer) {
        Image** new_stickers = new Image*[max]();
        int* new_xcoord = new int[max];
        int* new_ycoord = new int[max];
        for (unsigned i = 0; i < max_layer; i++) {
            //if (stickers[i] != NULL) { 
                new_stickers[i] = stickers[i];
                new_xcoord[i] = xcoord[i];
                new_ycoord[i] = ycoord[i];
            //}
        }
        delete []stickers;
        delete []xcoord;
        delete []ycoord;
        stickers = new_stickers;
        xcoord = new_xcoord;
        ycoord = new_ycoord;
    }
    else {
        for (unsigned i = max; i < max_layer; i++) {
            delete stickers[i];
            stickers[i] = NULL;
        }
    }
    max_layer = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    for (unsigned i = 0; i < max_layer; i++) {
        if (stickers[i] == NULL) {
            //add
            stickers[i] = new Image(sticker);
            xcoord[i] = x;
            ycoord[i] = y;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= max_layer || stickers[index] == NULL)
        return false;
    xcoord[index] = x;
    ycoord[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= max_layer)
        return;
    if (stickers[index]) {
        delete stickers[index];
        stickers[index] = NULL;
    }
}

Image * StickerSheet::getSticker(unsigned index) const {
    if (index >= max_layer)
        return NULL;
    return stickers[index];
}

Image StickerSheet::render() const {
    Image myArt(*base);
    for (unsigned i = 0; i < max_layer; i++) {
        int width = myArt.width();
        int height = myArt.height();
        //cout << "Entering loop :" << i << " and max layer is " << max_layer << endl;
        if (stickers[i] != NULL) {
            //TODO: check size
            //cout << i << " is NOT NULL" << endl;
            int sticker_w = stickers[i] -> width();
            int sticker_h = stickers[i] -> height();
            if (xcoord[i] + sticker_w > width || ycoord[i] + sticker_h > height) {
                myArt.resize(max(xcoord[i] + sticker_w, width), max(ycoord[i] + sticker_h, height));
            }
            //TODO: change pixel by pixel
            for (int y = 0; y < sticker_h; y++) 
                for (int x = 0; x < sticker_w; x++) {
                    cs225::HSLAPixel &pixel = myArt.getPixel(xcoord[i] + x, ycoord[i] + y);
                    cs225::HSLAPixel &new_pixel = stickers[i] -> getPixel(x, y);
                    if (new_pixel.a != 0)
                        pixel = new_pixel;
                }
        }
        //cout << "Exiting loop :" << i << endl;
    }
    return myArt;
}

void StickerSheet::clear() {
    delete base;
    for (unsigned i = 0; i < max_layer; i++) {
        if (stickers[i] != NULL) {
            delete stickers[i];
            stickers[i] = NULL;
        }
    }
    delete []stickers;
    stickers = NULL;
    delete []xcoord;
    delete []ycoord;
    xcoord = NULL;
    ycoord = NULL;
}

void StickerSheet::copy(const StickerSheet &other) {
    base = new Image(*other.base);
    max_layer = other.max_layer;
    stickers = new Image* [max_layer]();
    xcoord = new int [max_layer];
    ycoord = new int [max_layer];
    for (unsigned i = 0; i < max_layer; i++) {
        if (other.stickers[i] != NULL) {
            stickers[i] = new Image(*other.stickers[i]);
            xcoord[i] = other.xcoord[i];
            ycoord[i] = other.ycoord[i];
        }
    }
}
