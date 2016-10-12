#include <stdint.h>

// GPIO

#define GPIO_PA_BASE 0x40006000
#define GPIO_PB_BASE 0x40006024
#define GPIO_PC_BASE 0x40006048

#define GPIO_PA_CTRL     ((volatile uint32_t*)(GPIO_PA_BASE + 0x00))
#define GPIO_PA_MODEL    ((volatile uint32_t*)(GPIO_PA_BASE + 0x04))
#define GPIO_PA_MODEH    ((volatile uint32_t*)(GPIO_PA_BASE + 0x08))
#define GPIO_PA_DOUT     ((volatile uint32_t*)(GPIO_PA_BASE + 0x0c))
#define GPIO_PA_DOUTSET  ((volatile uint32_t*)(GPIO_PA_BASE + 0x10))
#define GPIO_PA_DOUTCLR  ((volatile uint32_t*)(GPIO_PA_BASE + 0x14))
#define GPIO_PA_DOUTTGL  ((volatile uint32_t*)(GPIO_PA_BASE + 0x18))
#define GPIO_PA_DIN      ((volatile uint32_t*)(GPIO_PA_BASE + 0x1c))
#define GPIO_PA_PINLOCKN ((volatile uint32_t*)(GPIO_PA_BASE + 0x20))

#define GPIO_PB_CTRL     ((volatile uint32_t*)(GPIO_PB_BASE + 0x00))
#define GPIO_PB_MODEL    ((volatile uint32_t*)(GPIO_PB_BASE + 0x04))
#define GPIO_PB_MODEH    ((volatile uint32_t*)(GPIO_PB_BASE + 0x08))
#define GPIO_PB_DOUT     ((volatile uint32_t*)(GPIO_PB_BASE + 0x0c))
#define GPIO_PB_DOUTSET  ((volatile uint32_t*)(GPIO_PB_BASE + 0x10))
#define GPIO_PB_DOUTCLR  ((volatile uint32_t*)(GPIO_PB_BASE + 0x14))
#define GPIO_PB_DOUTTGL  ((volatile uint32_t*)(GPIO_PB_BASE + 0x18))
#define GPIO_PB_DIN      ((volatile uint32_t*)(GPIO_PB_BASE + 0x1c))
#define GPIO_PB_PINLOCKN ((volatile uint32_t*)(GPIO_PB_BASE + 0x20))

#define GPIO_PC_CTRL     ((volatile uint32_t*)(GPIO_PC_BASE + 0x00))
#define GPIO_PC_MODEL    ((volatile uint32_t*)(GPIO_PC_BASE + 0x04))
#define GPIO_PC_MODEH    ((volatile uint32_t*)(GPIO_PC_BASE + 0x08))
#define GPIO_PC_DOUT     ((volatile uint32_t*)(GPIO_PC_BASE + 0x0c))
#define GPIO_PC_DOUTSET  ((volatile uint32_t*)(GPIO_PC_BASE + 0x10))
#define GPIO_PC_DOUTCLR  ((volatile uint32_t*)(GPIO_PC_BASE + 0x14))
#define GPIO_PC_DOUTTGL  ((volatile uint32_t*)(GPIO_PC_BASE + 0x18))
#define GPIO_PC_DIN      ((volatile uint32_t*)(GPIO_PC_BASE + 0x1c))
#define GPIO_PC_PINLOCKN ((volatile uint32_t*)(GPIO_PC_BASE + 0x20))

#define GPIO_EXTIPSELL ((volatile uint32_t*)(GPIO_PA_BASE + 0x100))
#define GPIO_EXTIPSELH ((volatile uint32_t*)(GPIO_PA_BASE + 0x104))
#define GPIO_EXTIRISE  ((volatile uint32_t*)(GPIO_PA_BASE + 0x108))
#define GPIO_EXTIFALL  ((volatile uint32_t*)(GPIO_PA_BASE + 0x10c))
#define GPIO_IEN       ((volatile uint32_t*)(GPIO_PA_BASE + 0x110))
#define GPIO_IFC       ((volatile uint32_t*)(GPIO_PA_BASE + 0x11c))

// CMU

#define CMU_BASE2 0x400c8000

#define CMU_HFPERCLKDIV  ((volatile uint32_t*)(CMU_BASE2 + 0x008))
#define CMU_HFCORECLKEN0 ((volatile uint32_t*)(CMU_BASE2 + 0x040))
#define CMU_HFPERCLKEN0  ((volatile uint32_t*)(CMU_BASE2 + 0x044))
#define CMU_CMD          ((volatile uint32_t*)(CMU_BASE2 + 0x024))
#define CMU_LFACLKEN0    ((volatile uint32_t*)(CMU_BASE2 + 0x058))
#define CMU_LFCLKSEL	 ((volatile uint32_t*)(CMU_BASE2 + 0x028))
#define CMU_OSCENCMD 	 ((volatile uint32_t*)(CMU_BASE2 + 0x020))

#define CMU2_HFPERCLKEN0_DAC0   (1 << 17)
#define CMU2_HFPERCLKEN0_PRS    (1 << 15)
#define CMU2_HFPERCLKEN0_GPIO   (1 << 13)
#define CMU2_HFPERCLKEN0_TIMER1 (1 << 6)
#define CMU2_HFPERCLKEN0_TIMER2 (1 << 7)

#define CMU_HFCORECLKEN0_DMA (1 << 0)

// TIMER1

#define TIMER1_BASE 0x40010400

#define TIMER1_CMD ((volatile uint32_t*)(TIMER1_BASE + 0x04))
#define TIMER1_IEN ((volatile uint32_t*)(TIMER1_BASE + 0x0c))
#define TIMER1_IFC ((volatile uint32_t*)(TIMER1_BASE + 0x18))
#define TIMER1_TOP ((volatile uint32_t*)(TIMER1_BASE + 0x1c))
#define TIMER1_CNT ((volatile uint32_t*)(TIMER1_BASE + 0x24))
#define TIMER1_CTRL ((volatile uint32_t*)(TIMER1_BASE + 0x00))
#define TIMER1_PER (1 << 24)

// TIMER2

#define TIMER2_BASE 0x40010800


#define TIMER2_CMD ((volatile uint32_t*)(TIMER2_BASE + 0x04))
#define TIMER2_IEN ((volatile uint32_t*)(TIMER2_BASE + 0x0c))
#define TIMER2_IFC ((volatile uint32_t*)(TIMER2_BASE + 0x18))
#define TIMER2_TOP ((volatile uint32_t*)(TIMER2_BASE + 0x1c))
#define TIMER2_CNT ((volatile uint32_t*)(TIMER2_BASE + 0x24))
#define TIMER2_CTRL ((volatile uint32_t*)(TIMER2_BASE + 0x00))
#define TIMER2_PER (1 << 24)

// NVIC

#define ISER0 ((volatile uint32_t*)0xe000e100)
#define ISER1 ((volatile uint32_t*)0xe000e104)
#define ICER0 ((volatile uint32_t*)0xe000e180)
#define ICER1 ((volatile uint32_t*)0xe000e184)
#define ISPR0 ((volatile uint32_t*)0xe000e200)
#define ISPR1 ((volatile uint32_t*)0xe000e204)
#define ICPR0 ((volatile uint32_t*)0xe000e280)
#define ICPR1 ((volatile uint32_t*)0xe000e284)
#define IABR0 ((volatile uint32_t*)0xe000e300)
#define IABR1 ((volatile uint32_t*)0xe000e304)

// IPR

#define IPR_BASE  0xe000e400

#define IPR0 ((volatile uint32_t*)(IPR_BASE + 0x00))
#define IPR1 ((volatile uint32_t*)(IPR_BASE + 0x04))
#define IPR2 ((volatile uint32_t*)(IPR_BASE + 0x08))
#define IPR3 ((volatile uint32_t*)(IPR_BASE + 0x0c))

// EMU

#define EMU_BASE2 0x400c6000

#define EMU_CTRL ((volatile uint32_t*)(EMU_BASE2 + 0x000))

// DAC0

#define DAC0_BASE2 0x40004000

#define DAC0_CTRL     ((volatile uint32_t*)(DAC0_BASE2 + 0x000))
#define DAC0_CH0CTRL  ((volatile uint32_t*)(DAC0_BASE2 + 0x008))
#define DAC0_CH1CTRL  ((volatile uint32_t*)(DAC0_BASE2 + 0x00c))
#define DAC0_IEN      ((volatile uint32_t*)(DAC0_BASE2 + 0x010))
#define DAC0_IF       ((volatile uint32_t*)(DAC0_BASE2 + 0x014))
#define DAC0_IFS      ((volatile uint32_t*)(DAC0_BASE2 + 0x018))
#define DAC0_IFC      ((volatile uint32_t*)(DAC0_BASE2 + 0x01c))
#define DAC0_CH0DATA  ((volatile uint32_t*)(DAC0_BASE2 + 0x020))
#define DAC0_CH1DATA  ((volatile uint32_t*)(DAC0_BASE2 + 0x024))
#define DAC0_COMBDATA ((volatile uint32_t*)(DAC0_BASE2 + 0x028))

// DMA

#define DMA_BASE 0x400c2000

#define DMA_STATUS      ((volatile uint32_t*)(DMA_BASE + 0x0000))
#define DMA_CONFIG      ((volatile uint32_t*)(DMA_BASE + 0x0004))
#define DMA_CTRLBASE    ((volatile uint32_t*)(DMA_BASE + 0x0008))
#define DMA_ALTCTRLBASE ((volatile uint32_t*)(DMA_BASE + 0x000c))
#define DMA_CHUSEBURSTS ((volatile uint32_t*)(DMA_BASE + 0x0018))
#define DMA_CHUSEBURSTC ((volatile uint32_t*)(DMA_BASE + 0x001c))
#define DMA_REQMASKC    ((volatile uint32_t*)(DMA_BASE + 0x0024))
#define DMA_CHENS       ((volatile uint32_t*)(DMA_BASE + 0x0028))
#define DMA_CHALTC      ((volatile uint32_t*)(DMA_BASE + 0x0034))
#define DMA_IFC         ((volatile uint32_t*)(DMA_BASE + 0x1008))
#define DMA_IEN         ((volatile uint32_t*)(DMA_BASE + 0x100c))
#define DMA_CH0_CTRL    ((volatile uint32_t*)(DMA_BASE + 0x1100))

// PRS

#define PRS_BASE 0x400cc000

#define PRS_CH0_CTRL ((volatile uint32_t*)(PRS_BASE + 0x010))

// System Control Block

#define SCR          ((volatile uint32_t*)0xe000ed10)
#define SYSTICK_CTRL ((volatile uint32_t*)0xe000e010)
#define SYSTICK_LOAD ((volatile uint32_t*)0xe000e014)

//LETIMER0
#define LETIMER0_BASE 0x40082000

#define LETIMER0_CTRL ((volatile uint32_t*)(LETIMER0_BASE + 0x000))
#define LETIMER0_CMD  ((volatile uint32_t*)(LETIMER0_BASE + 0x004))
#define LETIMER0_IEN  ((volatile uint32_t*)(LETIMER0_BASE + 0x02c))
#define LETIMER0_IFC  ((volatile uint32_t*)(LETIMER0_BASE + 0x028))
#define LETIMER0_TOP  ((volatile uint32_t*)(LETIMER0_BASE + 0x010))
#define LETIMER0_CNT  ((volatile uint32_t*)(LETIMER0_BASE + 0x00c))
#define LETIMER0_IF ((volatile uint32_t*)(LETTIMER0_BASE + 0x020))


void setupDAC ();
void disableDAC ();
void setupTimer2 (uint16_t period);
void setupTimer (uint16_t period);
void stopTimer1 ();
void stopTimer2 ();
void GPIO_interrupt ();

struct tone
{
  int note, time;
};

void playStart (void);

struct tone sounds[7];

void playMusic (struct tone test[], uint32_t lengde);

void play (uint32_t a);

void startTimer ();

void stopTimer ();

void disableTimer ();

void setupLowEnergyTimer ();

void changeTopCounter (int sample_rate);

void disableLowEnergyTimer ();

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
