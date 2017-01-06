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
	while (index)
	{
		cout << index->GetEmail() << "\n";
		_FRequests->next();
		index = _FRequests->get_current();
	}
}

void Follower::DisplayFriendList()
{
	_Friends->go_to_first();
	Follower* index = _Friends->get_current();
	while (index)
	{
		cout << index->GetEmail() << "\n";
		_Friends->next();
		index = _Friends->get_current();
	}
}

void Follower::AddFriendRequest(string email)
{
	Follower* new_follower;
	new_follower = new Follower("a", email, "a");
	_FRequests->prepend(*new_follower);
}

void Follower::AcceptedFriendRequest(string email)
{
	//find the friend requests in list	
	_FRequests->go_to_first();
	Follower* index = _FRequests->get_current();

	while (index)
	{
		if (index->GetEmail() == email)
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

void Follower::RemoveFriend(string email)
{
	//find the friend requests in list	
	_Friends->go_to_first();
	Follower* index = _Friends->get_current();

	while (index)
	{
		if (index->GetEmail() == email)
		{
			delete index;
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

Message Follower::SendMessage(string name, string email, string content)
{
	return *new Message(name, email, content);
}
 
int Follower::CountMessages() const
{
	return _MessageBox->get_size();
}


/*
int main()
{
	//Message* msg1 = new Message("alibaba", "shodedim", "tellmestory");
	//Message* msg2 = new Message("eli", "yossi", "chupar me la");
	//Message* msg3 = new Message("Sneh", "Shussman", "fuck me");

	Message msg1("alibaba", "shodedim", "tellmestory");
	Message msg2("eli", "yossi", "chupar me la");
	Message msg3("Sneh", "Shussman", "fuck me");


	Follower F1("f1", "f1@walla","1234");
	//Follower F2("f2", "f2@walla", "4321");
	//Follower F3("f3", "f2@walla", "qwerty");
	cout << F1.GetName() << " " << F1.GetEmail() << "\n";
	if (F1.isPassword("1234"))
		cout << "alright my man!\n";

	F1.AddFriendRequest("dude1@");
	F1.AddFriendRequest("dude2@");
	F1.AddFriendRequest("dude3@");
	//F1.DisplayFriendRequests();
	cout << F1.CountFriendRequests() << "\n";
	F1.AcceptedFriendRequest("dude1@");
	F1.AcceptedFriendRequest("dude2@");
	F1.AcceptedFriendRequest("dude3@");
	//cout << F1.CountFriendRequests() << "\n";
	cout << "Before remove\n";
	F1.DisplayFriendList();
	cout << "\n";
	F1.RemoveFriend("dude1@");
	cout << "After removal\n";
	F1.DisplayFriendList();
	cout << "\n";
	F1.DisplayFriendRequests();


	F1.AddMessage(msg1);
	F1.AddMessage(msg2);
	F1.AddMessage(msg3);
	F1.ShowMessageList();
	cout << "\nThe message:\n\n";
	F1.ReadMessage(3);


	F1.ShowMessageList();
	cout << "\nThree messages:\n\n";
	cout << F1.CountMessages();


	
	//cout << F2.GetName() << " " << F2.GetEmail << "\n";
	return 0;
}
*/