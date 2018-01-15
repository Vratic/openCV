//
//  BodyMoving.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef BodyMoving_hpp
#define BodyMoving_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "BM_Multi.hpp"

enum {
    _BM_BLOB,
    _BM_MULTI,
};

class BodyMoving{
private:
    void trackingMulti();
    void trackingBlob();
    
private:
    void matchCurrentFrameBlobsToExistingBlobs(std::vector<BMMulti> &existingBlobs, std::vector<BMMulti> &currentFrameBlobs);
    void addBlobToExistingBlobs(BMMulti &currentFrameBlob, std::vector<BMMulti> &existingBlobs, int &intIndex);
    void addNewBlob(BMMulti &currentFrameBlob, std::vector<BMMulti> &existingBlobs);
    double distanceBetweenPoints(cv::Point point1, cv::Point point2);
    void drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName);
    void drawAndShowContours(cv::Size imageSize, std::vector<BMMulti> blobs, std::string strImageName);
    void drawBlobInfoOnImage(std::vector<BMMulti> &blobs, cv::Mat &imgFrame2Copy);
    
public:
    BodyMoving();
    ~BodyMoving();
    static BodyMoving * create();
    void show(int type);
};

#endif /* BodyMoving_hpp */
