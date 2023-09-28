
#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
 #include <opencv2/opencv.hpp>
#include <iostream>
 #include <cmath>
using namespace std;
cv::Mat image;
double  xPrimer;
double  yPrimer;

double xSegun;
double  ySegun;

double  xLugar = 1;
double  yLugar = 1;
//callback function. Whenever the mouse is moved or a button pressed, this function is called
void on_mouse( int event, int x, int y, int flags, void* param )
{
if (event==cv::EVENT_RBUTTONDOWN) 
{
  cout<<"x,y="<<x<<" "<<y<<endl;
  //set as red a small window around
  int xleft=x-3;
  if( xleft<0) xleft=0;//check not out of image
  int yleft=y-3;
  if( yleft<0) yleft=0;//check not out of image
  int xright=x+3;
  if( xright> image.cols) xright=image.cols-1;//check not out of image
  int yright=y+3;
  if( yright> image.rows) yright=image.rows-1;//check not out of image
  
  image=cv::imread("isla.png");
  cv::imshow("image",image);
  for( int x=xleft;x<=xright;x++)
	for( int y=yleft;y<=yright;y++){


	uchar *ptr=image.ptr<uchar>(y)+3*x;

	ptr[0]=0;
	ptr[1]=100;
	ptr[2]=255;

  xLugar = x;
  yLugar = y;
	}
	


  //refresh the image window
  cv::imshow("image",image);

}

if (event==cv::EVENT_LBUTTONDOWN) 
{

  cout<<"x,y="<<x<<" "<<y<<endl;
  //set as red a small window around
  int xleft=x-3;
  if( xleft<0) xleft=0;//check not out of image
  int yleft=y-3;
  if( yleft<0) yleft=0;//check not out of image
  int xright=x+3;
  if( xright> image.cols) xright=image.cols-1;//check not out of image
  int yright=y+3;
  if( yright> image.rows) yright=image.rows-1;//check not out of image
  
 xPrimer = x;
 yPrimer = y;
 

}
  if (event==cv::EVENT_LBUTTONUP) 
  {
    cout<<"x,y="<<x<<" "<<y<<endl;
    cv::Point point1(xPrimer, yPrimer);
    cv::Point point2(x,y);
    xSegun=x;
    ySegun=y;
    cv::Scalar color(0, 0, 255);  // Red color
    cv::Scalar color2(255, 255, 0);  // cyan color
    cv::Scalar color3(0, 100, 255);  // naranja

    // Draw a line between the two points
    cv::line(image, point1, point2, color, 2); // 2 is the line thickness


    //HACER LO DEMAS
      //Obtener polinomio de la recta
      //f(x) = m*x + b
        double m = (ySegun - yPrimer) / (xSegun - xPrimer);
        double b = yPrimer - m * xPrimer;

      //Obtener perpendicular que pase por xLugar e yLugar
        double mP = -1/(m+0.000000001);
        
        double bP = yLugar - mP * xLugar;

      //Obtener donde cruzan
        double xI = (bP - b)/(m - mP);
        
        double yI = m * xI + b;

        cv::Point point3(xLugar,yLugar);
        cv::Point point4(xI,yI);
        cv::line(image, point3, point4, color2, 5);
        
      //Medir distancia entre Lugar e I
        double longitud = sqrt( pow(xLugar-xI ,2) + pow(yLugar - yI ,2) );

        double longitudImportante = longitud * 0.24358882621; //cos(13.69);

        cv::circle(image, point4, longitudImportante, color3, 2);

    // Display the image with the line
    cv::imshow("image", image);
  }
}


int main(int argc,char **argv){
try{

image=cv::imread("isla.png");
//Create image 320x240
//creates a window
cv::namedWindow("image");
//indicates that the on_mouse function should be called in case of mouse moved or pressed over window
cv::setMouseCallback( "image", on_mouse, 0 );
//shows image
cv::imshow("image",image);
char c=0;
while(c!=27)  //waits until ESC pressed
	c=cv::waitKey(0);

}catch(std::exception &ex)
{
  cout<<ex.what()<<endl;
}
}
 
