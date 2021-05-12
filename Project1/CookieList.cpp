/*
    Group No Idea
    Alvarez, Mauricio (41298)
    Nguyen, Thu (41298)

    Date (month in letters)

    CS A250
    Project 1
*/

#include "CookieList.h"

#include <iostream>

#include <iomanip>

using namespace std;

// Function addCookie
	void CookieList::addCookie(const Cookie& aCookie){
        last->setNext(new Node(aCookie, nullptr));
        last = last->getNext();
    }
	//addCookie overloaded
	void CookieList::addCookie(const std::string& newName, size_t newCalories,
		const std::set<std::string>& newIngredients, size_t newServings){
            Cookie(newName, newCalories, newIngredients, newServings);
            last->setNext(new Node(Cookie(newName, newCalories, newIngredients, newServings), nullptr));
            last = last->getNext();
        }

// Accessor function
	size_t CookieList::getCount() const{
        	return count;
    }

// Boolean functions
	bool CookieList::isEmpty() const{
        	return count == 0;
    }
	bool CookieList::searchCookie(const std::string& aCookie) const{
        Node* currentNode = first;
        bool found = false;

        while(currentNode != nullptr && !found){
            if(currentNode->getCookie().getName() == aCookie){
                found = true;
            }
            currentNode = currentNode->getNext();
        }

        return found;
    }

// Print functions
	void CookieList::printAllCookies() const
	{
	    if(first == nullptr)
	        cerr <<"List is empty";
	    else
	    {
	        for(int i = 0; i < 65; i++)   // we need to print it follow the output of partC!!
                cout << "*";
            cout << endl << setw(38) << "COOKIE RECIPES" << endl; 
            for(int i = 0; i < 65; i++)
                cout << "*";
	        Node* currentNode = first;
	        while( currentNode != nullptr)
	        {
	            cout << setw(26) << currentNode->getCookie().getName() << endl;
	            currentNode = currentNode->getNext();
	        }
	    }
	}
	
//Function clearList
	void CookieList::clearList()
	{  
	    Node* temp = first;
	
	    while (first != nullptr)
	    {
	        first = first->getNext();
	        delete temp;
	        temp = first;
	    }
	    last = nullptr;
	    count = 0;
	}
// The Big Three
	CookieList::CookieList(const CookieList& otherCookieList)
	{
		count = otherCookieList.count;
	    first = otherCookieList.first;
	    last = otherCookieList.last;
	    while(first != nullptr)
	    {
	        addCookie(first->getCookie());
            first = first->getNext();
		    count++; 
	    }
	}
	CookieList& CookieList::operator=(const CookieList& otherCookieList)	
	{
		if(count == 0) 
		{
	    		copyCallingObjIsEmpty(otherCookieList);
		}
		
		//if( &otherCookieList == this) // check for two object are the same??
		//{
			//cerr << "Attempted assignment to itself." <<endl;
		//}
		else if (count != otherCookieList.count) //check for same length
		{
			if (count > otherCookieList.count) //longer
				copyCallingObjLonger(otherCookieList);
			else
				copyCallingObjShorter(otherCookieList); //shorter
		}
		copyObjectsSameLength(otherCookieList);
		
		return *this;
	}
	//Part C
	void printCookiesSelection() const;
	void printRecipe(size_t cookieSelect)
	{
	void CookieList::printLimitedCalories(size_t maxOfCalo)
	{
		Node* current = first;
		while(current != nullptr)
		{
			if(current->getCookie().getCalories() <= maxOfCalo)
				printCalories();
		}
	}
		
	
	CookieList::~CookieList()
	{
	   clearList();
	}

//helper Function
//Function copy
void CookieList::copyCallingObjIsEmpty(const CookieList& otherCookieList)
{
    Node* temp = otherCookieList.first;
    while(temp != nullptr)
    {
        addCookie(temp->getCookie());
        temp = temp->getNext();
		count++; 
    }
}

//Function copyObjectsSameLength
void CookieList::copyObjectsSameLength(const CookieList& otherCookieList)
{
    Node* temp = otherCookieList.first;
    Node* tempCalling = first;
    while(temp!= nullptr)
    {
        tempCalling->setCookie(temp->getCookie());
		temp = temp->getNext();
		tempCalling = tempCalling->getNext();
    }
}

void CookieList::copyCallingObjLonger(const CookieList& otherCookieList){
	Node* temp = otherCookieList.first;
    	Node* tempCalling = first;
	Node* prev = nullptr;
    while(temp!= nullptr)
    {
        tempCalling->setCookie(temp->getCookie());
		temp = temp->getNext();
		prev = tempCalling;
		tempCalling = tempCalling->getNext();
    }

	last = prev;
	
	while(tempCalling != nullptr){
		tempCalling = tempCalling->getNext();
		prev = tempCalling;
		prev->setNext(nullptr);
		delete prev;
		count--;
	}
}

void CookieList::copyCallingObjShorter(const CookieList& otherCookieList){
	Node* temp = otherCookieList.first;
	Node* tempCalling = first;

    while(tempCalling != nullptr)
    {
        tempCalling->setCookie(temp->getCookie());
		temp = temp->getNext();
		tempCalling = tempCalling->getNext();
    }
	while(temp != nullptr){
		addCookie(temp->getCookie());
		temp = temp->getNext();
		count++;
	}
}







