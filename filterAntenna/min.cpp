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
  	std::ofstream myfile;
	std::ifstream infile1("/home/pengcao/blastQuery_100_50.txt");
  	myfile.open("blastQuery_.txt", std::ios_base::app);
std::string line1;
std::string line2;
    std::istringstream iss2;
while (std::getline(infile1, line1))
{
    int n1=0,n2=0;
    double t1=0,t2=0;
    char s1[20],s2[20];
    int found=0;
    double time=0;
    std::istringstream iss1(line1);
     if(!(iss1 >> s1 >> n1)) { break; }
	std::ifstream infile2("/home/pengcao/blastQuery_100_50.txt");
while (std::getline(infile2, line2)){
    std::istringstream iss2(line2);
     if(!(iss2 >> s2 >> n2)) { found=0;continue; }
     if (n2==n1) {found =1; cout<<"found"<<endl;break;}
}
	cout<<n1<<" = " << n2<<endl;
    if (found==0) continue;
    std::istringstream iss2(line2);
     iss2 >> s2 >> n2; 
    std::ostringstream query1;
  	query1<<"/home/pengcao/min/./min "<<n1<<" ";
	for (int i=0; i<40;i++){
		//cout<<i<<" "<<time<<" "<<endl;
		//cout<<iss1.str()<<endl;
		//cout<<iss2.str()<<endl;
//		iss1>>t1;
//		iss2>>t2;
		if (!(iss1>>t1)) break; 
		if (!(iss2>>t2)) break; 
		if(t1!=0)     {
			query1<<t1<<" ";
		}
		else {
			query1<<"0"<<" ";
		}
	}
      		printf ("\n");
	query1<<"\n";
        cout<<query1.str()<<endl;
	myfile<<query1.str();
     
}
	
  myfile.close();
  return 1;
}
