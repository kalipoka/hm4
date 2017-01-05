#include<iostream>
#include "Lists.H"
#include "Message.H"

using std::cout;

/*LIST FOR MESSAGES*/

void list_m::prepend(Message& m) {
	Node_m* temp = new Node_m; // allocation
	temp->next = h;
	temp->data = &m;  //  NEW Syntax 
	h = temp;
	list_m::size = list_m::size++;
}
/* this function works for int - need special modifications for other types*/

void list_m::print() const {
	Node_m* temp = h;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}
 
void list_m::delete_head() {
	Node_m* temp = h;
	h = h->next;
	delete temp;                   //free memory
}

void list_m::release() {
	while (h != 0)
		delete_head();
}

void list_m::go_to_first() {
	list_m::iterator = list_m::h;
}

void list_m::next() {
	list_m::iterator = list_m::iterator->next;
}

void* list_m::get_current() {                          //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	return list_m::iterator->data;
}

int list_m::get_size() {                          
	return list_m::size;
}

void list_m::delete_current() {

	if (list_m::iterator == list_m::h)
		list_m::delete_head();
	else
	{
		Node_m* temp = list_m::h;
		while (temp->next != list_m::iterator)                //searching for the element before the deleted one
		{
			temp = temp->next;
		}
		//here we found the element that is previous to the one that we need to delete
		temp->next = list_m::iterator->next;
		delete (list_m::iterator);
		list_m::size--;
		list_m::iterator = NULL;
	}
}

/*LIST FOR FOLLOWERS*/

void list_f::prepend(Follower& f) {
	Node_f* temp = new Node_f; // allocation
	temp->next = h;
	temp->data = &f;  //  NEW Syntax 
	h = temp;
	list_f::size = list_f::size++;
}
/* this function works for int - need special modifications for other types*/

void list_f::print() const {
	Node_f* temp = h;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}
void list_f::delete_head() {
	Node_f* temp = h;
	h = h->next;
	delete temp;                   //free memory
}

void list_f::release() {
	while (h != 0)
		delete_head();
}

void list_f::go_to_first() {
	list_f::iterator = list_f::h;
}

void list_f::next() {
	list_f::iterator = list_f::iterator->next;
}

void* list_f::get_current() {                          //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	return list_f::iterator->data;
}

int list_f::get_size() {
	return list_f::size;
}

void list_f::delete_current() {

	if (list_f::iterator == list_f::h)
		list_f::delete_head();
	else
	{
		Node_f* temp = list_f::h;
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


/*LIST FOR LEADERS*/

void list_l::prepend(Leader& f) {
	Node_l* temp = new Node_l; // allocation
	temp->next = h;
	temp->data = &f;  //  NEW Syntax 
	h = temp;
	list_l::size = list_l::size++;
}
/* this function works for int - need special modifications for other types*/

void list_l::print() const {
	Node_l* temp = h;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}

void list_l::delete_head() {
	Node_l* temp = h;
	h = h->next;
	delete temp;                   //free memory
}

void list_l::release() {
	while (h != 0)
		delete_head();
}

void list_l::go_to_first() {
	list_l::iterator = list_l::h;
}

void list_l::next() {
	list_l::iterator = list_l::iterator->next;
}

void* list_l::get_current() {                          //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	return list_l::iterator->data;
}

int list_l::get_size() {
	return list_l::size;
}

void list_l::delete_current() {

	if (list_l::iterator == list_l::h)
		list_l::delete_head();
	else
	{
		Node_l* temp = list_l::h;
		while (temp->next != list_l::iterator)                //searching for the element before the deleted one
		{
			temp = temp->next;
		}
		//here we found the element that is previous to the one that we need to delete
		temp->next = list_l::iterator->next;
		delete (list_l::iterator);
		list_l::size--;
		list_l::iterator = NULL;
	}
}

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

		Message *tmp4 = w.get_current();
		w.delete_current();
		w.release();
		
		//w.prepend(6);
		//w.prepend(10);
		//w.prepend(15);
		//w.print();
		//w.go_to_first();
		//w.next();
		//int temp = w.get_current();
		//int size = w.get_size();
		//w.delete_current();
		//cout << "deleted\n";
		//w.release();
		//w.print();
		
	}


	return 0;
}

*/