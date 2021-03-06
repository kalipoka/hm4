#ifndef _LISTS_H_
#define _LISTS_H_

#include "defs.H"
//#include "Message.H"

class Follower;
class Leader;
class Message;

struct Node_m {
	Message* data;
	Node_m* next;
};

struct Node_f {
	Follower* data;
	Node_f* next;
};

struct Node_l {
	Leader* data;
	Node_l* next;
};

/*###############CLASSES######################*/
class list_m {
private:
	Node_m* h; //head of the list
	Node_m* iterator; //Iterator
	int size; // not sure if the right place
public:
	list_m();
	~list_m();
	
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

//namespace followers_list {
class list_f {
	private:
		Node_f* h; //head of the list
		Node_f* iterator; //Iterator
		int size; // not sure if the right place
	public:
		list_f();
		~list_f();

		void go_to_first();
		void prepend(Follower& f); // insert the 1st element to the list  $$$$$$$$$$$$$$$ int only for testing - change to Follower later
		void delete_current();
		void delete_head();
		void next();
		Follower* get_current();          //   $$$$$$$$$$$$$$$ int only for testing - change to Follower later
		int get_size();
		void release();  // not sure if we need it
		void print() const; // only for debug 
	};
//}

class list_l {
private:
	Node_l* h; //head of the list
	Node_l* iterator; //Iterator
	int size;
public:
	list_l();
	~list_l();

	void go_to_first();
	void prepend(Leader& l); // insert the 1st element to the list  $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	void delete_current();
	void delete_head();
	void next();
	Leader* get_current();          //   $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	int get_size();
	void release();  // not sure if we need it
	void print() const; // only for debug 
};

#endif
