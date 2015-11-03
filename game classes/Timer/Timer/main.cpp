// Timer class
#include<iostream>
#include<Windows.h>
using namespace std;

//start the variables
struct timer{

	int sec;

};

int main()
{
	//initialize the timer class by giving it another name
	timer a;
	a.sec = 0;
			for (int k = 0; k<11; k++)
			{
				cout << "Timer: " << a.sec << endl;
				a.sec++;
				Sleep(1000);
				system("Cls"); 
				if (a.sec == 10){
					cout << "Stop" << endl;
				}
			}
}