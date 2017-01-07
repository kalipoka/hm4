#include <iostream>
#include "Message.H"

/*************************************
* The Constructor of the Message
*
**************************************/
Message::Message(string source, string subject, string content) : source_(source), subject_(subject), content_(content), read_(false) {}

/*************************************
* Displays othe Message
*
**************************************/
void Message::Display(int num) const
{
	cout << num << ") "<< (read_ ? "" : "(Unread) ") << "From: " << source_ << endl;
	cout << "Subject: " << subject_ << endl;
}
/*************************************
* Reads the Message
*
**************************************/
void Message::Read()
{
    read_ = true;
	cout << "From: " << source_ << endl;
	cout << "Subject: " << subject_ << endl;
	cout << "Content: " << content_ << endl;
}
/*************************************
* Bool - cheks if the message is read
*
**************************************/
bool Message::isRead()
{
	return read_;
}

/*******************************************************
*The message box class - contains message and some very cool operations
*
*********************************************************/

/*************************************
*The constructor of the Message box
*
**************************************/
MessageBox::MessageBox(Node_m* h=NULL, Node_m* iterator=NULL, int size=0) :list_m() {}

/*************************************
* Prints all the messages in the box
*
**************************************/
void MessageBox::Print()
{
	Message* tmp;
	MessageBox::go_to_first();  // we go to the 1st
	tmp = MessageBox::get_current();
	int size = MessageBox::get_size();
	int mone = 1;
	while (tmp != NULL && size > 0 ) {
		tmp->Display(mone);                  // fix the number later; &&&&&&&&
		MessageBox::next();
		mone++;
		size--;
		if ( size > 0 )                         // patch  of liiegal memory fck
			tmp = MessageBox::get_current();         
	}
}

/*************************************
*This function Gives the  ammount of unreaded messages
*
**************************************/
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


/*************************************
*this function Reads a specific Message
*
**************************************/
Result MessageBox::ReadMessage(int messageNum) 
{
	int size = MessageBox::get_size();
	if (messageNum > size)                   // no such message;
		return FAILURE;

	Message* tmp;
	MessageBox::go_to_first();  // we go to the 1st
	tmp = MessageBox::get_current();            // on the current message
	
	int mone = 1;

	while (mone <= size) {
		if (mone == messageNum) {
			tmp->Read();             // Do I need to mark the readed??
			return SUCCESS;
		}              
		MessageBox::next();
		tmp = MessageBox::get_current();
		mone++;
		//if (size > 0)                         // patch  of liiegal memory fck
			//tmp = MessageBox::get_current();
	}
	return FAILURE;
}


/*
int main() {

	Message msg("alibaba", "shodedim", "tellmestory");
	Message msg2("eli", "yossi", "chupar me la");
	Message msg3("Sneh", "Shussman", "fuck me");
	Message* tmp;
	MessageBox box(NULL, NULL, 0);

	msg.Read();
	box.prepend(msg);
	box.prepend(msg2);
	box.prepend(msg3);
	int size = box.get_size();
	box.go_to_first();
	tmp = box.get_current();
	int unread = box.UnreadSize();
	box.ReadMessage(1);
	box.ReadMessage(1);
	box.ReadMessage(2);
	box.ReadMessage(3);
	box.ReadMessage(6);
	int unread1 = box.UnreadSize();

	//tmp->Display(3);
	//tmp->Display(3);

	//box.Print();
	
	/*
	msg.Display(3);
	msg.Read();
	msg.Display(3);
	bool is_read = msg.isRead();
	
	return 0;
}
*/