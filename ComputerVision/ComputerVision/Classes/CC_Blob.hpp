//
//  CC_Blob.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef CC_Blob_hpp
#define CC_Blob_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>


class Blob {
public:
    std::vector<cv::Point> currentContour;
    cv::Rect currentBoundingRect;
    std::vector<cv::Point> centerPositions;
    
    double dblCurrentDiagonalSize;
    double dblCurrentAspectRatio;
    
    bool blnCurrentMatchFoundOrNewBlob;
    
    bool blnStillBeingTracked;
    
    int intNumOfConsecutiveFramesWithoutAMatch;
    
    cv::Point predictedNextPosition;
    
    Blob(std::vector<cv::Point> _contour);
    void predictNextPosition(void);
};

#endif /* CC_Blob_hpp */
