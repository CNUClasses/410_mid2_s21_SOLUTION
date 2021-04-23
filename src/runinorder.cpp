//TODO please ensure that t1 runs to completion, while threads t2 and t3 efficiently wait
//     then t2 runs to completion while thread t3 efficiently waits
//     then t3 runs to completion
//     Please do not use any programmatic delays (sleep, sleep_for, yield etc.)
//     Please assume this code runs in an exception prone environment

#include <thread>
#include <iostream>
#include <condition_variable>				//-5 forget these includes
#include <mutex>
using namespace std;

mutex m;									//-10 rio: no global mutex
condition_variable cv;						//-10 rio: no condition var

bool t1_done=false;							//-8 rio:nothing to loop on
bool t2_done=false;
bool t3_done=false;

void fun1(int id){
	{
		unique_lock<mutex> lck(m);			
											
		cout<<"Thread 1 running"<<endl;	
		t1_done = true;						
	}										
	
	cv.notify_all();						
											
}
void fun2(int id){
	{
		unique_lock<mutex> lck(m);			//-10 fun2:no locking
											//-5 fun2:no unique_lock
		while(!t1_done)						//-5 fun2:no while at all
											//-4 fun2:if instead of while
			cv.wait(lck);
		cout<<"Thread 2 running"<<endl;	
		t2_done = true;						//-3 fun2:forget to set
	}										//-2 fun2:forget to unlock
	cv.notify_all();						//-5 fun2:no notify
											//-3 fun2:notify_one instead of all
}
void fun3(int id){
	{
		unique_lock<mutex> lck(m);
		while(!t2_done)
			cv.wait(lck);
		cout<<"Thread 3 running"<<endl;	
		t3_done = true;
	}
	cv.notify_all();

}

void run_in_order(){
	thread t3(fun3,3);
	thread t2(fun2,2);
	thread t1(fun1,1);

	t1.join();
	t2.join();
	t3.join();
	cout<<"All threads done!\n\n"<<endl;   	//-5 fun2:lock final cout
}

