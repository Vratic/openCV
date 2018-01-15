//
//  CarCounter.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef CarCounter_hpp
#define CarCounter_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "CC_Blob.hpp"

class CarCounter {
public:
    CarCounter();
    ~CarCounter();
    static CarCounter * create();
    
    void show();
    
    // function prototypes ////////////////////////////////////////////////////////////////////////////
    void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
    void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
    void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
    double distanceBetweenPoints(cv::Point point1, cv::Point point2);
    void drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName);
    void drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName);
    bool checkIfBlobsCrossedTheLine(std::vector<Blob> &blobs, int &intHorizontalLinePosition, int &carCount);
    void drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy);
    void drawCarCountOnImage(int &carCount, cv::Mat &imgFrame2Copy);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
};

#endif /* CarCounter_hpp */
