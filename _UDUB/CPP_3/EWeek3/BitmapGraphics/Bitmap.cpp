//
//  Bitmap.cpp
//  EWeek3
//
//  Created by CLAYTON WONG on 8/9/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#include "DoubleWord.hpp"
#include "Color.hpp"
#include "Bitmap.hpp"

namespace BitmapGraphics
{
    Bitmap::Bitmap ( int width, int height, std::istream& is ) :
    myWidth{ width },
    myHeight{ height }
    {
        int scanLineSize = Color::BYTE_COUNT * myWidth;
        int align = Binary::DoubleWord::BYTE_COUNT;
        myPaddingSize = ( align - ( scanLineSize % align ) ) % align;
    
        for ( int i = 0;  i < myHeight;  ++i )
        {
            ScanLine scanLine;
            for ( int j = 0;  j < myWidth;  ++j )
            {
                auto color = Color::read( is );
                scanLine.emplace_back(  std::move( color )  );
            }
            myScanLines.emplace_back(  std::move( scanLine )  );
            
            for ( int p = 0;  p < myPaddingSize; ++p)
            {
                is.ignore();
            }
        }
    }
    
    int Bitmap::getWidth() const noexcept
    {
        return myWidth;
    }

    int Bitmap::getHeight() const noexcept
    {
        return myHeight;
    }

    Bitmap::ScanLineIterator Bitmap::begin() const noexcept
    {
        return myScanLines.begin();
    }

    Bitmap::ScanLineIterator Bitmap::end() const noexcept
    {
        return myScanLines.end();
    }
    
    void Bitmap::write ( std::ostream& os ) const
    {
        for ( const auto& scanLine: myScanLines )
        {
            for ( const auto& color: scanLine )
            {
                color.write( os );
            }
            
            Binary::Byte padding;
            for ( int p = 0; p < myPaddingSize; ++p )
            {
                padding.write( os );
            }
        }
    }
}
