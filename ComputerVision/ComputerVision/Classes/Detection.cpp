//
//  Detection.cpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 15/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#include "Detection.hpp"
#include <opencv2/opencv.hpp>

Detection::Detection(){
}

Detection * Detection::create(){
    Detection * instance = new Detection();
    
    if(instance && instance->init()){
        return instance;
    }
    
    return 0;
}

bool Detection::init(){
    return true;
}

void Detection::show(int type){
    switch (type) {
        case _D_FACE:
            faceDetection();
            break;
            
        case _D_BODY:
            bodyDetection();
            break;
        
        default:
            break;
    }
}


void Detection::faceDetection(){
    cv::VideoCapture cap;
    cap.open(0);
    
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 500);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    
    cv::Mat img;
    cv::CascadeClassifier detector;
    
    cv::String cascadeName = "/Users/vratic/projects/openCV/opencv-3.2.0/data/haarcascades/haarcascade_frontalface_alt.xml";
    detector.load(cascadeName);
    
    int groundThreshold = 2;
    double scaleStep = 1.1;
    cv::Size minimalObjectSize(80, 80);
    cv::Size maximalObjectSize(200, 200);
    
    std::vector<cv::Rect> faces;
    
    while(true) {
        cap >> img;
        cv::Mat image_grey;
        cv::cvtColor(img, image_grey, CV_BGR2GRAY);
        
        detector.detectMultiScale(image_grey,
                                  faces,
                                  scaleStep,
                                  groundThreshold,
                                  0|2,
                                  minimalObjectSize,
                                  maximalObjectSize);
        
        if (faces.size() > 0) {
            for (int i = 0; i <= faces.size() - 1; i++) {
                cv::rectangle(img, faces[i].br(), faces[i].tl(), cv::Scalar(0, 0, 0), 1, 8, 0);
            }
        }
        
        if(img.empty()){
            break;
        }
        cv::imshow("FaceDetection", img);
        cv::waitKey(20);
    }
}


void Detection::bodyDetection(){
    cv::VideoCapture cap;
    cap.open("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/peaple.mp4");
    
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 500);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    
    cv::Mat img;
    cv::CascadeClassifier detector;
    
    cv::String cascadeName = "/Users/vratic/projects/openCV/opencv-3.2.0/data/haarcascades/haarcascade_fullbody.xml";
    detector.load(cascadeName);
    
    int groundThreshold = 2;
    double scaleStep = 1.1;
    cv::Size minimalObjectSize(80, 80);
    cv::Size maximalObjectSize(200, 200);
    
    std::vector<cv::Rect> faces;
    
    while(true) {
        cap >> img;
        cv::Mat image_grey;
        cv::cvtColor(img, image_grey, CV_BGR2GRAY);
        
        detector.detectMultiScale(image_grey,
                                  faces,
                                  scaleStep,
                                  groundThreshold,
                                  0|2,
                                  minimalObjectSize,
                                  maximalObjectSize);
        
        if (faces.size() > 0) {
            for (int i = 0; i <= faces.size() - 1; i++) {
                cv::rectangle(img, faces[i].br(), faces[i].tl(), cv::Scalar(0, 0, 0), 1, 8, 0);
            }
        }
        
        if(img.empty()){
            break;
        }
        cv::imshow("FaceDetection", img);
        cv::waitKey(20);
    }
}
