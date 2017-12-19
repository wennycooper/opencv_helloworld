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

String face_cascade_name = "./data/haarcascades/haarcascade_upperbody.xml";
//String face_cascade_name = "/home/pi/lbpcascades/lbpcascade_frontalface.xml";
//String eyes_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier face_cascade;
String window_name = "Capture - Face detection";

float	t;

/** @function main */
int main( void )
{
    VideoCapture stream1(0);  // my camera is in /dev/video1
    Mat frame;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
//    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };

    //-- 2. Read the video stream
    //stream1.open( -1 );
    if ( ! stream1.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }


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
void detectAndDisplay( Mat frameOrig )
{
    std::vector<Rect> faces;
    //Mat frame;
    Mat frame_gray;

    Mat frame(frameOrig);
    resize(frame, frame, Size(160, 120));
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );


    t = (double)cvGetTickCount();
    //-- Detect faces
    //face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(16, 12), Size(80, 60) ); // 30ms

    face_cascade.detectMultiScale( frame_gray, faces); // 35ms
    
    t = (double)cvGetTickCount() - t;
    printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
       //Point center( (faces[i].x + faces[i].width/2) * 4, (faces[i].y + faces[i].height/2) * 4 );
       //ellipse( frameOrig, center, Size( faces[i].width/2 * 4, faces[i].height/2 *4), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        rectangle( frameOrig,
           Point( faces[i].x * 4, faces[i].y * 4),
           Point( (faces[i].x + faces[i].width) * 4, (faces[i].y + faces[i].height) * 4),
           Scalar( 0, 255, 255 ),
           5,
           8 );
    }
    //-- Show what you got
    imshow( window_name, frameOrig );

    cout.flush();

}
