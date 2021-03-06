#include<iostream>
#include "Lists.H"
#include "Message.H"

using std::cout;

/*LIST FOR MESSAGES*/

/*************************************
* The Constructor of the list
*
**************************************/
list_m::list_m() {
	h = NULL;
	iterator = NULL;
	size = 0;
}

/*************************************
* The Destructor of the list
*
**************************************/
list_m::~list_m() {
	release();
}
/*************************************
* Prepend Function - Adds item to the head of the list
*
**************************************/
void list_m::prepend(Message& m) {
	Node_m* temp = new Node_m; // allocation
	temp->next = h;
	temp->data = &m;  //  NEW Syntax 
	h = temp;
	list_m::size = list_m::size++;
}

/*************************************
* 
*This function prints the content of the list
**************************************/
void list_m::print() const {
	Node_m* temp = h;
	while (temp != 0) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}

/*************************************
*This function delete the head of the list
*
**************************************/
void list_m::delete_head() {
	Node_m* temp = h;
	h = h->next;
	if (size == 1)
		h = NULL;
	delete temp;                   //free memory
}

/*************************************
*This function delete whole list
*
**************************************/

void list_m::release() {
	while (h)
		delete_head();
}

/*************************************
*This function puts the iterator on the head of the list
*
**************************************/
void list_m::go_to_first() {
	list_m::iterator = list_m::h;
}

/*************************************
*This function advances the iterator one step forward
*
**************************************/
void list_m::next() {
	list_m::iterator = list_m::iterator->next;
}

/*************************************
*This function gives us the element that the iterator points to
*
**************************************/
Message* list_m::get_current() {
	if (!list_m::iterator) return NULL;
	return list_m::iterator->data;
}
/*************************************
*This function gives us the size of the list
*
**************************************/
int list_m::get_size() {                          
	return list_m::size;
}
/*************************************
*This function deletes the current element
*
**************************************/

void list_m::delete_current() {

	if (list_m::iterator == list_m::h)
	{
		list_m::delete_head();
		list_m::size--;
		list_m::iterator = NULL;
	}
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
		list_m::iterator = temp->next;
	}
}
/***********************************************************************
* LIST FOR FOLLOWERS begins here - descriptions are the same!!!
*
*************************************************************************/
list_f::list_f() {
	h = NULL;
	iterator = NULL;
	size = 0;
}

list_f::~list_f() {
	release();
}


void list_f::prepend(Follower& f) {
	Node_f* temp = new Node_f; // allocation
	temp->next = h;
	temp->data = &f;  //  NEW Syntax 
	h = temp;
	list_f::size = list_f::size++;
}

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
	if (size == 1)
		h = NULL;
	delete temp;                   //free memory
}

void list_f::release() {
	while (h)
		delete_head();
}

void list_f::go_to_first() {
	list_f::iterator = list_f::h;
}

void list_f::next() {
	list_f::iterator = list_f::iterator->next;
}

Follower* list_f::get_current() {
	if (!list_f::iterator)
		return NULL;
	return list_f::iterator->data;
}

int list_f::get_size() {
	return list_f::size;
}

void list_f::delete_current() {

	if (list_f::iterator == list_f::h) {
		list_f::delete_head();
		list_f::size--;
		list_f::iterator = NULL;
	}
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
		list_f::iterator = temp->next;
	}
}


/***********************************************************************
* LIST FOR LEADER begins here - descriptions are the same as for the first list!!!
*
*************************************************************************/

list_l::list_l() {
	h = NULL;
	iterator = NULL;
	size = 0;
}

list_l::~list_l() {
	release();
}

void list_l::prepend(Leader& f) {
	Node_l* temp = new Node_l; // allocation
	temp->next = h;
	temp->data = &f;  //  NEW Syntax 
	h = temp;
	list_l::size = list_l::size++;
}

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
	if (size == 1)
		h = NULL;
	delete temp;                   //free memory
}

void list_l::release() {
	while (h)
		delete_head();
}

void list_l::go_to_first() {
	list_l::iterator = list_l::h;
}

void list_l::next() {
	list_l::iterator = list_l::iterator->next;
}

Leader* list_l::get_current() {   
	if (!list_l::iterator)
		return NULL;
	return list_l::iterator->data;
}

int list_l::get_size() {
	return list_l::size;
}

void list_l::delete_current() {

	if (list_l::iterator == list_l::h){
		list_l::delete_head();
		list_l::size--;
		list_l::iterator = NULL;
	}
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
		list_l::iterator = temp->next;
	}
}

/*
int main() {

		list_m w;
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
		/*
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
	return 0;
}

*/