#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* Base addresses ************************************************************/
#define PERIPH_BASE           ((uint32_t)0x40000000)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000)

/* Peripheral memory map */
#define RCC_BASE              (AHBPERIPH_BASE + 0x00001000)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x00000800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x00000C00)
#define AFIO_BASE             (APB2PERIPH_BASE + 0x00000000)

/* Register structures *******************************************************/

/* Reset and Clock Control (RCC) */
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_TypeDef;

/* Alternate Function I/O (AFIO) */
typedef struct
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
    volatile uint32_t RESERVED0;
    volatile uint32_t MAPR2;
} AFIO_TypeDef;

/* General Purpose I/O (GPIO) */
typedef struct
{
    volatile uint32_t CRL;    /* Configuration register low */
    volatile uint32_t CRH;    /* Configuration register high */
    volatile uint32_t IDR;    /* Input data register */
    volatile uint32_t ODR;    /* Output data register */
    volatile uint32_t BSRR;   /* Bit set/reset register */
    volatile uint32_t BRR;    /* Bit reset register */
    volatile uint32_t LCKR;   /* Configuration lock register */
} GPIO_TypeDef;

/* Peripheral declarations ***************************************************/

#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define AFIO                ((AFIO_TypeDef *) AFIO_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)

/* RCC_APB2ENR register bits */
#define RCC_APB2ENR_AFIOEN       ((uint32_t)0x00000001)
#define RCC_APB2ENR_IOPAEN       ((uint32_t)0x00000004)
#define RCC_APB2ENR_IOPBEN       ((uint32_t)0x00000008)

/* AFIO_MAPR register bits */
#define AFIO_MAPR_SWJ_CFG         ((uint32_t)0x07000000)
#define AFIO_MAPR_SWJ_CFG_JTAGDISABLE ((uint32_t)0x02000000)

/* GPIO Pin definitions ******************************************************/

#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected */

/* Define LEDs and Buttons ***************************************************/

/* LEDs */
#define LED_PIN_0        GPIO_PIN_0  /* PA0 */
#define LED_PIN_1       GPIO_PIN_1  /* PA1 */
#define LED_PIN_2      GPIO_PIN_4  /* PA4 */
#define LED_PIN_3       GPIO_PIN_0  /* PB0 */

/* Buttons */
#define BTN_PIN_0     GPIO_PIN_4  /* PB4 */
#define BTN_PIN_1     GPIO_PIN_6  /* PB6 */
#define BTN_PIN_2     GPIO_PIN_8  /* PB8 */
#define BTN_PIN_3     GPIO_PIN_9  /* PB9 */

/* Function prototypes *******************************************************/

// Existing prototypes...
void GPIO_Config(void);
void Delay(volatile uint32_t nCount);
void turnOnLED(int ledIndex);
void turnOffLED(int ledIndex);
void turnOffAllLEDs(void);
void turnOnAllLEDs(void);
bool isbuttonPressed(void);
int getButtonPressed(void);
void BeginningLEDsSequence(void);
bool StartRound(int roundNumber, int sequence[]);
int generateRandomLED(void);
int getUserInput(volatile uint32_t timeout);
void WinningSequence(void);
void FailureSequence(int failedRound);          // Updated prototype
void displayFailedRoundinbinary(int round);             // New prototype
void displaywinningLevelInBinary(int level);
void restartGame(void);
void seedRandomGeneration(void);

#endif /* MAIN_H */
