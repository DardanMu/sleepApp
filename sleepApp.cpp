// This is a small program which counts backwards in 90min seep cycles
// to reccomend a sleep time or wake up time to the user depending on
// what time they input. Based off this article: http://www.bbc.co.uk/news/magazine-16964783
//
// This code was written entirly by myself, Dardan M.
// This isn't the best looking code, and could be re-written in
// a better way, but I wrote it to help myself understand pointers in C.
//TODO: create something silimar for a phone app.
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

#define rdcycle(x) x + 360
#define thcycle(x) x + 450
#define ghcycle(x) x + 540

#define mrdcycle(x) x - 360
#define mthcycle(x) x - 450
#define mghcycle(x) x - 540

#include <windows.h>

#include "resource.h"

void Pause();
int when_to_wake_up();
int when_to_sleep();

int main () {

	int option = 0;

	printf("Select one of the following options:\n\n");
	printf("1: If you know when you will go to bed.\n");
	printf("2: If you know when you want to wake up.\n\n");
		scanf("%d", &option);

			if (option == 1) { when_to_wake_up();}
			else if (option == 2) { when_to_sleep();}
			else if (option >=3 || option < 1 ) { printf("Invalid Input");}

Pause();
return 0;
}

// pause the console window.
void Pause(){
   std::cout << " ";
   std::cout.flush();
   std::cin.ignore(10000, '\n');
   return;
}
//function 1: outputs what time to wake up if you know your bed time.
int when_to_wake_up() {

	int hr = 0;
	int mins = 0;

	//Ask the initial question, and take two answers using scanf()
	printf("\nWhat time will you go to bed?\nInput the time in 24hr format (e.g. 23:30)\n\n");
		scanf("%d:%d", &hr, &mins);

	//assigning pointers
	int *ptr3 = &hr;
	int *ptr4 = &mins;

		//if input is above 24hr and 60mins, send an error
		if (*ptr3 > 24 || *ptr4 > 60){
			printf("Invalid input: Please type down the correct hour and minutes.\n");
		}

		else {
			//90mins = 1 sleepy cycle. must add 5-6 sleep cycles
			*ptr4 = rdcycle(*ptr4);

			//For each instance where minute is greater than 60: take away 60 and run following.
			for ( ; *ptr4 >= 60 ; *ptr4-=60 ){
				*ptr3 = *ptr3 + 1;
                if (*ptr3 > 24){  *ptr3 = 01;}
			}

	printf( "Wake up at one of the following times:\n %02d:%02d\n", *ptr3, *ptr4);
	//second cycle
    int *ptr5 = &hr;
    int *ptr6 = &mins;

    *ptr6 = mrdcycle(*ptr6);

    *ptr6 = thcycle(*ptr6);

        for ( ; *ptr6 >= 60 ; *ptr6-=60 ){
			*ptr5 = *ptr5 + 1;
                if (*ptr5 > 24){  *ptr5 = 01;}
        }

	printf(" %02d:%02d\n", *ptr5, *ptr6);
	//third cycle
    int *ptr7 = &hr;
    int *ptr8 = &mins;

    *ptr6 = mthcycle(*ptr8);

    *ptr6 = ghcycle(*ptr8);

        for ( ; *ptr8 >= 60 ; *ptr8-=60 ){
			*ptr5 = *ptr7 + 1;
                if (*ptr7 > 24){  *ptr7 = 01;}
        }

	printf(" %02d:%02d\n", *ptr7, *ptr8);
		}

	printf("\nPress any key to exit...");
Pause();
return 1;
}
//function 2: outputs time to go to sleep if you know what time you want to wake up at.
int when_to_sleep() {

	int hr = 0;
	int mins = 0;

	//Ask the initial question, and take two answers using scanf()
	printf("\nWhat time do you want to wake up?\nInput the time in 24hr format (e.g. 07:35)\n\n");
		scanf("%d:%d", &hr, &mins);

	//assigning pointers
	int *ptrhr1 = &hr;
	int *ptrmins1 = &mins;

		//if input is above 24hr and 60mins, send an error
		if (*ptrhr1 > 24 || *ptrmins1 > 60){
		printf("Invalid input: Please type down the correct hour and minutes.\n");
		}

		else {

			//90mins = 1 sleepy cycle. must add 5-6 sleep cycles
			*ptrmins1 = mghcycle(*ptrmins1);

			//For each instance where minute is greater than 60: take away 60 and run following.
			for ( ; *ptrmins1 <= -60 ; *ptrmins1+=60 ){
				*ptrhr1 = *ptrhr1 - 1;
                if (*ptrhr1 <= 0){  *ptrhr1 = 24;}
			}

				//turn negative number into positive, and minus 1 hour
				if (*ptrmins1 < 0) {
					*ptrmins1 = abs(*ptrmins1);
					*ptrhr1 = *ptrhr1 - 1;
						if (*ptrhr1 == 0){ *ptrhr1 = 24;}
				}

	printf( "Go to sleep at one of the following times:\n %02d:%02d\n", *ptrhr1, *ptrmins1);

	//second cycle
    int *ptrhr2 = &hr;
    int *ptrmins2 = &mins;

    *ptrmins2 = ghcycle(*ptrmins2);
		//adjusting the time after reseting from previous functions on hr and mins
		for ( ; *ptrmins2 >= 60 ; *ptrmins2-=60 ){
			*ptrhr2 = *ptrhr2 + 1;
                if (*ptrhr2 > 24){  *ptrhr2 = 01;}
        }

    *ptrmins2 = mthcycle(*ptrmins2);

        for ( ; *ptrmins2 <= -60 ; *ptrmins2 +=60 ){
			*ptrhr2 = *ptrhr2 - 1;
               if (*ptrhr2 <= 0){  *ptrhr2 = 24;}
        }
			//turn negative number into positive, and minus 1 hour
			if (*ptrmins2 < 0) {
				*ptrmins2 = abs(*ptrmins2);
				*ptrhr2 = *ptrhr2 - 1;
					if (*ptrhr2 == 0){ *ptrhr2 = 24;}
			}

	printf(" %02d:%02d\n", *ptrhr2, *ptrmins2);

//third cycle
    int *ptrhr3 = &hr;
    int *ptrmins3 = &mins;

    *ptrmins3 = thcycle(*ptrmins3);
	//adjusting the time after reseting from previous functions on hr and mins
    for ( ; *ptrmins3 >= 60 ; *ptrmins3-=60 ){
		*ptrhr3 = *ptrhr3 + 1;
			if (*ptrhr3 > 24){  *ptrhr3 = 01;}
        }

	*ptrmins3 = mrdcycle(*ptrmins3);

        for ( ; *ptrmins3 <= -60 ; *ptrmins3 +=60 ){
			*ptrhr3 = *ptrhr3 - 1;
                if (*ptrhr3 <= 0){  *ptrhr3 = 24;}
        }
			//turn negative number into positive, and minus 1 hour
			if (*ptrmins3 < 0) {
				*ptrmins3 = abs(*ptrmins3);
				*ptrhr3 = *ptrhr3 - 1;
					if (*ptrhr3 == 0){ *ptrhr3 = 24;}
			}

	printf(" %02d:%02d\n", *ptrhr3, *ptrmins3);
		}

	printf("\nPress any key to exit...");
Pause();
return 1;
}

