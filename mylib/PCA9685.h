/* Registers for NXP PCA9685 16-channel, 12-bit PWM Fm+ I2C-bus LED controller 
 * Ref: Product data sheet, Rev. 4 -- 16 April 2015
 */

// I2C bus address (shift left 1 bit before sending!)
#define PCA9685_ADDR	0x60	

// PCA9685 REGISTER TABLE
#define	MODE1			0	// Mode register 1    
#define	MODE2			1	// Mode register 2    

#define	SUBADR1			2	// I2C-bus subaddress 1    
#define	SUBADR2			3	// I2C-bus subaddress 2    
#define	SUBADR3			4	// I2C-bus subaddress 3    
#define	ALLCALLADR		5	// LED All Call I2C-bus address  

#define	LED0_ON_L		6	// LED0 output and brightness control byte 0
#define	LED0_ON_H		7	// LED0 output and brightness control byte 1
#define	LED0_OFF_L		8	// LED0 output and brightness control byte 2   
#define	LED0_OFF_H		9	// LED0 output and brightness control byte 3   

#define	LED1_ON_L		10	// LED1 output and brightness control byte 0   
#define	LED1_ON_H		11	// LED1 output and brightness control byte 1   
#define	LED1_OFF_L		12	// LED1 output and brightness control byte 2   
#define	LED1_OFF_H		13	// LED1 output and brightness control byte 3  
 
#define	LED2_ON_L		14	// LED2 output and brightness control byte 0   
#define	LED2_ON_H		15	// LED2 output and brightness control byte 1   
#define	LED2_OFF_L		16	// LED2 output and brightness control byte 2   
#define	LED2_OFF_H		17	// LED2 output and brightness control byte 3  
 
#define	LED3_ON_L		18	// LED3 output and brightness control byte 0   
#define	LED3_ON_H		19	// LED3 output and brightness control byte 1   
#define	LED3_OFF_L		20	// LED3 output and brightness control byte 2   
#define	LED3_OFF_H		21	// LED3 output and brightness control byte 3   

#define	LED4_ON_L		22	// LED4 output and brightness control byte 0   
#define	LED4_ON_H		23	// LED4 output and brightness control byte 1   
#define	LED4_OFF_L		24	// LED4 output and brightness control byte 2   
#define	LED4_OFF_H		25	// LED4 output and brightness control byte 3 
  
#define	LED5_ON_L		26	// LED5 output and brightness control byte 0   
#define	LED5_ON_H		27	// LED5 output and brightness control byte 1   
#define	LED5_OFF_L		28	// LED5 output and brightness control byte 2   
#define	LED5_OFF_H		29	// LED5 output and brightness control byte 3 
  
#define	LED6_ON_L		30	// LED6 output and brightness control byte 0   
#define	LED6_ON_H		31	// LED6 output and brightness control byte 1   
#define	LED6_OFF_L		32	// LED6 output and brightness control byte 2   
#define	LED6_OFF_H		33	// LED6 output and brightness control byte 3  
 
#define	LED7_ON_L		34	// LED7 output and brightness control byte 0   
#define	LED7_ON_H		35	// LED7 output and brightness control byte 1   
#define	LED7_OFF_L		36	// LED7 output and brightness control byte 2   
#define	LED7_OFF_H		37	// LED7 output and brightness control byte 3  
 
#define	LED8_ON_L		38	// LED8 output and brightness control byte 0   
#define	LED8_ON_H		39	// LED8 output and brightness control byte 1   
#define	LED8_OFF_L		40	// LED8 output and brightness control byte 2   
#define	LED8_OFF_H		41	// LED8 output and brightness control byte 3  
 
#define	LED9_ON_L		42	// LED9 output and brightness control byte 0   
#define	LED9_ON_H		43	// LED9 output and brightness control byte 1   
#define	LED9_OFF_L		44	// LED9 output and brightness control byte 2   
#define	LED9_OFF_H		45	// LED9 output and brightness control byte 3   

#define	LED10_ON_L		46	// LED10 output and brightness control byte 0   
#define	LED10_ON_H		47	// LED10 output and brightness control byte 1   
#define	LED10_OFF_L		48	// LED10 output and brightness control byte 2   
#define	LED10_OFF_H		49	// LED10 output and brightness control byte 3 
  
#define	LED11_ON_L		50	// LED11 output and brightness control byte 0   
#define	LED11_ON_H		51	// LED11 output and brightness control byte 1   
#define	LED11_OFF_L		52	// LED11 output and brightness control byte 2   
#define	LED11_OFF_H		53	// LED11 output and brightness control byte 3  
 
#define	LED12_ON_L		54	// LED12 output and brightness control byte 0   
#define	LED12_ON_H		55	// LED12 output and brightness control byte 1   
#define	LED12_OFF_L		56	// LED12 output and brightness control byte 2   
#define	LED12_OFF_H		57	// LED12 output and brightness control byte 3 
  
#define	LED13_ON_L		58	// LED13 output and brightness control byte 0   
#define	LED13_ON_H		59	// LED13 output and brightness control byte 1   
#define	LED13_OFF_L		60	// LED13 output and brightness control byte 2   
#define	LED13_OFF_H		61	// LED13 output and brightness control byte 3 
  
#define	LED14_ON_L		62	// LED14 output and brightness control byte 0   
#define	LED14_ON_H		63	// LED14 output and brightness control byte 1   
#define	LED14_OFF_L		64	// LED14 output and brightness control byte 2   
#define	LED14_OFF_H		65	// LED14 output and brightness control byte 3 
  
#define	LED15_ON_L		66	// LED15 output and brightness control byte 0   
#define	LED15_ON_H		67	// LED15 output and brightness control byte 1   
#define	LED15_OFF_L		68	// LED15 output and brightness control byte 2   
#define	LED15_OFF_H		69	// LED15 output and brightness control byte 3   

#define	ALL_LED_ON_L	250	// load all the LEDn_ON registers, byte 0
#define	ALL_LED_ON_H	251	// load all the LEDn_ON registers, byte 1
#define	ALL_LED_OFF_L	252	// load all the LEDn_OFF registers, byte 0
#define	ALL_LED_OFF_H	253	// load all the LEDn_OFF registers, byte 1

#define	PRE_SCALE		254	// prescaler for PWM output frequency
#define	TESTMODE		255	// Defines the test mode to be entered
