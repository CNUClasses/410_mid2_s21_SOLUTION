//TODO nothing in this file
#ifndef CASHCARD_H_
#define CASHCARD_H_
#include <mutex>

class CashCard {
public:
	/*** 
	 * @param initialbalance  initial amount placed on cashcard
	 */
	CashCard(int initial_balance);
	
	/***
	 * Deducts price from balance, iff balance>=price
	 * 
	 * @param price the cost
	 * @return true transaction approved balance =balance-price
	 * 	       false transaction denied, balance is not debited
	 */
	bool buy(int price);
	
	/***
	 * how much is left on the card?
	 * 
	 * @return the current balance
	 */
	int get_balance();
	
	
	virtual ~CashCard();
private:
	int balance;
	std::mutex m;
};

#endif /* CASHCARD_H_ */
