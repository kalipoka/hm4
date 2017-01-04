#ifndef _LISTS_H_
#define _LISTS_H_

#include "defs.H"
#include "Message.H"

class Follower;
class Leader;
////////////////////////////////////////////////////////////////////////////////////////////
// define the node for Message List
struct Node {
	Message* data;       
	Node* next;
};
// define the  Message list
class list {
private:
	Node* head; //head of the list
	Node* iterator; //Iterator
	int size = 0; // not sure if the right place
public:
	list() {						 //not sure what it is - probably creator
		head = NULL;
	}
	~list() {
		release();          //destory the list also not sure
	}
	
	void go_to_first(); 
	void prepend(Message& m); // insert the 1st element to the list  $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	void delete_current();
	void delete_head();
	void next();
	Message* get_current();          //   $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	int get_size();
	void release();  // not sure if we need it
	void print() const; // only for debug 
};


////////////////////////////////////////////////////////////////////////////////////////////
// define the node for Follower List
/*
struct Node_f {
	Follower* data;      
	Node_f* next;
};

class list_f {
private:
	Node_f* head; //head of the list
	Node_f* iterator; //Iterator
	int size = 0; // not sure if the right place
public:
	list_f() {						 //not sure what it is - probably creator
		head = NULL;
	}
	~list_f() {
		release();          //destory the list also not sure
	}

	void go_to_first();
	void prepend(Follower& m); // insert the 1st element to the list  $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	void delete_current();
	void delete_head();
	void next();
	Follower* get_current();          //   $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	int get_size();
	void release();  // not sure if we need it
	void print() const; // only for debug 
};
*/
#endif
