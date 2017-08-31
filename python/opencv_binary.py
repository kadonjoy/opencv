#!/usr/bin/python
#coding:utf8

import sys
import cv2

def main(argv):
    image=cv2.imread(argv[0])
    cv2.namedWindow("image_binary_win")
    cv2.namedWindow("image_scale")
    # convert one image to gray image
    image_gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY) 
    # resize one picture
    image_scale=cv2.resize(image_gray,(1280,720),interpolation=cv2.INTER_CUBIC)
    # ret, image_binary = cv2.threshold(image_scale, 125, 255, cv2.THRESH_BINARY) 
    ret, image_binary = cv2.threshold(image_gray, float(argv[1]), 255, cv2.THRESH_BINARY) 
    cv2.imshow("image_scale", image_scale)
    cv2.imshow("image_binary_win", image_binary)
    cv2.imwrite('dst.jpg', image_binary)
    cv2.imwrite('dst_gray.jpg', image_gray)
    cv2.waitKey(0)

if __name__ == "__main__":
    main(sys.argv[1:])
