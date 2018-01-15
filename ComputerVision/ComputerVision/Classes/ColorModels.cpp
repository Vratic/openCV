//
//  ColorModels.cpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 15/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#include "ColorModels.hpp"
#include <opencv2/opencv.hpp>

ColorModels * ColorModels::create(){
    ColorModels * instance = new ColorModels();
    if(instance && instance->init()){
        return instance;
    }
    return 0;
}


ColorModels::ColorModels(){
}

bool ColorModels::init(){
    return true;
}

void ColorModels::show(int model){
    switch (model) {
        case _CM_HSV:
            HSV();
            break;
            
        case _CM_GRAY:
            gray();
            break;
            
        case _CM_DETECTION:
            colorDetection();
            break;
            
        default:
            break;
    }
}


// ------------------------------------------------------------
// COLOR DETECTION

void ColorModels::colorDetection(){
    // BGR : Blue Green Red
    // GET RED COLOR
    cv::Mat img;
    img = cv::imread("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/redball.jpg", 1);
    cv::namedWindow("image", CV_WINDOW_FREERATIO);
    cv::imshow("image", img);

    cv::Mat outputImg;
    cv::inRange(img, cv::Scalar(10, 10, 100), cv::Scalar(100, 100, 255), outputImg);
    cv::imshow("out_image", outputImg);
    
    
    
    // GET BLUE BALL
    cv::Mat img2;
    img2 = cv::imread("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/blueball.jpg", 1);
    cv::namedWindow("image2", CV_WINDOW_FREERATIO);
    cv::imshow("image2", img2);
    
    cv::Mat outputImg2;
    cv::inRange(img2, cv::Scalar(100, 10, 10), cv::Scalar(255, 100, 100), outputImg2);
    cv::imshow("out_image2", outputImg2);
    
//    int red, blue;
//    red = cv::countNonZero(outputImg);
//    blue = cv::countNonZero(outputImg2);
//
//    cv::namedWindow("out_image", CV_WINDOW_FREERATIO);
//    if(red>blue){
//        std::cout << "RED BALL \n";
//        cv::imshow("out_image", outputImg);
//    } else {
//        std::cout << "BLUE BALL \n";
//        cv::imshow("out_image", outputImg2);
//    }
//    cv::waitKey(0);
}


// ------------------------------------------------------------
// CONVERT COLOR MODEL FROM IMG
// COLOR MODEL : HSV

void ColorModels::HSV(){
    cv::Mat img;
    cv::Mat HSVimg;
    cv::Mat processedImg;
    
    img = cv::imread("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/img.jpg");
    
    if(!img.data){
        std::cout << "Could not open or find the image" << std::endl ;
    }
    
    cv::cvtColor(img, HSVimg, CV_BGR2HLS);
    cv::inRange(HSVimg, cv::Scalar(0,0,0), cv::Scalar(100,100,100), processedImg);
    
    cv::imshow("Display HSV", processedImg);
//    cv::waitKey(0);
}


// ------------------------------------------------------------
// CONVERT COLOR MODEL FROM IMG
// COLOR MODEL : IMG IN GRAY SCALE

void ColorModels::gray(){
    cv::Mat img;
    
    img = cv::imread("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    
    if(!img.data){
        std::cout << "Could not open or find the image" << std::endl ;
    }
    
    cv::imshow("Display Gray", img);
//    cv::waitKey(0);
}

