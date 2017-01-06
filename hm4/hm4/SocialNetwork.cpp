#include "SocialNetwork.H"
#include <iostream>


using std::cout;

// creator 
SocialNetwork::SocialNetwork(string name, string password)
{
	_network_name = name;			// do we need to initialize now?
	_admin_password = password;     // do we need to initialize now?

	_Followers = new list_f;
	_Leaders = new list_l;

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
	delete &_email_connected;
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
	if ( _any_body_in == true)
	{
		_any_body_in = false;    // marking the logout
		cout << LOGOUT_SUCCESS;
	}
	else
		cout << LOGOUT_FAIL;
}

void SocialNetwork::CreateFollower(string name, string email, string password)
{
	if (SocialNetwork::is_user_exists(email))   //user email exists
	{
		cout << CREATE_FOLLOWER_FAIL;
	}
	else  // user not exsits
	{
		Follower* new_follower;
		new_follower = new Follower("a", email, "a");
		_Followers->prepend(*new_follower);
		cout << CREATE_FOLLOWER_SUCCESS;
	}
}



//check if this email already exists in leaders or followers list
bool SocialNetwork::is_user_exists(string email)
{
	_Followers->go_to_first();
	_Leaders->go_to_first();

	Follower* indexF = _Followers->get_current();
	Leader* indexL = _Leaders->get_current();
	while (indexF || indexL)
	{
		if ((indexF->GetEmail() == email) || (indexL->GetEmail() == email))
			return true;				//email exists already;
		_Followers->next();
		_Leaders->next();
		 indexF = _Followers->get_current();
		 indexL = _Leaders->get_current();
	}
	return false;   // email does not exist
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



