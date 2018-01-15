//
//  CVDelegate.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 15/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef CVDelegate_hpp
#define CVDelegate_hpp

#include <stdio.h>

enum{
    _CV_IMG,
    _CV_DETECTION,
    _CV_MOVING,
    _CV_COUNTER,
    _CV_LIB,
};

class CVDelagate{
    
public:
    CVDelagate();
    ~CVDelagate();
    void release(int type);
};

#endif /* CVDelegate_hpp */
