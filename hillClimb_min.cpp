#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib> 
#include <math.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_multimin.h>

#include "hillClimb_min.h"

int main (int argc, char* argv[])
{
  
  if(argc!=42) {
    printf("Wrong number of variables.  %d", argc);
    return 0;
  }
  size_t iter = 0;
  int status;

  const gsl_multimin_fdfminimizer_type *T;
  gsl_multimin_fdfminimizer *s;
  /* Position of the minimum (1,2), scale factors 
     10,20, height 30. */
  double par[40]; 
  int c=0;
  for(int i=0; i<40; i++){
    par[i]=atof(argv[i+2]);
    if(par[i]>0.001||par[i]<-0.001) c++;
  //printf("%d ", c);
  }
  if (c<=4) return 0;
	
/* {
			0,0,0,0,0,0,0,0,0,0,		//1~10
			0,0,0,0,0,0,0,0,35.33,30.66,	//11~20
			32.11,25.79,0,0,0,0,0,0,0,0,		//21~30
			0,0,0,36.48,31.98,35.79,0,0,0,0		//31~40
			};
*/

  gsl_vector *x;
  gsl_multimin_function_fdf my_func;

  my_func.n = 3;
  my_func.f = my_f;
  my_func.df = my_df;
  my_func.fdf = my_fdf;
  my_func.params = par;

  /* Starting point, x = (5,7) */
  x = gsl_vector_alloc (3);
/*
  gsl_vector_set (x, 0, 10);
  gsl_vector_set (x, 1, 10);
  gsl_vector_set (x, 2, -4);
*/
  gsl_vector_set (x, 0, 0.12);
  gsl_vector_set (x, 1, 0.1);
  gsl_vector_set (x, 2, -3.5);

  T = gsl_multimin_fdfminimizer_conjugate_fr;
  s = gsl_multimin_fdfminimizer_alloc (T, 3);

  gsl_multimin_fdfminimizer_set (s, &my_func, x, 0.01, 1e-4);

  do
    {
      iter++;
      status = gsl_multimin_fdfminimizer_iterate (s);

      if (status)
        break;

      status = gsl_multimin_test_gradient (s->gradient, 1e-3);

      if (status == GSL_SUCCESS)
        printf ("Minimum found iter%d:\n",iter);
	;
/*
*/
    }
  while (status == GSL_CONTINUE && iter < 1000);

	std::ofstream myfile;
	myfile.open("blastReco.txt", std::ios_base::app); // out for write
	//myfile.open("/home/pengcao/aview_cp/truck/blastReco.txt", std::ios_base::app);
	//myfile.open("blastReco.txt", std::ios_base::app);

      	if (iter==1000){
      		printf ("%5s %.5f %.5f %.5f %.5f %d\n", argv[1],0,0,0,-999, -999);//not found the min
  		myfile<<argv[1]<<" "<<0<<" "<<0<<" "<<0<<" "<<-999<<" "<<-999<<"\n";
	}
	else{
      		printf ("%5s %.5f %.5f %.5f %.5f %d\n", argv[1],gsl_vector_get (s->x, 0),gsl_vector_get (s->x, 1),gsl_vector_get (s->x, 2), 
              	s->f, c);
  		myfile<<argv[1]<<" "<<gsl_vector_get(s->x,0)<<" "<<gsl_vector_get(s->x,1)<<" "<<gsl_vector_get(s->x,2)<<" "<<s->f<<" "<<c<<"\n";
	}
  	myfile.close();
  gsl_multimin_fdfminimizer_free (s);
  gsl_vector_free (x);

  return 0;
}
