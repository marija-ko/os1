/*
 * test1.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: OS1
 */

/*#include "Thread.h"
#include "System.h"
#include "Semaphor.h"
#include "PCB.h"
#include <iostream.h>
#include "define.h"


/*
 	 Test: Semafori sa spavanjem 3


int t=-1;

Semaphore s(0);

class TestThread : public Thread
{
private:
	Time waitTime;

public:

	TestThread(Time WT): Thread(), waitTime(WT){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	lock;
	cout<<"Thread "<<getId()<<" waits for "<<waitTime<<" units of time."<<endl;
	unlock;
	int r = s.wait(waitTime);
	//s.signal();
	lock;
	cout<<"Thread "<<getId()<<" finished. r= "<<r<<endl;
	unlock;}

void tick()
{

	/*t++;
	if(t)
		lock;
		cout<<t<<endl;
		unlock;


}

Semaphore* mutex = 0;

class Znak : public Thread
{
public:
	Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
	virtual ~Znak() { waitToComplete(); }

	void run()
	{
		for (long i = 0; i < 4000; i++)
		{

			mutex->wait(0);
			cout << znak;
			mutex->signal();

			}

			mutex->wait(0);
			cout << endl << znak << " finished" << endl;
			mutex->signal();
	}

private:
	char znak;
	int n;

};


int userMain(int argc, char* argv[]) {
	mutex = new Semaphore(1);

	Znak* a = new Znak('a', 10);
	Znak* b = new Znak('b', 15);
	Znak* c = new Znak('c', 20);

	a->start();
	b->start();
	c->start();

	delete a;
	delete b;
	delete c;

		mutex->wait(0);
		cout << endl << "userMain finished" << endl;
		mutex->signal();

	delete mutex;



	return 0;
}
*/






