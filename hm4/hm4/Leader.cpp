#include<iostream>
#include "Leader.H"

Leader::Leader(string name, string email, string password) :Follower(name, email, password) {
	_Followers = new list_f;
}

Leader::~Leader()
{
	_Followers->release();
	delete _Followers;
}

void Leader::AddFollower(Follower& Friend)
{
	_Followers->prepend(Friend);
}
int Leader::CountFollowers()
{
	return _Followers->get_size();
}

void Leader::RemoveFollower(Follower& Friend)
{
	//find the friend requests in list	
	_Followers->go_to_first();
	Follower* index = _Followers->get_current();

	while (index)
	{
		if (*index == Friend)
		{
			_Followers->delete_current();
		}
		else
		{
			_Followers->next();
		}
		index = _Followers->get_current();
	}
}

void Leader::BroadcastMessage(Message& TheMessage)
{
	//find the friend requests in list	
	_Followers->go_to_first();
	Follower* index = _Followers->get_current();

	while (index)
	{
		SendMessage(TheMessage, *index);
		_Followers->next();
		index = _Followers->get_current();
	}
}
