#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include "defs.H"


class Follower {
public:
	Follower(string name, string email, string password);
	~Follower();

    string GetName() const;
	string GetEmail() const;
	bool isPassword(string password) const;

	// To do
private:
    // To do
};


// Aid Functions ?

#endif
