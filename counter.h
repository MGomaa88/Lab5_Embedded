/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: counter.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD  Mohamed Gomaa
* --------------------
* 090215  MoH   Module created.
*
*****************************************************************************/

#ifndef COUNTER_H_
#define COUNTER_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U counter( INT8U );
/*****************************************************************************
*   Input    : event from button press
*   Output   : counter value to set LED color
*   Function : controls counter and switches between manual and auto mode
******************************************************************************/

INT8U count_UART( INT8U event_state );
/*****************************************************************************
*   Input    : - Int state value
*   Output   : -
*   Function : Check the input value and throw
*   a switch case decide what should be transmit to the receiver (fx. Putty).
*   Inside the function we use 2 functions.
*   First: Boolen uart0_tx_rdy() to check if we can send a char.
*   second: uart0_putc( man_up[i]) to send a single char.
******************************************************************************/

void cout_counter_value_UART(INT8U  counter_value);
/*****************************************************************************
*   Input    : - int counter value for each state in counter()
*   Output   : -
*   Function : transmit a counter value, which increments and decrements
*   every time the led lights up depends on the state.
******************************************************************************/
char change_int_to_char(INT8U number);

/****************************** End Of Module *******************************/
#endif /*COUNTER_H_*/
