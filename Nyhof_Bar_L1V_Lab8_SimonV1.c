#define _CRT_SECURE_NO_WARNINGS
 
 /* headers */
#include <stdio.h>
#include <DAQlib.h>
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*symbolic constants*/
#define TRUE     1
#define FALSE    0
#define ON       1
#define OFF      0
#define GREEN	 0
#define RED		 1
#define YELLOW	 2
#define BLUE	 3

#define DAQ_SIMULATOR 6


/* function prototypes*/
void runSimon(void);
void flashLEDs(int sequence[], int round);
void flashGreen(void);
void flashRed(void);
void flashRainbow(void);
int readButtons(void);



int main(void)
{
		if (setupDAQ(DAQ_SIMULATOR) == TRUE) {
			runSimon();
		}
		else {
			printf("ERROR: failed to initialize DAQ\n");
		}

		return 0;
}


void runSimon(void)
{
	/*Lenght of the game*/
	int length = 10;
	int sequence[10]; //make sure the two numbers match

	/*starting values for the game*/
	srand(time(0));
	int round = 1;
	int button = 0;
	int clicks = 0;
	int fail = FALSE;

	/*generating the sequence of LED flashes*/
	for (int i = 0; i < length; i++)
	{
		sequence[i] = rand() % 4;
		/*the following block of code simply ensures that there are no two of the same digits in a row, which wasn't in the program outline but in my opinion makes the game better.
		The game would still functin the same without this block of code, there would just be a possibiliity that a light will repeat itself*/
		if (i > 0)
		{
			if (sequence[i] == sequence[i - 1])
			{
				while (sequence[i] == sequence[i - 1])
				{
					sequence[i] = rand() % 4;
				}
			}
		}
	}

	Sleep(300);
	/*Indicates a new round is starting*/
	flashRainbow();

	while (continueSuperLoop() == TRUE)
	{
		while (round <= length && fail == FALSE)
		{
			Sleep(500);
			flashLEDs(sequence, round);
			while (button < round && fail == FALSE)
			{
				while (clicks <= button && fail == FALSE) //The number of clicks has to equal the number in the sequence for that LED
				{
					if (readButtons() == sequence[button])
						clicks++;
					else						
						fail = TRUE;
				}
				clicks = 0;
				button++;			
			}
			if (fail == FALSE)
				flashGreen();
			button = 0;
			round++;
		}

		/*Notifies the user if they made an incorrect button press*/
		if (fail == TRUE)
			flashRed();
			
		/*Indicates a new round is starting*/
		flashRainbow();

		/*starting values (resetting the game)*/
		srand(time(0));
		round = 1;
		button = 0;
		clicks = 0;
		fail = FALSE;

		/*Generating a new sequence of LED flashes*/
		for (int i = 0; i < length; i++)
		{
			sequence[i] = rand() % 4;
			/*the following block of code simply ensures that there are no two of the same digits in a row, which wasn't in the program outline but in my opinion makes the game better.
			The game would still functin the same without this block of code, there would just be a possibiliity that a light will repeat itself*/
			if (i > 0)
			{
				if (sequence[i] == sequence[i - 1])
				{
					while (sequence[i] == sequence[i - 1])
					{
						sequence[i] = rand() % 4;
					}
				}
			}
		}
	}
}



/*waits for the user to press a button and returns the button that they press*/
int readButtons(void)
{
	int read = -1;
	while (read < 0)
	{
		if (digitalRead(0) == TRUE)
		{
			while (digitalRead(0) == TRUE) //waits until the user has released the button to continue. This prevents one click registering as multiple
			{

			}
			read = 0;
		}

		if (digitalRead(1) == TRUE)
		{
			while (digitalRead(1) == TRUE)
			{

			}
			read = 1;
		}

		if (digitalRead(2) == TRUE)
		{
			while (digitalRead(2) == TRUE)
			{

			}
			read = 2;
		}

		if (digitalRead(3) == TRUE)
		{
			while (digitalRead(3) == TRUE)
			{

			}
			read = 3;
		}

	}

	return read;
}


/*Flashes the green LED 3 times in quick succession*/
void flashGreen(void)
{
	digitalWrite(0, ON);
	Sleep(200);
	digitalWrite(0, OFF);
	Sleep(200);
	digitalWrite(0, ON);
	Sleep(200);
	digitalWrite(0, OFF);
	Sleep(200);
	digitalWrite(0, ON);
	Sleep(200);
	digitalWrite(0, OFF);
	Sleep(200);
}

/*Flashes the red LED 3 times in quick succession*/
void flashRed(void)
{
	digitalWrite(1, ON);
	Sleep(200);
	digitalWrite(1, OFF);
	Sleep(200);
	digitalWrite(1, ON);
	Sleep(200);
	digitalWrite(1, OFF);
	Sleep(200);
	digitalWrite(1, ON);
	Sleep(200);
	digitalWrite(1, OFF);
	Sleep(200);
}

/*flashes all the LED's in a sequence to indicate a new round will be starting*/
void flashRainbow(void)
{
	digitalWrite(GREEN, ON);
	Sleep(100);
	digitalWrite(RED, ON);
	Sleep(100);
	digitalWrite(YELLOW, ON);
	Sleep(100);
	digitalWrite(BLUE, ON);
	Sleep(100);
	digitalWrite(GREEN, OFF);
	Sleep(100);
	digitalWrite(RED, OFF);
	Sleep(100);
	digitalWrite(YELLOW, OFF);
	Sleep(100);
	digitalWrite(BLUE, OFF);
	Sleep(100);
}

/*Flashes the number LED's specified by the round that the user has reached*/
void flashLEDs(int sequence[], int round)
{
	Sleep(1000);
	for (int i = 0; i < round; i++)
	{
		digitalWrite(sequence[i], ON);
		Sleep(500);
		digitalWrite(sequence[i], OFF);
		Sleep(500);
	}

}