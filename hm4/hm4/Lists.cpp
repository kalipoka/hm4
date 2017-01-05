#include<iostream>
#include "Lists.H"
#include "Message.H"

using std::cout;

void list::prepend(Message& f) {                    //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	Node* temp = new Node; // allocation
	temp->next = h;
	temp->data = &f;  //  NEW Syntax 
	h = temp;
	list::size = list::size++;
}
/* this function works for int - need special modifications for other types*/
void list::print() const {
	Node* temp = h;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}
 
void list::delete_head() {
	Node* temp = h;
	h = h->next;
	delete temp;                   //free memory
}

void list::release() {
	while (h != 0)
		delete_head();
}

void list::go_to_first() {
	list::iterator = list::h;
}

void list::next() {
	list::iterator = list::iterator->next;
}

Message* list::get_current() {                          //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	return list::iterator->data;
}

int list::get_size() {                          
	return list::size;
}

void list::delete_current() {

	if (list::iterator == list::h)
		list::delete_head();
	else
	{
		Node* temp = list::h;
		while (temp->next != list::iterator)                //searching for the element before the deleted one
		{
			temp = temp->next;
		}
		//here we found the element that is previous to the one that we need to delete
		temp->next = list::iterator->next;
		delete (list::iterator);
		list::size--;
		list::iterator = NULL;
	}
}
/*
int main() {
		list w;
		//Message tmp1;

		Message msg1("Bibi", "Netantyao", "ElOr");
		Message msg2("alibaba", "shodedim", "tellmestory");
		Message msg3("Shakira", "Eminem", "Soy Mujera");
		Message msg4("Betty", "Bam", "ohevet bambam");
		
		w.prepend(msg1);
		w.prepend(msg2);
		
		w.go_to_first();
		w.prepend(msg3);
		w.print();
		w.prepend(msg4);
		w.go_to_first();
		w.next();
		w.delete_current();
		//w.release();
	
	return 0;
}
*/