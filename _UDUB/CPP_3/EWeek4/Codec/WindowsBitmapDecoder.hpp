//
//  WindowsBitmapDecoder.hpp
//  EWeek4
//
//  Created by CLAYTON WONG on 8/25/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#pragma once

#include "IBitmapDecoder.hpp"
#include "IBitmapIterator.hpp"
#include "BitmapIterator.hpp"
#include "WindowsBitmapHeader.hpp"
#include "Bitmap.hpp"
#include <iostream>
#include <sstream>

namespace Codec
{
    class WindowsBitmapDecoder : public IBitmapDecoder
    {
        public:
        
            WindowsBitmapDecoder ( ) :
            myMimeType{ "image/x-ms-bmp" }
            {
            }
        
            virtual ~WindowsBitmapDecoder ( ) = default;
        
            virtual HBitmapDecoder clone ( std::istream& inStream ) noexcept override
            {
                auto result = std::make_shared<WindowsBitmapDecoder>();
                result->myStream << inStream.rdbuf();
                BitmapGraphics::WindowsBitmapHeader header{ result->myStream };
                result->myBitmap = BitmapGraphics::Bitmap{
                    header.getBitmapWidth(), header.getBitmapHeight(), result->myStream };
                return result;
            }
        
            virtual BitmapGraphics::HBitmapIterator createIterator ( ) const noexcept override
            {
                auto it = BitmapGraphics::BitmapIterator{ myBitmap };
                return std::make_shared<BitmapGraphics::BitmapIterator>( it );
            }
        
            virtual const std::string& getMimeType ( ) const noexcept override
            {
                return myMimeType;
            }
        
            virtual bool isSupported ( ) const noexcept override
            {
                return true; // TODO: I'm not sure how this method is intended to be used?
            }
        
        private:
        
            std::stringstream myStream;
            const std::string myMimeType;
            BitmapGraphics::Bitmap myBitmap;
    };
    
}
