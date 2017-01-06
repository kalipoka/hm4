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
		if (index->GetEmail() == Friend.GetEmail() && index->GetName() == Friend.GetName())
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

bool Leader::isFollower(string mail)
{
	_Followers->go_to_first();
	Follower* index = _Followers->get_current();

	while (index)
	{
		if (!index->GetEmail().compare(mail))
			return true;
		_Followers->next();
		index = _Followers->get_current();
	}
	return false;
}

/*
int main()
{
	//Message* msg1 = new Message("alibaba", "shodedim", "tellmestory");
	//Message* msg2 = new Message("eli", "yossi", "chupar me la");
	//Message* msg3 = new Message("Sneh", "Shussman", "fuck me");

	Message msg1("f1@walla", "tellmegood", "tellmestory");
	Message msg2("eli", "yossi", "chupar me la");
	Message msg3("Sneh", "Shussman", "fuck me");


	Leader F1("f1", "f1@walla", "1234");
	Follower F2("f2", "f2@walla", "4321");
	Follower F3("f3", "f2@walla", "qwerty");
	
	cout << F1.GetName() << " " << F1.GetEmail() << "\n";
	if (F1.isPassword("1234"))
	cout << "alright my man!\n";
	

	F1.AddFriendRequest(F2);
	F1.AddFriendRequest(F3);

	F1.DisplayFriendRequests();
	cout << F1.NumFriendRequests() << "\n";

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
	cout << F1.NumUnreadMessages() << "\n";
	

	F1.AddFollower(F2);
	F1.AddFollower(F3);
	cout << "\nTwo Followers:\n";
	cout << F1.CountFollowers() << "\n";
	F1.BroadcastMessage(msg1);

	F2.ShowMessageList();
	F1.RemoveFollower(F3);
	F1.RemoveFollower(F2);
	F3.ShowMessageList();
	cout << "\nNo Followers:\n";
	cout << F1.CountFollowers() << "\n";
	//cout << F2.GetName() << " " << F2.GetEmail << "\n";
	return 0;
}
*/