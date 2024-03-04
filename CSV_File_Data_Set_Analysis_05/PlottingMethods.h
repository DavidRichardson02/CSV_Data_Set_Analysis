//  PlottingMethods.h
//  CSV_File_Data_Set_Analysis_05


#ifndef PlottingMethods_h
#define PlottingMethods_h




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Integrators.h"
#include "StatisticalMethods.h"






typedef struct
{
    // members for the plottable data set
    // member for the MATLAB script to be generated
    
} DataPlottingScript;








// ------------- Helper Functions for Creating MATLAB(.m) Scripts/Files to Plot Some Model(various statistical models of a file's(.csv) data set, including but not limited to: histogram, theoretical distribution, standard normal distribution, etc.) of Data -------------
/// \{
//void particle_data_plot();


void gaussian_erf_plot(const char* filePathName);

void histogram_plot(const char* filePathName, const char *delimiter);


void histogram_data_plot(const char *filePathName, const char *plotDirectory, const char *delimiter);
char ** write_histogram_to_matlab_file(Histogram histogram, const char *filePathName, const char *fileNameMatlab, const char *matlabPlotDirectory);


void matlab_plot(const char* dataFilePathName, char **matlabScript, const char *matlabPlotDirectory);



//void theoretical_distribution_plot();
//void stndard_normal_distribution_plot();
/// \}





#endif /* PlottingMethods_h */
