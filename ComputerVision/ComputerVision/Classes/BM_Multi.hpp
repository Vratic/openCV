//
//  BM_Multi.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef BM_Multi_hpp
#define BM_Multi_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

class BMMulti {
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
    
    BMMulti(std::vector<cv::Point> _contour);
    void predictNextPosition(void);
    
};

#endif /* BM_Multi_hpp */
