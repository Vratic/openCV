//
//  main.cpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 15/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#include <iostream>
#include "CVDelegate.hpp"


class Doom {
public:
    Doom(){};
    void show(){
        std::cout << "Doom \n";
    }
};

class Block : public Doom{
public:
    Block(){};
    void show(){
        std::cout << "Block \n";
    }
};


int main(int argc, const char * argv[]) {
    CVDelagate * cvd = new CVDelagate();
    cvd->release(_CV_IMG);
//    cvd->release(_CV_DETECTION); // TODO : FIX
//    cvd->release(_CV_COUNTER);
//    cvd->release(_CV_MOVING);
//    cvd->release(_CV_LIB);
    
    Doom * d = new Block();
    d->show();
    
    return 0;
    
}
