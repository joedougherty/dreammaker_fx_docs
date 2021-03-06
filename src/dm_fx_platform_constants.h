#ifndef DM_FX_PLATFORM_CONSTANTS_H
#define DM_FX_PLATFORM_CONSTANTS_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS


#ifndef PI2
#define PI2 (3.14159265358979323846*2)
#endif 

#define MAX_INSTANCES                 (100)
#define MAX_ROUTES                    (100)
#define MAX_NODES_PER_FX              (10)
#define MAX_PARMS_PER_FX              (256)
#define MAX_NODE_NAME                 (32)
#define UNDEFINED                     (0xff)

#if defined (DM_FX)

  #define PIN_FOOTSW_1                  (0)
  #define PIN_FOOTSW_RIGHT              (0)
  #define PIN_FOOTSW_2                  (1)
  #define PIN_FOOTSW_LEFT               (1)
  #define PIN_FOOTSW_LED_1              (2)
  #define PIN_FOOTSW_LED_RIGHT          (2)
  #define PIN_FOOTSW_LED_2              (3)
  #define PIN_FOOTSW_LED_LEFT           (3)
  #define PIN_USR_PB                    (4)
  #define PIN_ARD_LED                   (5)
  #define SPI_SS_PIN                    (47) 
  #define PIN_DSP_RESET                 (6)
  #define SPI_SHARC_RESET               (PIN_DSP_RESET)   
  #define PIN_DSP_SPI_FLASH_SELECT      (7)
  #define SPI_SHARC_SELECT              (PIN_DSP_SPI_FLASH_SELECT)

#elif defined (DM_FX_TWO)
  #define PIN_FOOTSW_1                  (0)
  #define PIN_FOOTSW_RIGHT              (0)
  #define PIN_FOOTSW_2                  (1)
  #define PIN_FOOTSW_LEFT               (1)
  #define PIN_ARD_LED                   (5)
  #define PIN_ARD_LED_G                 (4)
  #define PIN_ARD_LED_Y                 (5)
  #define RGB_LED_ENABLE                (39)
  #define SPI_SS_PIN                    (40) 
  #define PIN_DSP_RESET                 (6)
  #define SPI_SHARC_RESET               (PIN_DSP_RESET)   
  #define PIN_DSP_SPI_FLASH_SELECT      (7)
  #define SPI_SHARC_SELECT              (PIN_DSP_SPI_FLASH_SELECT)

#else
  // Handle error where neither board defined
  #error "Neither DM_FX nor DM_FX_TWO are defined"
#endif 


#endif 
#endif   // DM_FX_PLATFORM_CONSTANTS_H