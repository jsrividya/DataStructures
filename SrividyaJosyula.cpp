#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include<cstring>

using namespace std;


const int NUMBER_OF_ALPHABETS = 26;
const int NUMBER_OF_MONTHS=12;
const int NUMBER_OF_STATES=4;
const int NUMBER_OF_CITIES=8;
const int lowerBound = 1000;
const int upperBound = 9999;
int randomNumberGenerator(int);
string addressGenerator(int);
int idList[1000];
char alphabets[NUMBER_OF_ALPHABETS] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                                        'h', 'i', 'j', 'k', 'l', 'm', 'n',  
                                        'o', 'p', 'q', 'r', 's', 't', 'u', 
                                        'v', 'w', 'x', 'y', 'z' };
string months[NUMBER_OF_MONTHS] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
string states[NUMBER_OF_STATES] = {"WA", "CO", "TX", "NY"};
string cities[NUMBER_OF_CITIES] = {"SEATTLE", "SPOKANE", "DENVER", "AURORA", "FRISCO", "COMMERCE", "MANHATTAN", "BROOKLYN"};
// A struct to keep items
struct item
{
    string Cust_Name;
    int Cust_Id;
    string Cust_Dob;
    string Cust_address;
    item *next;
    string country;
	item(string x,int x1,string x2,string x3, item* t) // constructor
    {
    	Cust_Name = x;
        Cust_Id = x1;
        Cust_Dob = x2;
        Cust_address = x3;
        next = t;
	}
};
typedef item *link;

class Bag
{
public:
    Bag();							// Construction
    bool add (string name_str,int num_id,string dofb,string address_str);			// Adds a new item to bag
    bool has (int num_id);			// Check if Bag has this item
	bool remove (int num_id);		// Delete customer record of particular id from the bag
    bool remove();                  // Delete last inserted item in the linked list
    bool removeAll();               // Delete all items in the linked list
    unsigned short getCapacity ();	// get the capacity of the Bag. Is there any capacity
    void ListBag();	// void ListBag(string address_str)				// List names and id's of the customer whose address matches with given string.
    unsigned short getSize();		// How many customers in  the Bag has
    //Remove last inserted customer
    //Remove all customer (do not forget to free structs from memory)
    //get bag(int id)
private:
    link first;						// A pointer to show the first node
    link last;						// A pointer to show the last node
    unsigned short size;			// how many items Bag has
};
Bag::Bag() // Initialize an instance of the class
{
    size = 0;
    first = last = NULL; // At the beginning both, first and last are null
    // cout << "A new bag with  " <<  getCapacity()  << " was created...!" << endl ;
}
unsigned short Bag::getSize ()
{
    return size;
}
unsigned short Bag::getCapacity ()
{
    return 30000; // A made-up number.
}
void Bag::ListBag()	// List, print out, all items in the arrays, // make 5 coloumns
{
	cout << "Size of the bag is: "<< size << endl ;
    link it = first;   // it means iterator, visit all items one by one.
	//int i=0;  			// i is used to format the outpur
    while (it != NULL) {
        cout << it->Cust_Name<<"  "<< it->Cust_Id <<"  "<< it->Cust_Dob << "  "<< it->Cust_address << "   "<<endl;
        it = it->next; //next
		//if ( (i+1)%5 == 0) cout << endl;
		//i++;
    }
	cout << endl;
}
bool Bag::add(string name_str,int num_id,string dofb,string address_str)
{
    link AddItem = new item(name_str,num_id,dofb,address_str,NULL);		//  dynamically create a new struct/item
    if ( AddItem == NULL) 
        return false; //Null //may be == first ,if it is full or if it is null		// not enought memory

    if ( first == NULL ) 
        first = AddItem;		// first item to be added
    else last->next = AddItem;					// add to the end of array

    last = AddItem;
	size++;
    return true;	// added.
}
bool Bag::remove(int num_id)		// Delete the str from the bag
{
	link back;
	link front;
	if (first == NULL) return false; //we cant delete anything
	back=front=first; //

	if(first->Cust_Id == num_id) // delete this first or front
	{
		if (first == last) // (last) there is only one item, which will be deleted
			first = last = NULL;
		else
			first = first->next;	// (next) first of many items is being deleted
		delete front; //front is not deleted by OS thats why we need to delete it. if we dont delete this then we are going to have memory leak problems.
        
		size--;
		return true;
	}

	front = front->next;	// if reach this line, the first item of bag is not being deleted.

	while (front != NULL)
	{
		if (front->Cust_Id == num_id) //str
		{
			back->next = front->next;	// a mid-item is being deleted. By-pass the (front)
			if (front == last) 
                last = back; // back  // the last item is being deleted
			delete front;
			size--;
			return true;
		}
		back = front ; //front (guessing)
		front = front -> next; //front
    }
	return	false; // if reach this line, item is not found in the list.
}
bool Bag::remove()		// Delete last inserted item in the linked list
{
	link back;
	link front;
	if (first == NULL) return false; //we cant delete anything
	back=front=first; //

	if(front==last)
	{
		first=back=last=NULL;
		delete front;
		size--;
		return true;
	}
	front=front->next;
	while(front!=NULL)
	{
		front=front->next;
		if(front==last)
		{
			back->next=front->next;
			last=back;
			delete front;
			size --;
			return true;
		}
		back=front;
		front=front->next;
	}
	return false;
}
bool Bag::removeAll() // Delete all items in the linked list
{
	link front;
	if(first==NULL)
		return false;
	front=first;
	while(front!=NULL)
	{
		first=front->next;
		delete front;
		front=first;
	}
	first=last=NULL;
	delete front;
	size --;
    Bag justABag;
    if (justABag.getSize() == 0){
        return true;
    }
    else{
        return false;
    }
}
bool Bag::has(int num_id)   // Check if the bag has item "str", // You can return bool too
{
    link it = first;
    for (int i=0; i < size; i++)
    {
        if (it->Cust_Id == num_id) 
            return true; 
        it = it->next; //next
    }
    return false;
}
int main() 
{
    Bag bigBag,justABag; //object creation
    int str_no,id_to_search,id_to_delete;
    string name="",mon="",day="",year="",dateOfBirth="", personAddress="",street_no="",street_name="",city="",state="";

    srand(time(NULL));
    int n = 10; //length of the string 
    for(int i=0;i<1000;i++) //loop to generate 1000 names of length 10
    {
        name="",mon="",day="",year="",dateOfBirth="", personAddress="",street_no="",street_name="",city="",state="";
        name = toupper(alphabets[rand() % NUMBER_OF_ALPHABETS]); //converts first letter of the string to capital
        for (int i = 1; i < n; i++)
        {  
            name = name + alphabets[rand() % NUMBER_OF_ALPHABETS];
        }
        mon = months[rand() % NUMBER_OF_MONTHS];
        day = to_string(rand() % 30 + 1);
        year = to_string(1900 + rand() % 69 + 20);
        dateOfBirth = mon + " " + day + "," + year ;
        int personID = randomNumberGenerator(i);
        str_no = (rand()%(upperBound-lowerBound + 1)) + lowerBound;
        street_no = to_string(str_no);
        street_name = toupper(alphabets[rand()%NUMBER_OF_ALPHABETS]);
        city = cities[rand()%NUMBER_OF_CITIES];
        state = states[rand()%NUMBER_OF_STATES];
        personAddress = street_no + " " + street_name + " " + "street" + "," + city + "," + state;
        bigBag.add(name,personID,dateOfBirth,personAddress);
        
    }
    bigBag.ListBag();
    cout<<"Enter a person_id between 1000-9999 to delete: ";
    cin>>id_to_delete;
    bool y=bigBag.remove(id_to_delete);
    if(y==1)
    {
        cout<<"Customer's record with ID "<<id_to_delete<<" is deleted successfully!"<<endl;
    }
    else
    {
        cout<<"Customer's record with ID "<<id_to_delete<<" is not found!"<<endl;
    }
    bool z=bigBag.remove(); //delete last inserted item
    if(z==1)
    {
        cout<<"Last inserted item in the list is deleted! "<<endl;
    }
    else
    {
        cout<<"Last inserted item is not deleted! "<<endl;
    }
    //bigBag.ListBag();
    cout<<"Enter a person_id between 1000-9999 to search: " ;
    cin>>id_to_search;
    bool x=bigBag.has(id_to_search);
    if(x==1)
    {
        cout<<"ID FOUND!"<<endl;
    }
    else
    {
        cout<<"Not Found!"<<endl;
    }
    bool s=bigBag.removeAll();
    if(s==1)
    {
        cout<<"All items in the linked list are deleted " <<endl;
    }
    else
    {
        cout<<"Items not deleted! "<<endl; 
    }
    cout<< "New size of the Bag is: "<<justABag.getSize()<<endl;
    
    
    
   return 0; 
}
int randomNumberGenerator(int index){
    int personID = (rand()%(upperBound-lowerBound + 1)) + lowerBound;
    bool idNotExists=true;
    for (int i=0; i<1000; i++)
    {
        if (personID == idList[i])
        {
            idNotExists = false;
            //cout<<"Existing ID generated "<< personID<<endl;
            break;
        }
        
    }
    if (!idNotExists){
        // cout << idExists;
        randomNumberGenerator(index);
    }
    else
    {
        idList[index] = personID;
    }
    return personID;
}