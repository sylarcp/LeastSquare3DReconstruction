#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_multimin.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_siman.h>
/* Paraboloid centered on (p[0],p[1]), with  
   scale factors (p[2],p[3]) and minimum p[4] */
double pt[40]={0};
double p[40][3]=
{
{0.851303, -0.782132, 3.77305 },
{1.2609, 0.0774464, 3.75559 },
{0.847652, 0.878752, 3.74412 },
{0.0146769, 1.36617, 3.73133 },
{-0.850897, 0.988541, 3.74469 },
{-1.21888, 0.0704681, 3.76409 },
{-0.874596, -0.813353, 3.78441 },
{0.0172452, -1.17478, 3.78645 },
{0.388515, -0.934518, 2.81491 },
{0.911143, -0.315571, 2.80072 },
{0.976795, 0.450304, 2.78617 },
{0.387991, 1.01313, 2.77466 },
{-0.392901, 1.07516, 2.77802 },
{-0.960917, 0.473008, 2.79233 },
{-0.977216, -0.342213, 2.81029 },
{-0.377598, -0.908763, 2.82143 },
{0.890987, -2.22549, 0.0955942 },
{1.63878, -1.64624, 0.0802275 },
{2.16351, -0.915372, 0.0443497 },
{2.37786, -0.0202301, 0.0191496 },
{2.15856, 0.869905, -0.00763382 },
{1.63715, 1.60336, -0.0172236 },
{0.902373, 2.17488, -0.0255111 },
{-0.00447999, 2.4022, -0.019316 },
{-0.914281, 2.24851, -0.0140433 },
{-1.68655, 1.71984, 0.00922827 },
{-2.15223, 0.930778, 0.0181269 },
{-2.38688, 0.0165769, 0.0375507 },
{-2.17565, -0.888935, 0.0549908 },
{-1.68395, -1.68552, 0.0787049 },
{-0.918437, -2.19669, 0.0919852 },
{-0.00662788, -2.38385, 0.104732 },
{0.732935, -1.86177, -1.7791 },
{1.75167, -0.83757, -1.81525 },
{1.75746, 0.674138, -1.86666 },
{0.749555, 1.77469, -1.87331 },
{-0.77756, 1.83634, -1.86825 },
{-1.76849, 0.747545, -1.84284 },
{-1.72451, -0.764133, -1.8074 },
{-0.730816, -1.86165, -1.77558 }
};

/* set up parameters for this simulated annealing run */

/* how many points do we try before stopping */
#define N_TRIES 200             

/* how many iterations for each T? */
#define ITERS_FIXED_T 10000

/* max step size in random walk */
#define STEP_SIZE .001            

/* Boltzmann constant */
#define K 1.0                   

/* initial temperature */
#define T_INITIAL 0.008         

/* damping factor for temperature */
#define MU_T 1.003              
#define T_MIN 2.0e-6

gsl_siman_params_t params 
  = {N_TRIES, ITERS_FIXED_T, STEP_SIZE,
     K, T_INITIAL, MU_T, T_MIN};

/* now some functions to test in one dimension */
double E1 (void *data)
{

  gsl_vector* v= (gsl_vector*)data;
  double x, y, z;
  int i,j;
  double result=0;

  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);
  z = gsl_vector_get(v, 2);
  for(i=0; i<40; i++){
    for(j=0; j<40; j++){
      if(i!=j && pt[i]!=0 && pt[j]!=0){
//      printf("%d ", i);
      result+=pow(sqrt((x-p[i][0])*(x-p[i][0])+(y-p[i][1])*(y-p[i][1])+(z-p[i][2])*(z-p[i][2]))-sqrt((x-p[j][0])*(x-p[j][0])+(y-p[j][1])*(y-p[j][1])+(z-p[j][2])*(z-p[j][2]))-0.3*(pt[i]-pt[j]),2);
      }
    }
  }
  return result;
}
//return distance between p1 and p2.
double M1(void *data1, void *data2)
{
  gsl_vector *p1 = ((gsl_vector *) data1);
  gsl_vector *p2 = ((gsl_vector *) data2);
  double x1= gsl_vector_get(p1, 0);
  double y1= gsl_vector_get(p1, 1);
  double z1= gsl_vector_get(p1, 2);
  double x2= gsl_vector_get(p2, 0);
  double y2= gsl_vector_get(p2, 1);
  double z2= gsl_vector_get(p2, 2);

  return fabs(sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2)));
}
//step function
void S1(const gsl_rng * r, void *data, double step_size)
{
  gsl_vector *v = (gsl_vector *) data;

  double x= gsl_vector_get(v, 0);
  double y= gsl_vector_get(v, 1);
  double z= gsl_vector_get(v, 2);
  
  double u1 = gsl_rng_uniform(r);  //random number generator  0--1
  double u2 = gsl_rng_uniform(r);  //random number generator  0--1
  double u3 = gsl_rng_uniform(r);  //random number generator  0--1

  gsl_vector_set (v, 0, x+u1*2*step_size-step_size);
  gsl_vector_set (v, 1, y+u2*2*step_size-step_size);
  gsl_vector_set (v, 2, z+u3*2*step_size-step_size);
}
//print the x,y,z for current postion
void P1(void *data)
{
  const gsl_vector *p1 = ((const gsl_vector *) data);
  double x1= gsl_vector_get(p1, 0);
  double y1= gsl_vector_get(p1, 1);
  double z1= gsl_vector_get(p1, 2);
  printf (" -- %5f %5f %5f --", x1,y1,z1);
}
