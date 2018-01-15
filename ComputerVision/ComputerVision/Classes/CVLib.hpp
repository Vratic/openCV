//
//  CVLib.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef CVLib_hpp
#define CVLib_hpp

#include <stdio.h>

enum {
    _CVL_FAST,
    _CVL_MSER,
};

class CVLib {
private:
    void cvlFast();
    void cvlMser();
public:
    CVLib();
    ~CVLib();
    static CVLib * create();
    
    void show(int type);
};

#endif /* CVLib_hpp */
