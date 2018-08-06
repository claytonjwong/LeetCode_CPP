//
//  Scene.cpp
//  EWeek2
//
//  Created by CLAYTON WONG on 8/5/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#include "Scene.hpp"

namespace Framework
{
    void Scene::setHeight(const int height) noexcept
    {
        myHeight = height;
    }

    void Scene::setWidth(const int width) noexcept
    {
        myWidth = width;
    }

    int Scene::getHeight() const noexcept
    {
        return myHeight;
    }

    int Scene::getWidth() const noexcept
    {
        return myWidth;
    }

    Scene::LayerIterator Scene::begin() const noexcept
    {
        return myLayers.begin();
    }

    Scene::LayerIterator Scene::end() const noexcept
    {
        return myLayers.end();
    }

    void Scene::pushBack(const Layer& layer) noexcept
    {
        myLayers.push_back( layer );
    }

    void Scene::remove(const Layer& target) noexcept
    {
        auto new_end = std::remove_if( myLayers.begin(), myLayers.end(),
            [&](const Layer& x){ return x.getAlias() == target.getAlias(); });
        
        if ( new_end != myLayers.end() )
        {
            myLayers.erase( new_end, myLayers.end() );
        }
    }
}
