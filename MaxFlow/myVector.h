//Because fuck weiss vector.  Why you gotta reinvent the wheel?!?!?! FUCK YOU BRO!!!
#ifndef MYVECTOR_H
#define	MYVECTOR_H

#include <cstring>
#include <cstdlib>

template <class Object>
class myVector
{
public:
    myVector()
    {
        size = 0;
        capacity = 0;
        data = 0;
    }

    ~myVector()
    {
        remove(data, data + size);
        free(data);
    }

    void copy(Object* startIndex, Object* endIndex, Object* destination) //copy from array[start]->array[end]
    {
        while(startIndex != endIndex)
        {
            new((void*)destination) Object(*startIndex);
            ++startIndex;
            ++destination;
        }
    }

    int getSize(){return size;}

    void pushBack(const Object& value)
    {
        if(size != capacity)
        {
            new((void*)(data + size)) Object(value);
            ++size;
            return;
        }
        int newCapacity = capacity ? capacity * 2 : 1;
        Object* newData = mAl(newCapacity);
        copy(data, data + size, newData);
        new((void*)(newData + size)) Object(value);
        remove(data, data + size);
        free(data);
        data = newData;
        capacity = newCapacity;
        ++size;
    }

    void remove(Object* startIndex, Object* endIndex) // delete from array[start]->array[end]
    {
        while(startIndex != endIndex)
        {
            startIndex->~Object();
            ++startIndex;
        }
    }

    Object& operator[](int index) {return data[index];}
private:
    int size;
    int capacity;
    Object* data;
    Object* mAl(int size){return static_cast<Object*>(malloc(sizeof(Object) * size));}
};

#endif	/* MYVECTOR_H */

