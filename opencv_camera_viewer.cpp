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

//String face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
//String face_cascade_name = "/home/pi/lbpcascades/lbpcascade_frontalface.xml";
//String eyes_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

//CascadeClassifier face_cascade;
//CascadeClassifier eyes_cascade;
String window_name = "camera_viewer";

float	t;

/** @function main */
int main( void )
{
    VideoCapture stream1(0);  // my camera is in /dev/video1
    Mat frame;

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
        //detectAndDisplay( frame );
        imshow(window_name, frame);

        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
    return 0;
}

