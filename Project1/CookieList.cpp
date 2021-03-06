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
void CookieList::addCookie(const Cookie& aCookie)
{
	if( count == 0)
	{
		first = new Node(aCookie, nullptr);
		first = last;
	}
	else
	{
		last->setNext(new Node(aCookie, nullptr));
		last = last->getNext();
	}
	count++;
}

//addCookie overloaded
void CookieList::addCookie(const std::string& newName, size_t newCalories,
		const std::set<std::string>& newIngredients, size_t newServings)
{
	Cookie aCookie(newName, newCalories, newIngredients, newServings);
	addCookie(aCookie);
}

// Accessor function
size_t CookieList::getCount() const
{
	return count;
}

// Boolean functions
bool CookieList::isEmpty() const
{
	return count == 0;
}

bool CookieList::searchCookie(const std::string& aCookie) const
{
	Node* currentNode = first;
	bool found = false;

        while(currentNode != nullptr && !found)
	{
		if(currentNode->getCookie().getName() == aCookie)
		{
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
	        Node* currentNode = first;
	        while( currentNode != nullptr)
	        {
	            cout << setw(26) << currentNode->getCookie().getName() << endl;
	            currentNode = currentNode->getNext();
	        }
	}
}

void CookieList::printCalories(size_t cookieSelection)
{
	Node* location = getCookieLocation(cookieSelection);
	location->getCookie().printCalories();
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

//partC
void CookieList::printCookiesSelection() const
{
	int count = 1;
	Node* current = first;
	while(current != nullptr)
	{
		cout << count << ": " << current->getCookie().getName() << endl;
		count++;
		current = current->getNext();
	}
}

void CookieList::printRecipe(size_t cookieSelect)
{
	Node* location = getCookieLocation(cookieSelect);
	location->getCookie().printRecipe();
}

void CookieList::printLimitedCalories(size_t maxOfCalo)
{
	Node* current = first;
	while(current != nullptr)
	{
		if(current->getCookie().getCalories() <= maxOfCalo)
		current->getCookie().printCalories();
		current = current->getNext();
	}
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
	if(&otherCookieList == this) //check if 2 obj are the same
	{
		cerr << "Attempted assignment to itself.";
	}
	else
	{
		if( count == 0) 
			copyCallingObjIsEmpty(otherCookieList);
		else if (count == otherCookieList.count) 
			copyObjectsSameLength(otherCookieList);
		else if(count > otherCookieList.count) 
			copyCallingObjLonger(otherCookieList);
		else if(count < otherCookieList.count)
			copyCallingObjShorter(otherCookieList);
	}
	return *this;
}
	
CookieList::~CookieList()
{
   clearList();
}

// private Part C 
Node* CookieList::getCookieLocation(size_t cookieSelect) const
{
	Node* temp = first;
	for( int i = 1; i < cookieSelect; i++)
	{
		temp = temp->getNext();
	}
	return temp;	
}

//helper Function
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

void CookieList::copyCallingObjLonger(const CookieList& otherCookieList)
{
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
	
	while(tempCalling != nullptr)
	{
		tempCalling = tempCalling->getNext();
		prev = tempCalling;
		prev->setNext(nullptr);
		delete prev;
		count--;
	}
}

void CookieList::copyCallingObjShorter(const CookieList& otherCookieList)
{
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
