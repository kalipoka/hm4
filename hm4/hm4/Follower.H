#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include "defs.H"
#include "Lists.H"
#include "Message.H"

using std::string;

class Follower {
public:
	Follower(string name, string email, string password);
	~Follower();
	

    string GetName(); //Checked
	string GetEmail(); //Checked
	bool isPassword(string password); //Checked

	//Friends Operations
	void DisplayFriendRequests();
	void DisplayFriendList();
	void AddFriendRequest(Follower& Friend);
	void AcceptedFriendRequest(Follower& Friend);
	void RemoveFriend(Follower& Friend);
	int NumFriendRequests() const;
	
	//Messages operations
	void ShowMessageList() const;
	void AddMessage(Message& newMessage);
	Result ReadMessage(int MessageNum) const; //<messageNumber>   //Alex Changed to result type
	void SendMessage(Message& TheMessage, Follower& Friend);
	int NumUnreadMessages() const;
	bool isFriend(string mail);
	bool isRequestExists(string mail);
	// To do
protected:

	string _name;
	string _email;
	string _password;
	MessageBox* _MessageBox;
	list_f *_Friends, *_FRequests;

	
};


#endif
