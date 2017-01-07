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
	_Messages = new list_m;

	_Active_Follower = NULL; // maybe can use inheritance?
	_Active_Leader = NULL;

	_any_body_in = false;       //if there is anyone connected
								
	_is_admin = false;
	_is_leader = false;
}
// destructor

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


void SocialNetwork::DeleteUser(string email)
{
	if (_is_admin == false)   //user email exists or not admin
	{
		cout << DELETE_USER_FAIL;
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
		cout << DELETE_USER_FAIL;
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
	cout << DELETE_USER_SUCCESS;
}

// function for admin login
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
		_Active_Follower = NULL;
		_Active_Leader = NULL;
		// marking the logout
		cout << LOGOUT_SUCCESS;
	}
	else
		cout << LOGOUT_FAIL;
}

// function adds follower to social network
void SocialNetwork::CreateFollower(string name, string email, string password)
{
	int type = user_identifier(email);
	if ( type != 0)   //user email exists
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

// function adds leader to social network
void SocialNetwork::CreateLeader(string name, string email, string password)
{
	int type = user_identifier(email);
	if ( type!=0 || (_is_admin == false))   //user email exists or not admin
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
// 1 for leader 2 for follower 0 for nothing

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


// to find the follower my email - after debug version
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

/*
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
*/

void SocialNetwork::BroadcastMessage(string subject, string content)
{
	if (!_is_leader || !_any_body_in) {
		cout << BROADCAST_MESSAGE_FAIL;
		return;
	}

	Message* newMessage; 
	newMessage = new Message(_Active_Leader->GetEmail(), subject, content);
	_Messages->prepend(*newMessage); // A list for all the messages in the network so we can delete them and ensure no memory leak
	_Active_Leader->BroadcastMessage(*newMessage);
	cout << BROADCAST_MESSAGE_SUCCESS;
}

void SocialNetwork::ShowFriendRequests()
{
	if (!_any_body_in) {
		cout << SHOW_FRIEND_REQUESTS_FAIL;
		return;
	}
	_Active_Follower->DisplayFriendRequests();
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
	int user_type = SocialNetwork::user_identifier(email);
	if (user_type == 0) // user does not exist
		cout << LOGIN_FAIL;  // user does not exist

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
			cout << LOGIN_SUCCESS;
			return;
		}
		else
		{
			cout << LOGIN_FAIL;
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
			cout << LOGIN_SUCCESS;
		}
		else
		{
			cout << LOGIN_FAIL;
			return;
		}
	}
}

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

void SocialNetwork::ShowMessageList()
{
	if (!_any_body_in || _is_admin == true) // no one home or admin connected
	{
		cout << SHOW_MESSAGE_LIST_FAIL;
		return;
	}
		
	else
	{
		_Active_Follower->ShowMessageList();       // Maybe will need modifications to the def file
		return;
	}

}

void SocialNetwork::ReadMessage(int messageNum)
{
	if (!_any_body_in) // no one home
		cout << READ_MESSAGE_FAIL;
	else             // some one connected         
	{	
		if (_Active_Follower->ReadMessage(messageNum) == FAILURE ) // Maybe will need modifications to the def file
			cout << READ_MESSAGE_FAIL;
	}
}

void SocialNetwork::SendMessage(string email, string subject, string content)
{
	if ((_any_body_in) && _Active_Follower->isFriend(email))
	{
		Message* new_message;
		new_message = new Message(email, subject, content);
		_Messages->prepend(*new_message); // A list for all the messages in the network so we can delete them and ensure no memory leak
		_FollowerByMail(email)->AddMessage(*new_message);
		cout << SEND_MESSAGE_SUCCESS;
	}
	else
		cout << SEND_MESSAGE_FAIL;
} 

void SocialNetwork::Follow(string leaderEmail)
{
	int type = user_identifier(leaderEmail);

	if ((!_any_body_in) || (type!=1))
	{
		cout << FOLLOW_FAIL;
		return;
	}
	Leader* the_leader = _find_leader(leaderEmail);
	// if we are here means that some one is connected and the leader exists
	if (the_leader->isFollower(_Active_Follower->GetEmail()) )
	{
		//we get here of the follower already follows this leader
		cout << FOLLOW_FAIL;
		return;
	}
	//here we add the mew follower to the leader's list
	else
	{ 
	the_leader->AddFollower(*_Active_Follower);
	cout << FOLLOW_SUCCESS;
	}
}

void SocialNetwork::SendFriendRequest(string friendEmail)
{
	if (!_any_body_in) {
		cout << SEND_FRIEND_REQUEST_FAIL;
		return;
	}

	if (!_Active_Follower->GetEmail().compare(friendEmail)){ //friend himself
		cout << SEND_FRIEND_REQUEST_FAIL;
		return;
	}

	int user_id = user_identifier(friendEmail);

	if (!user_id) { //user doesn't exist
		cout << SEND_FRIEND_REQUEST_FAIL;
		return;
	}

	Follower* temp = _find_follower(friendEmail);

	if (temp->isFriend(_Active_Follower->GetEmail())) { //friend already exists - SHOULD BE ON THE SENDED mail
		cout << SEND_FRIEND_REQUEST_FAIL;
		return;
	}

	if (temp->isRequestExists(_Active_Follower->GetEmail())) { //friend already exists - SHOULD BE ON THE SENDED mail
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
		_Active_Follower->AcceptedFriendRequest(*_FollowerByMail(friendEmail));
		if (_FollowerByMail(friendEmail)->isRequestExists(friendEmail)) 
			_FollowerByMail(friendEmail)->AddFriendRequest(*_Active_Follower); //add request before aproval on the accepted friend
		_FollowerByMail(friendEmail)->AcceptedFriendRequest(*_Active_Follower); //add a friend to the list of the other person
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
		_FollowerByMail(friendEmail)->RemoveFriend(*_Active_Follower);
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

//    @@@@@@@@@@@@@@@                DEBUUUUUUUUUUUUUUG             @@@@@@@@@@@@@@@@2
int main()
{
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
	SocNetwork.CreateLeader("L3", "l3@", "1234");  //s
	cout << "\n";
	SocNetwork.CreateFollower("Zenzor1", "f1@", "1234"); //s
	cout << "\n";
	SocNetwork.CreateFollower("Zenzor2", "f2@", "1234"); //s
	cout << "\n";
	SocNetwork.CreateFollower("Zenzor3", "f3@", "1234"); //s
	cout << "\n";
	SocNetwork.CreateFollower("Zenzor4", "f4@", "1234"); //s
	cout << "\n";


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

	SocNetwork.AdminLogin("1234");	cout << "\n";
	SocNetwork.DeleteUser("l1@");	cout << "\n";
	SocNetwork.DeleteUser("f2@");	cout << "\n";
	SocNetwork.DeleteUser("f3@");

	SocNetwork.Login("l3@", "1234"); cout << "\n";
	
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
	*/
	int num = 6;
	return 0;
}
