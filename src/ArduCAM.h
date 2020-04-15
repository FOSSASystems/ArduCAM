/*
  ArduCAM.h - Arduino library support for CMOS Image Sensor
  Copyright (C)2011-2015 ArduCAM.com. All right reserved

  Basic functionality of this library are based on the demo-code provided by
  ArduCAM.com. You can find the latest version of the library at
  http://www.ArduCAM.com

  Now supported controllers:
		- OV7670
		- MT9D111
		- OV7675
		- OV2640
		- OV3640
		- OV5642
		- OV5640
		- OV7660
		- OV7725
		- MT9M112
		- MT9V111
		- OV5640
		- MT9M001
		- MT9T112
		- MT9D112

	We will add support for many other sensors in next release.

  Supported MCU platform
 		-	Theoretically support all Arduino families
  		-	Arduino UNO R3			(Tested)
  		-	Arduino MEGA2560 R3		(Tested)
  		-	Arduino Leonardo R3		(Tested)
  		-	Arduino Nano			(Tested)
  		-	Arduino DUE				(Tested)
  		- Arduino Yun				(Tested)
  		-	Raspberry Pi			(Tested)
  		- ESP8266-12				(Tested)
		* Feather M0                (Tested with OV5642)

  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.ArduCAM.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*------------------------------------
	Revision History:
	2012/09/20 	V1.0.0	by Lee	first release
	2012/10/23  V1.0.1  by Lee  Resolved some timing issue for the Read/Write Register
	2012/11/29	V1.1.0	by Lee  Add support for MT9D111 sensor
	2012/12/13	V1.2.0	by Lee	Add support for OV7675 sensor
	2012/12/28  V1.3.0	by Lee	Add support for OV2640,OV3640,OV5642 sensors
	2013/02/26	V2.0.0	by Lee	New Rev.B shield hardware, add support for FIFO control
															and support Mega1280/2560 boards
	2013/05/28	V2.1.0	by Lee	Add support all drawing functions derived from UTFT library
	2013/08/24	V3.0.0	by Lee	Support ArudCAM shield Rev.C hardware, features SPI interface and low power mode.
								Support almost all series of Arduino boards including DUE.
	2014/03/09  V3.1.0  by Lee  Add the more impressive example sketches.
								Optimise the OV5642 settings, improve image quality.
								Add live preview before JPEG capture.
								Add play back photos one by one	after BMP capture.
	2014/05/01  V3.1.1  by Lee  Minor changes to add support Arduino IDE for linux distributions.
	2014/09/30  V3.2.0  by Lee  Improvement on OV5642 camera dirver.
	2014/10/06  V3.3.0  by Lee  Add OV7660,OV7725 camera support.
	2015/02/27  V3.4.0  by Lee  Add the support for Arduino Yun board, update the latest UTFT library for ArduCAM.
	2015/06/09  V3.4.1  by Lee	Minor changes and add some comments
	2015/06/19  V3.4.2  by Lee	Add support for MT9M112 camera.
	2015/06/20  V3.4.3  by Lee	Add support for MT9V111 camera.
	2015/06/22  V3.4.4  by Lee	Add support for OV5640 camera.
	2015/06/22  V3.4.5  by Lee	Add support for MT9M001 camera.
	2015/08/05  V3.4.6  by Lee	Add support for MT9T112 camera.
	2015/08/08  V3.4.7  by Lee	Add support for MT9D112 camera.
	2015/09/20  V3.4.8  by Lee	Add support for ESP8266 processor.
	2016/02/03	V3.4.9	by Lee	Add support for Arduino ZERO board.
	2016/06/07  V3.5.0  by Lee	Add support for OV5642_CAM_BIT_ROTATION_FIXED.
	2016/06/14  V3.5.1  by Lee	Add support for ArduCAM-Mini-5MP-Plus OV5640_CAM.
	2016/09/29	V3.5.2	by Lee	Optimize the OV5642 register settings
	2016/10/05	V4.0.0	by Lee	Add support for second generation of ArduCAM shield V2, ArduCAM-Mini-5MP-Plus(OV5642/OV5640).
	2016/10/28  V4.0.1  by Lee	Add support for Raspberry Pi
	2017/04/27  V4.1.0  by Lee	Add support for OV2640/OV5640/OV5642 functions.
	2017/07/07  V4.1.0  by Lee	Add support for ArduCAM_ESP32 paltform
	2017/07/25  V4.1.1  by Lee	Add support for MT9V034
	2017/11/27  V4.1.2  by Max      Add support for Feather M0
	2018/10/15  V4.1.2  by Lee      Add support for NRF52
	2018/10/15  V4.1.2  by Lee      Add support for TEENSYDUINO
--------------------------------------*/

#ifndef ArduCAM_H
#define ArduCAM_H
#include "Arduino.h"
#include "Camera.h"
#include "base_defs.h"
#include "OV2640_MINI_2MP.h"
#include "ov2640_regs.h"

enum CameraModel
{
	OV7670,
	MT9D111_A,
	OV7675,
	OV5642,
	OV3640,
	OV2640,
	OV9655,
	MT9M112,
	OV7725,
	OV7660,
	MT9M001,
	OV5640,
	MT9D111_B,
	OV9650,
	MT9V111,
	MT9T112,
	MT9D112,
	MT9V034,
	MT9M034,
};

class ArduCAM
{
public:
	static Camera * createCamera(CameraModel model, int16_t cs)
	{
		switch (model)
		{
		case OV2640:
			return new OV2640_MINI_2MP(cs);
			break;

		default:
			return new OV2640_MINI_2MP(cs);
			break;
		}
	}
};

#endif
