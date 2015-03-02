#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <sys/time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */

String face_cascade_name = "/home/pi/haarcascades/haarcascade_frontalface_alt.xml";
//String face_cascade_name = "/home/pi/lbpcascades/lbpcascade_frontalface.xml";
String eyes_cascade_name = "/home/pi/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

struct timeval 		tv, tv2;
unsigned long long	start_timestamp;
unsigned long long	current_timestamp;
unsigned long frameCounter = 1;
float	t;

/** @function main */
int main( void )
{
    VideoCapture stream1(0);
    Mat frame;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
//    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };

    //-- 2. Read the video stream
    //stream1.open( -1 );
    if ( ! stream1.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    gettimeofday(&tv, NULL);
    start_timestamp = tv.tv_sec * 1000000 + tv.tv_usec;

    while ( stream1.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );

        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    //Mat frame;
    Mat frame_gray;

    resize(frame, frame, Size(80, 60));
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
//    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(5, 5), Size(40, 30) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
       Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        //cout << faces[i].x << endl;

        //Mat faceROI = frame_gray( faces[i] );
        //std::vector<Rect> eyes;

        //-- In each face, detect eyes
        //eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        //for ( size_t j = 0; j < eyes.size(); j++ )
        //{
        //    Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
        //    int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
        //    circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        //}
    }
    //-- Show what you got
    imshow( window_name, frame );

    gettimeofday(&tv2, NULL);
    current_timestamp = tv2.tv_sec * 1000000 + tv2.tv_usec;

    t = (float) (current_timestamp - start_timestamp)/1000000;

    printf("FPS = %f, t=%f\n", (float) frameCounter/t, (float)t);
    cout.flush();

    frameCounter++;
}
