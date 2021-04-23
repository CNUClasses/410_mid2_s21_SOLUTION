//TODO find the SMALLEST critical sections and protect them
//TODO be sure to MAXIMIZE concurrency (the number of threads that can run simultaneously)
//     Please assume this code runs in an exception prone environment

#include <thread>
#include <iostream>
#include "CashCard.h"
using namespace std;

const int INITIAL_CASH=1000;
const int PRICE=5;

CashCard c(INITIAL_CASH);
mutex m1;								//-15 fscc global:have no global mutex

void buy_widgets(int id){
										//-13 buy_widgets:no locking
										//-10 buy_widgets:lock entire function
	int numb_widgets_purchased=0;		//-5 buy_widgets:add useless lock around local var
										//-8 buy_widgets:lock entire while loop
	while (c.buy(PRICE)){
		lock_guard<mutex> lck(m1);		//-5 buy_widgets:forget to lock here
		cout<<"Thread "<<id<<", Purchased one!  Total owned="<<numb_widgets_purchased<<endl;
		numb_widgets_purchased++;
	}
	lock_guard<mutex> lck(m1);			//-5 buy_widgets:forget to lock here
	cout<<"Thread "<<id<<",Purchased failed! Remaining balance="<<c.get_balance()<<" Exiting"<<endl;
}

void find_smallest_critical_section(){
	CashCard cc(INITIAL_CASH);
	
	thread t1(buy_widgets,1);
	thread t2(buy_widgets,2);
	thread t3(buy_widgets,3);

	t1.join();
	t2.join();
	t3.join();							//-5 fscc:lock final cout
	cout<<"All threads done! Remaining balance="<<c.get_balance()<<"\n\n"<<endl;

}
