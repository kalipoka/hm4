#include <iostream>
#include "Follower.H"

using std::cout;

Follower::Follower(string name, string email, string password)
{
	_name = name;
	_email = email;
	_password = password;
	_MessageBox = new MessageBox(); // still in constraction;
	_Friends = new list_f;
	_FRequests = new list_f;
}

Follower::~Follower()
{
	delete _MessageBox;
	delete _Friends;
	delete _FRequests;
}

string Follower::GetName() { return _name; }
string Follower::GetEmail() { return _email; }

bool Follower::isPassword(string password)
{
	if (password.compare(_password))
		return true;
	else
		return false;
}


void Follower::DisplayFriendRequests()
{
	_FRequests->print;
}

void Follower::DisplayFriendList()
{
	_Friends->print;
}

void Follower::AddFriendRequest(string email)
{
	Follower* new_follower;
	new_follower = new Follower("a", email, "a");
	_FRequests->prepend(*new_follower);
}

void  Follower::AcceptdFriendRequest(string email)
{
	Follower* new_follower;
	//find the friend requests in list
	new_follower = new Follower("a", email, "a");
	_FRequests->go_to_first;

	//add new member to followers friend list

	_FRequests->prepend(*new_follower);
	delete new_follower;
}