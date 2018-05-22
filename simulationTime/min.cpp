#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib> 
#include <math.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_multimin.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_rng.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_randist.h>

#include "min.h"
using namespace std;
int main ()
{
	double v1[3]={2.75,1.1,-0};
	double v2[3]={2.75,1.1,-1};
	double v3[3]={2.75,1.1,-2};
	//double v[3]={2.5,1,0};
	//double v[3]={5,2,-3};
	//double v[3]={1.35,0.56,0.93};
	//double v[3]={3,3,-3};
	//double sigma=.3;  //1ns.  1*0.3=0.3 meters. error should less than 0.9 meter. 3 sigma!
	double sigma=1;  //1ns.  1*0.3=0.3 meters. error should less than 0.9 meter. 3 sigma!
	double distance[40]={0};
	double distance1[40]={0};
	double distance2[40]={0};
	double distance3[40]={0};
	const gsl_rng* r=gsl_rng_alloc(gsl_rng_taus);
  	std::ofstream myfile;
	std::ifstream infile("/home/pengcao/backup/rootdata_blast_aview_7_22_2015/trunk/blastQuery_Cali_root_2half.txt");
  	myfile.open("simulationTime.txt", std::ios_base::app);
std::string line;
while (std::getline(infile, line))
{
    std::istringstream iss(line);
//	cout<<iss.str()<<endl;
    int n=0;
    double t=0;
    char s[20];
    std::ostringstream query1;
    std::ostringstream query2;
    std::ostringstream query3;
    std::ostringstream hornNum;
     if(!(iss >> s >> n)) { break; }
  	query1<<"/home/pengcao/min/./min "<<n<<" ";
  	query2<<"/home/pengcao/min/./min "<<n<<" ";
  	query3<<"/home/pengcao/min/./min "<<n<<" ";
	for (int i=0; i<40;i++){
		if (!(iss>>t)) break; 
		distance1[i]= sqrt((p[i][0]-v1[0])*(p[i][0]-v1[0])+(p[i][1]-v1[1])*(p[i][1]-v1[1])+(p[i][2]-v1[2])*(p[i][2]-v1[2]));
		distance2[i]= sqrt((p[i][0]-v2[0])*(p[i][0]-v2[0])+(p[i][1]-v2[1])*(p[i][1]-v2[1])+(p[i][2]-v2[2])*(p[i][2]-v2[2]));
		distance3[i]= sqrt((p[i][0]-v3[0])*(p[i][0]-v3[0])+(p[i][1]-v3[1])*(p[i][1]-v3[1])+(p[i][2]-v3[2])*(p[i][2]-v3[2]));
		if(t!=0)     {
			distance1[i]= distance1[i]/0.3+ gsl_ran_gaussian(r, sigma);
			distance2[i]= distance2[i]/0.3+ gsl_ran_gaussian(r, sigma);
			distance3[i]= distance3[i]/0.3+ gsl_ran_gaussian(r, sigma);
			hornNum<<i+1<<" ";
		}
		else {
			distance1[i]=0;
			distance2[i]=0;
			distance3[i]=0;
		}
		query1<<distance1[i]<<" ";
		query2<<distance2[i]<<" ";
		query3<<distance3[i]<<" ";
	}
      		printf ("\n");
	query1<<"\n";
	query2<<"\n";
	query3<<"\n";
/*
        cout<<hornNum.str()<<endl;
	myfile<<hornNum.str();
*/
        cout<<query1.str()<<endl;
        cout<<query2.str()<<endl;
        cout<<query3.str()<<endl;
	myfile<<query1.str();
	myfile<<query2.str();
	myfile<<query3.str();
     
}
	
  myfile.close();
  return 1;
}
