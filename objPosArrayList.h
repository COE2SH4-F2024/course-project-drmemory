#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();
        objPosArrayList(int aCapacity);
        ~objPosArrayList();
        objPosArrayList(const objPosArrayList& a);
        objPosArrayList& operator= (const objPosArrayList &a);
        objPosArrayList copy();

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;

        //new function used to update the positions of the randomly generated food
        void setElement(int index, int x, int y, char sym);
};

#endif