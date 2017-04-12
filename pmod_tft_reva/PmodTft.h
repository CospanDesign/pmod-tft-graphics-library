/*

Software License Agreement (BSD License)

Copyright (c) 2017 Dave McCoy (dave.mccoy@cospandesign.com)

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef __PMOD_TFT_H__
#define __PMOD_TFT_H__


#define WIDTH   480
#define HEIGHT  272

class PmodTFT : public Adafruit_GFX {
  private:
  uint32_t pmod_tft_address;
  uint8_t vdma_index;
  uint8_t frame_buffer;
  uint32_t width;
  uint32_t height;
  uint32_t size;

  uint32_t x0, y0, x1, y1;

  initialize();

  public:

  static uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);

  PmodTFT(uint32_t pmod_tft_address, uint8_t vdma_index);
  ~PmodTFT();

  void reset();
  void setWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
  void fillScreen(uint16_t c);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
  void invertDisplay(uint8_t i);
};


#endif
