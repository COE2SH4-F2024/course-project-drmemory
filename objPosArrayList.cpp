#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];

}   

// additional constructor

objPosArrayList::objPosArrayList(int aCapacity)
{
    arrayCapacity = aCapacity;
    listSize = 0;
    aList = new objPos[arrayCapacity];
}   

// Copy constructor

objPosArrayList::objPosArrayList(const objPosArrayList& a){

    arrayCapacity = a.arrayCapacity;
    listSize = a.listSize;
    aList = new objPos[arrayCapacity];

    for(int i = 0; i < listSize; i++){
            aList[i] = a.aList[i];
        }
}

// Destructor

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    aList = nullptr;
}

// Copy assignment Operator

objPosArrayList& objPosArrayList::operator= (const objPosArrayList& a){
    if(this != &a)
    {
        delete[] this->aList;

        this->arrayCapacity = a.arrayCapacity;
        this->listSize = a.listSize;

        if (a.arrayCapacity > 0) {
            this->aList = new objPos[a.arrayCapacity];
            for (int i = 0; i < a.listSize; i++) {
                this->aList[i] = a.aList[i];
            }
        } else {
            this->aList = nullptr; 
        }
    }

    return *this;
}

// Copy Function

objPosArrayList objPosArrayList::copy(){
    objPosArrayList copy = objPosArrayList(arrayCapacity);
    copy.listSize = listSize;

    for(int i = 0; i < listSize; i++){
        copy.aList[i] = aList[i];
    }
    return copy;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize < arrayCapacity){
        for(int i = listSize; i > 0; i--){
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
        listSize++;
    }    
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize < arrayCapacity){
        aList[listSize] = thisPos;
        listSize++;
    }
}

void objPosArrayList::removeHead()
{
    if(listSize > 0){
        for(int i = 0; i < listSize - 1; i++){
            aList[i] = aList[i + 1];
        }
        listSize--;   
    }
}

void objPosArrayList::removeTail()
{
    if(listSize > 0){
        listSize--;
    }
    
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}