/*
    Vario function for ez430 chronos watch.
    Copyright (C) 2010 Marc Poulhiès <dkm@kataplop.net>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// *************************************************************************************************
//
//	Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
//	 
//	 
//	  Redistribution and use in source and binary forms, with or without 
//	  modification, are permitted provided that the following conditions 
//	  are met:
//	
//	    Redistributions of source code must retain the above copyright 
//	    notice, this list of conditions and the following disclaimer.
//	 
//	    Redistributions in binary form must reproduce the above copyright
//	    notice, this list of conditions and the following disclaimer in the 
//	    documentation and/or other materials provided with the   
//	    distribution.
//	 
//	    Neither the name of Texas Instruments Incorporated nor the names of
//	    its contributors may be used to endorse or promote products derived
//	    from this software without specific prior written permission.
//	
//	  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//	  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//	  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//	  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//	  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//	  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//	  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//	  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//	  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//	  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include "project.h"

#ifdef CONFIG_CONTROL

// driver
#include "altitude.h"
#include "display.h"
#include "vti_ps.h"
#include "ports.h"
#include "timer.h"

#include "stopwatch.h"

// logic
#include "user.h"
#include "control.h"

#include "menu.h"

struct controltimer scontroltimer;

#define CONTROL_STR " ABCDEFGHIJKLMNOPQRSTUVWXYZ"

static u8 *str = CONTROL_STR;

void control_tick()
{
  scontroltimer.pos = (scontroltimer.pos+1) % (sizeof(CONTROL_STR)-7);
  display_control(0, 0);
}

u8 is_control(void)
{
  return (scontroltimer.state == CONTROL_RUN &&  (ptrMenu_L2 == &menu_L2_Control));
}

void update_control_timer()
{
  /* TA0CCR2 = TA0CCR2 + STOPWATCH_1HZ_TICK; */
}

void start_control()
{

  scontroltimer.state = CONTROL_RUN;
  /* // Init CCR register with current time */
  /* TA0CCR2 = TA0R; */
		
  /* // Load CCR register with next capture time */
  /* update_control_timer(); */

  /* // Reset IRQ flag     */
  /* TA0CCTL2 &= ~CCIFG;  */
	          
  /* // Enable timer interrupt     */
  /* TA0CCTL2 |= CCIE;  */
	
  display_symbol(LCD_ICON_RECORD, SEG_ON);
}

void stop_control()
{
  /* // Clear timer interrupt enable    */
  /* TA0CCTL2 &= ~CCIE;  */

  scontroltimer.state = CONTROL_STOP;
	
  display_symbol(LCD_ICON_RECORD, SEG_OFF);

  // Call draw routine immediately
  display_control(LINE2, DISPLAY_LINE_UPDATE_FULL);
}

void sx_control(u8 line)
{
  if (button.flag.down)
    {
      if (scontroltimer.state == CONTROL_STOP){
        start_control();
      } else {
        stop_control();
      }
    }
}

void mx_control(u8 line)
{
}

void display_control(u8 line, u8 update)
{
  u8 cur[7];
  memcpy(cur, str + scontroltimer.pos, 6);
  cur[6] = 0;
  
  display_chars(LCD_SEG_L2_5_0, cur, SEG_ON);
}

void reset_control(void)
{
  scontroltimer.pos = 0;
  scontroltimer.state = CONTROL_STOP;
}

#endif /* CONFIG_CONTROL */
