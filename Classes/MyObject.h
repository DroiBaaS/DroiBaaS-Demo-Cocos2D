//
//  MyObject.hpp
//  TestGame
//
//  Created by jiang on 16/12/5.
//
//


#include <stdio.h>
#include "DroiObject.h"

class MyObject : public DroiObject
{
public:
    static DroiObject* create();
    
private:
    MyObject() : DroiObject("MyObject")
    {
        
    }
};
