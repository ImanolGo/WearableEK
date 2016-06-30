/*
 * adp8866.c
 *
 *  Created on: 20.06.2016
 *      Author: Imanol Gomez
 */

#include "adp8866.h"
#include "i2c.h"

bool adp8866_initialize(void)
{
	bool completed = adp8866_initMDCR();
	completed = completed && adp8866_initLevels();
	completed = completed && adp8866_initPwrSource();
	completed = completed && adp8866_initCfr();
	completed = completed && adp8866_initfadeRates();
	completed = completed && adp8866_initFadeBLCurrent();
	completed = completed && adp8866_initInterrupts();
	completed = completed && adp8866_initLeds();

	adp8866_isInitialized = true;
	return completed;
}

bool adp8866_initMDCR(void)
{
	 // Turn on charge pump. Limit it to 1.5x with autoscale.
	uint8_t i2c_write_data = 0b01110101;
	return writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_MDCR,  i2c_write_data);
}

bool adp8866_initLevels(void)
{
	// Maximum current of ~21mA.
	// All LED outputs are set with the level bits.

	uint8_t i2c_write_data = 0b01000000;
	bool completed = writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_LVL_SEL_1,  i2c_write_data);

	i2c_write_data = 0xFF;
	completed = completed && writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_LVL_SEL_2,  i2c_write_data);

	i2c_write_data = 0b00000100;
	completed = completed && writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_GAIN_SEL,  i2c_write_data);

	return completed;
}

bool adp8866_initPwrSource(void)
{
	// All LEDs are being driven by the charge pump.

	uint8_t i2c_write_data = 0x00;
	bool completed = writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_PWR_SEL_1,  i2c_write_data);
	completed = completed && writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_PWR_SEL_2,  i2c_write_data);

	return completed;
}

bool adp8866_initCfr(void)
{
	 // All LED's independently sinkd. Backlight cubic transition.

	uint8_t i2c_write_data = 0b00010100;
	bool completed = writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_CFGR,  i2c_write_data);

	i2c_write_data = 0b11111111;
	completed = completed &&  writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_BLSEL,  i2c_write_data);

	return completed;
}
bool adp8866_initfadeRates(void)
{
	 // Backlight fade rates...
	uint8_t i2c_write_data = 0b01100110;
	return writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_BLFR,  i2c_write_data);
}
bool adp8866_initFadeBLCurrent(void)
{
	 // No backlight current.
	uint8_t i2c_write_data = 0b00000000;
	return writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_BLMX,  i2c_write_data);
}
bool adp8866_initSinkCtrl(void)
{
	// Sink control. All on. Cubic transfer fxn.
	uint8_t i2c_write_data = 0b00000111;
	bool completed = writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_ISCC1,  i2c_write_data);

	i2c_write_data = 0b11111111;
	completed = completed && writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_ISCC2,  i2c_write_data);

	return completed;
}
bool adp8866_initSinkDelays(void)
{
	// Sink control. All on. Cubic transfer fxn.
	uint8_t i2c_write_data = 0b11110000;
	bool completed = writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_ISCT1,  i2c_write_data);

	i2c_write_data = 0b00000000;
	completed = completed && writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_ISCT2,  i2c_write_data);

	return completed;
}
bool adp8866_initInterrupts(void)
{
	// Enabled interrupts: Over-volt, short-circuit, thermal shutdown
	uint8_t i2c_write_data = 0x1C;
	return writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_INT_EN,  i2c_write_data);

}
bool adp8866_initLeds(void)
{
	uint8_t i2c_write_data = 0x00;
	bool completed = writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_ISC1,  i2c_write_data);


	i2c_write_data = 0x0A;
	completed = completed &&writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_ISCT_HB,  i2c_write_data);

	adp8866_set_all_black();
	//adp8866_enable_all_leds(true);
	//adp8866_enable_heartbeat(false);

	return completed;
}



bool adp8866_testConnection(void)
{
	uint8_t id = adp8866_getDeviceID();
	if(id == ADP8866_ID)
		return true;

    return false;
}


uint8_t adp8866_getDeviceID(void)
{
	return readI2C_1Byte(ADP8866_I2CADDR,  ADP8866_MANU_DEV_ID);
}

uint8_t adp8866_getChannelEnable(uint8_t chan)
{
	uint8_t regstr   = (chan > 7) ? ADP8866_ISCC1 : ADP8866_ISCC2;
	return readI2C_1Byte(ADP8866_I2CADDR,  regstr);
}

uint8_t adp8866_getChannelState(uint8_t chan)
{
	uint8_t regstr  = (chan > 8) ? ADP8866_BLMX : ADP8866_ISC1+chan;
	return readI2C_1Byte(ADP8866_I2CADDR,  regstr);
}

uint8_t adp8866_getInterruptState()
{
	return readI2C_1Byte(ADP8866_I2CADDR,  ADP8866_INT_STAT);
}

void adp8866_processInterrupt()
{
	uint8_t value = adp8866_getInterruptState();
	if (value & 0x04) {
		//ADP8866 experienced an over-voltage fault
	}
	if (value & 0x08) {
		//ADP8866 experienced a thermal shutdown.
	}
	if (value & 0x10) {
		//ADP8866 experienced a short-circuit fault"
	}
	if (value & 0x1C) {
	// If we experienced a fault, we may as well shut off the device.
		uint8_t mdcr = readI2C_1Byte(ADP8866_I2CADDR,  ADP8866_MDCR);
		writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_MDCR,  mdcr & 0b01011010);
	}
	if (value & 0x20) {
	// Backlight off
	}
	if (value & 0x40) {
	// Independent sink off
	}
   // Whatever the interrupt was, clear it.
	writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_INT_STAT,  value);
}

bool adp8866_enable_channel(uint8_t chan, bool en)
{
	bool completed = false;

	if (chan > 8) {
		// Not that many channels....
		return completed;
	}

	uint8_t bitmask  = (chan > 7) ? 4 : (1 << chan);
	uint8_t present_state = adp8866_getChannelEnable(chan);
	uint8_t desired_state = (en ? (present_state | bitmask) : (present_state & ~bitmask));

	if (present_state != desired_state) {
		uint8_t regstr  = (chan > 7) ? ADP8866_ISCC1 : ADP8866_ISCC2;
		completed = writeI2C_1Byte(ADP8866_I2CADDR,  regstr,  desired_state);
	}

	return completed;
}

bool adp8866_enable_heartbeat(bool en)
{
	bool completed = false;

	uint8_t i2c_write_data = (en ? 0b00001110 : 0b00000000);
	completed = writeI2C_1Byte(ADP8866_I2CADDR,  ADP8866_HB_SEL,  i2c_write_data);

	return completed;
}
bool adp8866_pulse_channel(uint8_t chan, uint8_t nu_brightness) {

	bool completed = false;
	if ((chan > 9) || (chan < 6)) {
		// Channel outside of the valid range...
		return completed;
	}

	nu_brightness = nu_brightness & 0x7F;  // Only these bits matter.

	uint8_t i2c_write_data = nu_brightness;
	writeI2C_1Byte(ADP8866_I2CADDR,   ADP8866_ISC6_HB  + (chan - 5),  i2c_write_data);

	i2c_write_data = 0x20;
	completed = completed && writeI2C_1Byte(ADP8866_I2CADDR,   ADP8866_OFFTIMER6  + (chan - 5),  i2c_write_data);

	completed = completed &&  writeI2C_1Byte(ADP8866_I2CADDR,   ADP8866_OFFTIMER6_HB  + (chan - 5),  i2c_write_data);

	//  writeIndirect(ADP8866_HB_SEL, 0x01 << (chan - 6), true);
	//  writeIndirect(ADP8866_ISC6_HB      + (chan - 6), 0x20, true);
	//  writeIndirect(ADP8866_OFFTIMER6    + (chan - 6), 0x20, true);
	//  writeIndirect(ADP8866_OFFTIMER6_HB + (chan - 6), 0x20);

	return completed;
}


bool adp8866_set_brightness(uint8_t chan, uint8_t nu_brightness) {

	bool completed = false;

	if (chan > 9 || !adp8866_isInitialized) {
		// Not that many channels....
		return completed;
	}

	//writeIndirect(reg_addr, nu_brightness);
	nu_brightness = nu_brightness & 0x7F;  // Only these bits matter.
	uint8_t reg_addr  = (chan > 8) ? ADP8866_BLMX : ADP8866_ISC1+chan;
	uint8_t present_state = adp8866_getChannelState(chan);

	if (present_state != nu_brightness)
	{
		completed = writeI2C_1Byte(ADP8866_I2CADDR,  reg_addr,  nu_brightness);
	}

	return completed;
}

bool adp8866_set_RGBbrightness(uint8_t ledId, uint8_t* nu_brightness)
{
	bool completed = false;

	if (ledId > 2 || !adp8866_isInitialized) {
		// Not that many channels....
		return completed;
	}

	uint8_t reg_addr  = ADP8866_ISC1+ ledId*3;

	I2C_TransferSeq_TypeDef i2cTransfer;
	i2cTransfer.addr  = ADP8866_I2CADDR;
	i2cTransfer.flags = I2C_FLAG_WRITE;

	uint8_t i2c_write_data[4];
	i2c_write_data[0] = reg_addr;
	i2c_write_data[1] = nu_brightness[0]& 0x7F;  // Only these bits matter.
	i2c_write_data[2] = nu_brightness[1]& 0x7F;  // Only these bits matter.
	i2c_write_data[3] = nu_brightness[2]& 0x7F;  // Only these bits matter.

	i2cTransfer.buf[0].data  = i2c_write_data;
	i2cTransfer.buf[0].len    = 3;

	completed = processI2C(&i2cTransfer);

	return completed;


}

void adp8866_set_led_rgb(uint8_t ledId, RGB *color)
{
	if ((ledId > 2) || (ledId < 0)) {
		// LED ID outside of the valid range...
		return ;
	}

	//adp8866_enable_heartbeat(false);

	uint8_t ledColor[] = {color->g, color->r, color->b};
	//adp8866_set_RGBbrightness(ledId, ledColor);

	uint8_t numRGB = 3;
	for(int i = 0; i < numRGB; i++){
		int channel = ledId*numRGB + i;
		adp8866_set_brightness(channel,ledColor[i]);
	}
}

void adp8866_enable_led_rgb(uint8_t ledId, bool en)
{
	if ((ledId > 2) || (ledId < 0)) {
		// LED ID outside of the valid range...
		return ;
	}

	uint8_t numRGB = 3;
	for(int i = 0; i < numRGB; i++){
		int channel = ledId*numRGB + i;
		adp8866_enable_channel(channel,en);
	}
}

void adp8866_enable_all_leds(bool en)
{
	uint8_t numLeds= 3;
	for(int i = 0; i < numLeds; i++){
		adp8866_enable_led_rgb(i,en);
	}
}

void adp8866_set_led_rgb_pulse(uint8_t ledId, RGB color)
{

	if ((ledId > 2) || (ledId < 0)) {
		// LED ID outside of the valid range...
		return ;
	}

	//adp8866_enable_heartbeat(true);

	uint8_t numRGB = 3;
	uint8_t ledColor[] = {color.g, color.r, color.b};
	for(int i = 0; i < numRGB; i++){
		int channel = ledId*numRGB + i;
		adp8866_pulse_channel(channel,ledColor[i]);
	}
}

void adp8866_set_all_red()
{
	RGB  color;
	color.r = 50; color.g = 0;  color.b = 0;
	uint8_t numeLeds = 3;
	for(int i = 0; i < numeLeds; i++)
	{
		adp8866_set_led_rgb(i,&color);
	}
}

void adp8866_set_all_green()
{
	RGB  color;
	color.r = 0; color.g = 50;  color.b = 0;
	uint8_t numeLeds = 3;
	for(int i = 0; i < numeLeds; i++)
	{
		adp8866_set_led_rgb(i,&color);
	}
}


void adp8866_set_all_yellow()
{
	RGB  color;
	color.r = 50; color.g = 50;  color.b = 0;
	uint8_t numeLeds = 3;
	for(int i = 0; i < numeLeds; i++)
	{
		adp8866_set_led_rgb(i,&color);
	}
}

void adp8866_set_all_black()
{
	RGB  color;
	color.r = 0; color.g = 0;  color.b = 0;
	uint8_t numeLeds = 3;
	for(int i = 0; i < numeLeds; i++)
	{
		adp8866_set_led_rgb(i,&color);
	}
}

void adp8866_set_all_white()
{
	RGB  color;
	color.r = 50; color.g = 50;  color.b = 50;
	uint8_t numeLeds = 3;
	for(int i = 0; i < numeLeds; i++)
	{
		adp8866_set_led_rgb(i,&color);
	}
}

void adp8866_set_all_blue()
{
	RGB  color;
	color.r = 0; color.g = 0;  color.b = 50;
	uint8_t numeLeds = 3;
	for(int i = 0; i < numeLeds; i++)
	{
		adp8866_set_led_rgb(i,&color);
	}
}

void adp8866_set_led_red(uint8_t ledId)
{
	RGB  color;
	color.r = 50; color.g = 0;  color.b = 0;
	adp8866_set_led_rgb(ledId,&color);
}

void adp8866_set_led_blue(uint8_t ledId)
{
	RGB  color;
	color.r = 0; color.g = 0;  color.b = 50;
	adp8866_set_led_rgb(ledId,&color);
}

void adp8866_set_led_green(uint8_t ledId)
{
	RGB  color;
	color.r = 0; color.g = 50;  color.b = 0;
	adp8866_set_led_rgb(ledId,&color);
}

void adp8866_set_led_yellow(uint8_t ledId)
{
	RGB  color;
	color.r = 50; color.g = 50;  color.b = 0;
	adp8866_set_led_rgb(ledId,&color);
}

void adp8866_set_led_black(uint8_t ledId)
{
	RGB  color;
	color.r = 0; color.g = 0;  color.b = 0;
	adp8866_set_led_rgb(ledId,&color);
}

void adp8866_set_led_white(uint8_t ledId)
{
	RGB  color;
	color.r = 50; color.g = 50;  color.b = 50;
	adp8866_set_led_rgb(ledId,&color);
}




HSV rgb2hsv(RGB in)
{
	HSV         out;
	uint8_t 	min, max, delta;
	uint8_t 	maxRange = 128;

	if(in.r<in.g)min=in.r; else min=in.g;
	if(in.b<min)min=in.b;

	if(in.r>in.g)max=in.r; else max=in.g;
	if(in.b>max)max=in.b;

	out.v = max;                // v, 0..128
	delta = max - min;                      // 0..128, < v

	if( max != 0 ){
		out.s = (int)(delta)*maxRange / max;        // s, 0..128
	}
	else {
		// r = g = b = 0        // s = 0, v is undefined
		out.s = 0;
		out.h = 0;
		return out;
	}

	if( in.r == max ){
	 out.h = (in.g - in.b)*60/delta;        // between yellow & magenta
	}
	else if( in.g == max ){
		out.h = 120 + (in.b - in.r)*60/delta;    // between cyan & yellow
	}
	else{
		out.h = 240 + (in.r - in.g)*60/delta;    // between magenta & cyan
	}

	if( out.h < 0 )
		out.h += 360;

	return out;
}

RGB hsv2rgb(HSV in)
{
	RGB         out;
	int i;
	uint8_t 	maxRange = 128;
	float f, p, q, t, h, s, v;

	h=(float)in.h;
	s=(float)in.s;
	v=(float)in.v;

	s /= maxRange;

	if( s == 0 ) { // achromatic (grey)
		out.r = out.g = out.b = v;
		return out;
	}

	h /= 60;            // sector 0 to 5
	i =  ifloor( h );
	f = h - i;            // factorial part of h
	p = (uint8_t)(v * ( 1 - s ));
	q = (uint8_t)(v * ( 1 - s * f ));
	t = (uint8_t)(v * ( 1 - s * ( 1 - f ) ));

	switch( i ) {
	case 0:
		out.r = v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = v;
		out.b = t;
		break;
	case 3:
		out.r = p;
		out.g = q;
		out.b = v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = v;
		break;
	default:        // case 5:
		out.r = v;
		out.g = p;
		out.b = q;
		break;
	}

	return out;
}

int ifloor( float x )
{
	if (x >= 0)
	{
		return (int)x;
	}
	else
	{
		int y = (int)x;
		return ((float)y == x) ? y : y - 1;
	}
}



