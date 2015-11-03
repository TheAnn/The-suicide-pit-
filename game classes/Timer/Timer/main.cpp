//Creating Digital Watch in C++
#include<iostream>
#include<Windows.h>
using namespace std;

struct time{

	int sec;
};
int main()
{
	time a;
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