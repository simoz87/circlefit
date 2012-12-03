#include "CircleFitter.h"
#include <limits>
#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>

using namespace std;

CircleFitter::CircleFitter(void)
{
	//initialize the Circle Fitter object
}

CircleFitter::CircleFitter(int maxIter):
	maxIter_(maxIter)
{
}

void CircleFitter::setMaxIter(int maxIter){
	maxIter_=maxIter;
}


CircleFitter::Circle CircleFitter::Run(const std::vector<Point2D> &input)
{
	int count=0;
	bool continua;
	Point2D sum=accumulate(input.begin(), input.end(), Point2D(0.0, 0.0));
	z_[0]=sum.getx()/input.size();
	z_[1]=sum.gety()/input.size();
	//z_[2]=(((*max_element(input.begin(), input.end(), compx)).getx()-(*min_element(input.begin(), input.end(), compx)).getx())/2);
	//Alternativa: 
	z_[2]=(*max_element(input.begin(), input.end(), compx)).getx()-z_[1];
	do{
		count++;
		ddF_[0]=ddF_[1]=ddF_[2]=ddF_[3]=ddF_[4]=ddF_[5]=ddF_[6]=ddF_[7]=ddF_[8]=0.0f;
		dF_[0]=dF_[1]=dF_[2]=0.0f;
		for (int ii=0; ii<input.size(); ii++){
			Point2D p=input.at(ii);
			float f=(pow((z_[0]-p.getx()),2)+pow((z_[1]-p.gety()),2)-pow(z_[2],2));
			float Dx=z_[0]-p.getx();
			float Dy=z_[1]-p.gety();
			
			dF_[0]+=(4*f*Dx);
			dF_[1]+=(4*f*Dy);
			dF_[2]+=(4*f*(-z_[2]));
			ddF_[0]+=(4*(2*pow(Dx,2)+f));
			ddF_[1]+=(8*Dx*Dy);	
			ddF_[2]+=(-8*Dx*abs(z_[2]));
			ddF_[4]+=(4*(2*pow(Dy,2)+f));
			ddF_[5]+=(-8*Dy*abs(z_[2]));
			ddF_[8]+=(4*(2*pow(z_[2],2)-f));
		}
		ddF_[3]=ddF_[1];
		ddF_[6]=ddF_[2];
		ddF_[7]=ddF_[5];



		long int info;
		long int n=3;
		long int one(1);
		long int piv[3];
		sgetrf_(&n,&n,ddF_,&n,piv,&info);
		if(info !=0)
			throw runtime_error ("Illegal value for solve the system");

		sgetrs_("N",&n,&one,ddF_,&n,piv,dF_,&n,&info);
		if(info !=0)
			throw runtime_error ("Illegal value for solve the system");

		continua=false;
		for (int ii=0; ii<n; ii++){
			z_[ii]-=dF_[ii];
			continua=continua||(abs(dF_[ii])>(abs(z_[ii])/1000));
		}
	}while (continua && count<maxIter_);
	cout<<"count = "<<count<<endl;
	if(count>=maxIter_)
		//returns a fake invalid circle
		return Circle(numeric_limits<float>::quiet_NaN(),
					numeric_limits<float>::quiet_NaN(),
					numeric_limits<float>::quiet_NaN());
	return Circle(z_[0], z_[1], abs(z_[2]));
}


CircleFitter::~CircleFitter(void)
{
}

std::ostream& operator<< (std::ostream& stream, const CircleFitter::Circle& c)
{
  stream<<"center "<<c._centerX<<" , "<<c._centerY<<endl;
  stream<<"radius "<<c._radius<<endl;
  return stream;
}
