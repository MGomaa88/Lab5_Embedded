/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: counter.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD  MOhamed Gomaa
* --------------------
* 090215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "events.h"
#include "swtimers.h"
/*****************************    Defines    *******************************/
// Counter States
// --------------
#define CS_MAN_UP    0
#define CS_MAN_DOWN  1
#define CS_AUTO_UP   2
#define CS_AUTO_DOWN 3

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/


INT8U counter( INT8U event )
/*****************************************************************************
*   Input    : event from button press
*   Output   : counter value to set LED color
*   Function : controls counter and switches between manual and auto mode
******************************************************************************/
{
  static INT8U  counter_state =  CS_MAN_UP;
  static INT8U  counter_value = 0;
  static INT16U counter_timer = 0;

  if( counter_timer )					// if timer is running
    if( ! --counter_timer )				// decrement timer and check if now zero
      event = TE_TIMEOUT;				// then set event to timeout
  
  if( event )
  {
      cout_counter_value_UART(counter_value);
    switch( counter_state )
    {
	    case CS_MAN_UP:				// if in manual mode and counting up

	        count_UART(1);
	      switch( event )
	      {
	        case BE_SINGLE_PUSH:			// if event is single push
	          counter_value++;			// increment counter value
	          break;
	        case BE_DOUBBLE_PUSH:			// if event is double push
		        counter_state = CS_MAN_DOWN;	// change mode to counting down
	          break;
	        case BE_LONG_PUSH:			// if event is long push
	            counter_state = CS_AUTO_UP;		// change mode to auto
		        counter_timer = TIM_200_MSEC;	// and start the timer
	          break;
	        default:
	          break;
	      }
	      break;
	    case CS_MAN_DOWN:				// if in manual mode and counting down; same as previous but decrement value
	        count_UART(2);
	      switch( event )
	      {
	        case BE_SINGLE_PUSH:
	          counter_value--;
	          break;
	        case BE_DOUBBLE_PUSH:
		        counter_state = CS_MAN_UP;
	          break;
	        case BE_LONG_PUSH:
		        counter_timer = TIM_200_MSEC;
		        counter_state = CS_AUTO_DOWN;
	          break;
	        default:
	          break;
	      }
	      break;
	    case CS_AUTO_UP:				// if in auto mode and counting up
	        count_UART(3);
	      switch( event )
	      {
	        case TE_TIMEOUT:			// if timer has run out
	          counter_value++;			// increment the counter value
	          counter_timer = TIM_200_MSEC;		// and reset the timer
	          break;
	        default:				// if event is any button press
	          counter_state = CS_MAN_UP;		// change mode back to manual
	          break;
	      }
	      break;
	    case CS_AUTO_DOWN:				// if in auto mode and counting down; same as previous but decrement value
	        count_UART(4);
	      switch( event )
	      {
	        case TE_TIMEOUT:
	          counter_value--;
	          counter_timer = TIM_200_MSEC;
	          break;
	        default:
	          counter_state = CS_MAN_UP;
	          break;
	      }
	      break;
	    default:
	      break;
    }
  }
  return( counter_value );
}

INT8U count_UART( INT8U event_state )
{
    INT8U man_up []= {'\n','M', 'a', 'n',' ','U','p'};
    INT8U man_dn []= {'\n','M', 'a', 'n',' ','D','n'};
    INT8U auto_up []= {'\n','A', 'u','t','o',' ','U','P'};
    INT8U auto_dn []= {'\n','A', 'u','t','o',' ','D','N'};

    int i=0;

    switch(event_state)
    {
    case 1:
        i = 0;

        while(i < 7)
        {

        if(uart0_tx_rdy())
        {
        uart0_putc( man_up[i]);
            i++;
        }
        }
        break;

    case 2:
        i = 0;
        while(i < 7)
        {
        if(uart0_tx_rdy())
        {
        uart0_putc( man_dn[i]);
            i++;
        }
        }
        break;

    case 3:
        i = 0;
        while(i < 8)
        {
            if(uart0_tx_rdy()){

            uart0_putc( auto_up[i]);
                i++;
            }
        }
        break;

    default:
        i = 0;

        while(i < 8){

        if(uart0_tx_rdy()){

        uart0_putc( auto_dn[i]);
            i++;
        }
        }

        break;

    }


}

void cout_counter_value_UART(INT8U  counter_value)
{
    int increment = 0;
    int for_loop_i = 0;

    int cv_mod0 = counter_value % 10;
    int cv_mod10 = counter_value/10 % 10;
    int cv_mod100 = counter_value/100 % 10;

    char input0;
    char input1;
    char input2;

    while(increment != 3){
        if(uart0_tx_rdy()){
            switch(increment){
                case 0:
                    input0 = change_int_to_char(cv_mod100);
                    uart0_putc(input0); //highest number
                    increment++;
                    break;
                case 1:
                    input1 = change_int_to_char(cv_mod10);
                    uart0_putc(input1);
                    increment++;
                    break;
                case 2:
                    input2 = change_int_to_char(cv_mod0);
                    uart0_putc(input2); //lowest number
                    increment++;
                    break;
                default:
                    break;
            }
        }

    }
}

char change_int_to_char(INT8U number){
    switch(number){
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
    }
}
/****************************** End Of Module *******************************/












