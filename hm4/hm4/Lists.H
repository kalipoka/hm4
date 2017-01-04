#ifndef _LISTS_H_
#define _LISTS_H_

#include "defs.H"
#include "Message.H"

// those are the classes than need to be stored in the lists
class Follower;
class Leader;
//class Message;

struct Node {
	Message* data;					 // $$$$$$$$$$$$$$$ int only for testing - change to Follower/Leader/ Message later
	Node *next;
};

class list {
private:
	Node* head; //head of the list
	Node* iterator; //Iterator
	int size = 0; 
public:
	list() { head = NULL; }
						 //not sure what it is - probably creator
		
	~list() {
		Node *tmp;
		while (head) {
			tmp = head->next;
			delete head;
			head = tmp;		}
	}
	void go_to_first(); 
	void prepend(Message m); // insert element to the top of the list  $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	void delete_current(); // delete the element that the iterator points to
	void delete_head();     // delete the head
	void next();             // advance one step to the end with the iterator
	Message get_current();          //   $$$$$$$$$$$$$$$ int only for testing - change to Follower later
	int get_size();
	void release();			 // delete the list
	void print() const;		// print the list 
};

#endif
