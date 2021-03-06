/*
 * Bitmaps.h
 *
 *  Created on: 3/3/2016
 *      Author: Prototipado
 */

#ifndef INC_BITMAPS_H_
#define INC_BITMAPS_H_

const uint8_t GpsBitmaps[] = {
		  11,16,0x14, 0x0A, 0x85, 0xBA, 0x49, 0x88, 0x10, 0x2C, 0xCE, 0x07, 0x03,
		        0x06, 0x07, 0x03, 0x01, 0x00, 0x00, 0x01, 0x01, 0x05, 0x06, 0x03,
};

const uint8_t WindsBitmaps[] = {
		  11,16, 0x3C, 0x48, 0x90, 0x20, 0x20, 0x1C, 0x02, 0x8B, 0x62, 0x14, 0x08,
			     0x0E, 0x04, 0x04, 0x05, 0x1F, 0x05, 0x05, 0x04, 0x04, 0x0E, 0x04,
};
const uint8_t FlowBitmaps[] = {
		7,16, 	0x7F, 0x43, 0xC3, 0xC3, 0xC3, 0x43, 0x7F,
		        0x18, 0x06, 0x00, 0x1E, 0x00, 0x06, 0x18,
};
const uint8_t TyhBitmaps[] = {
		9,16, 0x00, 0x00, 0xFE, 0x03, 0xF9, 0x03, 0xFE, 0x00, 0x00,
		      0x0E, 0x1B, 0x31, 0x24, 0x2F, 0x24, 0x31, 0x1B, 0x0E,
};

const uint8_t InicioBitmaps[] = {
		48,40, 	0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xB8, 0xBC, 0xBC, 0x7C, 0x00, 0xFE, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xFE, 0x00, 0x7C, 0xBC, 0xBC, 0xB8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
		0x02, 0x03, 0x02, 0x06, 0x03, 0x06, 0x02, 0x0D, 0x04, 0x0E, 0x05, 0x0C, 0x06, 0x19, 0x0C, 0x0A, 0xE9, 0xEF, 0x80, 0xC0, 0x67, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0xF4, 0x67, 0xC0, 0x80, 0xEF, 0xE9, 0x0A, 0x0C, 0x19, 0x06, 0x0C, 0x05, 0x0E, 0x04, 0x0D, 0x02, 0x06, 0x03, 0x06, 0x02, 0x03, 0x02,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xFE, 0x00, 0xFE, 0x0C, 0x30, 0xC0, 0xFE, 0x00, 0x02, 0xFE, 0x02, 0xE2, 0x78, 0x46, 0x46, 0x78, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFE, 0x00, 0xFE, 0x0C, 0x30, 0xC0, 0xFE, 0x00, 0xFE, 0x12, 0x12, 0x02, 0x00, 0xFE, 0x22, 0x22, 0xDC, 0x00, 0x00,
		0x00, 0x00, 0x15, 0x14, 0x15, 0x14, 0x14, 0x14, 0x15, 0x14, 0x14, 0x15, 0x14, 0x15, 0x14, 0x14, 0x14, 0x14, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0D, 0x09, 0x18, 0x10, 0x11, 0x18, 0x08, 0x0C, 0x05, 0x10, 0x19, 0x09, 0x0D, 0x05, 0x04, 0x0D, 0x08, 0x18, 0x11, 0x00, 0x00,
};

const uint8_t Signal1Bitmaps[] = {
		1,8,
		0x80,
};

const uint8_t Signal2Bitmaps[] = {
		3,8,
		0x80, 0x00, 0xE0,
};

const uint8_t Signal3Bitmaps[] = {
		5,8,
		0x80, 0x00, 0xE0, 0x00, 0xF8,
};

const uint8_t Signal4Bitmaps[] = {
		7,8,
		0x80, 0x00, 0xE0, 0x00, 0xF8, 0x00, 0xFE,
};

const uint8_t SdOkBitmaps[] = {
		6,8,
		0xFE, 0x82, 0x82, 0x86, 0x8C, 0xF8,
};

const uint8_t SdFailBitmaps[] = {
		6,8,
		0xAE, 0x42, 0xA2, 0x06, 0x8C, 0xF8,
};

#endif /* INC_BITMAPS_H_ */
