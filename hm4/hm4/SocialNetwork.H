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
	SocialNetwork(string name, string password);   //alex - done
	~SocialNetwork();								 //alex - done

	void AdminLogin(string password);				 //alex - done
	void Login(string email, string password);	 // alex - done
	void Logout();								 // alex - done

												 // Admin actions
	void CreateLeader(string name, string email, string password);  //alex - done
	void DeleteUser(string email);

	// Leader actions	
	void BroadcastMessage(string subject, string content); //ofir

	// Follower actions (also leader actions)
	void CreateFollower(string name, string email, string password);  // alex - done

	void ShowFriendRequests(); //ofir
	void ShowFriendList(); //ofir
	void SendFriendRequest(string friendEmail); //ofir
	void AcceptFriendRequest(string friendEmail); //ofir
	void RemoveFriend(string friendEmail); //ofir

	void ShowMessageList();                  // alex - done
	void ReadMessage(int messageNum);		 // alex - done
	void SendMessage(string email, string subject, string content); // alex - done

	void Follow(string leaderEmail);       // alex - done

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
	int user_identifyer(string email);  // d
	Follower* _FollowerByMail(string email);
};

#endif
