#include "SocialNetwork.H"
#include <iostream>


using std::cout;

/*************************************
* The creater of the Social Network 
* 
**************************************/
SocialNetwork::SocialNetwork(string name, string password)
{
	_network_name = name;			// do we need to initialize now?
	_admin_password = "1234";     // do we need to initialize now?

	_Followers = new list_f;
	_Leaders = new list_l;
	_Messages = new list_m;

	_Active_Follower = NULL; // maybe can use inheritance?
	_Active_Leader = NULL;

	_any_body_in = false;       //if there is anyone connected
								
	_is_admin = false;
	_is_leader = false;
}
// destructor
/*************************************
* The destructor of the social network
*
**************************************/
SocialNetwork::~SocialNetwork()
{
	_delete_All_followers();
	_delete_All_leaders();
	_delete_All_messages();
	_Followers->release();
	delete _Followers;
	_Leaders->release();
	delete _Leaders;
	_Messages->release();
	delete _Messages;
}

/*************************************
*
*This function deletes  any user
*
**************************************/
void SocialNetwork::DeleteUser(string email)
{
	if (_is_admin == false)   //user email exists or not admin
	{
		cout << DELETE_USER_FAIL << "\n";
		return;
	}
	int id = user_identifier(email);
	Follower* DUser = NULL;

	if (id == 1) //leader
	{
		DUser = _find_leader(email);
	}
	else {
		DUser = _find_follower(email);
	}

	if (!DUser) {
		cout << DELETE_USER_FAIL << "\n";
		return;
	}
	
	_Followers->go_to_first();
	Follower* indexF = _Followers->get_current();
	while (indexF)
	{
		indexF->AcceptedFriendRequest(*DUser); //Approve all requests from the specific friend
		indexF->RemoveFriend(*DUser); //Remove the friendships
		_Followers->next();
		indexF = _Followers->get_current();
	}

	_Leaders->go_to_first();
	Leader* indexL = _Leaders->get_current();
	while (indexL)
	{
		indexL->AcceptedFriendRequest(*DUser); //Approve all requests from the specific friend
		indexL->RemoveFriend(*DUser); //Remove the friendships
		indexL->RemoveFollower(*DUser);
		_Leaders->next();
		indexL = _Leaders->get_current();
	}

	// remove user from general leader or followers list

	

	if (id == 1) //leader
	{
		_delete_leader(email);
	}
	else {
		_delete_follower(email);
	}
	cout << DELETE_USER_SUCCESS << "\n";
}

/*************************************
* Admin Login Function
**************************************/
void SocialNetwork::AdminLogin(string password)
{
	if (!_admin_password.compare(password))   // check the passwrod
	{
		//admin login succesfull
		_any_body_in = true;
		_is_admin = true;
		_is_leader = false;
		_Active_Follower = NULL;
		_Active_Leader = NULL;

		cout << ADMIN_LOGIN_SUCCESS << _network_name << "\n";
	}
	else
	{
		//admin login FAIL
		cout << ADMIN_LOGIN_FAIL << "\n";
	}
}

/*************************************
*Logout Function
**************************************/
void SocialNetwork::Logout()
{
	if (_any_body_in == true)
	{
		_any_body_in = false;
		_is_admin = false;
		_is_leader =false;
		_Active_Follower = NULL;
		_Active_Leader = NULL;
		// marking the logout
		cout << LOGOUT_SUCCESS << "\n";
	}
	else
		cout << LOGOUT_FAIL << "\n";
}

/*************************************
* Function to Add follower to the social network
*
*
**************************************/
void SocialNetwork::CreateFollower(string name, string email, string password)
{
	int type = user_identifier(email);
	if ( type != 0)   //user email exists
	{
		cout << CREATE_FOLLOWER_FAIL << "\n";
	}
	else  // user not exsits
	{
		Follower* new_follower;
		new_follower = new Follower(name, email, password);
		_Followers->prepend(*new_follower);
		cout << CREATE_FOLLOWER_SUCCESS << "\n";
	}
}

/*************************************
* Functions add Leader to the social network
*
*
**************************************/
void SocialNetwork::CreateLeader(string name, string email, string password)
{
	int type = user_identifier(email);
	if ( type!=0 || (_is_admin == false))   //user email exists or not admin
	{
		cout << CREATE_LEADER_FAIL << "\n";
	}
	else  // user not exsits
	{
		Leader* new_leader;
		new_leader = new Leader(name, email, password);
		_Leaders->prepend(*new_leader);
		cout << CREATE_LEADER_SUCCESS << "\n";
	}
}


/*************************************
* This Function check if this email already exists in leaders or followers list
* indicates if the leader is follower or leader
* 1 for leader 2 for follower 0 for nothing
**************************************/
int SocialNetwork::user_identifier(string email)
{
	_Followers->go_to_first();
	_Leaders->go_to_first();

	Follower* indexF = _Followers->get_current();
	Leader* indexL = _Leaders->get_current();

	while (indexF)
	{
		if (!indexF->GetEmail().compare(email))    //equal if 0
			return 2;      // exists and it is a follower
		_Followers->next();
		indexF = _Followers->get_current();
	}

	while (indexL)
	{
		if (!indexL->GetEmail().compare(email))
			return 1;      // exists and it is a leader	
		_Leaders->next();
		indexL = _Leaders->get_current();
	}

	return 0;   // email does not exist
}


/*************************************
*This function search for a user (Leader or follower) and retuns pointer to it

**************************************/
Follower* SocialNetwork::_FollowerByMail(string email)
{
	_Followers->go_to_first();
	_Leaders->go_to_first();

	Follower* indexF = _Followers->get_current();
	Leader* indexL = _Leaders->get_current();
	
	while (indexF)
	{
		if (!indexF->GetEmail().compare(email))    //equal if 0
			return indexF;      // exists and it is a follower
		_Followers->next();
		indexF = _Followers->get_current();
	}

	while (indexL)
	{
		if (!indexL->GetEmail().compare(email))
			return indexL;      // exists and it is a leader	
		_Leaders->next();
		indexL = _Leaders->get_current();
	}
	return NULL;   // email does not exist
}
/*************************************
*This fucntion Broadcast a message to all the followers of that leader
*
*
**************************************/

void SocialNetwork::BroadcastMessage(string subject, string content)
{
	if (_is_admin) {
		cout << BROADCAST_MESSAGE_FAIL << "\n";
		return;
	}
	if (!_is_leader || !_any_body_in) {
		cout << BROADCAST_MESSAGE_FAIL << "\n";
		return;
	}

	Message* newMessage; 
	newMessage = new Message(_Active_Leader->GetEmail(), subject, content);
	_Messages->prepend(*newMessage); // A list for all the messages in the network so we can delete them and ensure no memory leak
	_Active_Leader->BroadcastMessage(*newMessage);
	cout << BROADCAST_MESSAGE_SUCCESS << "\n";
}
/*************************************
* This function shows the friend requests of the logged in user
*
*
**************************************/

void SocialNetwork::ShowFriendRequests()
{
	if (!_any_body_in || _is_admin) {
		cout << SHOW_FRIEND_REQUESTS_FAIL << "\n";
		return;
	}
	_Active_Follower->DisplayFriendRequests();
}
/*************************************
*This function shows the friend lists a logged in user
*
*
**************************************/
void SocialNetwork::ShowFriendList()
{
	if (!_any_body_in || _is_admin) {
		cout << SHOW_FRIEND_LIST_FAIL << "\n";
		return;
	}
	_Active_Follower->DisplayFriendList();
	
}
/*************************************
* Login function  for Leader or Follower
*
*
**************************************/
void SocialNetwork::Login(string email, string password)
{
	int user_type = SocialNetwork::user_identifier(email);
	if (user_type == 0) // user does not exist
		cout << LOGIN_FAIL << "\n";  // user does not exist

	if (user_type == 1)       // it is a leader, look in  and compare in leaders list
	{
		Leader* tmp = SocialNetwork::_find_leader(email);
		if (tmp->isPassword(password))   // password is OK
		{
			_any_body_in = true;
			_is_leader = true;
			_is_admin = false;
			_Active_Follower = tmp;
			_Active_Leader = tmp;
			cout << LOGIN_SUCCESS << "\n";
			return;
		}
		else
		{
			cout << LOGIN_FAIL << "\n";
			return;
		}
			
	}
	if (user_type == 2)
	{
		Follower* tmp = SocialNetwork::_find_follower(email);
		if (tmp->isPassword(password))   // password is OK
		{
			_any_body_in = true;
			_is_admin = false;
			_is_leader = false;
			_Active_Follower = tmp;
			_Active_Leader = NULL;
			cout << LOGIN_SUCCESS << "\n";
		}
		else
		{
			cout << LOGIN_FAIL << "\n";
			return;
		}
	}
}
/*************************************
* This auxilary function returns a leader my email
*
*
**************************************/
Leader* SocialNetwork::_find_leader(string email)
{
	_Leaders->go_to_first();
	Leader* index = _Leaders->get_current();
	while (index)
	{
		if (index->GetEmail() == email)
			return index;
		_Leaders->next();
		index = _Leaders->get_current();
	}
	return NULL;
}
/*************************************
*This auxilary function return a folloer by email
*
*
**************************************/
Follower* SocialNetwork::_find_follower(string email)
{
	_Followers->go_to_first();
	Follower* index = _Followers->get_current();
	while (index)
	{
		if (index->GetEmail() == email)
			return index;

		_Followers->next();
		index = _Followers->get_current();
	}
	return NULL;
}

/*************************************
* This function deletes a leader from the list of leaders
*
*
**************************************/
void SocialNetwork::_delete_leader(string email)
{
	_Leaders->go_to_first();
	Leader* index = _Leaders->get_current();
	while (index)
	{
		if (index->GetEmail() == email) {
			delete index;
			_Leaders->delete_current();
			return;
		}
		_Leaders->next();
		index = _Leaders->get_current();
	}
	return;
}
/*************************************
* This functions deletes follower from the followers list
*
*
**************************************/
void SocialNetwork::_delete_follower(string email)
{
	_Followers->go_to_first();
	Follower* index = _Followers->get_current();
	while (index)
	{
		if (index->GetEmail() == email) {
			delete index;
			_Followers->delete_current();
			return;
		}
		_Followers->next();
		index = _Followers->get_current();
	}
	return;
}

/*************************************
* Delete all leaders to free memory
*
*
**************************************/
void SocialNetwork::_delete_All_leaders()
{
	_Leaders->go_to_first();
	Leader* index = _Leaders->get_current();
	while (index)
	{
		delete index;
		_Leaders->next();
		index = _Leaders->get_current();
	}
	return;
}

/*************************************
* Deletes all followers to free memory
*
*
**************************************/
void SocialNetwork::_delete_All_followers()
{
	_Followers->go_to_first();
	Follower* index = _Followers->get_current();
	while (index)
	{
		delete index;
		_Followers->next();
		index = _Followers->get_current();
	}
	return;
}

/*************************************
* Delets all mesaages to free memory
*
*
**************************************/
void SocialNetwork::_delete_All_messages()
{
	_Messages->go_to_first();
	Message* index = _Messages->get_current();
	while (index)
	{
		delete index;
		_Messages->next();
		index = _Messages->get_current();
	}
	return;
}
/*************************************
* Shows The messages list of a logged in user
*
**************************************/
void SocialNetwork::ShowMessageList()
{
	if (!_any_body_in || _is_admin == true) // no one home or admin connected
	{
		cout << SHOW_MESSAGE_LIST_FAIL << "\n";
		return;
	}
		
	else
	{
		_Active_Follower->ShowMessageList();       // Maybe will need modifications to the def file
		return;
	}
}
/*************************************
* Reads a specific number of a messages in the users Messagebox
*
**************************************/
void SocialNetwork::ReadMessage(int messageNum)
{
	if ((!_any_body_in) || _is_admin) // no one home or admin tries to read message
		cout << READ_MESSAGE_FAIL << "\n";
	else             // some one connected         
	{	
		if (_Active_Follower->ReadMessage(messageNum) == FAILURE ) // Maybe will need modifications to the def file
			cout << READ_MESSAGE_FAIL << "\n";
	}
}
/*************************************
* Send a message to a friend
*
**************************************/
void SocialNetwork::SendMessage(string email, string subject, string content)
{
	if (_is_admin)
	{
		cout << SEND_MESSAGE_FAIL << "\n";
		return;
	}
	if ((_any_body_in) && _Active_Follower->isFriend(email))
	{
		Message* new_message;
		new_message = new Message(_Active_Follower->GetEmail(), subject, content);
		_Messages->prepend(*new_message); // A list for all the messages in the network so we can delete them and ensure no memory leak
		_FollowerByMail(email)->AddMessage(*new_message);
		cout << SEND_MESSAGE_SUCCESS << "\n";
	}
	else
		cout << SEND_MESSAGE_FAIL << "\n";
} 
/*************************************
* Start following a Leader
*
**************************************/
void SocialNetwork::Follow(string leaderEmail)
{
	int type = user_identifier(leaderEmail);
	if (_is_admin)
	{
		cout << FOLLOW_FAIL << "\n";
		return;
	}

	if ((!_any_body_in) || (type!=1))
	{
		cout << FOLLOW_FAIL << "\n";
		return;
	}
	Leader* the_leader = _find_leader(leaderEmail);
	// if we are here means that some one is connected and the leader exists
	if (the_leader->isFollower(_Active_Follower->GetEmail()) )
	{
		//we get here of the follower already follows this leader
		cout << FOLLOW_FAIL << "\n";
		return;
	}
	//here we add the mew follower to the leader's list
	else
	{ 
	the_leader->AddFollower(*_Active_Follower);
	cout << FOLLOW_SUCCESS << "\n";
	}
}
/*************************************
* Send a friend request to another user
*
**************************************/
void SocialNetwork::SendFriendRequest(string friendEmail)
{
	if (!_any_body_in || _is_admin ) {                                     // Alex fix big bug
		cout << SEND_FRIEND_REQUEST_FAIL << "\n";
		return;
	}

	if (!_Active_Follower->GetEmail().compare(friendEmail)){ //friend himself
		cout << SEND_FRIEND_REQUEST_FAIL << "\n";
		return;
	}

	int user_id = user_identifier(friendEmail);

	if (!user_id) { //user doesn't exist
		cout << SEND_FRIEND_REQUEST_FAIL << "\n";
		return;
	}
	
	Follower* temp = NULL;

	if (user_id == 1) //leader
	{
		temp = _find_leader(friendEmail);
	}
	else {
		temp = _find_follower(friendEmail);
	}


	if (temp->isFriend(_Active_Follower->GetEmail())) { //friend already exists - SHOULD BE ON THE SENDED mail
		cout << SEND_FRIEND_REQUEST_FAIL << "\n";
		return;
	}

	if (temp->isRequestExists(_Active_Follower->GetEmail())) { //friend already exists - SHOULD BE ON THE SENDED mail
		cout << SEND_FRIEND_REQUEST_FAIL << "\n";
		return;
	}
	cout << SEND_FRIEND_REQUEST_SUCCESS << "\n";
	_FollowerByMail(friendEmail)->AddFriendRequest(*_Active_Follower); //send the friend request
}
/*************************************
*Accept a friend request from another user and add user the the friends list
*
**************************************/
void SocialNetwork::AcceptFriendRequest(string friendEmail)
{
	if (_is_admin)
	{
		cout << ACCEPT_FRIEND_REQUEST_FAIL << "\n";
		return;
	}
	if (!_any_body_in) {
		cout << ACCEPT_FRIEND_REQUEST_FAIL << "\n";
		return;
	}

	Follower* TheFriend = _FollowerByMail(friendEmail);

	if (_Active_Follower->isRequestExists(friendEmail)) {
		if (TheFriend->isRequestExists(_Active_Follower->GetEmail()))
			TheFriend->AcceptedFriendRequest(*_Active_Follower);
		else
			TheFriend->AddFriend(*_Active_Follower); //add request before aproval on the accepted friend
		_Active_Follower->AcceptedFriendRequest(*TheFriend);
		//TheFriend->AcceptedFriendRequest(*_Active_Follower); //add a friend to the list of the other person
		cout << ACCEPT_FRIEND_REQUEST_SUCCESS << "\n";
	}
	else {
		cout << ACCEPT_FRIEND_REQUEST_FAIL << "\n";
	}
	return;
}

/*************************************
*Remove a friend from the list of friends
*
**************************************/
void SocialNetwork::RemoveFriend(string friendEmail)
{

	if (_is_admin)
	{
		cout << REMOVE_FRIEND_FAIL << "\n";
		return;
	}

	if (!_any_body_in) {
		cout << REMOVE_FRIEND_FAIL << "\n";
		return;
	}
	if (_Active_Follower->isFriend(friendEmail)) {
		_Active_Follower->RemoveFriend(*_FollowerByMail(friendEmail)); //remove the friend
		_FollowerByMail(friendEmail)->RemoveFriend(*_Active_Follower);
		cout << REMOVE_FRIEND_SUCCESS << "\n";
	}
	else {
		cout << REMOVE_FRIEND_FAIL << "\n";
	}
}
/*************************************
*Exit and delete the social network;
*
*************************************
void SocialNetwork::Exit()
{
	SocialNetwork::~SocialNetwork();
}
*/

// General actions
/*************************************
* Find a user (Follower of Leader) in the lists of the 
* Social network which's name contains the desired string
*
**************************************/
void SocialNetwork::FindUser(string partialName)
{
	_Followers->go_to_first();
	_Leaders->go_to_first();
	Follower* indexF = _Followers->get_current();
	Leader* indexL = _Leaders->get_current();
	int i = 0;

	cout << "Followers:" << endl;
	while (indexF)
	{
		if (indexF->GetName().find(partialName) != string::npos)
			cout << i + 1 << ") " << indexF->GetName() << ": " << indexF->GetEmail() << endl;

		_Followers->next();
		indexF = _Followers->get_current();
		i++;
	}

	i = 0;
	cout << "Leaders:" << endl;
	while (indexL)
	{
		if (indexL->GetName().find(partialName) != string::npos)
			cout << i + 1 << ") " << indexL->GetName() << ": " << indexL->GetEmail() << endl;

		_Leaders->next();
		indexL = _Leaders->get_current();
		i++;
	}
}

/*
//    @@@@@@@@@@@@@@@                DEBUUUUUUUUUUUUUUG             @@@@@@@@@@@@@@@@2
int main()
{
	// the falling test debug






	
	Message msg1("alibaba", "shodedim", "tellmestory");
	Message msg2("eli", "yossi", "chupar me la");
	Message msg3("Sneh", "Shussman", "fuck me");
	SocialNetwork SocNetwork("MamatNet", "1234");
	// login test
	SocNetwork.AdminLogin("bulbul");
	cout << "\n";
	SocNetwork.AdminLogin("1234");

	
	SocNetwork.CreateLeader("L1", "l1@", "1234");   //s
	cout << "\n";
	SocNetwork.CreateLeader("L2", "l2@", "1234");  //s
	cout << "\n";
	SocNetwork.CreateLeader("Zen", "l3@", "1234");  //s
	cout << "\n";
	SocNetwork.CreateFollower("Zenzor1", "f1@", "1234"); //s
	cout << "\n";
	SocNetwork.CreateFollower("Zenzor2", "f2@", "1234"); //s
	cout << "\n";
	SocNetwork.CreateFollower("Zenzor3", "f3@", "1234"); //s
	cout << "\n";
	SocNetwork.CreateFollower("Zinzana4", "f4@", "1234"); //s
	cout << "\n";

	SocNetwork.FindUser("ZIMBABUA");  //nothing to print
	SocNetwork.FindUser("Zen");		//needs to print 3 followers and 1 leader
	SocNetwork.FindUser("L");
	SocNetwork.FindUser("L");
	/*
	SocNetwork.Login("l1@", "1234");	cout << "\n"; // f1
	SocNetwork.SendFriendRequest("f4@");
	SocNetwork.Follow("l3@");

	SocNetwork.Login("f2@", "1234");	cout << "\n"; // f2
	SocNetwork.SendFriendRequest("f4@");
	SocNetwork.Follow("l3@");

	SocNetwork.Login("f3@", "1234");	cout << "\n"; // f3
	SocNetwork.SendFriendRequest("f4@");
	SocNetwork.Follow("l3@");
	
	SocNetwork.Login("l3@", "1234"); cout << "\n";
	SocNetwork.BroadcastMessage("A message", "From the prime leader");

	SocNetwork.Login("f3@", "1234");
	SocNetwork.ShowMessageList();

	SocNetwork.BroadcastMessage("A message", "From the prime leader");	cout << "\n";

	SocNetwork.Login("f4@", "1234");
	SocNetwork.AcceptFriendRequest("l1@");
	SocNetwork.AcceptFriendRequest("f2@");
	//SocNetwork.AcceptFriendRequest("f3@");

	SocNetwork.DeleteUser("f3@");	cout << "\n";

	SocNetwork.Login("l3@", "1234"); cout << "\n";
	/*
	SocNetwork.AdminLogin("1234");	cout << "\n";
	SocNetwork.DeleteUser("l1@");	cout << "\n";
	SocNetwork.DeleteUser("f2@");	cout << "\n";
	SocNetwork.DeleteUser("f3@");

	SocNetwork.Login("l3@", "1234"); cout << "\n";
	SocNetwork.Follow("l3@"); cout << "\n";
	SocNetwork.Login("f4@", "1234");cout << "\n";
	SocNetwork.Follow("l3@"); cout << "\n";
	*/

	/*
	 //Accept friend request - send message
	SocNetwork.Login("f4@", "1234");cout << "\n";
	SocNetwork.AcceptFriendRequest("f3@"); cout << "\n";
	SocNetwork.SendMessage("f0@", "Hi_Nigger", "You are a nigger"); cout << "\n";  //wrong email
	SocNetwork.SendMessage("f3@", "Hi_Nigger", "You are a nigger"); cout << "\n"; //correct email
	// check if we received the message - then read and display the images
	SocNetwork.Login("f3@", "1234");cout << "\n";
	SocNetwork.ShowMessageList();cout << "\n";
	SocNetwork.ReadMessage(1); cout << "\n";
	SocNetwork.ShowMessageList();cout << "\n";
	*/

	/*
	//needed tests:
	void ShowFriendRequests(); //ofir - checked
	void ShowFriendList(); //ofir = checked
	void SendFriendRequest(string friendEmail); //ofir = checked
	void AcceptFriendRequest(string friendEmail); //ofir = checked
	void RemoveFriend(string friendEmail); //ofir = checked
	void BroadcastMessage(string subject, string content); //ofir
	*/


	/*
	// testing for messages  $$$$$$$$$$$$$$$$$$$$$ need to add friend before

	SocNetwork.AdminLogin("1234"); cout << "\n";
	SocNetwork.ShowMessageList(); cout << "\n";
	SocNetwork.Login("hedva@onecup", "qwerty"); cout << "\n";  //  follower login correct password
	SocNetwork.ShowMessageList(); cout << "\n";
	// need to send messages before
	SocNetwork.ReadMessage(2);          // need to fail - not messages yet
	cout << "\n";
	SocNetwork.SendMessage("hedva@onecup", "Hi_Nigger", "You are a nigger");  //wrong email
	cout << "\n";
	SocNetwork.SendMessage("hedva@onecup", "Hi_Nigger", "You are a nigger");   //should work
	cout << "\n";

	// testing for Follow
	SocNetwork.Login("hedva@onecup", "qwerty"); cout << "\n";  //  follower login correct password

	SocNetwork.Follow("zzzzzzzzzzzz");   cout << "\n"; // should fail - no such follower
	SocNetwork.Follow("L2@gmail");  cout << "\n";  // shoud succeed
	SocNetwork.Follow("L2@gmail");  cout << "\n";  // shoud fail - already follow this one
	
	int num = 6;
	
	return 0;
}
*/