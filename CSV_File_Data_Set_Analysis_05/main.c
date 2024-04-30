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
	printf("Entering: 'main' function.\n");
    /*-----------   User-Provide Pathname(Hardcoded for now)   -----------*/
    const char *particleDataSetFilePathName = "/Users/98dav/Desktop/Xcode/C-Programs/CSV_File_Data_Set_Analysis_05/physics_particles.txt";
    const char *weatherDataSetFilePathName =  "/Users/98dav/Desktop/Xcode/C-Programs/CSV_File_Data_Set_Analysis_05/weather_measurements.csv"; // weatherDataSetFilePathName
    
	const char *merge1_path = "/Users/98dav/Library/Mobile Documents/com~apple~TextEdit/Documents/HomeOwner.txt";//"/Users/98dav/Desktop/ECE-370/Homework PDF's/Homework 5/HomeElectricalDeviceHeaderFile copzz.txt";
	const char *merge2_path = "/Users/98dav/Library/Mobile Documents/com~apple~TextEdit/Documents/HomeElectricalDevice.txt";//"/Users/98dav/Desktop/ECE-370/Homework PDF's/Homework 5/HomeElectricalDeviceImplementationFile.txt";
    
	const char *mergez_path = "/Users/98dav/Desktop/ECE-370/Homework PDF's/MergedHomeDevices.txt";//"/Users/98dav/Desktop/ECE-370/Homework PDF's/Homework 5/HomeElectricalDeviceHeaderFile copy 2.txt";
	const char *merges_path = "/Users/98dav/Desktop/ECE-370/Homework PDF's/MergedHomeDevices copy.txt";
    
    
    /*-----------   Merge Two Files   -----------*/
    merge_files(particleDataSetFilePathName, weatherDataSetFilePathName, merges_path);
	merge_filez(particleDataSetFilePathName, weatherDataSetFilePathName, mergez_path);
    
    print_file(mergez_path);
	
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	print_file(merges_path);
	
    
    //
    /*
    DataSetAnalysis particleDataSet = configure_data_set_analysis(particleDataSetFilePathName);
    //*/
    
    
    
    
    //DataSetProperties dataSetProperties = analyze_data_set_properties(particleDataSetFilePathName);
    
    
    ///*
    /*-----------   Capture File Contents in an Array of Strings   -----------*/
    //int lineCount = count_file_lines(particleDataSetFilePathName, MAX_NUM_FILE_LINES);
    //char **fileContents = read_file_contents(particleDataSetFilePathName, lineCount);
    //const char *delimiter = identify_delimiter(fileContents, lineCount);

    
    
    /*-----------   Run Data Set   -----------*/
    //run_data_set(particleDataSetFilePathName, fileContents, lineCount, delimiter);
    //*/
    
    
    return 0;
}



