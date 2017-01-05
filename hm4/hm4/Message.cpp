#include <iostream>
#include "Message.H"


Message::Message(string source, string subject, string content) : source_(source), subject_(subject), content_(content), read_(false) {}

void Message::Display(int num) const
{
	cout << num << ") "<< (read_ ? "" : "(Unread) ") << "From: " << source_ << endl;
	cout << "Subject: " << subject_ << endl;
}

void Message::Read()
{
    read_ = true;
	cout << "From: " << source_ << endl;
	cout << "Subject: " << subject_ << endl;
	cout << "Content: " << content_ << endl;
}

bool Message::isRead()
{
	return read_;
}


int main() {

	Message msg("alibaba", "shodedim", "tellmestory");
	msg.Display(3);
	msg.Read();
	msg.Display(3);
	bool is_read = msg.isRead();

	return 0;
}
