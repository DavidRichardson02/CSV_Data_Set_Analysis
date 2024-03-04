//  PlottingMethods.c
//  CSV_File_Data_Set_Analysis_05


#include "PlottingMethods.h"
#include "GeneralUtilities.h"
#include "StringUtilities.h"
#include "FileUtilities.h"
#include "DataSetUtilities.h"





void gaussian_erf_plot(const char* filePathName)
{
    double xmin = 0.0;
    double xmax = 5.0;
    double step = 0.01;
    
    int n; // Number of samples
    double* x = get_uniform_samples(&n, xmin, xmax, step);  // Sample the x-axis uniformly
    double* f = compute_gaussian(n, x); // Compute the Gaussian samples
    double* F = gaussian_riemann_sum_integration(n, x, f); // Compute the integral samples using Riemann approximation
    
    
    
    
    char *directoryPathName = find_file_directory_path(filePathName);
    char *gaussian_erf_data = combine_char_ptr(directoryPathName, "gaussian_erf_data.txt");
    
    // Write the results to a file for plotting in MATLAB here
    FILE* data_file = fopen(gaussian_erf_data, "w");
    if (data_file == NULL)
    {
        perror("\n\nError: Could not open the file for writing in 'gaussian_erf_plot'.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(data_file, "%.17g %.17g %.17g\n", x[i], f[i], F[i]);

        
    }
    fclose(data_file);
    printf("\n\nData written to gaussian_erf_data.txt\n");




    char *matlabFile = combine_char_ptr(directoryPathName, "MATLAB_Guassian_Erf_Data_Plot.m");
    // Using the contents of the file that was written to previously, 'data.txt', create a ".m" matlab script that when run from a matlab application will plot the graphs.
    FILE* matlab_file = fopen(matlabFile, "w"); ///*footnote 5 in 'Utilities.h'*
    if (matlab_file == NULL)
    {
        perror("\n\nError: Could not open the MATLAB script file for writing in 'gaussian_erf_plot'.\n");
        exit(1);
    }

    fprintf(matlab_file, "data = load('gaussian_erf_data.txt');\n");
    fprintf(matlab_file, "x = data(:,1);\n");
    fprintf(matlab_file, "f = data(:,2);\n");
    fprintf(matlab_file, "F = data(:,3);\n\n");
    fprintf(matlab_file, "f1 = figure('Name', 'Gaussian and Error Function Plot');\n");
    fprintf(matlab_file, "plot(x, f, 'r', 'LineWidth', 1.5);\n\n");
    fprintf(matlab_file, "hold on;\n");
    fprintf(matlab_file, "plot(x, F, 'b', 'LineWidth', 1.5);\n\n");
    fprintf(matlab_file, "xlabel('x');\n");
    fprintf(matlab_file, "ytit = '$\\frac{f}{F}$';\n");
    fprintf(matlab_file, "ylabel(ytit,'interpreter','latex');\n\n");
    fprintf(matlab_file, "t = 'Gaussian $f =  \\frac{2}{\\sqrt{\\pi}}  e^{-x^{2}} $ and Error Function: $F = erf(x)$';\n\n");
    fprintf(matlab_file, "title(t,'interpreter','latex');\n\n");
    fprintf(matlab_file, "grid on;\n");
    fclose(matlab_file);
    printf("\n\nMATLAB script written to Plot_Problem_One_MATLAB.m\n");
    
    
    
    
    free(directoryPathName);
    free(gaussian_erf_data);
    free(x);
    free(f);
    free(F);
}








//
/*
void histogram_data_plot(const char *filePathName, const char *plotDirectory, const char *delimiter)
{
    FILE *file = fopen(filePathName, "r");
    if (!file)
    {
        perror("\n\nError: Unable to open file.\n");
        exit(1);
    }
    int n = count_file_lines(filePathName, MAX_NUM_FILE_LINES);
    char **particleContents = read_file_contents(filePathName, n);
    fclose(file);

    
    //Declare an array of Particle structs to hold particle data, the elements of the array capture a particle, i.e., a single entry of the data set
    // Populate the particles array Used to index individual lines in the file (i.e., the particles)
    
    int fieldCount = 0;
    // Call the parse_data function
    for(int i = 0; i < n; i++)
    {
        DataField* fields = parse_csv_data(particleContents[i], &fieldCount, delimiter);
        for (int j = 0; j < fieldCount; j++)
        {
            printf("Key: %s, Value: %s\n", fields[j].key, fields[j].value);
        }
        fieldCount = 0;
    }
    
    
    Particle particles[n];
    for(int i = 0; i < n; i++)
    {
        particles[i] = parse_particle_data(particleContents[i], delimiter);
    }


    double* pdg_idsHistogram = allocate_memory_double_ptr(n);  // PDG ID
    double* chargesHistogram = allocate_memory_double_ptr(n); // Charge
    double* ranksHistogram = allocate_memory_double_ptr(n);  // Rank
    double* massHistogram = allocate_memory_double_ptr(n); // Mass
    double* masses_lower_uncertaintiesHistogram = allocate_memory_double_ptr(n); // Mass Lower Uncertainty
    double* masses_upper_uncertaintiesHistogram = allocate_memory_double_ptr(n);  // Mass Upper Uncertainty
    double* decay_widthsHistogram = allocate_memory_double_ptr(n);     // Decay Widths
    double* decay_widths_lowerHistogram = allocate_memory_double_ptr(n); // Decay Widths Lower
    double* decay_widths_upperHistogram = allocate_memory_double_ptr(n); // Decay Widths Upper
    

    // Initialize the histogram arrays from the existing particle data arrays
    for(int i = 0; i < n; i++)
    {
        pdg_idsHistogram[i] = particles[i].pdg_id;
        chargesHistogram[i] = particles[i].charge;
        ranksHistogram[i] = particles[i].rank;

        printf("\n\n ranksHistogram[i]: %.17g", ranksHistogram[i]);
        
        
        massHistogram[i] = particles[i].mass;
        masses_lower_uncertaintiesHistogram[i] = particles[i].mass_lower_uncertainty;
        masses_upper_uncertaintiesHistogram[i] = particles[i].mass_upper_uncertainty;

        decay_widthsHistogram[i] = particles[i].decay_width;
        decay_widths_lowerHistogram[i] = particles[i].decay_width_lower;
        decay_widths_upperHistogram[i] = particles[i].decay_width_upper;
    }

    Histogram pdg_idHist, chargesHist, ranksHist, massHist, masses_lower_uncertaintiesHist, masses_upper_uncertaintiesHist, decay_widthsHist,decay_widths_lowerHist, decay_widths_upperHist;


    //Compute the Histograms
    pdg_idHist = compute_data_set_binning(&pdg_idsHistogram, n);     // PDG ID
    chargesHist = compute_data_set_binning(&chargesHistogram, n);     // Charge
    ranksHist = compute_data_set_binning(&ranksHistogram, n);     // Rank

    massHist = compute_data_set_binning(&massHistogram, n);     // Mass
    masses_lower_uncertaintiesHist = compute_data_set_binning(&masses_lower_uncertaintiesHistogram, n);     // Mass Lower Uncertainty
    masses_upper_uncertaintiesHist = compute_data_set_binning(&masses_upper_uncertaintiesHistogram, n);     // Mass Upper Uncertainty

    decay_widthsHist = compute_data_set_binning(&decay_widthsHistogram, n);     // Decay Widths
    decay_widths_lowerHist = compute_data_set_binning(&decay_widths_lowerHistogram, n);     // Decay Widths Lower
    decay_widths_upperHist = compute_data_set_binning(&decay_widths_upperHistogram, n);     // Decay Widths Upper


    print_histogram(ranksHist, "ranksHist");
    
    
    
    
    char **pdg_script = write_histogram_to_matlab_file(pdg_idHist, filePathName, "PDG ID", plotDirectory);
    char **charge_script = write_histogram_to_matlab_file(chargesHist, filePathName, "Charge", plotDirectory);
    char **rank_script = write_histogram_to_matlab_file(ranksHist, filePathName, "Rank", plotDirectory);
    char **mass_script = write_histogram_to_matlab_file(massHist, filePathName, "Mass", plotDirectory);
    char **masses_lower_script = write_histogram_to_matlab_file(masses_lower_uncertaintiesHist, filePathName, "Mass  Lower Uncertainty", plotDirectory);
    char **masses_upper_script = write_histogram_to_matlab_file(masses_upper_uncertaintiesHist, filePathName, "Mass Upper Uncertainty", plotDirectory);
    char **decay_width_script = write_histogram_to_matlab_file(decay_widthsHist, filePathName, "Decay Width", plotDirectory);
    char **decay_width_lower_script = write_histogram_to_matlab_file(decay_widths_lowerHist, filePathName, "Decay Width Lower Uncertainty", plotDirectory);
    char **decay_width_upper_script = write_histogram_to_matlab_file(decay_widths_upperHist, filePathName, "Decay Width Upper Uncertainty", plotDirectory);
    
    
    
    //const char *directoryPathName = plotDirectory;
    //char *directoryPathName = find_file_directory_path(plotDirectory);
    const char *histogramDataFilePathName = plotDirectory;
    histogramDataFilePathName = combine_char_ptr(histogramDataFilePathName, "_Histogram_Data_MATLAB_Plot.txt");
    
    // Write the results to a text file for plotting in MATLAB
    FILE* histogram_data_file = fopen(histogramDataFilePathName, "w+"); /// *footnote 5 in 'Utilities.h'*
    write_file_contents(histogramDataFilePathName, pdg_script);
    write_file_contents(histogramDataFilePathName, charge_script);
    write_file_contents(histogramDataFilePathName, rank_script);
    write_file_contents(histogramDataFilePathName, mass_script);
    write_file_contents(histogramDataFilePathName, masses_lower_script);
    write_file_contents(histogramDataFilePathName, masses_upper_script);
    write_file_contents(histogramDataFilePathName, decay_width_script);
    write_file_contents(histogramDataFilePathName, decay_width_lower_script);
    write_file_contents(histogramDataFilePathName, decay_width_upper_script);
    
    int lineCount = count_file_lines(histogramDataFilePathName, MAX_NUM_FILE_LINES);
    char **matlabScriptHistogram = read_file_contents(histogramDataFilePathName, lineCount);
    
    fclose(histogram_data_file);
    
    
    matlab_plot(filePathName, matlabScriptHistogram, plotDirectory);
    
   
    
    
    
    
    free(particleContents);
    //free(directoryPathName);
    free(histogramDataFilePathName);
    //free(pdg_names);
    //free(names);
    //free(quarks);
    free(pdg_idsHistogram);
    free(chargesHistogram);
    free(ranksHistogram);
    free(massHistogram);
    free(masses_lower_uncertaintiesHistogram);
    free(decay_widthsHistogram);
    free(decay_widths_lowerHistogram);
    free(decay_widths_upperHistogram);
}
//*/

















































































//
/*
void histogram_plot(const char* filePathName, const char *delimiter)
{
    FILE *file = fopen(filePathName, "r");
    if (!file)
    {
        perror("\n\nError: Unable to open file.\n");
        exit(1);
    }
    int n = count_file_lines(filePathName, MAX_NUM_FILE_LINES);
    int charCount = *count_characters_in_file_lines_range(filePathName, n, 0);
    char **weatherMeasurementContents = read_file_contents(filePathName, n);
    fclose(file);
    
    
    
    //print_file(filePathName);
    
    //Declare an array of Particle structs to hold particle data, the elements of the array capture a particle, i.e., a single entry of the data set
    // Populate the particles array Used to index individual lines in the file (i.e., the particles)
    WeatherMeasurement *weatherMeasurements;
    weatherMeasurements = (WeatherMeasurement*)malloc(n * sizeof(WeatherMeasurement));
    
    for(int i = 0; i < n; i++)
    {
        weatherMeasurements[i] = parse_weather_measurement_data(weatherMeasurementContents[i], delimiter);
        //print_weather_measurement(weatherMeasurements[i] );
    }
    
    //int fieldCount = count_data_fields(weatherMeasurementContents[10]);
    //printf("\n\nCount of Data fields: %d", fieldCount);
    
    double *airTemperatures = allocate_memory_double_ptr(n);
    double *wetBulbTemperatires = allocate_memory_double_ptr(n);
    double *humidities = allocate_memory_double_ptr(n);
    double *rainIntensities = allocate_memory_double_ptr(n);
    double *intervalRains = allocate_memory_double_ptr(n);
    double *totalRains = allocate_memory_double_ptr(n);
    double *windSpeeds = allocate_memory_double_ptr(n);
    double *maxWindSpeeds = allocate_memory_double_ptr(n);
    double *barometricPressures = allocate_memory_double_ptr(n);
    double *solarRadiations = allocate_memory_double_ptr(n);
    double *stationBatteryLifes = allocate_memory_double_ptr(n);
    
    for(int i = 0; i < n; i++)
    {
        airTemperatures[i] = weatherMeasurements[i].airTemperature;
        wetBulbTemperatires[i] = weatherMeasurements[i].wetBulbTemperatire;
        humidities[i] = weatherMeasurements[i].humidity;
        rainIntensities[i] = weatherMeasurements[i].rainIntensity;
        intervalRains[i] = weatherMeasurements[i].intervalRain;
        totalRains[i] = weatherMeasurements[i].totalRain;
        windSpeeds[i] = weatherMeasurements[i].windSpeed;
        maxWindSpeeds[i] = weatherMeasurements[i].maxWindSpeed;
        barometricPressures[i] = weatherMeasurements[i].barometricPressure;
        solarRadiations[i] = weatherMeasurements[i].solarRadiation;
        stationBatteryLifes[i] = weatherMeasurements[i].stationBatteryLife;
    }
    
    Histogram airTempHist, wetBulbTempHist, humidityHist, rainIntensityHist, rainIntervalHist, totalRainHist, windSpeedHist, maxWindSpeedHist,barometricPressureHist, solarRadiationHist, stationBatteryLifeHist;
    
    //Compute the Histograms
    airTempHist = compute_data_set_binning(&airTemperatures, n);
    wetBulbTempHist = compute_data_set_binning(&wetBulbTemperatires, n);
    humidityHist = compute_data_set_binning(&humidities, n);

    rainIntensityHist = compute_data_set_binning(&rainIntensities, n);
    rainIntervalHist = compute_data_set_binning(&intervalRains, n);
    totalRainHist = compute_data_set_binning(&totalRains, n);

    windSpeedHist = compute_data_set_binning(&windSpeeds, n);
    maxWindSpeedHist = compute_data_set_binning(&maxWindSpeeds, n);
    barometricPressureHist = compute_data_set_binning(&barometricPressures, n);

    solarRadiationHist = compute_data_set_binning(&solarRadiations, n);
    stationBatteryLifeHist = compute_data_set_binning(&stationBatteryLifes, n);

    
    
    /*-----------   Write Data Set Fields into Seperate Files   -----------* /
    const char *matlabPlotDirectory = create_directory(filePathName, "matlabPlotDirectory");
    printf("\n\nmatlabPlotDirectory: %s", matlabPlotDirectory);
    
    
    
    char **airTemperature_script = write_histogram_to_matlab_file(airTempHist, filePathName, "Air Temperature", matlabPlotDirectory);
    char **wetBulbTemperature_script = write_histogram_to_matlab_file(wetBulbTempHist, filePathName, "Wet Bulb Temperature", matlabPlotDirectory);
    char **humidity_script = write_histogram_to_matlab_file(humidityHist, filePathName, "Humidity", matlabPlotDirectory);
    
    char **rainIntensity_script = write_histogram_to_matlab_file(rainIntensityHist, filePathName, "Rain Intensity", matlabPlotDirectory);
    char **rainInterval_script = write_histogram_to_matlab_file(rainIntervalHist, filePathName, "Rain Interval", matlabPlotDirectory);
    char **totalRain_script = write_histogram_to_matlab_file(totalRainHist, filePathName, "Total Rain", matlabPlotDirectory);
    
    char **windSpeed_script = write_histogram_to_matlab_file(windSpeedHist, filePathName, "Wind Speed", matlabPlotDirectory);
    char **maxWindSpeed_script = write_histogram_to_matlab_file(maxWindSpeedHist, filePathName, "Max Wind Speed", matlabPlotDirectory);
    char **barometricPressure_script = write_histogram_to_matlab_file(barometricPressureHist, filePathName, "Barometric Pressure", matlabPlotDirectory);
    
    char **solarRadiation_script = write_histogram_to_matlab_file(solarRadiationHist, filePathName, "Solar Radiation", matlabPlotDirectory);
    char **stationBatteryLife_script = write_histogram_to_matlab_file(stationBatteryLifeHist, filePathName, "Station BatteryLife", matlabPlotDirectory);
    
    
    char *directoryPathName = find_file_directory_path(filePathName);
    const char *histogramDataFilePathName = combine_char_ptr(directoryPathName, "WEATHER_Histogram_Data_MATLAB_Plot.m");
    
    // Write the results to a text file for plotting in MATLAB
    FILE* histogram_data_file = fopen(histogramDataFilePathName, "w"); ///*footnote 5 in 'Utilities.h'*
    write_file_contents(histogramDataFilePathName, airTemperature_script);
    write_file_contents(histogramDataFilePathName, wetBulbTemperature_script);
    write_file_contents(histogramDataFilePathName, humidity_script);
    write_file_contents(histogramDataFilePathName, rainIntensity_script);
    write_file_contents(histogramDataFilePathName, rainInterval_script);
    write_file_contents(histogramDataFilePathName, totalRain_script);
    write_file_contents(histogramDataFilePathName, windSpeed_script);
    write_file_contents(histogramDataFilePathName, maxWindSpeed_script);
    write_file_contents(histogramDataFilePathName, barometricPressure_script);
    write_file_contents(histogramDataFilePathName, solarRadiation_script);
    write_file_contents(histogramDataFilePathName, stationBatteryLife_script);
    

    //int lineCount = count_file_lines(histogramDataFilePathName, MAX_NUM_FILE_LINES);
    //char **matlabScriptHistogram = read_file_contents(histogramDataFilePathName, lineCount);
    
    
    fclose(histogram_data_file);
    
    
    //matlab_plot(filePathName, matlabScriptHistogram);

    
}
//*/




void matlab_plot(const char* dataFilePathName, char **matlabScript, const char *matlabPlotDirectory)
{
    /*-----------   Write Data Set Fields into Seperate Files   -----------*/
    //const char *matlabPlotDirectory = create_directory(dataFilePathName);
    
    printf("\n\nmatlabPlotDirectory: %s", matlabPlotDirectory);
    const char *matlabFilePath = combine_char_ptr(matlabPlotDirectory, "_Histogram_Data_MATLAB_Plot.m");
    
    // Write the results to a text file for plotting in MATLAB
    FILE* matlab_file = fopen(matlabFilePath, "w+");
    write_file_contents(matlabFilePath, matlabScript);
    fclose(matlab_file);
    
    
    printf("\n\nMATLAB script written to MATLAB_Histogram_Data_Plot.m\n");
}



char ** write_histogram_to_matlab_file(Histogram histogram, const char *filePathName, const char *fileNameMatlab, const char *matlabPlotDirectory)
{
    /*-----------   Write Data Set Fields into Seperate Files   -----------*/
    char *matlabPlotDirectoryFilePath = allocate_memory_char_ptr(strlen(filePathName) + strlen(fileNameMatlab) + 1);
    sprintf(matlabPlotDirectoryFilePath, "_MATLAB_Histogram_Data_Plot_%s.txt", fileNameMatlab);
    const char *matlabFilePath = combine_char_ptr(matlabPlotDirectory, matlabPlotDirectoryFilePath);
    
      

    FILE* histogram_data_file = fopen(matlabFilePath, "a+");
    fprintf(histogram_data_file, "f1 = figure('Name', 'Particle Data Histogram Plots');\n");
    fprintf(histogram_data_file, "histogram = [");
    for (int i = 0; i < histogram.num_bins; i++)
    {
        fprintf(histogram_data_file, "%.17g ", histogram.min_value + i * histogram.bin_width);
    }
    fprintf(histogram_data_file, "];\n");
    

    
    
    fprintf(histogram_data_file, "counts = [");
    for (int i = 0; i < histogram.num_bins; i++)
    {
        fprintf(histogram_data_file, "%d ", histogram.bins[i]);
    }
    fprintf(histogram_data_file, "];\n");
    fprintf(histogram_data_file, "bar(histogram);\n");
    fprintf(histogram_data_file, "xlabel('%s');\n", fileNameMatlab);
    fprintf(histogram_data_file, "ylabel('Frequency');\n");
    fprintf(histogram_data_file, "title('%s %s');\n", fileNameMatlab, "Histogram");
    fclose(histogram_data_file);

    int lineCount = count_file_lines(matlabFilePath, MAX_NUM_FILE_LINES);
    char **matlabScript = read_file_contents(matlabFilePath, lineCount);
    
    
    //print_file_contents(matlabScript, lineCount);
    
    return matlabScript;
    
}
