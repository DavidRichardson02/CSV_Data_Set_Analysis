# CSV File Data Set Analysis

## Overview
This repository provides a comprehensive suite of C utilities and functions for standardizing, automating data extraction, and preprocessing CSV file contents for analysis. The program captures and formats CSV file contents, generates custom directories of files, extracts data, performs analysis, and generates MATLAB scripts for further visualization.


## Usage

Include the necessary header files in your C project. Below is a basic example to get you started:

```c
#include "GeneralUtilities.h"
#include "StringUtilities.h"
#include "FileUtilities.h"
#include "DataSetUtilities.h"
#include "Integrators.h"
#include "StatisticalMethods.h"
#include "PlottingMethods.h"
#include "DataAnalysis.h"

int main() {
    const char *filePath = "path/to/your/csvfile.csv";
    char **fileContents = capture_and_prepare_data_set_contents(filePath);
    DataSetAnalysis dataSet = configure_data_set_analysis(filePath);
    run_data_set(filePath, fileContents, dataSet.lineCount, dataSet.delimiter);

    return 0;
}
```

## Header Files

### GeneralUtilities.h

Provides a collection of general utility functions for memory allocation, date/time conversions, bitwise operations, and sorting algorithms optimized for handling large datasets.

### StringUtilities.h

Offers utilities for string manipulation, analysis, and formatting. Useful for data parsing and preprocessing in data integration and analysis.

### FileUtilities.h

Includes functions for file-related operations such as analyzing file paths, counting data fields and characters, reading/writing file contents, merging file contents, and managing directories of files.

### DataSetUtilities.h

Contains functions for processing, analyzing, and formatting datasets stored in CSV format, facilitating data visualization and plotting by preparing datasets in a suitable format.

### Integrators.h

Defines functions for numerical integration, including methods like the Trapezoidal rule, Simpson's rule, Midpoint rule, Romberg's method, Euler's method, Verlet's method, and the Runge-Kutta method.

### StatisticalMethods.h

Provides functions for generating and sampling datasets, computing statistical properties, integrating statistical distributions, and performing statistical tests to assess the normality of datasets.

### PlottingMethods.h

Offers helper functions for creating MATLAB scripts to plot various statistical models of a dataset, including histograms and Gaussian plots.

### DataAnalysis.h

Defines structures and functions for configuring and analyzing datasets, capturing and preparing dataset contents, formatting datasets, and running dataset analysis.
