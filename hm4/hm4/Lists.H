#ifndef _LISTS_H_
#define _LISTS_H_

#include "defs.H"

class Follower;
class Leader;

struct listelem {
	int data;       // $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	listelem* next;
};

class list {
private:
	listelem* h; //head of the list
	listelem* iterator; //Iterator
	int size = 0; // not sure if the right place
public:
	list() {						 //not sure what it is - probably creator
		h = NULL;
	}
	~list() {
		release();          //destory the list also not sure
	}
	
	void go_to_first(); 
	void prepend(int f); // insert the 1st element to the list  $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	void delete_current();
	void delete_head();
	void next();
	int get_current();          //   $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	int get_size();
	void release();  // not sure if we need it
	void print() const; // only for debug 
};


#endif
