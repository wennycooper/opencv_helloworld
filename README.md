# opencv_helloworld #

## files
* opencv_helloworld.cpp:  
    only use detectMultiScale   
* opencv_helloworkd1.cpp:  
    use detectMultiScale to detect face, then crop image, then use templateMatch to speed up following detection process
* opencv_fullbodydetection.cpp:  
    use HAAR detectMultiScale to detect full body
* opencv_upperbodydetection.cpp:  
    use HAAR detectMultiScale to detect upper body
* opencv_peopledetection.cpp:  
    use HOG.detectMultiScale to detect people



## build instruction ##
g++ -o ./opencv_helloworld ./opencv_helloworld.cpp `pkg-config --cflags --libs opencv`
 
