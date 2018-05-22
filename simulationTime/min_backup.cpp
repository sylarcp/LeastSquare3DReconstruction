#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib> 
#include <math.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_multimin.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_rng.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_randist.h>

#include "min.h"

int main ()
{
	//double v[3]={5,2,-3};
	double v[3]={2,5,0};
	//double v[3]={1.35,0.56,0.93};
	//double v[3]={3,3,-3};
	//double sigma=.3;  //1ns.  1*0.3=0.3 meters. error should less than 0.9 meter. 3 sigma!
	double sigma=0.3;  //1ns.  1*0.3=0.3 meters. error should less than 0.9 meter. 3 sigma!
	double distance[40]={0};
	const gsl_rng* r=gsl_rng_alloc(gsl_rng_taus);
  	std::ofstream myfile;
  	myfile.open("simulationTime.txt", std::ios_base::app);
for(int n=0;n<1000;n++){
  	myfile<<"/home/pengcao/min/./min "<<n<<" ";
	for (int i=0; i<40;i++){
		distance[i]= sqrt((p[i][0]-v[0])*(p[i][0]-v[0])+(p[i][1]-v[1])*(p[i][1]-v[1])+(p[i][2]-v[2])*(p[i][2]-v[2]));
	//	distance[i]= distance[i]/0.3+ gsl_ran_gaussian(r, sigma);
		//if(i==18||i==19||i==20||i==21||i==22||i==33||i==34||i==35||i==37)  distance[i]= distance[i]/0.3;
		if(i==18||i==19||i==20||i==21||i==22||i==23||i==24||i==33||i==34||i==35||i==36||i==37||i==38)  distance[i]= distance[i]/0.3+ gsl_ran_gaussian(r, sigma);
		//if(i==18||i==19||i==20||i==21||i==22||i==33||i==34||i==35||i==37)  distance[i]= distance[i]/0.3+ gsl_ran_gaussian(r, sigma);
		else distance[i]=0;
      		printf ("%.5f ", distance[i]);
		myfile<<distance[i]<<" ";
	}
      		printf ("\n");
	myfile<<"\n";
}
  myfile.close();
  return 1;
}
