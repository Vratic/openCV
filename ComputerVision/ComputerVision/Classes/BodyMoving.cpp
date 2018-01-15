//
//  BodyMoving.cpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#include "BodyMoving.hpp"
#include "BM_Blob.hpp"

const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);

BodyMoving::BodyMoving(){
}

BodyMoving::~BodyMoving(){
}

BodyMoving * BodyMoving::create(){
    BodyMoving * instance = new BodyMoving();
    if(instance){
        return instance;
    }
    return 0;
}

void BodyMoving::show(int type){
    
    switch (type) {
        case _BM_BLOB:
            trackingBlob();
            break;
            
        case _BM_MULTI:
            trackingMulti();
            break;
            
        default:
            break;
    }

}

void BodyMoving::trackingBlob(){
    cv::VideoCapture capVideo;
    
    cv::Mat imgFrame1;
    cv::Mat imgFrame2;
    
    capVideo.open("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/peaple.mp4");
    
    if (!capVideo.isOpened()){
        std::cout << "\nerror reading video file" << std::endl;
    }
    
    capVideo.read(imgFrame1);
    capVideo.read(imgFrame2);
    
    char chCheckForEscKey = 0;
    
    while (capVideo.isOpened() && chCheckForEscKey != 27) {
        
        std::vector<BMBlob> blobs;
        
        cv::Mat imgFrame1Copy = imgFrame1.clone();
        cv::Mat imgFrame2Copy = imgFrame2.clone();
        
        cv::Mat imgDifference;
        cv::Mat imgThresh;
        
        cv::cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
        cv::cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);
        
        cv::GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
        cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);
        
        cv::absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);
        
        cv::threshold(imgDifference, imgThresh, 30, 255.0, CV_THRESH_BINARY);
        
        cv::imshow("imgThresh", imgThresh);
        
        cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
        cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
        
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::erode(imgThresh, imgThresh, structuringElement5x5);
        
        cv::Mat imgThreshCopy = imgThresh.clone();
        
        std::vector<std::vector<cv::Point> > contours;
        
        cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        cv::Mat imgContours(imgThresh.size(), CV_8UC3, SCALAR_BLACK);
        
        cv::drawContours(imgContours, contours, -1, SCALAR_WHITE, -1);
        
        cv::imshow("imgContours", imgContours);
        
        std::vector<std::vector<cv::Point> > convexHulls(contours.size());
        
        for (unsigned int i = 0; i < contours.size(); i++) {
            cv::convexHull(contours[i], convexHulls[i]);
        }
        
        for (auto &convexHull : convexHulls) {
            BMBlob possibleBlob(convexHull);
            
            if (possibleBlob.boundingRect.area() > 100 &&
                possibleBlob.dblAspectRatio >= 0.2 &&
                possibleBlob.dblAspectRatio <= 1.2 &&
                possibleBlob.boundingRect.width > 15 &&
                possibleBlob.boundingRect.height > 20 &&
                possibleBlob.dblDiagonalSize > 30.0) {
                blobs.push_back(possibleBlob);
            }
        }
        
        cv::Mat imgConvexHulls(imgThresh.size(), CV_8UC3, SCALAR_BLACK);
        
        convexHulls.clear();
        
        for (auto &blob : blobs) {
            convexHulls.push_back(blob.contour);
        }
        
        cv::drawContours(imgConvexHulls, convexHulls, -1, SCALAR_WHITE, -1);
        
        cv::imshow("imgConvexHulls", imgConvexHulls);
        
        imgFrame2Copy = imgFrame2.clone();
        
        for (auto &blob : blobs) {
            cv::rectangle(imgFrame2Copy, blob.boundingRect, SCALAR_RED, 2);
            cv::circle(imgFrame2Copy, blob.centerPosition, 3, SCALAR_GREEN, -1);
        }
        
        cv::imshow("imgFrame2Copy", imgFrame2Copy);
        
        imgFrame1 = imgFrame2.clone();
        
        if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) {
            capVideo.read(imgFrame2);
        }
        else {
            std::cout << "end of video\n";
            break;
        }
        
        chCheckForEscKey = cv::waitKey(1);
        
    }
    
    if (chCheckForEscKey != 27) {
        cv::waitKey(0);
    }
}

void BodyMoving::trackingMulti(){
    cv::VideoCapture capVideo;
    
    cv::Mat imgFrame1;
    cv::Mat imgFrame2;
    
    std::vector<BMMulti> blobs;
    
    capVideo.open("/Users/vratic/projects/openCV/ComputerVision/ComputerVision/Resources/peaple.mp4");
    
    if (!capVideo.isOpened()) {
        std::cout << "error reading video file" << std::endl;
    }
    
    if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 2) {
        std::cout << "error: video file must have at least two frames";
    }
    
    capVideo.read(imgFrame1);
    capVideo.read(imgFrame2);
    
    char chCheckForEscKey = 0;
    
    bool blnFirstFrame = true;
    
    int frameCount = 2;
    
    while (capVideo.isOpened() && chCheckForEscKey != 27) {
        
        std::vector<BMMulti> currentFrameBlobs;
        
        cv::Mat imgFrame1Copy = imgFrame1.clone();
        cv::Mat imgFrame2Copy = imgFrame2.clone();
        
        cv::Mat imgDifference;
        cv::Mat imgThresh;
        
        cv::cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
        cv::cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);
        
        cv::GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
        cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);
        
        cv::absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);
        
        cv::threshold(imgDifference, imgThresh, 30, 255.0, CV_THRESH_BINARY);
        
        cv::imshow("imgThresh", imgThresh);
        
        cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
        cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
        
        /*
         cv::dilate(imgThresh, imgThresh, structuringElement7x7);
         cv::erode(imgThresh, imgThresh, structuringElement3x3);
         */
        
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::erode(imgThresh, imgThresh, structuringElement5x5);
        
        
        cv::Mat imgThreshCopy = imgThresh.clone();
        
        std::vector<std::vector<cv::Point> > contours;
        
        cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        drawAndShowContours(imgThresh.size(), contours, "imgContours");
        
        std::vector<std::vector<cv::Point> > convexHulls(contours.size());
        
        for (unsigned int i = 0; i < contours.size(); i++) {
            cv::convexHull(contours[i], convexHulls[i]);
        }
        
        drawAndShowContours(imgThresh.size(), convexHulls, "imgConvexHulls");
        
        for (auto &convexHull : convexHulls) {
            BMMulti possibleBlob(convexHull);
            
            if (possibleBlob.currentBoundingRect.area() > 100 &&
                possibleBlob.dblCurrentAspectRatio >= 0.2 &&
                possibleBlob.dblCurrentAspectRatio <= 1.25 &&
                possibleBlob.currentBoundingRect.width > 20 &&
                possibleBlob.currentBoundingRect.height > 20 &&
                possibleBlob.dblCurrentDiagonalSize > 30.0 &&
                (cv::contourArea(possibleBlob.currentContour) / (double)possibleBlob.currentBoundingRect.area()) > 0.40) {
                currentFrameBlobs.push_back(possibleBlob);
            }
        }
        
        drawAndShowContours(imgThresh.size(), currentFrameBlobs, "imgCurrentFrameBlobs");
        
        if (blnFirstFrame == true) {
            for (auto &currentFrameBlob : currentFrameBlobs) {
                blobs.push_back(currentFrameBlob);
            }
        }
        else {
            matchCurrentFrameBlobsToExistingBlobs(blobs, currentFrameBlobs);
        }
        
        drawAndShowContours(imgThresh.size(), blobs, "imgBlobs");
        
        imgFrame2Copy = imgFrame2.clone();
        
        drawBlobInfoOnImage(blobs, imgFrame2Copy);
        
        cv::imshow("imgFrame2Copy", imgFrame2Copy);
        
        //cv::waitKey(0);                 // uncomment this line to go frame by frame for debugging
        
        currentFrameBlobs.clear();
        
        imgFrame1 = imgFrame2.clone();
        
        if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) {
            capVideo.read(imgFrame2);
        }
        else {
            std::cout << "end of video\n";
            break;
        }
        
        blnFirstFrame = false;
        frameCount++;
        chCheckForEscKey = cv::waitKey(1);
    }
    
    if (chCheckForEscKey != 27) {
        cv::waitKey(0);
    }
}



void BodyMoving::matchCurrentFrameBlobsToExistingBlobs(std::vector<BMMulti> &existingBlobs, std::vector<BMMulti> &currentFrameBlobs) {
    
    for (auto &existingBlob : existingBlobs) {
        
        existingBlob.blnCurrentMatchFoundOrNewBlob = false;
        
        existingBlob.predictNextPosition();
    }
    
    for (auto &currentFrameBlob : currentFrameBlobs) {
        
        int intIndexOfLeastDistance = 0;
        double dblLeastDistance = 100000.0;
        
        for (unsigned int i = 0; i < existingBlobs.size(); i++) {
            if (existingBlobs[i].blnStillBeingTracked == true) {
                double dblDistance = distanceBetweenPoints(currentFrameBlob.centerPositions.back(), existingBlobs[i].predictedNextPosition);
                
                if (dblDistance < dblLeastDistance) {
                    dblLeastDistance = dblDistance;
                    intIndexOfLeastDistance = i;
                }
            }
        }
        
        if (dblLeastDistance < currentFrameBlob.dblCurrentDiagonalSize * 1.15) {
            addBlobToExistingBlobs(currentFrameBlob, existingBlobs, intIndexOfLeastDistance);
        }
        else {
            addNewBlob(currentFrameBlob, existingBlobs);
        }
        
    }
    
    for (auto &existingBlob : existingBlobs) {
        
        if (existingBlob.blnCurrentMatchFoundOrNewBlob == false) {
            existingBlob.intNumOfConsecutiveFramesWithoutAMatch++;
        }
        
        if (existingBlob.intNumOfConsecutiveFramesWithoutAMatch >= 5) {
            existingBlob.blnStillBeingTracked = false;
        }
        
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void BodyMoving::addBlobToExistingBlobs(BMMulti &currentFrameBlob, std::vector<BMMulti> &existingBlobs, int &intIndex) {
    
    existingBlobs[intIndex].currentContour = currentFrameBlob.currentContour;
    existingBlobs[intIndex].currentBoundingRect = currentFrameBlob.currentBoundingRect;
    
    existingBlobs[intIndex].centerPositions.push_back(currentFrameBlob.centerPositions.back());
    
    existingBlobs[intIndex].dblCurrentDiagonalSize = currentFrameBlob.dblCurrentDiagonalSize;
    existingBlobs[intIndex].dblCurrentAspectRatio = currentFrameBlob.dblCurrentAspectRatio;
    
    existingBlobs[intIndex].blnStillBeingTracked = true;
    existingBlobs[intIndex].blnCurrentMatchFoundOrNewBlob = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void BodyMoving::addNewBlob(BMMulti &currentFrameBlob, std::vector<BMMulti> &existingBlobs) {
    
    currentFrameBlob.blnCurrentMatchFoundOrNewBlob = true;
    
    existingBlobs.push_back(currentFrameBlob);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
double BodyMoving::distanceBetweenPoints(cv::Point point1, cv::Point point2) {
    
    int intX = abs(point1.x - point2.x);
    int intY = abs(point1.y - point2.y);
    
    return(sqrt(pow(intX, 2) + pow(intY, 2)));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void BodyMoving::drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName) {
    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);
    
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    
    cv::imshow(strImageName, image);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void BodyMoving::drawAndShowContours(cv::Size imageSize, std::vector<BMMulti> blobs, std::string strImageName) {
    
    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);
    
    std::vector<std::vector<cv::Point> > contours;
    
    for (auto &blob : blobs) {
        if (blob.blnStillBeingTracked == true) {
            contours.push_back(blob.currentContour);
        }
    }
    
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    
    cv::imshow(strImageName, image);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void BodyMoving::drawBlobInfoOnImage(std::vector<BMMulti> &blobs, cv::Mat &imgFrame2Copy) {
    
    for (unsigned int i = 0; i < blobs.size(); i++) {
        
        if (blobs[i].blnStillBeingTracked == true) {
            cv::rectangle(imgFrame2Copy, blobs[i].currentBoundingRect, SCALAR_RED, 2);
            
            int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
            double dblFontScale = blobs[i].dblCurrentDiagonalSize / 60.0;
            int intFontThickness = (int)std::round(dblFontScale * 1.0);
            
            cv::putText(imgFrame2Copy, std::to_string(i), blobs[i].centerPositions.back(), intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
        }
    }
}
