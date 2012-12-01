#include "CircleFitter.h"
#include <limits>
#include <iostream>
#include <cmath>

using namespace std;

CircleFitter::CircleFitter(void)
{
	//initialize the Circle Fitter object
	ddF[0]=ddF[1]=ddF[2]=ddF[3]=ddF[4]=ddF[5]=ddF[6]=ddF[7]=ddF[8]=0.0f;
	dF[0]=dF[1]=dF[2]=0.0f;
	z[0]=z[1]=z[2]=0.0f;
  

}

CircleFitter::Circle CircleFitter::Run(const std::vector<Point2D> &input)
{
	int count=0;
	double inc;
	do{
		count++;
		ddF[0]=ddF[1]=ddF[2]=ddF[3]=ddF[4]=ddF[5]=ddF[6]=ddF[7]=ddF[8]=0.0f;
		dF[0]=dF[1]=dF[2]=0.0f;
		for (int ii=0; ii<input.size()-1; ii++){
			Point2D p=input.at(ii);
			float f=(pow((z[0]-p.getx()),2)+pow((z[1]-p.gety()),2)-pow(z[2],2));
			float Dx=z[0]-p.getx();
			float Dy=z[1]-p.gety();
			
			dF[0]+=(4*f*Dx);
			dF[1]+=(4*f*Dy);
			dF[2]+=(4*f*(-z[2]));
			ddF[0]+=(4*(2*pow(Dx,2)+f));
			ddF[1]+=(8*Dx*Dy);	
			ddF[2]+=(-8*Dx*z[2]);
			ddF[4]+=(4*(2*pow(Dy,2)+f));
			ddF[5]+=(-8*Dy*z[2]);
			ddF[8]+=(4*(2*pow(z[2],2)-f));
		}
		ddF[3]=ddF[1];
		ddF[6]=ddF[2];
		ddF[7]=ddF[5];



		long int info;
		long int n=3;
		long int one(1);
		long int piv[3];
		sgetrf_(&n,&n,ddF,&n,piv,&info);
		if(info !=0)
			throw runtime_error ("Illegal value for solve the system");

		sgetrs_("N",&n,&one,ddF,&n,piv,dF,&n,&info);
		if(info !=0)
			throw runtime_error ("Illegal value for solve the system");
		inc=0.0;
		for (int ii=0; ii<n; ii++){
			z[ii]-=dF[ii];
			inc+=pow(dF[ii],2);
		}
	}while (inc>MIN_INC || count>MAX_ITER);
	cout<<"count = "<<count<<endl;
	if(count>MAX_ITER)
		//returns a fake invalid circle
		return Circle(numeric_limits<float>::quiet_NaN(),
					numeric_limits<float>::quiet_NaN(),
					numeric_limits<float>::quiet_NaN());
	return Circle(z[0], z[1], z[2]);
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
