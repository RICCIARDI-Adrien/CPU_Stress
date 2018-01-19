/** @file Main.c
 * Stress the specified amount of processors to 100% of their computing power.
 * @author Adrien RICCIARDI
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(void)
{
	int Processes_Count, i;
	volatile int Dummy_Value = 0;
	
	// Display banner
	puts("+--------------------------------------+");
	puts("| CPU stress (C) 2018 Adrien RICCIARDI |");
	puts("+--------------------------------------+");
	
	// Get the amount of processes to create
	printf("Amount of CPUs to stress : ");
	if ((scanf("%d", &Processes_Count) != 1) || (Processes_Count < 1)) // Try to make sure it is a valid number
	{
		printf("Please enter an integer number starting from 1.\n");
		return EXIT_FAILURE;
	}
	
	// Fork as many processes as requested
	for (i = 0; i < Processes_Count; i++)
	{
		switch (fork())
		{
			// An error occurred
			case -1:
				printf("Failed to create process %d (%s).\n", i, strerror(errno));
				return EXIT_FAILURE;
			
			// Child starts executing here
			case 0:
				while (1)
				{
					Dummy_Value += 6;
					Dummy_Value *= 3;
					Dummy_Value -= 7;
					Dummy_Value /= 9;
				}
		
			// Parent continues execution here
			default:
				break;
		}
	}
	
	// Block parent process without using processor resource
	printf("Stressing %d processor(s)... Use Ctrl+C to stop the program.\n", Processes_Count);
	wait(NULL);
	
	return EXIT_SUCCESS; // Quit if one of the children has been killed
}
