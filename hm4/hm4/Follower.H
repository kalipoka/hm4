#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include "defs.H"
#include "Lists.H"

using std::string;

class Follower {
public:
	Follower(string name, string email, string password);
	~Follower();

    string GetName();
	string GetEmail();
	bool isPassword(string password);

	void DisplayFriendRequests();
	void DisplayFriendList();
	void SendFriendRequest(string email);
	void AddFriendRequest(string email);
	void AcceptdFriendRequest(string email);
	void RemoveFriend(string email);

	int CountFriendRequests() const;
	void ShowMessageList() const;
	void AddMessage();
	void ReadMessage() const; //<messageNumber>
	void SendMessage(string name, string email, string content);
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
