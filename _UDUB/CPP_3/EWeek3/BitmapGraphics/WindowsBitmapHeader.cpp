//
//  WindowsBitmapHeader.cpp
//  EWeek3
//
//  Created by CLAYTON WONG on 8/9/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#include "WindowsBitmapHeader.hpp"
#include <sstream>

using namespace Binary;

namespace BitmapGraphics
{
    //
    // file header: https://en.wikipedia.org/wiki/BMP_file_format#Bitmap_file_header
    //
    const Byte WindowsBitmapHeader::firstIdentifier{ 'B' };
    const Byte WindowsBitmapHeader::secondIdentifier{ 'M' };
    // << myFileSize >>
    const DoubleWord WindowsBitmapHeader::reserved{ 0 };
    // << myRawImageOffset >>
    
    //
    // info header: https://en.wikipedia.org/wiki/BMP_file_format#DIB_header_(bitmap_information_header)
    //
    const DoubleWord WindowsBitmapHeader::infoHeaderSize{ INFO_HEADER_SIZE };
    // << myWidth >>
    // << myHeight >>
    const Word WindowsBitmapHeader::colorPlanes{ 1 };
    const Word WindowsBitmapHeader::colorDepth{ 24 };
    // << myCompressionMethod >>
    // << myImageSize >>
    // << myHorizontalPixelsPerMeter >>
    // << myVerticalPixelsPerMeter >>
    const Binary::DoubleWord WindowsBitmapHeader::numberOfColors{ 0 };
    const Binary::DoubleWord WindowsBitmapHeader::numberOfImportantColors{ 0 };


    WindowsBitmapHeader::WindowsBitmapHeader ( std::istream& is )
    {
        read( is );
    }
    
    void WindowsBitmapHeader::read ( std::istream& is )
    {
        readFileHeader( is );
        readInfoHeader( is );
    
        auto rawImagePos = static_cast<std::streampos>( myRawImageOffset );
    
        if ( rawImagePos != is.tellg() ) // skip past "other" headers
        {
            is.seekg( rawImagePos );
        }
        
        verifyEquality( rawImagePos, is.tellg(),
            "actual raw image position referred to via myRawImageOffset" );
    }
    
    //
    // order of read() matters based on the file header!
    //
    // file header: https://en.wikipedia.org/wiki/BMP_file_format#Bitmap_file_header
    //
    void WindowsBitmapHeader::readFileHeader ( std::istream& is )
    {
        verifyEquality( static_cast<std::streampos>( 0 ), is.tellg(), "myFirstIdentifier position" );
        verifyEquality( firstIdentifier, Byte::read( is ), "myFirstIdentifier value" );

        verifyEquality( static_cast<std::streampos>( 1 ), is.tellg(), "mySecondIdentifier position" );
        verifyEquality( secondIdentifier, Byte::read( is ), "mySecondIdentifier value");
        
        verifyEquality( static_cast<std::streampos>( 2 ), is.tellg(), "myFileSize position" );
        myFileSize = DoubleWord::read( is );
        
        verifyEquality( static_cast<std::streampos>( 6 ), is.tellg(), "reserved position" );
        verifyEquality( reserved, DoubleWord::read( is ), "reserved value" );
        
        verifyEquality( static_cast<std::streampos>( 10 ), is.tellg(), "rawImageOffset position" );
        myRawImageOffset = DoubleWord::read( is );
        
        verifyEquality( static_cast<std::streampos>( 14 ), is.tellg(), "end file header" );
    }
    
    //
    // order of read() matters based on the info header!
    //
    // info header: https://en.wikipedia.org/wiki/BMP_file_format#DIB_header_(bitmap_information_header)
    //
    void WindowsBitmapHeader::readInfoHeader ( std::istream& is )
    {
        verifyEquality( static_cast<std::streampos>( 14 ), is.tellg(), "infoHeaderSize position" );
        verifyEquality( infoHeaderSize, DoubleWord::read( is ), "infoHeaderSize value" );
        
        verifyEquality( static_cast<std::streampos>( 18 ), is.tellg(), "myWidth position" );
        myWidth = DoubleWord::read( is );
        
        verifyEquality( static_cast<std::streampos>( 22 ), is.tellg(), "myHeight position" );
        myHeight = DoubleWord::read( is );
        
        verifyEquality( static_cast<std::streampos>( 26 ), is.tellg(), "colorPlanes position" );
        verifyEquality( colorPlanes, Word::read( is ), "colorPlanes value" );
        
        verifyEquality( static_cast<std::streampos>( 28 ), is.tellg(), "colorDepth position" );
        Word::read( is ); // ignore colorDepth value
        
        verifyEquality( static_cast<std::streampos>( 30 ), is.tellg(), "compressionMethod position" );
        myCompressionMethod = DoubleWord::read( is );
        
        verifyEquality( static_cast<std::streampos>( 34 ), is.tellg(), "myImageSize position" );
        myImageSize = DoubleWord::read( is );
        
        verifyEquality( static_cast<std::streampos>( 38 ), is.tellg(), "myHorizontalPixelsPerMeter position" );
        myHorizontalPixelsPerMeter = DoubleWord::read( is );
        
        verifyEquality( static_cast<std::streampos>( 42 ), is.tellg(), "myVerticalPixelsPerMeter position" );
        myVerticalPixelsPerMeter = DoubleWord::read( is );
        
        verifyEquality( static_cast<std::streampos>( 46 ), is.tellg(), "numberOfColors position" );
        DoubleWord::read( is ); // ignore numberOfColors value
        
        verifyEquality( static_cast<std::streampos>( 50 ), is.tellg(), "numberOfImportantColors position" );
        DoubleWord::read( is ); // ignore numberOfImportantColors value
        
        verifyEquality( static_cast<std::streampos>( 54 ), is.tellg(), "end info header" );
    }
    
    int WindowsBitmapHeader::getBitmapWidth() const noexcept
    {
        return myWidth.getValue();
    }
    
    int WindowsBitmapHeader::getBitmapHeight() const noexcept
    {
        return myHeight.getValue();
    }
    
    int WindowsBitmapHeader::getFileSize() const noexcept
    {
        return myFileSize.getValue();
    }
    
    void WindowsBitmapHeader::write ( std::ostream& os ) const
    {
        writeFileHeader( os );
        writeInfoHeader( os );
    }
    
    void WindowsBitmapHeader::writeFileHeader ( std::ostream& os ) const
    {
        firstIdentifier.write( os );
        secondIdentifier.write( os );
        myFileSize.write( os );
        reserved.write( os );
        myRawImageOffset.write( os );
    }
    void WindowsBitmapHeader::writeInfoHeader ( std::ostream& os ) const
    {
        infoHeaderSize.write( os );
        myWidth.write( os );
        myHeight.write( os );
        colorPlanes.write( os );
        colorDepth.write( os );
        myCompressionMethod.write( os );
        myImageSize.write( os );
        myHorizontalPixelsPerMeter.write( os );
        myVerticalPixelsPerMeter.write( os );
        numberOfColors.write( os );
        numberOfImportantColors.write( os );
    }
}
