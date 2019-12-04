/**
  Main Source File

    File Name:          main.c
    Author:             Janelle Diesburg
	Commenter: 			Fowad Sohail
    Creation Date:      3 November 2019
  
  Summary:
    This is the main file for the Embedded PCB Class Project

  Project Description:
    A demonstration of a PIC microcontroller utilizing the following features:
        - external 4 MHz Xtal oscillator
        - 2 directly driven low power LEDs
        - 2 transistor driven high power LEDs
        - 1 button input
        - EUSART serial debug port, interfaces to FTDI module  
		

  Task:
	Understand and comment the given code after it properly functions on your PCB
*/

#include "mcc_generated_files/mcc.h"

//down and dirty blocking timer
void my_wait (unsigned char my_time);

/**
	@Description
		Delay function
	@Param
		my_time An unsinged char that determines the wait time here
	@Returns
		none
*/
void my_wait (unsigned char my_time)
{
    int j, k, l;
    for (j=0; j<my_time; j++) // outer loop iterating with my_time
    {
        for (k=0; k<255; k++) // inner loop iterating 0-254
        {
            l++;
        }
    }
}


/**
	Main driver function
*/
void main(void)
{
    int cnt = 0; // count variable
    unsigned char input;
    
    SYSTEM_Initialize(); // system init defined in header file
    
	// terminal print statements
    printf("\fEmbedded PCB Class Project");
    printf("\r\n\tRevision Date: " __DATE__); // log the current date
    printf("\r\n\tRevision Time: " __TIME__); // log the current date
    printf("\r\n(C)2019 Janelle Diesburg, Rowan University\r\n\n");

    while (1) // infinite while loop
    {
        if (IO_RA2_PORT==1) // when the button is NOT pressed
        {
            printf ("Embedded Class Project %d \n\r", cnt); // print string and counter variable
			// cycle through I0_RCx_LAT port with one hot encoding
			
			// 1000
            IO_RC0_LAT = 1;
            IO_RC1_LAT = 0;
            IO_RC2_LAT = 0;
            IO_RC3_LAT = 0;
            my_wait(30); // delay
			
			// 0100
            IO_RC0_LAT = 0;
            IO_RC1_LAT = 1;
            IO_RC2_LAT = 0;
            IO_RC3_LAT = 0;
            my_wait(30); // delay
			
			// 0010
            IO_RC0_LAT = 0;
            IO_RC1_LAT = 0;
            IO_RC2_LAT = 1;
            IO_RC3_LAT = 0;
            my_wait(30); // delay
			
			// 0001
            IO_RC0_LAT = 0;
            IO_RC1_LAT = 0;
            IO_RC2_LAT = 0;
            IO_RC3_LAT = 1;
            my_wait(30); // delay
			
            cnt++; // increment the counter for the next iteration of the loop
        }
        else // button press
        {
            printf("\r\nThe BUTTON has been pressed\r\n");
            while (IO_RA2_PORT==0) // loop while the button is held down
            {
				// 0011
                IO_RC0_LAT = 0;
                IO_RC1_LAT = 0;
                IO_RC2_LAT = 1;
                IO_RC3_LAT = 1;
                my_wait(45); // delay
				
				// 1100
                IO_RC0_LAT = 1;
                IO_RC1_LAT = 1;
                IO_RC2_LAT = 0;
                IO_RC3_LAT = 0;
                my_wait(45); // delay 
				
            }
            printf("The BUTTON has been released\r\n\n"); // the button has been released
        }   
        if(EUSART1_DataReady)
        {
            input = EUSART1_Read();
            printf("\r\n\nWe received an input, the %c%c%c key was pressed.\r\n\n", 0x22, input, 0x22);
        }
    }
}
