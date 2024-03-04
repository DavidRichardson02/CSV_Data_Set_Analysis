//  main.c
//  CSV_File_Data_Set_Analysis_05


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "GeneralUtilities.h"
#include "StringUtilities.h"
#include "FileUtilities.h"
#include "DataSetUtilities.h"
#include "Integrators.h"
#include "StatisticalMethods.h"
#include "PlottingMethods.h"
#include "DataAnalysis.h"






int main(int argc, const char * argv[])
{
    /*-----------   User-Provide Pathname(Hardcoded for now)   -----------*/
    const char *particleDataSetFilePathName = "/Users/98dav/Desktop/Xcode/C-Programs/CSV_File_Data_Set_Analysis_05/physics_particles.txt";
    //const char *particleDataSetFilePathName =  "/Users/98dav/Desktop/Xcode/C-Programs/CSV_File_Data_Set_Analysis_04/weather_measurements.csv"; // weatherDataSetFilePathName
    
    //
    /*
    DataSetAnalysis particleDataSet = configure_data_set_analysis(particleDataSetFilePathName);
    //*/
    
    
    
    
    //DataSetProperties dataSetProperties = analyze_data_set_properties(particleDataSetFilePathName);
    
    
    ///*
    /*-----------   Capture File Contents in an Array of Strings   -----------*/
    int lineCount = count_file_lines(particleDataSetFilePathName, MAX_NUM_FILE_LINES);
    char **fileContents = read_file_contents(particleDataSetFilePathName, lineCount);
    const char *delimiter = identify_delimiter(fileContents, lineCount);

    
    
    /*-----------   Run Data Set   -----------*/
    run_data_set(particleDataSetFilePathName, fileContents, lineCount, delimiter);
    //*/
    
    
    return 0;
}
