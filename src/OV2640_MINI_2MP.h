#ifndef OV2640_MINI_2MP_H
#define OV2640_MINI_2MP_H
#include "Camera.h"

class OV2640_MINI_2MP : public Camera
{
public:
    OV2640_MINI_2MP(int16_t cs); // Constructor.
    void InitCAM();
    void SetJPEGsize(JPEG_Size size);
    void SetLightMode(Light_Mode mode);
    void SetColorSaturation(Color_Saturation saturation);
    void SetBrightness(Brightness brightness);
    void SetContrast(Contrast contrast);
    void SetSpecialEffects(Special_Effects effect);
    bool checkModule();
};
#endif
