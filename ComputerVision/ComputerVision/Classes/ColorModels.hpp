//
//  ColorModels.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 15/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef ColorModels_hpp
#define ColorModels_hpp

#include <stdio.h>

enum{
    _CM_HSV,
    _CM_GRAY,
    _CM_DETECTION,
};

class ColorModels{
    
private:
    bool init();
    void HSV();
    void gray();
    void colorDetection();
public:
    ColorModels();
    static ColorModels * create();
    void show(int model);
};

#endif /* ColorModels_hpp */
