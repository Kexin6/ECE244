#include <galaxy-explorer/AsteroidList.hpp>
#include <signal.h>

AsteroidListItem::AsteroidListItem() {
    this->next = nullptr;
    this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    this->data = new Asteroid(a);
}

AsteroidListItem::~AsteroidListItem() {
    this->next = nullptr;
    delete this->data;
    this->data = nullptr;
    
}

AsteroidList::AsteroidList() {
    head.setNext(nullptr);
}

// Copy constructor
AsteroidList::AsteroidList(const AsteroidList& src) {
    // The functions in this class are listed in a suggested order of implementation,
    // except for this one and the destructor (because you should put all your constructors together).
    if(src.head.hasNext()) {
        const AsteroidListItem* ptr = src.head.getNext();
        AsteroidListItem* last = nullptr;
        AsteroidListItem* nptr = nullptr;
        while (ptr != nullptr) {
            nptr = new AsteroidListItem(ptr->getData());
            
            if (last == nullptr) {
                head.setNext(nptr);
            } else {
                last->setNext(nptr);   
            }
            ptr = ptr->getNext();
            last = nptr;
        }
        
    } else {
        head.setNext(nullptr);
    }
   
}

AsteroidList::~AsteroidList() {
    // The functions in this class are listed in a suggested order of implementation,
    // except for this one and the copy constructor (because you should put all your constructors together).
    AsteroidListItem* ptr;
    while (head.getNext() != nullptr) {
        ptr = head.getNext();
        head.setNext(ptr->getNext());
        delete ptr;
    }
    head.setNext(nullptr);
}

// Add an asteroid at the beginning of the list
void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem* nptr = new AsteroidListItem(e);
    if (head.hasNext()) {
        nptr->setNext(begin());
    }
    head.setNext(nptr);
   
}

// Return a reference to the first asteroid
Asteroid& AsteroidList::front() {
    if (head.hasNext()) {
        return head.getNext()->getData();
    } else {
        return *(Asteroid*)nullptr;
    }
}

const Asteroid& AsteroidList::front() const {
    if (head.hasNext()) {
        return head.getNext()->getData();
    } else {
        return *(Asteroid*)nullptr;
    }
}

bool AsteroidList::isEmpty() const {
    if (head.hasNext()) {
       return false;
    } else {
       return true;
    }
	
}

// Determine the number of nodes in the list
int AsteroidList::size() const {
    int count = 0;
    const AsteroidListItem* ptr = begin(); 
    if (isEmpty()) {
       return 0;
    } 
    
    while(ptr != nullptr) {
        count ++;
        ptr = ptr -> getNext();
    }
    
    return count;
}

// Return an item corresponding to the position before the first asteroid
AsteroidListItem* AsteroidList::beforeBegin() {
    return &head; 
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
    return &head; 
}

// Return the item corresponding to the first asteroid
AsteroidListItem* AsteroidList::begin() {
    return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
    return head.getNext();
}


// Return the item corresponding to the position of the last asteroid
AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem* ptr = head.getNext();
    AsteroidListItem* pptr = head.getNext();
    while(ptr != nullptr) {
        pptr = ptr;
        ptr = ptr->getNext();
    }
    return pptr;

}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    const AsteroidListItem* ptr = head.getNext();
    const AsteroidListItem* pptr = head.getNext();
    while(ptr != nullptr) {
        pptr = ptr;
        ptr = ptr->getNext();
    }
    return pptr;
}


// Returns node coming after the next node
AsteroidListItem* AsteroidList::end() {
	return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
	return nullptr;
}

/**
* Add a single asteroid to this list, in the position immediately after `prev`.
* returns the item that was inserted
*/
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem* ptr = new AsteroidListItem(e);
    ptr->setNext(prev->getNext());
    prev->setNext(ptr);
    return ptr;

}

/*
 * Add independent copies of the entities in `others` to this list, placed immediately after `insertion_point`,
 * in the same order as `others`.
 * Returns the last item that was inserted, or `insertion_point' if `others' is empty.
 */
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    if(!others.head.hasNext()) {
        return prev;
    }
    const AsteroidListItem* ptr = others.head.getNext();
    AsteroidListItem* temp = prev->getNext();
    while (ptr != nullptr) {
        prev->setNext(new AsteroidListItem(ptr->getData()));
        prev = prev->getNext();
        ptr = ptr->getNext();
    }
    prev->setNext(temp);
    return prev;
}
 

/** 
 * Given a position in this list, delete the following asteroid.
 * Returns the list item that followed the erased item, or end() if there wasn't one.
 * This function may have ANY BEHAVIOUR if there is no asteroid after `prev`.
 */
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    if (isEmpty()) {
        return nullptr;
    }
    if(prev->getNext() == nullptr) {
        return end();
    }
    AsteroidListItem* ptr = prev->getNext()->getNext();
    delete prev->getNext();
    prev->setNext(ptr);
    return ptr;
}




 // free all nodes
void AsteroidList::clear() {
    AsteroidListItem* ptr = head.getNext();
    AsteroidListItem* pptr = nullptr;
    if (!head.hasNext()) {
        return;
    } else {
        while(ptr != nullptr) {
            pptr = ptr;
            ptr = ptr->getNext();
            delete pptr;
        }
    }
    head.setNext(nullptr);
}


AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    if (this == &src) {
        return (*this);
    }
    this->clear();
    this->insertAfter(&head, src);
    return (*this);
}

