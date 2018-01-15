//
//  BM_Blob.cpp
//  ComputerVision
//
//  Created by Vratislav Beleni on 20/11/2017.
//  Copyright © 2017 Vratislav Beleni. All rights reserved.
//

#include "BM_Blob.hpp"

BMBlob::BMBlob(std::vector<cv::Point> _contour) {
    contour = _contour;
    
    boundingRect = cv::boundingRect(contour);
    centerPosition.x = (boundingRect.x + boundingRect.x + boundingRect.width) / 2;
    centerPosition.y = (boundingRect.y + boundingRect.y + boundingRect.height) / 2;
    dblDiagonalSize = sqrt(pow(boundingRect.width, 2) + pow(boundingRect.height, 2));
    dblAspectRatio = (float)boundingRect.width / (float)boundingRect.height;
    
}
