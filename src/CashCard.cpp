//TODO make this class threadsafe
#include "CashCard.h"
using namespace std;
												//-5 use raw mutexes
/*** 
 * @param initialbalance  initial amount placed on cashcard
 */
CashCard::CashCard(int initial_balance) {		//-3 locked CashGuard constructor  
	balance=initial_balance;					
}

/***
 * Deducts price from balance, iff balance>=price
 * 
 * @param price the cost
 * @return true transaction approved balance =balance-price
 * 	       false transaction denied, balance is not debited
 */
bool CashCard::buy(int price){
	lock_guard<mutex> lck(m);					//-6 lock in wrong place CashCard::buy
	if (price<=balance){
		balance -=price;
		return true;
	}
	return false;		
}

/***
 * how much is left on the card?
 * 
 * @return the current balance
 */
int CashCard::get_balance(){					//-4 forget to lock
	lock_guard<mutex> lck(m);
	return balance;
}

CashCard::~CashCard() {

}

