
#include "PmodTft.h"

#define COLOR_RED(c)    (0xF8 (c >> 8))
#define COLOR_GREEN(c)  (0xFC (c >> 2))
#define COLOR_BLUE(c)   (0xF8 (c << 5))

#define ADDRESS(x,y)    ((y * this->width * 3) + (x * 3))

#define BLUE_OFFSET     2
#define GREEN_OFFSET    1
#define RED_OFFSET      0

PmodTFT::PmodTFT(uint32_t pmod_tft_address, uint8_t vdma_index){
    this->pmod_tft_address = pmod_tft_address;
    this->vdma_index = vdma_index;
    this->width = WIDTH;
    this->height = HEIGHT;
    this->size = this->width * this->height;
    this->frame_buffer = NULL;
    this->initialize();
}

PmodTFT::~PmodTFT(){
}

void     PmodTFT::intialize(){
    //Initialize the PMOD Tft LCD
    //Initialize the Video DMA
    //Enable a parked video frame
    //Get a reference to the current Display
}

void     PmodTFT::reset(){
    this->intialize();
}

void PmodTFT::setWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    uint8_t t0, t1;

    switch(rotation) {
        case 1:
            t0 = WIDTH - 1 - y1;
            t1 = WIDTH - 1 - y0;
            this->y0 = x0;
            this->x0 = t0;
            this->y1 = x1;
            this->x1 = t1;
            break;
        case 2:
            t0 = x0;
            this->x0 = WIDTH  - 1 - x1;
            this->x1 = WIDTH  - 1 - t0;
            t0 = y0;
            this->y0 = HEIGHT - 1 - y1;
            this->y1 = HEIGHT - 1 - t0;
            break;
        case 3:
            t0 = HEIGHT - 1 - x1;
            t1 = HEIGHT - 1 - x0;
            this->x0 = y0;
            this->y0 = t0;
            this->x1 = y1;
            this->y1 = t1;
            break;
        default:
            this->x0 = x0;
            this->x1 = x1;
            this->y0 = y0;
            this->y1 = y1;
            break;
    }

    //We need to write to a subsection of the LCD Screen (Just write to that location in memory)
}

void PmodTFT::fillScreen(uint16_t c)
{
    for(y=height; y > 0; y--) {
        for(x=width; x > 0; x--) {
            frame_buffer[ADDRESS(x, y) + RED_OFFSET]    = COLOR_RED(c);
            frame_buffer[ADDRESS(x, y) + GREEN_OFFSET]  = COLOR_GREEN(c);
            frame_buffer[ADDRESS(x, y) + BLUE_OFFSET]   = COLOR_BLUE(c);
        }
    }
}
void PmodTFT::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    frame_buffer[ADDRESS(x, y) + RED_OFFSET]    = COLOR_RED(c);
    frame_buffer[ADDRESS(x, y) + GREEN_OFFSET]  = COLOR_GREEN(c);
    frame_buffer[ADDRESS(x, y) + BLUE_OFFSET]   = COLOR_BLUE(c);
}
void PmodTFT::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    if((x < 0) || (x >= width)            // Fully off left or right
            || (y >= height)) return;  // Fully off bottom
    int16_t y2 = y + h - 1;
    if(y2 < 0) return;                    // Fully off top
    if(y2 >= height) h = height - y;    // Clip bottom
    if(y < 0) { h += y; y = 0; }          // Clip top

    while (h--) {
        frame_buffer[ADDRESS(x, (y + h)) + RED_OFFSET]    = COLOR_RED(c);
        frame_buffer[ADDRESS(x, (y + h)) + GREEN_OFFSET]  = COLOR_GREEN(c);
        frame_buffer[ADDRESS(x, (y + h)) + BLUE_OFFSET]   = COLOR_BLUE(c);
    }
}
void PmodTFT::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    if((y < 0) || (y >= height)         // Fully off top or bottom
            || (x >= width)) return; // Fully off right
    int16_t x2 = x + w - 1;
    if(x2 < 0) return;                   // Fully off left
    if(x2 >= width) w = width - x;     // Clip right
    if(x < 0) { w += x; x = 0; }         // Clip left

    while (w--) {
        frame_buffer[ADDRESS((x + w), y) + RED_OFFSET]    = COLOR_RED(c);
        frame_buffer[ADDRESS((x + w), y) + GREEN_OFFSET]  = COLOR_GREEN(c);
        frame_buffer[ADDRESS((x + w), y) + BLUE_OFFSET]   = COLOR_BLUE(c);
    }
}
void PmodTFT::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c)
{
    // rudimentary clipping (drawChar w/big text requires this)
    if((x >= width) || (y >= height)) return;   // Fully off right or bottom
    int16_t x2, y2;
    if(((x2 = x + w - 1) < 0) ||
            ((y2 = y + h - 1) < 0)) return;     // Fully off left or top
    if(x2 >= width)  w = width  - x;            // Clip right
    if(x < 0) { w += x; x = 0; }                // Clip left
    if(y2 >= height) h = height - y;            // Clip bottom
    if(y < 0) { h += y; y = 0; }                // Clip top

    setWindow(x, y, x+w-1, y+h-1);
    for (; y < h; y++){
        for (; x < w; x++){
            frame_buffer[ADDRESS((x + w), y) + RED_OFFSET]    = COLOR_RED(c);
            frame_buffer[ADDRESS((x + w), y) + GREEN_OFFSET]  = COLOR_GREEN(c);
            frame_buffer[ADDRESS((x + w), y) + BLUE_OFFSET]   = COLOR_BLUE(c);
        }
    }
}
void PmodTFT::invertDisplay(uint8_t i)
{
}
uint16_t PmodTFT::Color565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

