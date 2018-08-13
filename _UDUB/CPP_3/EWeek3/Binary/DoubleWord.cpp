//
//  DoubleWord.cpp
//  EWeek3
//
//  Created by CLAYTON WONG on 8/9/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#include "DoubleWord.hpp"
#include "Common.hpp"

namespace Binary
{
    DoubleWord DoubleWord::readProperEndian ( std::istream& is )
    {
        Byte first, second, third, fourth;
        read ( is, first, second, third, fourth );
        
        if ( Binary::IS__LITTLE__ENDIAN() )
        {
            return DoubleWord{ fourth, third, second, first };
        }
        else
        {
            return DoubleWord{ first, second, third, fourth };
        }
    }

    DoubleWord DoubleWord::readLittleEndian ( std::istream& is )
    {
        Byte first, second, third, fourth;
        read ( is, first, second, third, fourth );
        return DoubleWord{ fourth, third, second, first };
    }

    DoubleWord DoubleWord::readBigEndian ( std::istream& is )
    {
        Byte first, second, third, fourth;
        read ( is, first, second, third, fourth );
        return DoubleWord{ first, second, third, fourth };
    }
    
    void DoubleWord::read ( std::istream& is,
                            Byte& first, Byte& second, Byte& third, Byte& fourth )
    {
        first = Byte::read( is );
        if ( ! is )
        {
            throw std::runtime_error{ "unable to read DoubleWord's first byte from istream" };
        }
        
        second = Byte::read( is );
        if ( ! is )
        {
            throw std::runtime_error{ "unable to read DoubleWord's second byte from istream" };
        }

        third = Byte::read( is );
        if ( ! is )
        {
            throw std::runtime_error{ "unable to read DoubleWord's third byte from istream" };
        }

        fourth = Byte::read( is );
        if ( ! is )
        {
            throw std::runtime_error{ "unable to read DoubleWord's fourth byte from istream" };
        }
    }
    
    DoubleWord::DoubleWord( DoubleWordType value ) :
    myValue{ value }
    {
    }
    
    DoubleWord::DoubleWord ( const Byte& first, const Byte& second,
                             const Byte& third, const Byte& fourth ) :
    myValue{ 0 }
    {
        myValue =
            first.getValue()  << ( 3 * Byte::BIT_COUNT ) |
            second.getValue() << ( 2 * Byte::BIT_COUNT ) |
            third.getValue()  << ( 1 * Byte::BIT_COUNT ) |
            fourth.getValue() << ( 0 * Byte::BIT_COUNT );
    }
    
    DoubleWordType DoubleWord::getValue() const noexcept
    {
        return myValue;
    }

    void DoubleWord::write ( std::ostream& os, bool forceBigEndian ) const
    {
        Binary::ByteType allBitsSet =
            static_cast<Binary::ByteType>(  (1 << ( Byte::BIT_COUNT + 1 )) - 1  );
        Byte mask{ allBitsSet };
        Byte first =  ( myValue & mask << ( 3 * Byte::BIT_COUNT ) )  >> ( 3 * Byte::BIT_COUNT );
        Byte second = ( myValue & mask << ( 2 * Byte::BIT_COUNT ) )  >> ( 2 * Byte::BIT_COUNT );
        Byte third =  ( myValue & mask << ( 1 * Byte::BIT_COUNT ) )  >> ( 1 * Byte::BIT_COUNT );
        Byte fourth = ( myValue & mask << ( 0 * Byte::BIT_COUNT ) )  >> ( 0 * Byte::BIT_COUNT );

        if ( !forceBigEndian && IS__LITTLE__ENDIAN() )
        {
            write( os, fourth, third, second, first );
        }
        else
        {
            write( os, first, second, third, fourth );
        }
    }
    
    void DoubleWord::writeLittleEndian ( std::ostream& os ) const
    {
        write( os );
    }
    
    void DoubleWord::writeBigEndian ( std::ostream& os ) const
    {
        write( os, true );
    }
    
    void DoubleWord::write ( std::ostream& os,
        const Byte& first, const Byte& second, const Byte& third, const Byte& fourth)
    {
        first.write( os );
        if ( ! os )
        {
            throw std::runtime_error{ "unable to write DoubleWord's first byte to ostream" };
        }
        second.write( os );
        if ( ! os )
        {
            throw std::runtime_error{ "unable to write DoubleWord's second byte to ostream" };
        }
        third.write( os );
        if ( ! os )
        {
            throw std::runtime_error{ "unable to write DoubleWord's second byte to ostream" };
        }
        fourth.write( os );
        if ( ! os )
        {
            throw std::runtime_error{ "unable to write DoubleWord's second byte to ostream" };
        }
    }

    DoubleWord::operator DoubleWordType() const noexcept
    {
        return myValue;
    }

    bool DoubleWord::operator== ( const DoubleWord& rhs ) const noexcept
    {
        return myValue == rhs.myValue;
    }
    
    std::ostream& operator<< ( std::ostream& os, const DoubleWord& rhs )
    {
        rhs.write( os );
        return os;
    }
}
