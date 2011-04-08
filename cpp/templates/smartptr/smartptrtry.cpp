/*
    Example
*/

/* Source: http://en.wikipedia.org/wiki/Smart_pointer */

#include <iostream>
#include "smartptrtry.h"
 
class base
{
    public:
 
    void print( char const* msg )
    {
        std::cout << reinterpret_cast< int* >( this ) 
        << " : " << msg << std::endl;
    }
 
    base( )
    {
        print( "base::base( )" );
    }
 
    base( base const& )
    {
        print( "base::base( base const& )" );
    }   
 
    virtual void test( )
    {
        print( "base::test( )" );
    }
 
    ~base( )
    {
        print( "base::~base( )" );
    }
};
 
class derived : public base
{
    public:
 
    derived( )
    {
        print( "derived::derived( )" );
    }
 
    derived( derived const& rhs )
    : base( rhs )
    {
        print( "derived::derived( derived const& )" );
    }       
 
    virtual void test( )
    {
        print( "derived::test( )" );
    }
 
    ~derived( )
    {
        print( "derived::~derived( )" );
    }   
};
 
int main( )
{
    value_ptr< base >
        vpb1 = new derived( ),
    /*
        Create a non-sliced copy of vpb1
    */      
        vpb2 = vpb1;
/*
    Prints "derived::test( )"
*/      
    vpb2->test( );  
/*
    Memory allocated to each object 
    is released within the destructor
*/          
    return 0;
}
