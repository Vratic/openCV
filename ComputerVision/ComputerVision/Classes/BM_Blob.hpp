//
//  BM_Blob.hpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#ifndef BM_Blob_hpp
#define BM_Blob_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

class BMBlob {
public:
    std::vector<cv::Point> contour;
    cv::Rect boundingRect;
    cv::Point centerPosition;
    
    double dblDiagonalSize;
    double dblAspectRatio;
    
    BMBlob(std::vector<cv::Point> _contour);
};

#endif /* BM_Blob_hpp */
