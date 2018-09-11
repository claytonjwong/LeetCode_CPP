//
//  SquarePen.hpp
//  EWeek5
//
//  Created by Clayton Wong on 9/11/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#pragma once

#include "ICanvas.hpp"
#include "IPen.hpp"
#include "Point.hpp"
#include "Color.hpp"

namespace BitmapGraphics
{
    class SquarePen : public IPen
    {
    public:
        
        SquarePen ( size_t size, Color color );
        
        virtual void drawPoint ( const HCanvas& canvas, const VG::Point& topLeftPoint ) const override;
    
    private:
        
        size_t mySize;
        Color myColor;
        
    };
    
} // namespace BitmapGraphics

