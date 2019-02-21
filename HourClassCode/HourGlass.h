/*
The Houe Glass Project
Created by: Dexter Dixon
 */
#ifndef HourGlass_h
#define HourGlass_h

class HourGlass 
{
    /* 
      Public so thesecan be accesed by all files in the project
    */
    public:
        /* 
           Function definitions
        */
        void resetLed();
        void startGyro();
        void fill_hourglass(int niv, int globe);
        void cleanup_pixels();



};

#endif	//HourGlass.h



