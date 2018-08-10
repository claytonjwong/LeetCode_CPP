//
//  Word.cpp
//  EWeek3
//
//  Created by CLAYTON WONG on 8/9/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#include "Word.hpp"

namespace Binary
{
    Word Word::readLittleEndian ( std::stringstream& ss )
    {
        auto first = Byte::read( ss );
        auto second = Byte::read( ss );
        return Word{
            static_cast<WordType>( first | second << 8 )
        };
    }

    Word Word::readBigEndian ( std::stringstream& ss )
    {
        auto first = Byte::read( ss );
        auto second = Byte::read( ss );
        return Word{
            static_cast<WordType>( first << 8 | second )
        };
    }

    Word::Word ( WordType value ) :
    myValue{ value }
    {
    }
    
    WordType Word::getValue() const noexcept
    {
        return myValue;
    }

    Word::operator WordType() const noexcept
    {
        return myValue;
    }
    
    bool Word::operator== ( const Word& rhs ) const noexcept
    {
        return myValue == rhs.myValue;
    }
}