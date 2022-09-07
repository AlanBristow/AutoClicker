#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif
#include <iostream>
#include <thread>
using namespace std;

bool on_off = false;
bool kill = false;
double delay;

void keyCheck()
{
    while(!kill)
    {
        if(GetKeyState('Z') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            on_off = true;
        }
        if(GetKeyState('X') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            on_off = false;
            
        }  
        if(GetKeyState('C') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            kill = true;
        }
    }
}

void clicker()
{
    while(!kill)
    {
        while(on_off)
        {
            if(on_off)
            {
                cout<<"Hello World!"<<endl;
                sleep(delay/1000);
            }
        }
    }   
}

int main()
{
    cout<<"Input the delay in milliseconds"<<endl;
    cin>>delay;
    cout<<"Click z to play, click x to pause and click c to end the program"<<endl;
    thread t1;
    thread t2;
    t1 = thread(keyCheck);
    t2 = thread(clicker);
    t1.join();
    t2.join();

    return 0;
}