#include "char_count.h"

uint16_t fib0=0, fib1=1,fibsum;
uint8_t c_count[256];
int i = 0;

void char_count(uint8_t  c_value)
{
	myputstr("Current Fibonacci Series Value:");
	myputint(fib1);
	myputstr("\n\r");
	c_count[c_value]++;
	for(i=0; i<127; i++)
	{
		if(c_count[i]!=0)
		{
			myputchar((char)i);
			myputchar(32);
			myputchar(45);
			myputchar(32);
			myputint(c_count[i]);
			myputstr("\n\r");

		}
	}
}

void fib()
{
	fibsum = fib0 + fib1;
	fib0 = fib1;
	fib1 = fibsum;
	if(fib1 > 65535 )
	{
		fib0=0;
		fib1=1;
	}
}
