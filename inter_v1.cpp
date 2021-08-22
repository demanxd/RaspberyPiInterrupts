#include <iostream>
#include <thread>

extern "C"{
#include <wiringPi.h>
}

#define PIN_GPIO_WATCHED 5


using namespace std;


void switchInterrupt(void);
void counter_th(void);


unsigned int counter = 0;
unsigned int trig_amount = 0;
bool is_rise = false;
bool checker_lvl = false;	//true - rising; false - falling
bool checker_lvl_last = true;  //true - rising; false - falling

int main()
{
	wiringPiSetup();			// Setup the library
	pinMode(PIN_GPIO_WATCHED, INPUT);		// Configure GPIO1 as an input //18 pin
	
	thread t(counter_th);


	wiringPiISR (PIN_GPIO_WATCHED, INT_EDGE_FALLING, switchInterrupt);

	t.join();

	return 0;
}


void show_is_rise_stat()
{
	cout << "is_rise = " << is_rise << endl;
}


void switchInterrupt(void)
{
	if(digitalRead(PIN_GPIO_WATCHED) == HIGH)
	{
		checker_lvl = true;
	}
	else
	{
		checker_lvl = false;
	}


	if(checker_lvl != checker_lvl_last)
	{
		trig_amount++;
		cout << "Triggered! counter = " << counter << "; trigger amount = " << trig_amount  << endl;
		is_rise = false;
		show_is_rise_stat();
		checker_lvl_last = checker_lvl;
	}

}


void counter_th(void)
{
	while(1)
		counter++;
}
