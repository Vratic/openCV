//
//  CVDelegate.cpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 15/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#include "CVDelegate.hpp"
#include "ColorModels.hpp"
#include "Detection.hpp"
#include "CarCounter.hpp"
#include "BodyMoving.hpp"
#include "CVLib.hpp"

#include <opencv2/opencv.hpp>

CVDelagate::CVDelagate(){
}

CVDelagate::~CVDelagate(){
}

void CVDelagate::release(int type){
    printf("release : %i \n", type);
    
    if(type == _CV_IMG){
        ColorModels * cm = ColorModels::create();
        cm->show(_CM_HSV);
        cm->show(_CM_GRAY);
        cm->show(_CM_DETECTION);
        cv::waitKey(0);
        
    // TODO : FIX
    // -----------------------------------------
    } else if(type == _CV_DETECTION){
        Detection * d = Detection::create();
        d->show(_D_FACE);
        d->show(_D_BODY);
    // -----------------------------------------
    } else if(type == _CV_COUNTER){
        CarCounter * cc = CarCounter::create();
        cc->show();
        
    }else if (type == _CV_MOVING){
        BodyMoving * bm = BodyMoving::create();
//        bm->show(_BM_MULTI);
        bm->show(_BM_BLOB);
        
    } else if(_CV_LIB){
        CVLib * cvl = CVLib::create();
//        cvl->show(_CVL_FAST); // detekce rohu
        cvl->show(_CVL_MSER); // detekce regionu
        cv::waitKey(0);
        
    } else {
        return;
    }
    
}

