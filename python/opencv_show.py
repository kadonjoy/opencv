#!/usr/bin/python
#coding:utf8

import sys
import cv2

def main(argv):
    image=cv2.imread(argv[0])
    cv2.namedWindow("image")
    cv2.namedWindow("image_scale")
    # convert one image to gray image
    image_gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY) 
    # cv2.imshow("Image", image)
    # cv2.imshow("Image", image_gray)
    # resize one picture
    image_scale=cv2.resize(image_gray,(1280,720),interpolation=cv2.INTER_CUBIC)
    cv2.imshow("image_scale", image_scale)
    cv2.imshow("image", image)
    cv2.waitKey(0)

if __name__ == "__main__":
    main(sys.argv[1:])
