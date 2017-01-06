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
	SocialNetwork(string name, string password);   //done
	~SocialNetwork();  //done

	void AdminLogin(string password);   //done
	void Login(string email, string password);
	void Logout(); // done

	// Admin actions
	void CreateLeader(string name, string email, string password);
	void DeleteUser(string email);

	// Leader actions
	void BroadcastMessage(string subject, string content);

	// Follower actions (also leader actions)
	void CreateFollower(string name, string email, string password);  // done

	void ShowFriendRequests();
	void ShowFriendList();
	void SendFriendRequest(string friendEmail);
	void AcceptFriendRequest(string friendEmail);
	void RemoveFriend(string friendEmail);

	void ShowMessageList();
	void ReadMessage(int messageNum);
	void SendMessage(string email, string subject, string content);

	void Follow(string leaderEmail);

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
	bool _any_body_in;       //if there is anyone connected
	string _email_connected;
	bool _is_admin;
	bool _is_leader;
	bool is_user_exists(string email);                 // done
};

#endif
