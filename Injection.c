/*******************************************************************************
*			UDF file for particle injection                  					*
*			Prepared by Department of Chemical Engineering						*
*			Pakistan Institute of Engineering & Applied Sciences, Pakistan		*
*																				*
********************************************************************************/
#include "udf.h"


#define MAX_VOF 0.61
#define m_flow 0.0001
#define DIAM_P 0.038



DEFINE_ON_DEMAND(Injection_file_prep)
{
	
	Domain *d = Get_Domain(1);
	Thread *t;
	cell_t c;
	face_t f;
	real CC[ND_ND];
	real R, VR;
	FILE *fp;
	
	if((fp= fopen("injection.inj", "w+")) == NULL)
	{
		Message("\n open injection.inj file error! \n");
		return;
	}
	thread_loop_c(t,d)
	{
		begin_c_loop(c,t)
		{
			C_CENTROID(CC, c, t);
			
			/* To place a particle at every cell , 
			mesh file should be generated considering no of particles.*/
			
			VR = MAX_VOF * C_VOLUME;
			R = pow((3*VR/4/M_PI), 1.0/3.0);
			
			\*((x y z u v w diameter temperature mass-flow) name ) *\
			
			fprintf(fp, "\n ((\t%g\t%g\t%g\t0\t0\t0\t%g\t273.0\t%g) injection0 )", CC[0], CC[1], CC[2],DIAM_P,m_flow);
			
			
			/* for placing particle fully closed packing 
			particle will be placed  side by side. */
			
			
			if (sqrt(ND_SUM(pow(CC[0] - 0.5,2.),
							pow(CC[1] - 0.5,2.),
							pow(CC[2] - 0.5,2.))) < DIAM_P)
				{
					fprintf(fp, "\n ((\t%g\t%g\t%g\t0\t0\t0\t%g\t273.0\t%g) injection0 )", CC[0], CC[1], CC[2],DIAM_P,m_flow);
					
				}
			
			
			/* for 3D there are 3 argument CC[0],CC[1],CC[2]. For 2D take only CC[0],CC[1]*/
			
		}
		end_c_loop(c,t)
		
		}
		
		fclose(fp);
}
	
