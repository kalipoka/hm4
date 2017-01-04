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

//////////////////    Message Box
/*
void MessageBox::Add(Message newMessage)
{
	MessageBox::Msges.prepend(newMessage);
}



int main() {

	Message *tmp1, *tmp2, *tmp3;
	tmp1 = new Message("alibaba", "shodedim", "tellmestory"); // aloocita
	tmp2 = new Message("Shakira", "Eminem", "Soy Mujera"); // aloocita
	tmp3 = new Message("Betty", "Bam", "ohevet bambam"); // aloocita

	MessageBox box;

	box.Add(tmp1);


	return 0;
}
*/