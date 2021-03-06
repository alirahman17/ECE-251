//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

         
// USER INCLUDES			
#include <SI_EFM8BB3_Register_Enums.h>
#include "bsp.h"
#include <stdio.h>
#include "joystick.h"
//#include "nav_up.h"
//#include "nav_down.h"
//#include "nav_left.h"
//#include "nav_right.h"


//FrequencySet
#define Supported_Num_Freq 10
//PresetFrequencies
static uint16_t frequencies[Supported_Num_Freq] = {
		10L,
		20L,
		30L,
		40L,
		50L,
		60L,
		70L,
		80L,
		90L,
		100L
};

static uint8_t FREQUENCY = 5;


//FrequencySelect
static void FrequencySelect(uint8_t dir)
{
		if (dir == JOYSTICK_N)
	{
		if(FREQUENCY == Supported_Num_Freq-1)
		{
			FREQUENCY = 0;
		}
			else

		{
			FREQUENCY++;
		}
	}
		else if (dir == JOYSTICK_S)
		{
			if (FREQUENCY == 0)
			{
				FREQUENCY = Supported_Num_Freq-1;
			}
			else
			{
				FREQUENCY--;
			}
		}

}


// getJoystick

static uint8_t getJoystick(void)
{
  uint32_t mv;
  uint8_t dir;
  ADC0CN0_ADBUSY = 1;
  while (!ADC0CN0_ADINT);
  ADC0CN0_ADINT = 0;
  mv = ((uint32_t)ADC0) * 3300 / 1024;
  dir = JOYSTICK_convert_mv_to_direction(mv);

  return dir;
}

// getWaitJoystick
// Get joystick input If joystick was moved, wait for release

static uint8_t getWaitJoystick(void)
{
  uint8_t dir, dirSave;
  dir = getJoystick();
  dirSave = dir;
  while (dir != JOYSTICK_NONE)
  {
    dir = getJoystick();
  }
  return dirSave;
}

//getJoystickWave
static void ProcessInput(uint8_t dir)
{
	if ((dir == JOYSTICK_N || dir == JOYSTICK_S))
	{
		//FreqencySelect(dir)
	}
}


//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
SI_SBIT(LED0, SFR_P1, 4);                  // P1.4 LED0
SI_SBIT(LED1, SFR_P1, 5);                  // P1.5 LED1
SI_SBIT(LED2, SFR_P1, 6);                  // P1.6 LED2

#define SYSCLK          24500000       // SYSCLK frequency in Hz

#define SAMPLE_RATE_DAC 200000L        // DAC sampling rate in Hz

#define PHASE_PRECISION 65536          // Range of phase accumulator

#define PHASE_ADD       (FREQUENCY * PHASE_PRECISION / SAMPLE_RATE_DAC)

// A full cycle, 12-bit, unsigned square wave lookup table
SI_SEGMENT_VARIABLE(SQUARE_TABLE[256], uint16_t, const SI_SEG_CODE) =
{
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
		  0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
		  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
		  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
		  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
		  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
		  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
		  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
		  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
		  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
		  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
		  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
		  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
		  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
};

//-----------------------------------------------------------------------------
// TIMER3_ISR
//-----------------------------------------------------------------------------
//
// TIMER3 ISR Content goes here. Remember to clear flag bits:
// TMR3CN::TF2H (Timer # High Byte Overflow Flag)
// TMR3CN::TF2L (Timer # Low Byte Overflow Flag)
//
// This routine changes the state of the LED whenever Timer3 overflows.
//
//-----------------------------------------------------------------------------

SI_INTERRUPT (TIMER3_ISR, TIMER3_IRQn)
{
   uint8_t SFRPAGE_save = SFRPAGE;

   static uint16_t phase_acc = 0;      // Holds phase accumulator

   SI_UU16_t temp;                     // The temporary value that holds
									   // value before being written
									   // to the IDAC

   SI_VARIABLE_SEGMENT_POINTER(table_ptr, uint16_t, const SI_SEG_CODE);  // Pointer to the lookup table


   TMR3CN0 &= ~0x80;                   // Clear Timer3 overflow flag

   table_ptr = SQUARE_TABLE;

   phase_acc += PHASE_ADD;             // Increment phase accumulator


   // Read the table value
   temp.u16 = *(table_ptr + (phase_acc >> 8));

   // Set the value of <temp> to the next output of DAC at full-scale
   // amplitude. The rails are 0x000 and 0xFFF. DAC low byte must be
   // written first.

   SFRPAGE = PG4_PAGE;

   DAC0L = temp.u8[LSB];
   DAC0H = temp.u8[MSB];

   DAC1L = temp.u8[LSB];
   DAC1H = temp.u8[MSB];

   SFRPAGE = SFRPAGE_save;

}

