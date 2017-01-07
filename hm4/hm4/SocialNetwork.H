#ifndef _SOCIALNETWORK_H
#define _SOCIALNETWORK_H

#include "defs.H"
#include "Lists.H"
#include "Message.H"
#include "Follower.H"
#include "Leader.H"
#include <string>
using namespace std;

class SocialNetwork {
public:
	SocialNetwork(string name, string password);   //alex - done and CHECKED
	~SocialNetwork();								 //alex - done and CHECKED (doesnt crush on finish)

	void AdminLogin(string password);				 //alex - done and CHECKED
	void Login(string email, string password);	 // alex - done and CHECKED
	void Logout();								 // alex - done and CHECKED

												 // Admin actions
	void CreateLeader(string name, string email, string password);  //alex - done and CHECKED
	void DeleteUser(string email);

	// Leader actions	
	

	// Follower actions (also leader actions)
	void CreateFollower(string name, string email, string password);  //alex - done and CHECKED 

	void ShowFriendRequests(); //ofir - done and CHECKED
	void ShowFriendList(); //ofir - done and CHECKED
	void SendFriendRequest(string friendEmail); //ofir - done and CHECKED
	void AcceptFriendRequest(string friendEmail); //ofir - done and CHECKED
	void RemoveFriend(string friendEmail); //ofir - done and CHECKED
	void BroadcastMessage(string subject, string content); //ofir - done and CHECKED
	// this sections needs to add friends before debug
	void ShowMessageList();                  // alex - done - await upper debug
	void ReadMessage(int messageNum);		 // alex - done - await upper debug
	void SendMessage(string email, string subject, string content); // alex - await upper debug

	void Follow(string leaderEmail);       // alex - done and CHECKED 

	// General actions
	void FindUser(string partialName);

private:
	// To do
	//network info
	string _network_name;
	string _admin_password;

	// users lists
	list_f *_Followers;
	list_l *_Leaders;

	// network indications  - maybe need more...
	Follower *_Active_Follower; // maybe can use inheritance?
	Leader *_Active_Leader;

	Leader *_find_leader(string email);
	Follower *_find_follower(string email);

	bool _any_body_in;       //if there is anyone connected
	bool _is_admin;
	bool _is_leader;
	// 0: not exists , 1:leader, 2: follower
	int user_identifier(string email);  //                             alex - done and CHECKED
	Follower* _FollowerByMail(string email);
};

#endif
