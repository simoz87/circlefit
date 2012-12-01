#include <iostream>
#include "Point2Dvector.h"
#include "CircleFitter.h"
#include "../libs/clapack.h"
using namespace std;

const double MIN_INC = 1e-9; 
const int MAX_ITER = 100;

//main function: accepts as input parameter a matlab file containing the points sampled on the circle
int main(int argc, char* argv[])
{
  try
  {
    if(argc<2)
      throw runtime_error("not enought parameters!");

    string inputfilename=argv[1];
    
    Point2Dvector points(inputfilename);//read input points

    CircleFitter cf;//initialize the circle fitter object

    CircleFitter::Circle fitted_circle=cf.Run(points);//solves the fitting problem

    cout<<"The optimal parameters are:\n"<<fitted_circle<<endl;//outputs the result
  }
  catch(std::exception &e)
  {
    cout<<"catched error: "<< e.what()<<endl;
  }

  return 0;
}

