#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());


    Mat image;
    VideoCapture capture;
    capture.open(0);
    if(capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        for(;;)
        {
            capture >> image;
            
            Mat gray;
            cvtColor(image, gray, COLOR_BGR2GRAY);
            

            vector<Rect> r;
            vector<double> w;
            hog.detectMultiScale(gray, r, w);

            for(int i=0; i<(int)r.size(); i++) {
                rectangle(image, r[i], Scalar(255,0,0), 3);
            }

            if(image.empty())
                break;
            imshow("Sample", image);
            if(waitKey(10) >= 0)
                break;
        }
    }
    else
    {
        cout << "No capture" << endl;
        image = Mat::zeros(480, 640, CV_8UC1);
        imshow("Sample", image);
        waitKey(0);
    }
    
    return 0;
}
