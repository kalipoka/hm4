#include<iostream>
#include "Lists.H"
#include "Message.H"

using std::cout;

void list::prepend(Message& f) {                    //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	Node* temp = new Node; // allocation
	temp->next = head;
	temp->data = &f;  //  NEW Syntax 
	head = temp;
	list::size = list::size++;
}
/* this function works for int - need special modifications for other types*/
void list::print() const {
	Node* temp = head;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}
 
void list::delete_head() {
	Node* temp = head;
	head = head->next;
	//delete temp->data;
	delete temp;                   //free memory
}

void list::release() {
	while (head != 0)
		delete_head();
}

void list::go_to_first() {
	list::iterator = list::head;
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
		delete (list::iterator);
		list::size--;
		list::iterator = NULL;
	}
}

// here start implementation of follower list &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
/*
void list_f::prepend(Follower& f) {                    
	Node_f* temp = new Node_f; // allocation
	temp->next = head;
	temp->data = &f;  //  NEW Syntax 
	head = temp;
	list_f::size = list_f::size++;
}
/* this function works for int - need special modifications for other types
void list_f::print() const {
	Node_f* temp = head;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}

void list_f::delete_head() {
	Node_f* temp = head;
	head = head->next;
	//delete temp->data;
	delete temp;                   //free memory
}

void list_f::release() {
	while (head != 0)
		delete_head();
}

void list_f::go_to_first() {
	list_f::iterator = list_f::head;
}

void list_f::next() {
	list_f::iterator = list_f::iterator->next;
}

Follower* list_f::get_current() {                          //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	return list_f::iterator->data;
}

int list_f::get_size() {
	return list_f::size;
}

void list_f::delete_current() {

	if (list_f::iterator == list_f::head)
		list_f::delete_head();
	else
	{
		Node_f* temp = list_f::head;
		while (temp->next != list_f::iterator)                //searching for the element before the deleted one
		{
			temp = temp->next;
		}
		//here we found the element that is previous to the one that we need to delete
		temp->next = list_f::iterator->next;
		delete (list_f::iterator);
		list_f::size--;
		list_f::iterator = NULL;
	}
}
*/

/*
int main() {
	list *p; {
		list w;
		Message *tmp1,*tmp2,*tmp3;
		tmp1 = new Message("alibaba", "shodedim", "tellmestory"); // aloocita
		tmp2 = new Message("Shakira", "Eminem", "Soy Mujera"); // aloocita
		tmp3 = new Message("Betty", "Bam", "ohevet bambam"); // aloocita

		
		w.prepend(*tmp1);
		w.go_to_first();
		w.prepend(*tmp2);
		w.print();
		w.prepend(*tmp3);
		w.go_to_first();
		w.next();

		Message *curent = w.get_current();
		w.delete_current();
		
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
		w.release();
		//w.print();
		
	}

	return 0;
}
*/