#include<iostream>
#include "Lists.H"
#include "Message.H"

using std::cout;

void list::prepend(Message m) {                    //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	Node* temp = new Node; // allocation
	temp->next = head;
	temp->data = m;
	head = temp;
	list::size = list::size++;
}
/*
void list::print() const {
	listelem* temp = h;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}
*/

void list::delete_head() {
	Node* temp = head;
	head = head->next;
	delete temp;                   //free memory
}
/*
void list::release() {
	while (h != 0)
		delete_head();
}
*/
void list::go_to_first() {
	list::iterator = list::head;
}

void list::next() {
	list::iterator = list::iterator->next;
}

Message list::get_current() {                          //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	return list::iterator->data;
}

int list::get_size() {                          
	return list::size;
}

void list::delete_current() {

	if (list::iterator == list::head)
		list::delete_head();
	else
	{
		Node* temp = list::head;
		while (temp->next != list::iterator)                //searching for the element before the deleted one
		{
			temp = temp->next;
		}
		//here we found the element that is previous to the one that we need to delete
		temp->next = list::iterator->next;
		delete (list::iterator);       //free memory
		list::size--;
		list::iterator = NULL;
	}
}

int main() {
	/*
	list *p; {
		list w;
		w.prepend(4);
		w.prepend(6);
		w.prepend(10);
		w.prepend(15);
		w.print();
		w.go_to_first();
		w.next();
		int temp = w.get_current();
		int size = w.get_size();
		w.delete_current();
		cout << "deleted\n";
		w.print();
	}
	*/
	return 0;
}