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

bool Follower::operator==(Follower& f1) const
{
	Follower temp = *this;
	if (temp.GetEmail() == f1.GetEmail() && temp.GetName() == f1.GetName())
		return true;
	else
		return false;
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
		if (*index == Friend)
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
		if (*index == Friend)
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



int main()
{
	//Message* msg1 = new Message("alibaba", "shodedim", "tellmestory");
	//Message* msg2 = new Message("eli", "yossi", "chupar me la");
	//Message* msg3 = new Message("Sneh", "Shussman", "fuck me");

	Message msg1("alibaba", "shodedim", "tellmestory");
	Message msg2("eli", "yossi", "chupar me la");
	Message msg3("Sneh", "Shussman", "fuck me");


	Follower F1("f1", "f1@walla","1234");
	Follower F2("f2", "f2@walla", "4321");
	Follower F3("f3", "f2@walla", "qwerty");
	/*
	cout << F1.GetName() << " " << F1.GetEmail() << "\n";
	if (F1.isPassword("1234"))
		cout << "alright my man!\n";
	*/

	F1.AddFriendRequest(F2);
	F1.AddFriendRequest(F3);
	
	F1.DisplayFriendRequests();
	cout << F1.CountFriendRequests() << "\n";

	F1.AcceptedFriendRequest(F2);
	F1.AcceptedFriendRequest(F3);
	//F1.AcceptedFriendRequest("dude3@");
	//cout << F1.CountFriendRequests() << "\n";

	cout << "Before remove\n";
	F1.DisplayFriendList();
	cout << "\n";
	F1.RemoveFriend(F2);
	cout << "After removal\n";
	F1.DisplayFriendList();
	cout << "\nNo friend requests\n";
	F1.DisplayFriendRequests();

	
	F1.AddMessage(msg1);
	F1.AddMessage(msg2);
	F1.AddMessage(msg3);
	F1.ShowMessageList();
	
	cout << "\nThe message:\n\n";
	F1.ReadMessage(3);


	//F1.ShowMessageList();
	cout << "\nThree messages:\n";
	cout << F1.CountMessages() <<"\n";
	

	
	//cout << F2.GetName() << " " << F2.GetEmail << "\n";
	return 0;
}