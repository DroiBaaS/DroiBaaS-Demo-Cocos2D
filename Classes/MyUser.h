//
//  MyUser.hpp
//  TestGame
//
//  Created by jiang on 16/12/5.
//
//
#include <stdio.h>
#include "DroiUser.h"

class MyUser : public DroiUser
{
public:
    static DroiObject* create();
    
    std::string getName() {
        std::string name;
        
        getValue("name", name);
        return name;
    }
    
    void setName(const std::string& name){
        setValue("name", name);
    }
private:
    MyUser():DroiUser()
    {
        
    }
};
