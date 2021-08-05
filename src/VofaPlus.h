#pragma once
#include <Arduino.h>

class VofaPlus
{

public:
    enum VofaMode_t{
        FIREWATER = 0,
        JUSTFLOAT
    };
    enum ImgFormat_t {
      Format_Invalid,
      Format_Mono,
      Format_MonoLSB,
      Format_Indexed8,
      Format_RGB32,
      Format_ARGB32,
      Format_ARGB32_Premultiplied,
      Format_RGB16,
      Format_ARGB8565_Premultiplied,
      Format_RGB666,
      Format_ARGB6666_Premultiplied,
      Format_RGB555,
      Format_ARGB8555_Premultiplied,
      Format_RGB888,
      Format_RGB444,
      Format_ARGB4444_Premultiplied,
      Format_RGBX8888,
      Format_RGBA8888,
      Format_RGBA8888_Premultiplied,
      Format_BGR30,
      Format_A2BGR30_Premultiplied,
      Format_RGB30,
      Format_A2RGB30_Premultiplied,
      Format_Alpha8,
      Format_Grayscale8,

      // 以下格式发送时，IMG_WIDTH和IMG_HEIGHT不需要强制指定，设置为-1即可
      Format_BMP,
      Format_GIF,
      Format_JPG,
      Format_PNG,
      Format_PBM,
      Format_PGM,
      Format_PPM,
      Format_XBM,
      Format_XPM,
      Format_SVG,
    };

    VofaPlus(Stream& stream_ = Serial);
    ~VofaPlus();
    void mode(VofaMode_t mode__);
    void sendImage(const uint8_t* data, int id, int size, int width, int height, ImgFormat_t format);

    void writeSamples(const float lastArg) {
      if (mode_ == FIREWATER) {
        stream.println(lastArg);
      } else {
        //write the arg1 to stream as 4 bytes
        stream.write(*((uint8_t*)&lastArg));
        stream.write(*((uint8_t*)&lastArg+1));
        stream.write(*((uint8_t*)&lastArg+2));
        stream.write(*((uint8_t*)&lastArg+3));
        stream.write((uint8_t)0x00);
        stream.write((uint8_t)0x00);
        stream.write(0x80);
        stream.write(0x7f);
      }
    }

    template <typename... Ts> 
    void writeSamples(const float arg1, Ts... args) {
      if (mode_ == FIREWATER) {
        stream.print(arg1);
        stream.print(',');
      } else {
        //write the arg1 to stream as 4 bytes
        stream.write(*((uint8_t*)&arg1));
        stream.write(*((uint8_t*)&arg1+1));
        stream.write(*((uint8_t*)&arg1+2));
        stream.write(*((uint8_t*)&arg1+3));
      }
      writeSamples(static_cast<float>(args)...);
    }

    template <typename... Ts> 
    void writeSamples(String label, Ts... args) {
      if (mode_ == FIREWATER) {
        stream.print(label);
        stream.print(':');
      }
      writeSamples(static_cast<float>(args)...);
    }

private:
    Stream& stream;
    VofaMode_t mode_ = FIREWATER;
};

