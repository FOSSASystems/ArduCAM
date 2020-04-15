#include "OV2640_MINI_2MP.h"
#include "Arduino.h"
#include "ov2640_regs.h"

OV2640_MINI_2MP::OV2640_MINI_2MP(int16_t cs)
{
    sensor_addr = 0x60;
    csPin = cs;
}

void OV2640_MINI_2MP::InitCAM()
{
    wrSensorReg8_8(0xff, 0x01);
    wrSensorReg8_8(0x12, 0x80);
    delay(100);
    if (m_fmt == JPEG_FMT)
    {
        wrSensorRegs8_8(JPEG_INIT);
        wrSensorRegs8_8(YUV422);
        wrSensorRegs8_8(JPEG);
        wrSensorReg8_8(0xff, 0x01);
        wrSensorReg8_8(0x15, 0x00);
        wrSensorRegs8_8(JPEG_320x240);
        //wrSensorReg8_8(0xff, 0x00);
        //wrSensorReg8_8(0x44, 0x32);
    }
    else
    {
        wrSensorRegs8_8(QVGA);
    }
}

void OV2640_MINI_2MP::SetJPEGsize(JPEG_Size size)
{
    switch (size)
    {
    case p160x120:
        wrSensorRegs8_8(JPEG_160x120);
        break;
    case p176x144:
        wrSensorRegs8_8(JPEG_176x144);
        break;
    case p320x240:
        wrSensorRegs8_8(JPEG_320x240);
        break;
    case p352x288:
        wrSensorRegs8_8(JPEG_352x288);
        break;
    case p640x480:
        wrSensorRegs8_8(JPEG_640x480);
        break;
    case p800x600:
        wrSensorRegs8_8(JPEG_800x600);
        break;
    case p1024x768:
        wrSensorRegs8_8(JPEG_1024x768);
        break;
    case p1280x1024:
        wrSensorRegs8_8(JPEG_1280x1024);
        break;
    case p1600x1200:
        wrSensorRegs8_8(JPEG_1600x1200);
        break;
    default:
        wrSensorRegs8_8(JPEG_320x240);
        break;
    }
}

void OV2640_MINI_2MP::SetLightMode(Light_Mode mode)
{
    switch (mode)
    {

    case Auto:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x00); //AWB on
        break;
    case Sunny:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x40); //AWB off
        wrSensorReg8_8(0xcc, 0x5e);
        wrSensorReg8_8(0xcd, 0x41);
        wrSensorReg8_8(0xce, 0x54);
        break;
    case Cloudy:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x40); //AWB off
        wrSensorReg8_8(0xcc, 0x65);
        wrSensorReg8_8(0xcd, 0x41);
        wrSensorReg8_8(0xce, 0x4f);
        break;
    case Office:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x40); //AWB off
        wrSensorReg8_8(0xcc, 0x52);
        wrSensorReg8_8(0xcd, 0x41);
        wrSensorReg8_8(0xce, 0x66);
        break;
    case Home:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x40); //AWB off
        wrSensorReg8_8(0xcc, 0x42);
        wrSensorReg8_8(0xcd, 0x3f);
        wrSensorReg8_8(0xce, 0x71);
        break;
    default:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0xc7, 0x00); //AWB on
        break;
    }
}

void OV2640_MINI_2MP::SetColorSaturation(Color_Saturation saturation)
{
    switch (saturation)
    {
    case Saturation4:
        break;
    case Saturation3:
        break;
    case Saturation2:

        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x68);
        wrSensorReg8_8(0x7d, 0x68);
        break;
    case Saturation1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x58);
        wrSensorReg8_8(0x7d, 0x58);
        break;
    case Saturation0:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x48);
        wrSensorReg8_8(0x7d, 0x48);
        break;
    case Saturation_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x38);
        wrSensorReg8_8(0x7d, 0x38);
        break;
    case Saturation_2:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x02);
        wrSensorReg8_8(0x7c, 0x03);
        wrSensorReg8_8(0x7d, 0x28);
        wrSensorReg8_8(0x7d, 0x28);
        break;
    case Saturation_3:
        break;
    case Saturation_4:
        break;
    }
}

void OV2640_MINI_2MP::SetBrightness(Brightness brightness)
{
    switch (brightness)
    {
    case Brightness4:
      break;
    case Brightness3:
      break;
    case Brightness2:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x30);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness0:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x10);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness_2:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x09);
        wrSensorReg8_8(0x7d, 0x00);
        wrSensorReg8_8(0x7d, 0x00);
        break;
    case Brightness_3:
      break;
    case Brightness_4:
      break;
    }
}

void OV2640_MINI_2MP::SetContrast(Contrast contrast)
{
    switch (contrast)
    {
    case Contrast4:
      break;
    case Contrast3:
      break;
    case Contrast2:

        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x28);
        wrSensorReg8_8(0x7d, 0x0c);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x24);
        wrSensorReg8_8(0x7d, 0x16);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast0:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast_1:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x2a);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast_2:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x04);
        wrSensorReg8_8(0x7c, 0x07);
        wrSensorReg8_8(0x7d, 0x20);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7d, 0x34);
        wrSensorReg8_8(0x7d, 0x06);
        break;
    case Contrast_3:
      break;
    case Contrast_4:
      break;
    }
}

void OV2640_MINI_2MP::SetSpecialEffects(Special_Effects effect)
{
    switch (effect)
    {
    case Antique:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7d, 0xa6);
        break;
    case Bluish:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0xa0);
        wrSensorReg8_8(0x7d, 0x40);
        break;
    case Greenish:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7d, 0x40);
        break;
    case Reddish:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7d, 0xc0);
        break;
    case BW:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x18);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x80);
        wrSensorReg8_8(0x7d, 0x80);
        break;
    case Negative:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x40);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x80);
        wrSensorReg8_8(0x7d, 0x80);
        break;
    case BWnegative:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x58);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x80);
        wrSensorReg8_8(0x7d, 0x80);
        break;
    case Normal:
        wrSensorReg8_8(0xff, 0x00);
        wrSensorReg8_8(0x7c, 0x00);
        wrSensorReg8_8(0x7d, 0x00);
        wrSensorReg8_8(0x7c, 0x05);
        wrSensorReg8_8(0x7d, 0x80);
        wrSensorReg8_8(0x7d, 0x80);
        break;
    case Sepia:
      break;
    case Overexposure:
      break;
    case Solarize:
      break;
    case Blueish:
      break;
    case Yellowish:
      break;
    }
}

bool OV2640_MINI_2MP::checkModule()
{
    uint8_t vid, pid;
    wrSensorReg8_8(0xff, 0x01);
    rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
    rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
    return ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)));
}
