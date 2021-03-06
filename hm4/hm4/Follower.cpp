#include <iostream>
#include "Follower.H"

using std::cout;
/*************************************
* Constructor of the follower
*
**************************************/
Follower::Follower(string name, string email, string password)
{
	_name = name;
	_email = email;
	_password = password;
	_MessageBox = new MessageBox(NULL, NULL, 0);
	_Friends = new list_f;
	_FRequests = new list_f;
}
/*************************************
* Destructor of the follower
*
**************************************/
Follower::~Follower()
{
	_delete_messages_inBox();
	_MessageBox->release();
	_Friends->release();
	_Friends->release();
	delete _MessageBox;
	delete _Friends;
	delete _FRequests;
}
/*************************************
* This function return the name of the follower
*
**************************************/
string Follower::GetName() { return _name; }

/*************************************
*This function return the  email of the follower
*
**************************************/
string Follower::GetEmail() { return _email; }

/*************************************
*Check if the input password is like the real password
*of the user
**************************************/
bool Follower::isPassword(string password)
{
	if (password.compare(_password))
		return false;
	else
		return true;
}
/*************************************
*Displays the friend requests of the follower
*
**************************************/
void Follower::DisplayFriendRequests()
{
	_FRequests->go_to_first();
	Follower* index = _FRequests->get_current();
	int i = 0;
	while (index)
	{
		cout << SHOW_FRIEND_REQUESTS_SUCCESS << "\n";
		i++;
		_FRequests->next();
		index = _FRequests->get_current();
	}
}
/*************************************
*Displays the frined list of the follower
*
**************************************/
void Follower::DisplayFriendList()
{
	_Friends->go_to_first();
	Follower* index = _Friends->get_current();
	int i = 0;
	while (index)
	{
		cout << SHOW_FRIEND_LIST_SUCCESS << "\n";
		i++;
		_Friends->next();
		index = _Friends->get_current();
	}
}
/*************************************
*Add a friend request to the follower
*
**************************************/
void Follower::AddFriend(Follower& Friend)
{
	_Friends->prepend(Friend);
}
/*************************************
*Add a friend request to the follower
*
**************************************/
void Follower::AddFriendRequest(Follower& Friend)
{
	_FRequests->prepend(Friend);
}
/*************************************
* Accepts a friend request
*
**************************************/
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
/*************************************
* Remove a friend from the friend list of the follower
*
**************************************/
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
/*************************************
*Removes a friend from the friend list of the follower
*
**************************************/
int Follower::NumFriendRequests() const
{
	return _FRequests->get_size();
}
/*************************************
*Shows the message list of the follower
*
**************************************/
void Follower::ShowMessageList() const
{
	_MessageBox->Print();
}
/*************************************
*Add a message to the messgae box of the follower
*
**************************************/
void Follower::AddMessage(Message& newMessage)
{
	Message* tmp = new Message(newMessage);
	_MessageBox->prepend(*tmp);
}
/*************************************
* Reads a message of the follower (if succeeds)
*
**************************************/Result Follower::ReadMessage(int MessageNum) const//<messageNumber>
{
	if (_MessageBox->ReadMessage(MessageNum) == SUCCESS)
		return SUCCESS;
	else
		return FAILURE;     //if message number is too big
}
/*************************************
* Adds a message to a friend who is on the list
*
**************************************/
void Follower::SendMessage(Message& TheMessage, Follower& Friend)
{
	Friend.AddMessage(TheMessage);
}
/*************************************
* Return the number of the unread messages
*
**************************************/
int Follower::NumUnreadMessages() const
{
	return _MessageBox->UnreadSize();
}

/*************************************
* Auxilary function
* Determines us if a certain email belongs to 
* someone on the friendlist
**************************************/
bool Follower::isFriend(string mail)
{
	_Friends->go_to_first();
	Follower* index = _Friends->get_current();

	while (index)
	{
		if (!index->GetEmail().compare(mail))
			return true;
		_Friends->next();
		index = _Friends->get_current();
	}
	return false;
}
/*************************************
* Auxilaty function
* Determins wether a friends request exists
*
**************************************/
bool Follower::isRequestExists(string mail)
{
	_FRequests->go_to_first();
	Follower* index = _FRequests->get_current();

	while (index)
	{
		if (!index->GetEmail().compare(mail))
			return true;
		_FRequests->next();
		index = _FRequests->get_current();
	}
	return false;
}

void Follower::_delete_messages_inBox()
{
	_MessageBox->go_to_first();
	Message* index = _MessageBox->get_current();
	while (index)
	{
		delete index;
		_MessageBox->next();
		index = _MessageBox->get_current();
	}
	return;
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
	Follower F2("f2", "f2@walla", "4321");
	Follower F3("f3", "f2@walla", "qwerty");
	/*
	cout << F1.GetName() << " " << F1.GetEmail() << "\n";
	if (F1.isPassword("1234"))
		cout << "alright my man!\n";
	

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
*/