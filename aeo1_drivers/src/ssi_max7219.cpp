/*
 * ssi_max7219.cpp
 *
 *  Created on: 3. mars 2015
 *      Author: Anders
 */
//--------------------------------
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "utils/uartstdio.h"
//--------------------------------
#include "inc/tm4c123gh6pm.h"
//--------------------------------
#include "ssi_max7219.h"
#include "alpha7segment.h"
//--------------------------------
namespace aeo1 {
//--------------------------------
enum {
	ssi_max7219_registercount = 16, ssi_max7219_bitrate = 1000000
};
//--------------------------------
struct max7219_registerset {
	int nRegValue[ssi_max7219_registercount];
};
//--------------------------------
static const max7219_registerset RegisterSet_Default = {

0x000, // No-op
		0x100, // Digit 0
		0x200, // Digit 1
		0x300, // Digit 2
		0x400, // Digit 3
		0x500, // Digit 4
		0x600, // Digit 5
		0x700, // Digit 6
		0x800, // Digit 7
		0x900, // Code-B: No Decode=0x00, Decode All=0xFF
		0xA08, // Intensity: Minimum=0x00, Maximum=0x0F
		0xB07, // Scan Limit: Digit 0 Only=0x00, All Digits=0x07
		0xC01, // Shutdown Mode=0, Normal Operation=1
		0x000, // No-op
		0x000, // No-op
		0xF00, // Display Test=1, Normal Operation=0

		};
//--------------------------------
ssi_max7219::ssi_max7219(ssi_peripheral::device_id nDevice) :
		ssi_peripheral(nDevice, ssi_max7219_bitrate, SSI_FRF_MOTO_MODE_0, false) {
}
//--------------------------------
ssi_max7219::~ssi_max7219() {
}
//--------------------------------
void ssi_max7219::Initialize() {
	ssi_peripheral::Initialize();
	for (int nRegisterNumber = 0; ssi_max7219_registercount > nRegisterNumber;
			nRegisterNumber++) {
		Put(RegisterSet_Default.nRegValue[nRegisterNumber]);
	}
}
//--------------------------------
static uint32_t Digit2Segments(uint32_t nDigitNumber, uint32_t nDigitValue,
		bool bbDecimalPoint) {
	const uint8_t Symbols[18] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
			0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
	if (0xF > nDigitValue) {
		uint8_t nSegmentValue = ~(Symbols[nDigitValue]
				| (bbDecimalPoint ? 0x80 : 0x0));
		return (nSegmentValue) | (nDigitNumber << 8);
	} else if (0x10 == nDigitValue) {
		return (0xBF) | (nDigitNumber << 8);
	} else {
		return (0xFF) | (nDigitNumber << 8);
	}
}
//--------------------------------
void ssi_max7219::Set(int32_t nValue, int nDecimals) {
	bool bNegative = (0 > nValue);
	if (bNegative) {
		nValue = -nValue;
	}
	for (int nDigitNumber = 0; BufferSize > nDigitNumber; nDigitNumber++) {
		int nDigitValue = nValue % 10;
		bool bDecimalPoint = (0 == nDecimals);
		if (nValue || nDigitValue || (0 <= nDecimals)) {
			Put(Digit2Segments(nDigitNumber, nDigitValue, bDecimalPoint));
		} else if (bNegative) {
			bNegative = false;
			Put(Digit2Segments(nDigitNumber, 0x10, bDecimalPoint));
		} else {
			Put(Digit2Segments(nDigitNumber, 0x11, bDecimalPoint));
		}
		nValue /= 10;
		nDecimals--;
	}
}
//--------------------------------
void ssi_max7219::Set(const char* zString) {
	for (int nGpc = BufferSize; 0 < nGpc; nGpc--) {
		int nSymbolNumber = nGpc - 1;
		uint8_t nCode;
		if (zString && *zString) {
			char cSymbol = *zString++;
			nCode = Alpha7Segment(cSymbol);
			if ('.' == *zString) {
				zString++;
				nCode |= alpha7segment_dot;
			}
		} else {
			nCode = alpha7segment_space;
		}
		nCode = ~nCode;
		Put((nCode << 8) | (1 << nSymbolNumber));
	}
}
//--------------------------------
void ssi_max7219::Diag() {
	UARTprintf("\nssi_max7219: ");
	ssi_peripheral::Diag();
}
//--------------------------------
} /* namespace aeo1 */
//--------------------------------
