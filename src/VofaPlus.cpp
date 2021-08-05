#include "VofaPlus.h"

VofaPlus::VofaPlus(Stream& stream_): stream(stream_){
}

VofaPlus::~VofaPlus(){
}

void VofaPlus::mode(VofaPlus::VofaMode_t mode__){
    mode_ = mode__;
}

void VofaPlus::sendImage(const uint8_t* data, int id, int size, int width, int height, ImgFormat_t format){
        if(mode_ == FIREWATER){
            stream.print("image:");
            stream.print(id);
            stream.print(',');
            stream.print(size);
            stream.print(',');
            stream.print(width);
            stream.print(',');
            stream.print(height);
            stream.print(',');
            stream.println((int)format);
        }else{
            int preFrame[7] = {id, size, width, height, (int)format, 0x7F800000, 0x7F800000};
            stream.write((uint8_t*)preFrame,7 * sizeof(int));
        }
        stream.write(data,size);
}