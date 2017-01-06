#include "SocialNetwork.H"
#include <iostream>


using std::cout;

// creator 
SocialNetwork::SocialNetwork(string name, string password)
{
	_network_name = name;			// do we need to initialize now?
	_admin_password = "1234";     // do we need to initialize now?

	_Followers = new list_f;
	_Leaders = new list_l;

	_Active_Follower = NULL; // maybe can use inheritance?
	_Active_Leader = NULL;

	_any_body_in = false;       //if there is anyone connected
								//_email_connected = "" ;    //not sure if need to initialize
	_is_admin = false;
	_is_leader = false;
}

SocialNetwork::~SocialNetwork()
{
	delete &_network_name;    //  added the & so it become a pointer - check later;
	delete &_admin_password;
	delete _Followers;
	delete _Leaders;

	delete &_any_body_in;
	//delete &_email_connected;
	delete &_is_admin;
	delete &_is_leader;
}

void SocialNetwork::AdminLogin(string password)
{
	if (password.compare(_admin_password))   // check the passwrod
	{
		//admin login succesfull
		_any_body_in = true;
		_is_admin = true;
		cout << ADMIN_LOGIN_SUCCESS << _network_name << "\n";
	}
	else
	{
		//admin login FAIL
		cout << ADMIN_LOGIN_FAIL;
	}
}

// function to log out
void SocialNetwork::Logout()
{
	if (_any_body_in == true)
	{
		_any_body_in = false;
		_is_admin = false;
		_is_leader =false;
		// marking the logout
		cout << LOGOUT_SUCCESS;
	}
	else
		cout << LOGOUT_FAIL;
}

void SocialNetwork::CreateFollower(string name, string email, string password)
{
	if (SocialNetwork::user_identifyer(email))   //user email exists
	{
		cout << CREATE_FOLLOWER_FAIL;
	}
	else  // user not exsits
	{
		Follower* new_follower;
		new_follower = new Follower(name, email, password);
		_Followers->prepend(*new_follower);
		cout << CREATE_FOLLOWER_SUCCESS;
	}
}

void SocialNetwork::CreateLeader(string name, string email, string password)
{
	if (SocialNetwork::user_identifyer(email) || (_is_admin == false))   //user email exists or not admin
	{
		cout << CREATE_LEADER_FAIL;
	}
	else  // user not exsits
	{
		Leader* new_leader;
		new_leader = new Leader(name, email, password);
		_Leaders->prepend(*new_leader);
		cout << CREATE_LEADER_SUCCESS;
	}
}

//check if this email already exists in leaders or followers list
// indicates if the leader is follower or leader
// 1 for leader 2 for follower

int SocialNetwork::user_identifyer(string email)
{
	_Followers->go_to_first();
	_Leaders->go_to_first();

	Follower* indexF = _Followers->get_current();
	Leader* indexL = _Leaders->get_current();
	while (indexF || indexL)
	{
		if (indexF->GetEmail() == email)
			return 2;      // exists and it is a follower
		if (indexL->GetEmail() == email)
			return 1;      // exists and it is a leader		

		_Followers->next();
		_Leaders->next();
		indexF = _Followers->get_current();
		indexL = _Leaders->get_current();
	}
	return 0;   // email does not exist
}

Follower* SocialNetwork::_FollowerByMail(string email)
{
	_Followers->go_to_first();
	_Leaders->go_to_first();

	Follower* indexF = _Followers->get_current();
	Leader* indexL = _Leaders->get_current();
	while (indexF || indexL)
	{
		if (indexF->GetEmail() == email)
			return indexF;      // exists and it is a follower
		if (indexL->GetEmail() == email)
			return indexL;      // exists and it is a leader		

		_Followers->next();
		_Leaders->next();
		indexF = _Followers->get_current();
		indexL = _Leaders->get_current();
	}
	return NULL;   // email does not exist
}


void SocialNetwork::BroadcastMessage(string subject, string content)
{
	if (!_is_leader || !_any_body_in) {
		cout << BROADCAST_MESSAGE_FAIL;
		return;
	}

	Message* newMessage; // we might want to append to list of all messages and release on exit ###################
	newMessage = new Message(_Active_Leader->GetEmail(), subject, content);
	_Active_Leader->BroadcastMessage(*newMessage);
	cout << BROADCAST_MESSAGE_SUCCESS;
}


void SocialNetwork::ShowFriendRequests()
{
	if (!_any_body_in) {
		cout << SHOW_FRIEND_REQUESTS_FAIL;
		return;
	}
	if (_is_leader){
		_Active_Leader->DisplayFriendRequests();
	}
	else {
		_Active_Follower->DisplayFriendRequests();
	}
}

void SocialNetwork::ShowFriendList()
{
	if (!_any_body_in) {
		cout << SHOW_FRIEND_LIST_FAIL;
		return;
	}
	_Active_Follower->DisplayFriendList();
	
}

void SocialNetwork::Login(string email, string password)
{
	int user_type = SocialNetwork::user_identifyer(email);
	if (user_type == 0) // user does not exist
		cout << LOGIN_FAIL;  // user does not exist

	if (user_type == 1)       // it is a leader, look in  and compare in leaders list
	{
		Leader* tmp = SocialNetwork::_find_leader(email);
		if (tmp->isPassword(password))   // password is OK
		{
			_any_body_in = true;
			_is_leader = true;
			_Active_Follower = tmp;
			cout << LOGIN_SUCCESS;
		}
	}
	if (user_type == 2)
	{
		Follower* tmp = SocialNetwork::_find_follower(email);
		if (tmp->isPassword(password))   // password is OK
		{
			_any_body_in = true;
			_Active_Follower = tmp;
			cout << LOGIN_SUCCESS;
		}
	}
}

Leader* SocialNetwork::_find_leader(string email)
{
	_Leaders->go_to_first();
	Leader* indexL = _Leaders->get_current();
	while (indexL)
	{
		if (indexL->GetEmail() == email)
			return indexL;

		_Leaders->next();
		indexL = _Leaders->get_current();
	}
	return NULL;
}

Follower* SocialNetwork::_find_follower(string email)
{
	_Followers->go_to_first();
	Follower* indexF = _Followers->get_current();
	while (indexF)
	{
		if (indexF->GetEmail() == email)
			return indexF;

		_Followers->next();
		indexF = _Leaders->get_current();
	}
	return NULL;
}


void SocialNetwork::SendFriendRequest(string friendEmail)
{
	if (!_any_body_in) {
		cout << SEND_FRIEND_REQUEST_FAIL;
		return;
	}
	if (_Active_Follower->GetEmail().compare(friendEmail)){ //friend himself
		cout << SEND_FRIEND_REQUEST_FAIL;
		return;
	}

	int user_id = user_identifyer(friendEmail);

	if (user_id) //user doesn't exist
		cout << SEND_FRIEND_REQUEST_FAIL;
	
	if (_Active_Follower->isFriend(friendEmail) || _Active_Follower->isRequestExists(friendEmail)) { //friend already exists
		cout << SEND_FRIEND_REQUEST_FAIL;
		return;
	}


	_FollowerByMail(friendEmail)->AddFriendRequest(*_Active_Follower); //send the friend request

}

void SocialNetwork::AcceptFriendRequest(string friendEmail)
{
	if (!_any_body_in) {
		cout << ACCEPT_FRIEND_REQUEST_FAIL;
		return;
	}

	if (_Active_Follower->isRequestExists(friendEmail)) {
		_Active_Follower->AcceptedFriendRequest(*_FollowerByMail(friendEmail)); //add the follower
		cout << ACCEPT_FRIEND_REQUEST_SUCCESS;
	}
	else {
		cout << ACCEPT_FRIEND_REQUEST_FAIL;
	}
	return;
}

void SocialNetwork::RemoveFriend(string friendEmail)
{
	if (!_any_body_in) {
		cout << REMOVE_FRIEND_FAIL;
		return;
	}
	if (_Active_Follower->isFriend(friendEmail)) {
		_Active_Follower->RemoveFriend(*_FollowerByMail(friendEmail)); //remove the friend
		cout << REMOVE_FRIEND_SUCCESS;
	}
	else {
		cout << REMOVE_FRIEND_FAIL;
	}
}

// General actions
/*
void SocialNetwork::FindUser(string partialName)
{
cout << "Followers:" << endl;
// Loop over all followers in network
for (int i = 0; ???????????????; ++i)
{
???????????????
if (curFollower->GetName().find(partialName) != string::npos)
cout << i + 1 << ") " << curFollower->GetName() << ": " << curFollower->GetEmail() << endl;
???????????????
}

cout << "Leaders:" << endl;
// Loop over all leaders in network
for (int i = 0; ???????????????; ++i)
{
???????????????
if (curLeader->GetName().find(partialName) != string::npos)
cout << i + 1 << ") " << curLeader->GetName() << ": " << curLeader->GetEmail() << endl;
???????????????
}
}

*/



