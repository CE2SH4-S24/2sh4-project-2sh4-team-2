#include "objPosArrayList.h" 

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

// Constructor: initializes the list with a maximum capacity and sets the current size to 0
objPosArrayList::objPosArrayList() : sizeList(0), sizeArray(ARRAY_MAX_CAP) {
    aList = new objPos[ARRAY_MAX_CAP];
}

// Destructor: deallocates the dynamically allocated array
objPosArrayList::~objPosArrayList() {
    delete[] aList;
}

// Returns the current number of elements in the list
int objPosArrayList::getSize() {
    return sizeList;
}

// Inserts an element at the head of the list, shifts other elements to the right
void objPosArrayList::insertHead(objPos thisPos) {
    if (sizeList < ARRAY_MAX_CAP) {// Ensure there's space in the array
        for (int i = sizeList; i > 0; i--) { 
            aList[i] = aList[i - 1];  // Shift elements to the right
        }
        aList[0] = thisPos; // Insert new element at the head
        sizeList++;// Increment size of the list
    }
}

// Removes the element at the head of the list, shifts other elements to the left
void objPosArrayList::removeHead() {
    if (sizeList > 0) {// Ensure the list is not empty
        for (int i = 0; i < sizeList - 1; i++) {
            aList[i] = aList[i + 1];// Shift elements to the left
        }
        sizeList--;
    }
}

// Inserts an element at the tail of the list
void objPosArrayList::insertTail(objPos thisPos) {
    if (sizeList < ARRAY_MAX_CAP) {
        aList[sizeList] = thisPos;// Insert new element at the tail
        sizeList++;
    }
}

// Removes the element at the tail of the list
void objPosArrayList::removeTail() {
    if (sizeList > 0) {
        sizeList--;
    }
}

void objPosArrayList::clear() {
    while (getSize() > 0) {
        removeTail();
    }
}

void objPosArrayList::getHeadElement(objPos& returnPos) {
    if (sizeList > 0) {
        returnPos = aList[0];// Return the head element
    }
}

// Retrieves the element at the tail of the list
void objPosArrayList::getTailElement(objPos& returnPos) {
    if (sizeList > 0) {
        returnPos = aList[sizeList - 1];// Return the tail element
    }
}

// Retrieves the element at the specified index of the list
void objPosArrayList::getElement(objPos& returnPos, int index) {
    if (index >= 0 && index < sizeList) {
        returnPos = aList[index];
    }
    else
    {
        returnPos = objPos {-1, -1, '\0'};// Return an invalid position if index is out of bounds
    }
}

void objPosArrayList::removeElement(int index) {
    if (index >= 0 && index < sizeList) {
        for (int i = index; i < sizeList - 1; i++) {
            aList[i] = aList[i + 1]; // Shift elements to the left
        }
        sizeList--; // Decrement size of the list
    }
}
