
#include "Camera.h"

void Camera::flush_fifo()
{
	write_reg(ARDUCHIP_FIFO, FIFO_CLEAR_MASK);
}

void Camera::start_capture()
{
	write_reg(ARDUCHIP_FIFO, FIFO_START_MASK);
}

void Camera::clear_fifo_flag()
{
	write_reg(ARDUCHIP_FIFO, FIFO_CLEAR_MASK);
}

uint32_t Camera::read_fifo_length()
{
	uint32_t len1, len2, len3, length = 0;
	len1 = read_reg(FIFO_SIZE1);
	len2 = read_reg(FIFO_SIZE2);
	len3 = read_reg(FIFO_SIZE3) & 0x7f;
	length = ((len3 << 16) | (len2 << 8) | len1) & 0x07fffff;
	return length;
}

void Camera::set_fifo_burst()
{
	SPI.transfer(BURST_FIFO_READ);
}

uint8_t Camera::read_fifo()
{
	uint8_t data;
	data = bus_read(SINGLE_FIFO_READ);
	return data;
}

uint8_t Camera::read_reg(uint8_t addr)
{
	uint8_t data;
	data = bus_read(addr & 0x7F);
	return data;
}

void Camera::write_reg(uint8_t addr, uint8_t data)
{
	bus_write(addr | 0x80, data);
}

//Set corresponding bit
void Camera::set_bit(uint8_t addr, uint8_t bit)
{
	uint8_t temp;
	temp = read_reg(addr);
	write_reg(addr, temp | bit);
}
//Clear corresponding bit
void Camera::clear_bit(uint8_t addr, uint8_t bit)
{
	uint8_t temp;
	temp = read_reg(addr);
	write_reg(addr, temp & (~bit));
}

//Get corresponding bit status
uint8_t Camera::get_bit(uint8_t addr, uint8_t bit)
{
	uint8_t temp;
	temp = read_reg(addr);
	temp = temp & bit;
	return temp;
}

//Set Camera working mode
//MCU2LCD_MODE: MCU writes the LCD screen GRAM
//CAM2LCD_MODE: Camera takes control of the LCD screen
//LCD2MCU_MODE: MCU read the LCD screen GRAM
void Camera::set_mode(uint8_t mode)
{
	switch (mode)
	{
	case MCU2LCD_MODE:
		write_reg(ARDUCHIP_MODE, MCU2LCD_MODE);
		break;
	case CAM2LCD_MODE:
		write_reg(ARDUCHIP_MODE, CAM2LCD_MODE);
		break;
	case LCD2MCU_MODE:
		write_reg(ARDUCHIP_MODE, LCD2MCU_MODE);
		break;
	default:
		write_reg(ARDUCHIP_MODE, MCU2LCD_MODE);
		break;
	}
}

void Camera::bus_write(int address, int value)
{
  digitalWrite(csPin, LOW);
	SPI.transfer(address);
	SPI.transfer(value);
  digitalWrite(csPin, HIGH);
}

uint8_t Camera::bus_read(int address)
{
	uint8_t value;
  digitalWrite(csPin, LOW);
	SPI.transfer(address);
	value = SPI.transfer(0x00);
  digitalWrite(csPin, HIGH);
	return value;
}

// Write 8 bit values to 8 bit register address
int Camera::wrSensorRegs8_8(const struct sensor_reg reglist[])
{
	uint16_t reg_addr = 0;
	uint16_t reg_val = 0;
	const struct sensor_reg *next = reglist;
	while ((reg_addr != 0xff) | (reg_val != 0xff))
	{
		reg_addr = pgm_read_word(&next->reg);
		reg_val = pgm_read_word(&next->val);
		wrSensorReg8_8(reg_addr, reg_val);
		next++;
	}
	return 1;
}

// Write 16 bit values to 8 bit register address
int Camera::wrSensorRegs8_16(const struct sensor_reg reglist[])
{
	uint16_t reg_addr = 0;
	uint16_t reg_val = 0;
	const struct sensor_reg *next = reglist;

	while ((reg_addr != 0xff) | (reg_val != 0xffff))
	{
		reg_addr = pgm_read_word(&next->reg);
		reg_val = pgm_read_word(&next->val);
		wrSensorReg8_16(reg_addr, reg_val);
		next++;
	}
	return 1;
}

// Write 8 bit values to 16 bit register address
int Camera::wrSensorRegs16_8(const struct sensor_reg reglist[])
{
	uint16_t reg_addr = 0;
	uint16_t reg_val = 0;
	const struct sensor_reg *next = reglist;

	while ((reg_addr != 0xffff) | (reg_val != 0xff))
	{
		reg_addr = pgm_read_word(&next->reg);
		reg_val = pgm_read_word(&next->val);
		wrSensorReg16_8(reg_addr, reg_val);
		next++;
	}
	return 1;
}

//I2C Array Write 16bit address, 16bit data
int Camera::wrSensorRegs16_16(const struct sensor_reg reglist[])
{
	unsigned int reg_addr, reg_val;
	const struct sensor_reg *next = reglist;
	reg_addr = pgm_read_word(&next->reg);
	reg_val = pgm_read_word(&next->val);
	while ((reg_addr != 0xffff) | (reg_val != 0xffff))
	{
		wrSensorReg16_16(reg_addr, reg_val);
		next++;
		reg_addr = pgm_read_word(&next->reg);
		reg_val = pgm_read_word(&next->val);
	}
	return 1;
}

// Read/write 8 bit value to/from 8 bit register address
byte Camera::wrSensorReg8_8(int regID, int regDat)
{
	Wire.beginTransmission(sensor_addr >> 1);
	Wire.write(regID & 0x00FF);
	Wire.write(regDat & 0x00FF);
	if (Wire.endTransmission())
	{
		return 0;
	}
	delay(1);
	return 1;
}
byte Camera::rdSensorReg8_8(uint8_t regID, uint8_t *regDat)
{
	Wire.beginTransmission(sensor_addr >> 1);
	Wire.write(regID & 0x00FF);
	Wire.endTransmission();

	Wire.requestFrom((sensor_addr >> 1), 1);
	if (Wire.available())
		*regDat = Wire.read();
	delay(1);
	return 1;
}
// Read/write 16 bit value to/from 8 bit register address
byte Camera::wrSensorReg8_16(int regID, int regDat)
{
	Wire.beginTransmission(sensor_addr >> 1);
	Wire.write(regID & 0x00FF);

	Wire.write(regDat >> 8); // sends data byte, MSB first
	Wire.write(regDat & 0x00FF);
	if (Wire.endTransmission())
	{
		return 0;
	}
	delay(1);
	return 1;
}
byte Camera::rdSensorReg8_16(uint8_t regID, uint16_t *regDat)
{
	uint8_t temp;
	Wire.beginTransmission(sensor_addr >> 1);
	Wire.write(regID);
	Wire.endTransmission();

	Wire.requestFrom((sensor_addr >> 1), 2);
	if (Wire.available())
	{
		temp = Wire.read();
		*regDat = (temp << 8) | Wire.read();
	}
	delay(1);
	return 1;
}

// Read/write 8 bit value to/from 16 bit register address
byte Camera::wrSensorReg16_8(int regID, int regDat)
{
	Wire.beginTransmission(sensor_addr >> 1);
	Wire.write(regID >> 8); // sends instruction byte, MSB first
	Wire.write(regID & 0x00FF);
	Wire.write(regDat & 0x00FF);
	if (Wire.endTransmission())
	{
		return 0;
	}
	delay(1);
	return 1;
}
byte Camera::rdSensorReg16_8(uint16_t regID, uint8_t *regDat)
{
	Wire.beginTransmission(sensor_addr >> 1);
	Wire.write(regID >> 8);
	Wire.write(regID & 0x00FF);
	Wire.endTransmission();
	Wire.requestFrom((sensor_addr >> 1), 1);
	if (Wire.available())
	{
		*regDat = Wire.read();
	}
	delay(1);
	return 1;
}

//I2C Write 16bit address, 16bit data
byte Camera::wrSensorReg16_16(int regID, int regDat)
{
	Wire.beginTransmission(sensor_addr >> 1);
	Wire.write(regID >> 8); // sends instruction byte, MSB first
	Wire.write(regID & 0x00FF);
	Wire.write(regDat >> 8); // sends data byte, MSB first
	Wire.write(regDat & 0x00FF);
	if (Wire.endTransmission())
	{
		return 0;
	}
	delay(1);
	return (1);
}

//I2C Read 16bit address, 16bit data
byte Camera::rdSensorReg16_16(uint16_t regID, uint16_t *regDat)
{
	uint16_t temp;
	Wire.beginTransmission(sensor_addr >> 1);
	Wire.write(regID >> 8);
	Wire.write(regID & 0x00FF);
	Wire.endTransmission();
	Wire.requestFrom((sensor_addr >> 1), 2);
	if (Wire.available())
	{
		temp = Wire.read();
		*regDat = (temp << 8) | Wire.read();
	}
	delay(1);
	return (1);
}
