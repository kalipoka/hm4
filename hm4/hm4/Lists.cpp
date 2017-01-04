#include<iostream>
#include "Lists.H"
#include "Message.H"

using std::cout;

void list::prepend(Message& f) {                    //$$$$$$$$$$$$$$$ int only for testing - change to Follower later
	listelem* temp = new listelem; // allocation
	temp->next = h;
	temp->data = &f;  //  NEW Syntax 
	h = temp;
	list::size = list::size++;
}
/* this function work for int - need special modifications for other types
void list::print() const {
	listelem* temp = h;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}
*/ 
void list::delete_head() {
	listelem* temp = h;
	h = h->next;
	//delete temp->data;
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
		listelem* temp = list::h;
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

int main() {
	list *p; {
		list w;
		Message *tmp1,*tmp2;
		tmp1 = new Message("alibaba", "shodedim", "tellmestory"); // aloocita
		tmp2 = new Message("Shakira", "Eminem", "Soy Mujera"); // aloocita

		
		w.prepend(*tmp1);
		w.go_to_first();
		w.prepend(*tmp2);
		w.print();
		/*
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
		*/
	}

	return 0;
}