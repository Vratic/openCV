//
//  CVLib.cpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#include "CVLib.hpp"
#include <opencv2/opencv.hpp>


CVLib::CVLib(){
}

CVLib::~CVLib(){
}

CVLib * CVLib::create(){
    CVLib * instance = new CVLib();
    if(instance){
        return instance;
    }
    return 0;
}

void CVLib::show(int type){
    switch (type) {
        case _CVL_FAST:
            cvlFast();
            break;
            
        case _CVL_MSER:
            cvlMser();
            break;
            
        default:
            break;
    }
}

void CVLib::cvlFast(){
    cv::Mat img = cv::imread("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/Greenwich.jpg" ,CV_LOAD_IMAGE_GRAYSCALE);
    if(img.data){
        std::vector<cv::KeyPoint> keypoints; // vektor slouzici pro ukladani nalezenych klicovych bodu
        std::vector<cv::KeyPoint>::iterator it; keypoints.clear();
        
        cv::FAST( img, keypoints, 50, true ); // provede detekci rohovych bodu pomoci FAST detektoru v matici obrazku img s prahem 50 a zaplym potlacenim blizkych bodu
        cv::Point point; // vsechny nalezene body postupne zaznamena do obrazku jako kruznice o polomeru 3
        for ( it = keypoints.begin(); it < keypoints.end(); it++
             ){
            point.x = it->pt.x;
            point.y = it->pt.y;
            cv::circle( img, point, 3, CV_RGB(255,255,0) );
        }
        cv::namedWindow( "FAST", CV_WINDOW_AUTOSIZE );
        cv::imshow( "FAST",img );
//        cv::waitKey(0);
    }
}

void CVLib::cvlMser(){
    cv::Mat img = cv::imread("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/Greenwich.jpg",CV_LOAD_IMAGE_COLOR);
    if( img.data ) {
        // vektor slouzici k ukladani nalezenych klicovych bodu
        std::vector<std::vector<cv::Point>> regions;
        std::vector<std::vector<cv::Point>>::iterator it;
        std::vector<cv::Point>::iterator it2;
        
        
        cv::Ptr<cv::MSER> mser = cv::MSER::create();
        std::vector<cv::Rect> mser_bbox;
        mser->detectRegions(img, regions, mser_bbox);
        
        // zobrazi region
        for (int i = 0; i < regions.size(); i++)
        {
//            rectangle(img, mser_bbox[i], CV_RGB(0, 255, 0));
        }
        
        // kazdy region zobrazi odlisnou barvou
        for (it = regions.begin(); it < regions.end(); it++) {
            
            cv::Scalar color(rand()&255,rand()&255,rand()&255);
            cv::Scalar color2(0,0,0);
            
            for (it2 = it->begin(); it2 < it->end(); it2++){
                cv::circle(img,cv::Point(it2->x,it2->y),0,color);
            }
        }
        cv::imshow("MSER", img);
//        cv::waitKey(0);
    }
}
