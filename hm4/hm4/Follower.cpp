#include <iostream>
#include "Follower.H"

using std::cout;

Follower::Follower(string name, string email, string password)
{
	_name = name;
	_email = email;
	_password = password;
	_MessageBox = new MessageBox(NULL, NULL, 0);
	_Friends = new list_f;
	_FRequests = new list_f;
}

Follower::~Follower()
{
	_MessageBox->release();
	_Friends->release();
	_Friends->release();
	delete _MessageBox;
	delete _Friends;
	delete _FRequests;
}

string Follower::GetName() { return _name; }
string Follower::GetEmail() { return _email; }

bool Follower::isPassword(string password)
{
	if (password.compare(_password))
		return false;
	else
		return true;
}

void Follower::DisplayFriendRequests()
{
	_FRequests->go_to_first();
	Follower* index = _FRequests->get_current();
	int size = 0;
	while (index)
	{
		size++;
		cout << size << ") " << index->GetName() << ": "<< index->GetEmail() << "\n";
		_FRequests->next();
		index = _FRequests->get_current();
	}
}

void Follower::DisplayFriendList()
{
	_Friends->go_to_first();
	Follower* index = _Friends->get_current();
	int size = 0;
	while (index)
	{
		size++;
		cout << size << ") " << index->GetName() << ": " << index->GetEmail() << "\n";
		_Friends->next();
		index = _Friends->get_current();
	}
}

void Follower::AddFriendRequest(Follower& Friend)
{
	_FRequests->prepend(Friend);
}

void Follower::AcceptedFriendRequest(Follower& Friend)
{
	//find the friend requests in list	
	_FRequests->go_to_first();
	Follower* index = _FRequests->get_current();

	while (index)
	{
		if (index->GetEmail() == Friend.GetEmail() && index->GetName() == Friend.GetName())
		{
			_Friends->prepend(*index);
			_FRequests->delete_current();
		}
		else
		{
			_FRequests->next();
		}
		index = _FRequests->get_current();
	}
}

void Follower::RemoveFriend(Follower& Friend)
{
	//find the friend requests in list	
	_Friends->go_to_first();
	Follower* index = _Friends->get_current();

	while (index)
	{
		if (index->GetEmail() == Friend.GetEmail() && index->GetName() == Friend.GetName())
		{
			_Friends->delete_current();
		}
		else
		{
			_Friends->next();
		}
		index = _Friends->get_current();
	}
}

int Follower::CountFriendRequests() const
{
	return _FRequests->get_size();
}

void Follower::ShowMessageList() const
{
	_MessageBox->Print();
}

void Follower::AddMessage(Message& newMessage)
{
	_MessageBox->prepend(newMessage);
}

void Follower::ReadMessage(int MessageNum) const//<messageNumber>
{
	_MessageBox->ReadMessage(MessageNum);
}

void Follower::SendMessage(Message& TheMessage, Follower& Friend)
{
	Friend.AddMessage(TheMessage);
}
 
int Follower::CountMessages() const
{
	return _MessageBox->get_size();
}



