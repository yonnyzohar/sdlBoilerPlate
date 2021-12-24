//
//  Man.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef Man_hpp
#define Man_hpp

#include <stdio.h>

#include "GameObject.hpp"


class Man : public GameObject
{
    
public:
    using GameObject::GameObject;
    void update() override;

};

#endif /* Man_hpp */
