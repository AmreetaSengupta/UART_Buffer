/***********************************************************************************
* @main.c
* @This code implements UART drivers in blocking and rx non-blocking way.
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "core_cm0plus.h"
#include "ring.h"
#include "uart.h"
#include "char_count.h"
#include "ledtoggle.h"

ring_t *tx_ptr, *rx_ptr;
char ele, read, ans;
int tx_size, rx_size, tx_newsize, rx_newsize;
int tx_count, rx_count, err;
int led_flag=0, rc;

int main(void)
{

	uartinit();
	led_init();
	#ifdef nonblocking
	rx_ptr = init(500);
	if(rx_ptr == NULL)
	{
		err = 2;
	}

	myputstr("Enter the character!\n\r");
	while(1)
    {
		fib();
		led_toggle();
		rx_count = entries(rx_ptr);
		if(rx_count != 0)
		{
			err = remove_element(rx_ptr, &read);

		    if(err == 1)
		    {
		    	err = 4;
		    }
			//myputchar(read);
			myputstr("\n\r");
			myputstr("Report:\n\r");
			char_count(read);
		}
		led_flag = ~led_flag;

    }
	#else
	myputstr("Enter the size of the transmit buffer:\n\r");
	tx_size = get_num();
	tx_ptr=init(tx_size);
	if(tx_ptr == NULL)
	{
		myputstr("Transmit Buffer Initialization Failed\n\r");
	}
	myputstr("Enter the size of the receive buffer:\n\r");
	rx_size = get_num();
	rx_ptr=init(rx_size);
	if(rx_ptr == NULL)
	{
		myputstr("Receive Buffer Initialization Failed\n\r");
	}
	myputstr("Press ~ to resize the buffer. Otherwise enter the character!\n\r");

	while(1)
	{
		ans=mygetchar();
		myputchar(ans);
		myputstr("\n\r");
		if(ans == '~')
		{
			myputstr("Enter the new size of the transmit buffer:\n\r");
			tx_newsize = get_num();

			rc = resize(tx_ptr,tx_newsize);
			if(rc == 1)
			{
				myputstr("Transmit Buffer Resize Failed\n\r");
			}
			else
			{
				myputstr("Enter the new size of the receive buffer:\n\r");
				rx_newsize = get_num();
				rc = resize(rx_ptr,rx_newsize);
				if(rc == 1)
				{
					myputstr("Receive Buffer Resize Failed\n\r");
				}
				else
				{
					myputstr("Buffer Resized Successfully!\n\r");
				}
			}

		}

		myputstr("Report:\n\r");
		char_count(ans);
	}


	#endif
}




