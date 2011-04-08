
/* Source: http://en.wikipedia.org/wiki/Smart_pointer */

#include <memory> // for std::allocator
#include <algorithm> // for std::swap
 
/*
    A simple "non-slicing" memory manager (non-sharing & copies on assignment)
    Note: NOT to be used to manage dynamically-allocated arrays 
    (for that, use std::vector or similar).
*/
template < typename Type, typename Allocator = std::allocator< Type > > 
class value_ptr 
{
    protected:
    class internal_allocator_base
    {
        public:
 
        virtual Type* clone( Type const* ) const = 0;
 
        virtual void destroy( Type* ) const = 0;
    };
 
    template < typename Derived >
    class internal_allocator : public internal_allocator_base
    {
        public: 
 
        virtual Type* clone( Type const* ptr ) const
        {
            if( ptr == 0 )
                return 0;
            Derived* 
                val = allocator.allocate( 1 );
            try
            {
                allocator.construct
                ( 
                    val, 
                    *static_cast< Derived const* >( ptr ) 
                 );
            }
            catch( ... )
            {
                allocator.deallocate( val, 1 );
                throw;
            }
            return val;
        }       
 
        virtual void destroy( Type* ptr ) const
        {
            if( ptr != 0 )
            {
                Derived* 
                    tmp = static_cast< Derived* >( ptr );
                try
                {
                    allocator.destroy( tmp );
                }
                catch( ... )
                {
                    allocator.deallocate( tmp, 1 );
                    throw;
                }               
                allocator.deallocate( tmp, 1 );         
            }   
        }       
 
        static internal_allocator 
            global;
        static typename Allocator::template rebind< Derived >::other 
            allocator;      
    };
 
    public:
 
    template < typename Derived >
    value_ptr( Derived* ptr )
    {   
        init( );
        reset( ptr );
    }
 
    value_ptr( Type* ptr = 0 )
    {   
        init( );
        reset( ptr );
    }   
 
    value_ptr( value_ptr const& rhs )
    {   
        init( );
        reset( rhs );
    }
 
    template < typename Derived >
    value_ptr& reset( Derived* ptr )
    {
        return internal_reset( ptr, &internal_allocator< Derived >::global );
    }
 
    template < typename Derived >
    inline value_ptr& operator = ( Derived* ptr )
    {
        return reset( ptr );
    }
 
    inline value_ptr& reset( Type* ptr = 0 )
    {
        return reset< Type >( ptr );
    }
 
    inline value_ptr& operator = ( Type* ptr )
    {
        return reset( ptr );
    }       
 
    value_ptr& reset( value_ptr const& rhs )
    {       
        return internal_reset( rhs.m_iab_->clone( rhs.m_ptr_ ), rhs.m_iab_ );       
    }
 
    inline value_ptr& operator = ( value_ptr const& rhs )
    {   
        return reset( rhs );
    }
 
    template < typename Derived >
    value_ptr& allocate( Derived const& val = Derived( ) )
    {
        return reset
        ( 
            static_cast< Derived* >
            ( 
                internal_allocator< Derived >::global.clone( &val ) 
             )
         );
    }
 
    inline value_ptr& allocate( )
    {
        return allocate< Type >( );
    }   
 
#ifdef VALUE_PTR_NO_IMPLICIT_CONVERSION
    inline Type& operator * ( )
    {
        return *m_ptr_;
    }
 
    inline Type const& operator * ( ) const
    {
        return *m_ptr_;
    }
#else   
    inline operator Type* ( )
    {
        return m_ptr_;
    }
 
    inline operator Type const* ( ) const
    {
        return m_ptr_;
    }
#endif
 
    inline Type* operator -> ( )
    {
        return m_ptr_;
    }
 
    inline Type const* operator -> ( ) const
    {
        return m_ptr_;
    }
 
    friend void swap( value_ptr& lhs, value_ptr& rhs )
    {
        std::swap( lhs.m_ptr_, rhs.m_ptr_ );
        std::swap( lhs.m_iab_, rhs.m_iab_ );
    }
 
    Type* orphan( )
    {
        Type*
            tmp = m_ptr_;
        m_ptr_ = 0;
        return tmp;
    }
 
    virtual ~value_ptr( )
    {
        reset( );
    }   
 
    protected:
 
    void init( )
    {
        m_ptr_ = 0;
        m_iab_ = &internal_allocator< Type >::global;
    }   
 
    value_ptr& internal_reset( Type* ptr, internal_allocator_base* iab )
    {
    /*
        The swap ensures that if the 'current' 
        data's destructor throws an exception, 
        the 'new' memory will still be cleaned up.
    */  
        std::swap( m_ptr_, ptr );
        std::swap( m_iab_, iab );   
        iab->destroy( ptr );
        return *this;
    } 
    Type* 
        m_ptr_;
    internal_allocator_base* 
        m_iab_;
};
 
template < typename Type, typename Allocator > 
template < typename Derived > 
typename value_ptr< Type, Allocator >::template internal_allocator< Derived >
    value_ptr< Type, Allocator >::internal_allocator< Derived >::global 
    = typename value_ptr< Type, Allocator >::template internal_allocator< Derived >( );     
template < typename Type, typename Allocator > 
template < typename Derived > 
typename Allocator::template rebind< Derived >::other 
    value_ptr< Type, Allocator >::internal_allocator< Derived >::allocator  
    = typename Allocator::template rebind< Derived >::other( );
