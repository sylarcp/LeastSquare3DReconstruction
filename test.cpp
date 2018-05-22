#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib> 
#include <math.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_multimin.h>

#include "test.h"

int main ()
{
  for(int n=0; n<11; n++){ 
  size_t iter = 0;
  int status;

  const gsl_multimin_fdfminimizer_type *T;
  gsl_multimin_fdfminimizer *s;
  /* Position of the minimum (1,2), scale factors 
     10,20, height 30. */
  double par[40]; 
  int c=0;
  for(int i=0; i<40; i++){
    par[i]=10./3.*sqrt((p[i][0]-test[n][0])*(p[i][0]-test[n][0])+(p[i][1]-test[n][1])*(p[i][1]-test[n][1])+(p[i][2]-test[n][2])*(p[i][2]-test[n][2]));
    if(par[i]>0.001||par[i]<-0.001) c++;
  //printf("par[]=%.5f ", par[i]*0.333333);
  }
  if (c<=4) break;
  printf("%.5f %.5f %.5f ",test[n][0],test[n][1],test[n][2]);
	
/* {
			0,0,0,0,0,0,0,0,0,0,		//1~10
			0,0,0,0,0,0,0,0,35.33,30.66,	//11~20
			32.11,25.79,0,0,0,0,0,0,0,0,		//21~30
			0,0,0,36.48,31.98,35.79,0,0,0,0		//31~40
			};
*/

  gsl_vector *x;
  gsl_multimin_function_fdf my_func;

  my_func.n = 4;
  my_func.f = my_f;
  my_func.df = my_df;
  my_func.fdf = my_fdf;
  my_func.params = par;

  /* Starting point, x = (5,7) */
  x = gsl_vector_alloc (4);
  gsl_vector_set (x, 0, 1);
  gsl_vector_set (x, 1, 2);
  gsl_vector_set (x, 2, 3);
  gsl_vector_set (x, 3, 0);

  T = gsl_multimin_fdfminimizer_conjugate_fr;
  s = gsl_multimin_fdfminimizer_alloc (T, 4);

  gsl_multimin_fdfminimizer_set (s, &my_func, x, 0.01, 1e-4);

  do
    {
      iter++;
      status = gsl_multimin_fdfminimizer_iterate (s);

      if (status)
        break;

      status = gsl_multimin_test_gradient (s->gradient, 1e-3);

      if (status == GSL_SUCCESS)
        printf ("Minimum found at:----->");
/*
      printf ("%5d %.5f %.5f %.5f %.5f %10.5f\n", iter,
              gsl_vector_get (s->x, 0), 
              gsl_vector_get (s->x, 1), 
              gsl_vector_get (s->x, 2), 
              gsl_vector_get (s->x, 3), 
              s->f);
*/
    }
  while (status == GSL_CONTINUE && iter < 1000);

      printf ("%.5f %.5f %.5f %.5f %.5f\n", 
              gsl_vector_get (s->x, 0), 
              gsl_vector_get (s->x, 1), 
              gsl_vector_get (s->x, 2), 
              gsl_vector_get (s->x, 3), 
              s->f
	      );
  gsl_multimin_fdfminimizer_free (s);
  gsl_vector_free (x);
  printf("\n");
}
  return 0;

}
