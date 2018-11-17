/**************************************************************************//**
 * Copyright (c) 2015 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/
/////////////////////////////////////////////////////////////////////////////
// Space_invaders.c
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "bsp.h"
#include "utils.h"
#include "rgb_led.h"
#include "joystick.h"
#include "tick.h"
#include "disp.h"
#include "render.h"
#include "space_invaders.h"
#include <string.h>
#include "retargetserial.h"
#include <stdlib.h>

// Generic line buffer
SI_SEGMENT_VARIABLE(Line[DISP_BUF_SIZE], uint8_t, RENDER_LINE_SEG);

/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

void InputPlayer();

/////////////////////////////////////////////////////////////////////////////
// Functions - Input
/////////////////////////////////////////////////////////////////////////////

char outputstr[1];
char output[16] = {0};
int xdata hextext;
int z;
char xdata savedinfo[26][16] = {0};
char xdata savedinfohex[26][16] = {0};
char xdata testbuffer[16] = {0};
int x;
char xdata outputbuffer[16] = {0};
int n;
int u;
int y;
int linenum;
int linenumhex;
int stringlength;
int stringlengthhex;
int rownumber;
int rownumberhex;
int hex;
char outputstrhex[1] = {0};
char xdata outputhex[16] = {0};
//-----------------------------------------------------------------------------
// drawScreenText
//-----------------------------------------------------------------------------
//
// Show one line of text on the screen
//
// str - pointer to string text (0 - 21 characters) to display
// rowNum - row number of the screen (0 - 127)
// fontScale - font scaler (1 - 4)
//
static void drawScreenText(SI_VARIABLE_SEGMENT_POINTER(str, char, RENDER_STR_SEG), uint8_t rowNum)
{
  uint8_t i;

  for (i = 0; i < FONT_HEIGHT; i++)
  {
    RENDER_ClrLine(Line);
    RENDER_StrLine(Line, 4, i, str);
    DISP_WriteLine(rowNum + i, Line);
  }
}
static void drawSplash(void)
{
	uint16_t ticks = GetTickCount();

	while (((GetTickCount() - ticks) < 30)
			);
}
int m;
int i;

//FUNCTIONS
int insertionmode;
static void Scroll(void){
    DISP_ClearAll();
    if(P1_B2 == 0){
	for(n = y; n < rownumber; n++){
	//if(hextext != 1) {
	memcpy(outputbuffer, savedinfo[n], 16);
	drawScreenText(outputbuffer, m);
    m+=8;
	}
    }
    if(P1_B2 == 1){
	for(n = y; n < rownumberhex; n++){
	//if(hextext != 1) {
	memcpy(outputbuffer, savedinfohex[n], 16);
	drawScreenText(outputbuffer, m);
    m+=8;
	}
    }
    insertionmode = 0;

	//}
}

int j = 0;
int k = 0;
int o;


void InputPlayer()
{
    uint32_t mv;
    uint8_t dir;

    ADC0CN0_ADBUSY = 1;
    while (!ADC0CN0_ADINT);
    ADC0CN0_ADINT = 0;

    mv = ((uint32_t)ADC0) * 3300 / 1024;

    dir = JOYSTICK_convert_mv_to_direction(mv);

    if (dir == JOYSTICK_N)
    {
    	y--;
    	Scroll();
    }

    if (dir == JOYSTICK_S)
    {
    	y++;
    	Scroll();
    }

    if (BSP_PB0 == BSP_PB_PRESSED)
    {
    	insertionmode = 0;
    }
    if (BSP_PB1 == BSP_PB_PRESSED)
    {
    	P1_B2 = !P1_B2;
    	Scroll();

    }
}

/////////////////////////////////////////////////////////////////////////////
// Functions - Main
/////////////////////////////////////////////////////////////////////////////

void SpaceInvaders_Main(void)
{
	  unsigned char inputchar;

	  hextext = 1;
	  insertionmode = 0;
	  linenum = 0;
	  rownumber = 0;
	  i = 0;
	  n = 0;
	  y = 0;
	  m = 0;
	  o = 0;
	  stringlength = 0;
	  DISP_ClearAll();
	  SCON0_TI = 1;
	  SCON0_RI = 1;
	  P1_B2 = 0;
	  while(1)
	  {
		  drawSplash();
		  InputPlayer();
		  if (P1_B2 == 1){
			  //drawScreenText("a",1);
		  }
		  if (P1_B2 == 0){
		  			 // drawScreenText("b",1);
		  		  }
		  if(insertionmode == 0){
		  if(inputchar == 9){
			  insertionmode = 1;
		  }
	      RETARGET_PRINTF ("\nEnter character: ");
	      inputchar = getchar();
	   	  RETARGET_PRINTF ("\nCharacter entered: %c", inputchar);
	   	  RETARGET_PRINTF ("\n     Value in Hex: %bx", inputchar);
	      if(linenum>120){
	    	  y++;
	    	  Scroll();
	    	  m = 0;
	    	  stringlength = 0;
	    	  linenum = 120;
	      }

	      RETARGET_SPRINTF (outputstr, "%c", inputchar);
	      //if(P1_B2 == 1){
	      RETARGET_SPRINTF (outputstrhex, "%bx", inputchar);
	      //}
	      strcat(savedinfohex[rownumberhex],&outputstrhex);
	      strcat(savedinfo[rownumber],&outputstr);
	      if(P1_B2 == 0){
	      drawScreenText(output, linenum);
	      }
	      if(P1_B2 == 1){
	      	    drawScreenText(outputhex, linenum);
	      	      }
	      strcat(output,&outputstr);
	      strcat(outputhex,&outputstrhex);
	      stringlength=strlen(output);
	      stringlengthhex=strlen(outputhex);
	  		  if(stringlength>16){
	  			  memset(output,0,16);
	  			  strcat(output,&outputstr);
	  			  rownumber++;
	  			  linenum+=8;
	  		  }
	  		if(stringlengthhex>16){
	  			  			  memset(outputhex,0,16);
	  			  			  strcat(outputhex,&outputstrhex);
	  			  			  rownumberhex++;
	  			  			  linenumhex+=8;
	  		}
		  }

	  }
}
