#ifndef CAMERA_H
#define CAMERA_H
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include "HardwareSerial.h"
#include "base_regs.h"
#include "base_defs.h"

enum JPEG_Size
{
    p160x120,
    p176x144,
    p320x240,
    p352x288,
    p640x480,
    p800x600,
    p1024x768,
    p1280x1024,
    p1600x1200,
};

enum Color_Saturation
{
    Saturation4,
    Saturation3,
    Saturation2,
    Saturation1,
    Saturation0,
    Saturation_1,
    Saturation_2,
    Saturation_3,
    Saturation_4,
};

enum Brightness
{
    Brightness4,
    Brightness3,
    Brightness2,
    Brightness1,
    Brightness0,
    Brightness_1,
    Brightness_2,
    Brightness_3,
    Brightness_4,
};

enum Contrast
{
    Contrast4,
    Contrast3,
    Contrast2,
    Contrast1,
    Contrast0,
    Contrast_1,
    Contrast_2,
    Contrast_3,
    Contrast_4,
};

enum Angle
{
    degree_180,
    degree_150,
    degree_120,
    degree_90,
    degree_60,
    degree_30,
    degree_0,
    degree30,
    degree60,
    degree90,
    degree120,
    degree150,
};

enum Special_Effects
{
    Antique,
    Bluish,
    Greenish,
    Reddish,
    BW,
    Negative,
    BWnegative,
    Normal,
    Sepia,
    Overexposure,
    Solarize,
    Blueish,
    Yellowish,
};

enum Format
{
    BMP_FMT,
    JPEG_FMT,
    RAW_FMT,
};

enum Light_Mode
{
    Auto,
    Sunny,
    Cloudy,
    Office,
    Home,
};

class Camera
{
public:
    Camera() {}
    ~Camera() {};
    virtual void InitCAM();
    virtual void SetJPEGsize(JPEG_Size size);
    virtual void SetLightMode(Light_Mode LightMode);
    virtual void SetColorSaturation(Color_Saturation ColorSaturation);
    virtual void SetBrightness(Brightness Brightness);
    virtual void SetContrast(Contrast Contrast);
    virtual void SetSpecialEffects(Special_Effects Specialeffect);
    virtual bool checkModule();

    void flush_fifo();
    void start_capture();
    void clear_fifo_flag();
    uint8_t read_fifo();

    uint8_t read_reg(uint8_t addr);
    void write_reg(uint8_t addr, uint8_t data);

    uint32_t read_fifo_length();
    void set_fifo_burst();

    void set_bit(uint8_t addr, uint8_t bit);
    void clear_bit(uint8_t addr, uint8_t bit);
    uint8_t get_bit(uint8_t addr, uint8_t bit);
    void set_mode(uint8_t mode);

    void bus_write(int address, int value);
    uint8_t bus_read(int address);

    // Write 8 bit values to 8 bit register address
    int wrSensorRegs8_8(const struct sensor_reg *);

    // Write 16 bit values to 8 bit register address
    int wrSensorRegs8_16(const struct sensor_reg *);

    // Write 8 bit values to 16 bit register address
    int wrSensorRegs16_8(const struct sensor_reg *);

    // Write 16 bit values to 16 bit register address
    int wrSensorRegs16_16(const struct sensor_reg *);

    // Read/write 8 bit value to/from 8 bit register address
    byte wrSensorReg8_8(int regID, int regDat);
    byte rdSensorReg8_8(uint8_t regID, uint8_t *regDat);

    // Read/write 16 bit value to/from 8 bit register address
    byte wrSensorReg8_16(int regID, int regDat);
    byte rdSensorReg8_16(uint8_t regID, uint16_t *regDat);

    // Read/write 8 bit value to/from 16 bit register address
    byte wrSensorReg16_8(int regID, int regDat);
    byte rdSensorReg16_8(uint16_t regID, uint8_t *regDat);

    // Read/write 16 bit value to/from 16 bit register address
    byte wrSensorReg16_16(int regID, int regDat);
    byte rdSensorReg16_16(uint16_t regID, uint16_t *regDat);

    void SetFormat(Format fmt)
    {
        m_fmt = fmt;
    };

    void resetCPLD()
    {
        //Reset the CPLD
        write_reg(0x07, 0x80);
        delay(100);
        write_reg(0x07, 0x00);
    };

    bool checkSPIBusStatus()
    {
        write_reg(ARDUCHIP_TEST1, 0x55);
        byte temp = read_reg(ARDUCHIP_TEST1);
        return temp == 0x55;
    };

protected:
    Format m_fmt;
    uint8_t sensor_addr;
    int16_t csPin;
};
#endif
