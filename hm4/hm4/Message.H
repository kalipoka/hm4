#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "defs.H"
#include <string>
#include "Lists.H"


using namespace std;

class Message {
public:
    Message(string source, string subject, string content);
    void Display(int num) const;
    void Read();
	bool isRead();
private:
    string source_;
	string subject_;
    string content_;
    bool   read_;
	int msgnum;
};

class MessageBox:public list_m {    // inherit from list_m
public:
     //void Add(Message newMessage); // can be done with .prepent(msg)
	//int Size();                 // can inherit from list with .get_size()
	int UnreadSize();    
	void Print();         
	Result ReadMessage(int messageNum);
	MessageBox(Node_m* h, Node_m* iterator, int size, int num_of_unread);
	//int num_of_unread;
private:
	// To do
	//int num_of_unread;
};
#endif
