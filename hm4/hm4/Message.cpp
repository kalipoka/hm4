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
MessageBox::MessageBox(Node_m* h, Node_m* iterator, int size, int num_of_unread) :list_m() {}


void MessageBox::Print()
{
	Message* tmp;
	MessageBox::go_to_first();  // we go to the 1st
	tmp = MessageBox::get_current();
	int size = MessageBox::get_size();

	while (tmp != NULL && size > 0 ) {
		tmp->Display(2);                  // fix the number later; &&&&&&&&
		MessageBox::next();
		size--;
		if ( size > 0 )                         // patch  of liiegal memory fck
			tmp = MessageBox::get_current();         
	}
}

int MessageBox::UnreadSize()
{
	Message* tmp;
	MessageBox::go_to_first();  // we go to the 1st
	tmp = MessageBox::get_current();
	int mone = 0;
	int size = MessageBox::get_size();

	while (tmp != NULL && size > 0) {
		if (tmp->isRead() == false)               // fix the number later; &&&&&&&&
			mone++;
		MessageBox::next();
		size--;
		if (size > 0)                         // patch  of liiegal memory fck
			tmp = MessageBox::get_current();
	}
	
	return mone;
}

/*
void MessageBox::Add(Message m)
{
	MessageBox::prepend(m);
}
*/


int main() {

	Message msg("alibaba", "shodedim", "tellmestory");
	Message msg2("eli", "yossi", "chupar me la");
	Message msg3("Sneh", "Shussman", "fuck me");
	Message* tmp;
	MessageBox box(NULL, NULL, 0, 0);

	msg.Read();

	box.prepend(msg);
	box.prepend(msg2);
	box.prepend(msg3);
	int size = box.get_size();
	box.go_to_first();
	tmp = box.get_current();
	int unread = box.UnreadSize();
	//tmp->Display(3);
	//tmp->Display(3);

	//box.Print();
	
	/*
	msg.Display(3);
	msg.Read();
	msg.Display(3);
	bool is_read = msg.isRead();
	*/


	return 0;
}
