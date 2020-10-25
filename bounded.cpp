//===========================================================================//
//   Project: Projekat iz Operativnih sistema 1
//   File:    bounded.cpp
//   Date:    Jun 2019
//===========================================================================//
#include "bounded.h"

#include <stdlib.h>
#include <iostream.h>

#include "intLock.h"

BoundedBuffer::BoundedBuffer (unsigned size) : Size(size),
	mutexa(1), mutext(1), spaceAvailable(size), itemAvailable(0),
	head(0), tail(0) {
		buffer = new char[size];
		if (!buffer) exit(1);
	}

BoundedBuffer::~BoundedBuffer(){
	intLock
	delete [] buffer;
	intUnlock
}

int BoundedBuffer::append (char d) {
	spaceAvailable.wait(0);
	/*intLock
	cout<<"spaceAvailable.val = "<<spaceAvailable.val()<<endl;
	intUnlock*/
	mutexa.wait(0);
	/*intLock
	cout<<"mutexa.val = "<<mutexa.val()<<endl;
	intUnlock*/
		buffer[tail] = d;
		tail = (tail+1)%Size;
		/*intLock
		cout<<"dodat "<<d<<" u bafer"<<endl;
		intUnlock*/
	mutexa.signal();
		/*intLock
		cout<<"mutexa.val = "<<mutexa.val()<<endl;
		intUnlock*/
		/*intLock
			cout<<"itemAvailable.val = "<<itemAvailable.val()<<endl;
			intUnlock*/
	itemAvailable.signal();

	return 0;
}

char BoundedBuffer::take () {
	/*intLock
			cout<<"itemAvailable.val = "<<itemAvailable.val()<<endl;
			intUnlock*/
	itemAvailable.wait(0);

	mutext.wait(0);
		/*intLock
		cout<<"mutext.val = "<<mutext.val()<<endl;
		intUnlock*/
		char d = buffer[head];
		head = (head+1)%Size;
		/*intLock
		cout<<"Nit "<<Thread::getRunningId()<<"uzela "<<d<<" iz bafera"<<endl;
		intUnlock*/
	mutext.signal();
		/*intLock
		cout<<"mutext.val = "<<mutext.val()<<endl;
		intUnlock*/
	spaceAvailable.signal();
		/*intLock
			cout<<"spaceAvailable.val = "<<spaceAvailable.val()<<endl;
			intUnlock*/
	return d;
}
