#ifndef _VECTOR_H
#define _VECTOR_H

/*
 * The next line is used because Codewarrior has a conflict with
 * the STL vector. Make sure to put the #include of this file
 * AFTER all the system includes.
 */
#define vector Vector
#include <cstddef>

class ArrayIndexOutOfBounds { };

template <class Object>
class vector
{
  public:
    explicit vector( int capacity = 0 ) : currentSize( capacity )
      { objects = new Object[ currentSize ]; }
    vector( const vector & rhs ) : objects( NULL )
      { operator=( rhs ); }
    ~vector( )
      { delete [ ] objects; }

    int size( ) const
      { return currentSize; }

    Object & operator[]( int index )
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }


    const vector & operator = ( const vector & rhs );
    void resize( int newSize );
    
    void push_back(const Object &rhs);
  private:
    int currentSize;
    Object * objects;
    int capacity;
};

#include "vector.cpp"
#endif


