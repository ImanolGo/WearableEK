/*
 * adp8866.h
 *
 *  Created on: 20.06.2016
 *      Author: Imanol Gomez
 */

#ifndef ADP8866_H_
#define ADP8866_H_

#include <stdint.h>
#include <stdbool.h>

// These are the register definitions.
#define ADP8866_MANU_DEV_ID        0x00
#define ADP8866_MDCR               0x01
#define ADP8866_INT_STAT           0x02
#define ADP8866_INT_EN             0x03
#define ADP8866_ISCOFF_SEL_1       0x04
#define ADP8866_ISCOFF_SEL_2       0x05
#define ADP8866_GAIN_SEL           0x06
#define ADP8866_LVL_SEL_1          0x07
#define ADP8866_LVL_SEL_2          0x08
#define ADP8866_PWR_SEL_1          0x09
#define ADP8866_PWR_SEL_2          0x0A
#define ADP8866_CFGR               0x10
#define ADP8866_BLSEL              0x11
#define ADP8866_BLFR               0x12
#define ADP8866_BLMX               0x13
#define ADP8866_ISCC1              0x1A
#define ADP8866_ISCC2              0x1B
#define ADP8866_ISCT1              0x1C
#define ADP8866_ISCT2              0x1D
#define ADP8866_OFFTIMER6          0x1E
#define ADP8866_OFFTIMER7          0x1F
#define ADP8866_OFFTIMER8          0x20
#define ADP8866_OFFTIMER9          0x21
#define ADP8866_ISCF               0x22
#define ADP8866_ISC1               0x23
#define ADP8866_ISC2               0x24
#define ADP8866_ISC3               0x25
#define ADP8866_ISC4               0x26
#define ADP8866_ISC5               0x27
#define ADP8866_ISC6               0x28
#define ADP8866_ISC7               0x29
#define ADP8866_ISC8               0x2A
#define ADP8866_ISC9               0x2B
#define ADP8866_HB_SEL             0x2C
#define ADP8866_ISC6_HB            0x2D
#define ADP8866_ISC7_HB            0x2E
#define ADP8866_ISC8_HB            0x2F
#define ADP8866_ISC9_HB            0x30
#define ADP8866_OFFTIMER6_HB       0x31
#define ADP8866_OFFTIMER7_HB       0x32
#define ADP8866_OFFTIMER8_HB       0x33
#define ADP8866_OFFTIMER9_HB       0x34
#define ADP8866_ISCT_HB            0x35
#define ADP8866_DELAY6             0x3C
#define ADP8866_DELAY7             0x3D
#define ADP8866_DELAY8             0x3E
#define ADP8866_DELAY9             0x3F

#define ADP8866_ID        		   0x53
#define ADP8866_I2CADDR            0x4E

/*
* These state flags are hosted by the EventReceiver. This may change in the future.
* Might be too much convention surrounding their assignment across inherritence.
*/
#define ADP8866_FLAG_INIT_COMPLETE 0x01    // Is the device initialized?


/*
* Internal register bitmask definitions.
*/
#define ADP8866_INT_STATUS_OV      0x04
#define ADP8866_INT_STATUS_OT      0x08
#define ADP8866_INT_STATUS_ICS_OFF 0x40
#define ADP8866_INT_STATUS_BL_OFF  0x20
#define ADP8866_INT_STATUS_SHORT   0x10


/*
* Used to aggregate channel information into a single place. Makes drive code more readable.
*/
typedef struct adp8866_led_chan {
  float          max_current;
  uint8_t        present;
  uint8_t        flags;
  uint16_t       reserved;     // Reserved for later use.
} ADPLEDChannel;

/*
* Used to set RGB colors
*/
typedef struct adp8866_rgb{
  uint8_t		r;		// Red (0-127)
  uint8_t		g;		// Green (0-127)
  uint8_t		b;     	// Blue (0-127)
} RGB;

/*
* Used to set HSV colors
*/
typedef struct adp8866_hsv {

  float			h;		// Angle (degrees, 0-360)
  uint8_t		s;		// Saturation (0-127)
  uint8_t		v;     	// Value (0-127)
} HSV;



HSV rgb2hsv(RGB in);
RGB hsv2rgb(HSV in);
int ifloor( float x );

bool adp8866_testConnection(void);
bool adp8866_initialize(void);
uint8_t adp8866_getDeviceID(void);
uint8_t adp8866_getChannelEnable(uint8_t);
uint8_t adp8866_getChannelState(uint8_t);
uint8_t adp8866_getInterruptState();
void adp8866_processInterrupt();
//uint8_t adp8866_getChannelHBEnable(void);

bool adp8866_initMDCR(void);
bool adp8866_initLevels(void);
bool adp8866_initPwrSource(void);
bool adp8866_initCfr(void);
bool adp8866_initfadeRates(void);
bool adp8866_initFadeBLCurrent(void);
bool adp8866_initSinkCtrl(void);
bool adp8866_initSinkDelays(void);
bool adp8866_initInterrupts(void);
bool adp8866_initLeds(void);

/* Dimmer breakouts. */
bool adp8866_set_brightness(uint8_t, uint8_t);
bool adp8866_set_RGBbrightness(uint8_t, uint8_t*);
bool adp8866_pulse_channel(uint8_t, uint8_t);
bool adp8866_enable_channel(uint8_t, bool);
bool adp8866_enable_heartbeat(bool);

void adp8866_set_all_red();
void adp8866_set_all_green();
void adp8866_set_all_yellow();
void adp8866_set_all_blue();
void adp8866_set_all_black();
void adp8866_set_all_white();

void adp8866_set_led_rgb(uint8_t ledId, RGB* color);

void adp8866_set_led_rgb_pulse(uint8_t ledId, RGB color);

void adp8866_set_led_red(uint8_t ledId);
void adp8866_set_led_blue(uint8_t ledId);
void adp8866_set_led_green(uint8_t ledId);
void adp8866_set_led_black(uint8_t ledId);
void adp8866_set_led_white(uint8_t ledId);
void adp8866_set_led_yellow(uint8_t ledId);

bool adp8866_isInitialized;


#endif /* ADP8866_H_ */
