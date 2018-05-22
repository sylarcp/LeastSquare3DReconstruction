#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include </home/pengcao/gsl-1.16/gsl/gsl_multimin.h>
/* Paraboloid centered on (p[0],p[1]), with  
   scale factors (p[2],p[3]) and minimum p[4] */
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
/*
double p[40][3] =
{
{ 0.921,	0,		0 }, 			//1    antenna 1
{ 0.651245,	0.651245,	0 }, 	//2
{ 0,		0.921,		0 }, 			//3
{ -0.651245,	0.651245,	0 }, 	//4
{ -0.921,	0,		0 }, 		//5
{ -0.651245,	-0.651245,	0 }, 	//6
{ 0,		-0.921,		0 },			//7
{ 0.651245,	-0.651245,	0 }, 	//8
{ 0.697529,	-0.288926,	-0.967 }, 	//9
{ 0.697529,	0.288926,	-0.967 },  	//10
{ 0.288926,	0.697529,	-0.967 },  	//11
{ -0.288926,	0.697529,	-0.967 }, 	//12
{ -0.697529,	0.288926,	-0.967 }, 	//13
{ -0.697529,	-0.288926,	-0.967 },	//14
{ -0.288926,	-0.697529,	-0.967 },	//15
{ 0.288926,	-0.697529,	-0.967 }, 	//16
{ 1.90781,	-0.790241,	-3.731 }, 	//17
{ 2.0635,	0, 		-3.731}, 	//18
{ 1.90781,	0.790241,	-3.731 },  	//19
{ 1.46018,	1.46018,	-3.731 },  	//20
{ 0.790241,	1.90781,	-3.731 },  	//21
{ 0,2.065,	-3.731 }, 	 	//22
{ -0.790241,	1.90781,	-3.731 },  	//23
{ -1.46018,	1.46018,	-3.731 },  	//24
{ -1.90781,	0.790241,	-3.731 },  	//25
{ -2.065,	0,		-3.731 },  		//26
{ -1.90781,	-0.790241,	-3.731 }, 	//27
{ -1.46018,	-1.46018,	-3.731 },  	//28
{ -0.790241,	-1.90781,	-3.731 }, 	//29
{ 0,		-2.065,		-3.731 },  		//30
{ 0.790241,	-1.90781,	-3.731 },  	//31
{ 1.46018,	-1.46018,	-3.731 },  	//32
{ 1.56136,	-0.646735,	-5.377 },  	//33
{ 1.56136,	0.646735,	-5.377 },  	//34
{ 0.646735,	1.56136,	-5.377 },  	//35
{ -0.646735,	1.56136,	-5.377 },  	//36
{ -1.56136,	0.646735,	-5.377 },  	//37
{ -1.56136,	-0.646735,	-5.377 }, 	//38
{ -0.646735,	-1.56136,	-5.377 }, 	//39
{ 0.646735,	-1.56136,	-5.377 }  	//40
};
*/
double
my_f (const gsl_vector *v, void *params)
{
  double x, y, z;
  double *pt = (double *)params;
  int i,j;
  double result=0;
  
  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);
  z = gsl_vector_get(v, 2);
  for(i=0; i<40; i++){
    for(j=0; j<40; j++){
      if(i!=j && pt[i]!=0 && pt[j]!=0){
//	printf("%d ", i);
      result+=pow(sqrt((x-p[i][0])*(x-p[i][0])+(y-p[i][1])*(y-p[i][1])+(z-p[i][2])*(z-p[i][2]))-sqrt((x-p[j][0])*(x-p[j][0])+(y-p[j][1])*(y-p[j][1])+(z-p[j][2])*(z-p[j][2]))-0.3*(pt[i]-pt[j]),2);
      }
    }
  } 
  return result;
}

/* The gradient of f, df = (df/dx, df/dy). */
void 
my_df (const gsl_vector *v, void *params, 
       gsl_vector *df)
{
  double x, y, z;
  int i,j;
  double result[3]={0,0,0};
  double *pt = (double *)params;
  
  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);
  z = gsl_vector_get(v, 2);
  for(i=0; i<40; i++){
    for(j=0; j<40; j++){
      if (i!=j && pt[i]!=0 && pt[j]!=0){
        result[0]+=2*((x-p[i][0])/(sqrt(pow(x-p[i][0],2)+pow(y-p[i][1],2)+pow(z-p[i][2],2)))-(x-p[j][0])/(sqrt(pow(x-p[j][0],2)+pow(y-p[j][1],2)+pow(z-p[j][2],2))))*(sqrt(pow(x-p[i][0],2)+pow(y-p[i][1],2)+pow(z-p[i][2],2))-sqrt(pow(x-p[j][0],2)+pow(y-p[j][1],2)+pow(z-p[j][2],2))-0.3*(pt[i]-pt[j]));
        result[1]+=2*((y-p[i][1])/(sqrt(pow(x-p[i][0],2)+pow(y-p[i][1],2)+pow(z-p[i][2],2)))-(y-p[j][1])/(sqrt(pow(x-p[j][0],2)+pow(y-p[j][1],2)+pow(z-p[j][2],2))))*(sqrt(pow(x-p[i][0],2)+pow(y-p[i][1],2)+pow(z-p[i][2],2))-sqrt(pow(x-p[j][0],2)+pow(y-p[j][1],2)+pow(z-p[j][2],2))-0.3*(pt[i]-pt[j]));
        result[2]+=2*((z-p[i][2])/(sqrt(pow(x-p[i][0],2)+pow(y-p[i][1],2)+pow(z-p[i][2],2)))-(z-p[j][2])/(sqrt(pow(x-p[j][0],2)+pow(y-p[j][1],2)+pow(z-p[j][2],2))))*(sqrt(pow(x-p[i][0],2)+pow(y-p[i][1],2)+pow(z-p[i][2],2))-sqrt(pow(x-p[j][0],2)+pow(y-p[j][1],2)+pow(z-p[j][2],2))-0.3*(pt[i]-pt[j]));
      }
    }
  }
  gsl_vector_set(df, 0, result[0]);
  gsl_vector_set(df, 1, result[1]);
  gsl_vector_set(df, 2, result[2]);
  
}

/* Compute both f and df together. */
void 
my_fdf (const gsl_vector *x, void *params, 
        double *f, gsl_vector *df) 
{
  *f = my_f(x, params); 
  my_df(x, params, df);
} 
