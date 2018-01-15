//
//  Detection.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 15/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef Detection_hpp
#define Detection_hpp

#include <stdio.h>

enum{
    _D_FACE,
    _D_BODY,
};

class Detection{
private:
    bool init();
    void faceDetection();
    void bodyDetection();
    
public:
    Detection();
    static Detection * create();
    void show(int type);
};

#endif /* Detection_hpp */
