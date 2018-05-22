#include <time.h>
#include <iostream>
#include <iomanip> 
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib> 
#include <math.h>
#include "min.h"
using namespace std;
int main (int argc, char* argv[])
{
  if(argc!=42) {
    printf("Wrong number of variables.  %d", argc);
    return 0;
  }
  const gsl_rng_type * T;
  gsl_rng * r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);
  size_t iter = 0;

  /* Position of the minimum (1,2), scale factors 
     10,20, height 30. */

  int c=0;
  for(int i=0; i<40; i++){
    pt[i]=atof(argv[i+2]);
    if(pt[i]>0.001||pt[i]<-0.001) c++;
  //printf("%d ", c);
  }
  if (c<=4) {
	printf("active antenna less than four!");
	return 0;

  }
  /* Starting point, x = (5,7) */
  gsl_vector *x;
  x = gsl_vector_alloc (3);
  gsl_vector_set (x, 0, 3);
  gsl_vector_set (x, 1, 3);
  gsl_vector_set (x, 2, -3);


  gsl_siman_solve(r, x, E1, S1, M1, P1,NULL, NULL, NULL,sizeof(gsl_vector), params);
  //gsl_siman_solve(r, x, E1, S1, M1, P1,NULL, NULL, NULL,sizeof(double), params);

	std::ofstream myfile;
	myfile.open("blastReco.txt", std::ios_base::app); // out for write

      	if (iter==1000){
      		printf ("%5s %.5f %.5f %.5f %.5f %d\n", argv[1],0,0,0,-999, -999);//not found the min
  		myfile<<argv[1]<<" "<<0<<" "<<0<<" "<<0<<" "<<-999<<" "<<-999<<"\n";
	}
	else{
      		cout<<setprecision(5)<< argv[1]<<" "<<gsl_vector_get (x, 0)<<" "<<gsl_vector_get (x, 1)<<" "<<gsl_vector_get (x, 2)<<" "<<"-99 "<< c<<endl;
  		myfile<<argv[1]<<" "<<gsl_vector_get(x,0)<<" "<<gsl_vector_get(x,1)<<" "<<gsl_vector_get(x,2)<<" "<<"-99"<<" "<<c<<"\n";
	}
  	myfile.close();
  gsl_rng_free (r);
  gsl_vector_free (x);
  return 0;
}
