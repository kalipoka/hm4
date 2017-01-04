#ifndef _LISTS_H_
#define _LISTS_H_

#include "defs.H"

class Follower;
class Leader;

struct listelem {
	int data;					 // $$$$$$$$$$$$$$$ int only for testing - change to Follower/Leader/ Message later
	listelem* next;
};

class list {
private:
	listelem* h; //head of the list
	listelem* iterator; //Iterator
	int size = 0; 
public:
	list() {						 //not sure what it is - probably creator
		h = NULL;
	}
	~list() {
		release();          //destory the liste
	}
	
	void go_to_first(); 
	void prepend(int f); // insert element to the top of the list  $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	void delete_current(); // delete the element that the iterator points to
	void delete_head();     // delete the head
	void next();             // advance one step to the end with the iterator
	int get_current();          //   $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	int get_size();
	void release();			 // delete the list
	void print() const;		// print the list 
};

#endif
