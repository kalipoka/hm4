#ifndef _LEADER_H_
#define _LEADER_H_

#include "defs.H"
#include "Follower.H"

class Leader : public Follower
{
public:
	Leader(string name, string email, string password);
	~Leader();

	void AddFollower(Follower& Friend);
	int CountFollowers();
	void RemoveFollower(Follower& Friend);
	void BroadcastMessage(Message& TheMessage);
	bool isFollower(string mail);

protected:
	list_f *_Followers;           
};


#endif
