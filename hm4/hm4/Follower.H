#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include "defs.H"
#include "Lists.H"

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
	void AddFriendRequest(string email);
	void AcceptedFriendRequest(string email);
	void RemoveFriend(string email);
	int CountFriendRequests() const;
	
	//Messages operations
	void ShowMessageList() const;
	void AddMessage(Message newMessage);
	void ReadMessage(int MessageNum) const; //<messageNumber>
	Message SendMessage(string name, string email, string content);
	int CountMessages() const;

	// To do
protected:

	string _name;
	string _email;
	string _password;
	MessageBox* _MessageBox;
	list_f *_Friends, *_FRequests;
};


#endif
