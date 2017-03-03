/**
********************************************************************************
*
*	@file		test_assignment2.cpp
*
*	@brief		Testing the filters, histogram and NCC/SAE.
*
*	@version	1.0
*
*	@date		9/12/2016
*
*	@author		Benjamin Roberts
*
*
********************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include <sstream>
#include <iostream>
#include <iomanip>
#include <exception>
#include <cmath>

#include "Image.h"
#include "test_assignment2.h"



//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    // Return code
    int error_code(0);
    
    // Catch exceptions
    try
    {
        // Test filters using lenna from /img/eeu47d-images/eeu47d-ImageJ Images/
        testFilters("lenna");

        // Test filters using clown from /img/eeu47d-images/eeu47d-ImageJ Images/
        testFilters("clown");
        
        // Test filters using bridge from /img/eeu47d-images/eeu47d-ImageJ Images/
        testFilters("bridge");
    }
    // An error occured
    catch (const std::exception& error)
    {
        error_code = 1;
        std::cerr << error.what() << std::endl;
    }
    catch (const std::string& error)
    {
        error_code = 1;
        std::cerr << error << std::endl;
    }
    catch (const char* error)
    {
        error_code = 1;
        std::cerr << error << std::endl;
    }
    catch (...)
    {
        error_code = 1;
        std::cerr << "Unknown error" << std::endl;
    }

    return (error_code);
}


void testFilters(std::string fileName) {
    // Load an image ( without noise)
    Image image;
    image.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/"+fileName+".txt");
    image.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+".txt");
    
    unsigned int number_of_pixels(image.getWidth() * image.getHeight());
    
    // Compute the histogram with a small number of bins
    // (compare with the same histogram in ImageJ)
    image.writeHistogram(8, "octave/my_"+fileName+"_histogram.txt");
    
    // Load an image (image with salt and pepper noise)
    Image image_noise;
    image_noise.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/"+fileName+"_noise.txt");
    image_noise.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_noise.txt");
    
    // Compute the histogram with a small number of bins
    // (compare with the same histogram in ImageJ)
    image_noise.writeHistogram(8, "octave/my_"+fileName+"_noise_histogram.txt");
    

    
    
    
    //============= SAE ===============
    std::cout << std::endl;
    std::cout << "Image Used: " + fileName << std::endl << std::endl;
    std::cout << "Test SAE:" << std::endl;
    
    // Should be ~ 0
    double SAE_test_1(image.computeSAE(image));
    double expected_results_3(0.0);
    std::cout << "SAE(I1, I1):  " << std::fixed << std::setprecision(2) <<
    SAE_test_1 << "   " <<
    (std::abs(SAE_test_1 - expected_results_3) < 1.0e-3?"SUCCESS":"FAILURE") << std::endl;
    
    // Should be ~ 0
    double SAE_test_2(image_noise.computeSAE(image_noise));
    std::cout << "SAE(I2, I2): " << std::fixed << std::setprecision(2) <<
    SAE_test_2 << "   " <<
    (std::abs(SAE_test_2 - expected_results_3) < 1.0e-3?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    //============= NCC ===============
    
    std::cout << "Test NCC:" << std::endl;
    
    // Should be ~ 100%
    double NCC_test_1(image.computeNCC(image * 3 + 2));
    double expected_results_1(1.0);
    std::cout << "NCC(I1,  I1 * 3 + 2):  " << std::fixed << std::setprecision(2) <<
    100.0 * NCC_test_1 << "\%   " <<
    (std::abs(NCC_test_1 - expected_results_1) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    // Should be ~ -100%
    double NCC_test_2(image.computeNCC(!image * 3 + 2));
    double expected_results_2(-1.0);
    std::cout << "NCC(I1, -I1 * 3 + 2): " << std::fixed << std::setprecision(2) <<
    100.0 * NCC_test_2 << "\%   " <<
    (std::abs(NCC_test_2 - expected_results_2) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    std::cout << std::endl;
    

    
    
    // TEST FILTERS
    std::cout << std::endl << std::endl;
    std::cout << "FILTER TYPE:\t" << " SAE  " << " MAE  " << "  NCC   " << "   STATUS" << std::endl;
    
    
    
    
    
    //============= CONVOLUTION ===============
    // Convolution on image
    double testArray[] = {1,1,1,
                          1,1,1,
                          1,1,1};
    Image my_image_convoultion( image.convolution(testArray)/9);
    my_image_convoultion.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_convolution.txt");
    
    // Same filter on ImageJ
    Image imagej_image_convoultion;
    imagej_image_convoultion.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_convolution.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_convolution(imagej_image_convoultion.computeSAE(my_image_convoultion));
    double NCC_convolution(imagej_image_convoultion.computeNCC(my_image_convoultion));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Convolution    \t" <<
    SAE_convolution << "  " <<
    SAE_convolution / number_of_pixels << "  " <<
    100.0 * NCC_convolution << "\%   " <<
    (std::abs(NCC_convolution - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    //============= CONVOLUTION2 ===============
    // Convolution on image
    double testArray2[] = {1,2,1,
                           1,2,1,
                           1,2,1};
    Image my_image_convoultion2( image.convolution(testArray2)/9 );
    my_image_convoultion.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_convolution2.txt");
    
    // Same filter on ImageJ
    Image imagej_image_convoultion2;
    imagej_image_convoultion2.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_convolution2.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_convolution2(imagej_image_convoultion2.computeSAE(my_image_convoultion2));
    double NCC_convolution2(imagej_image_convoultion2.computeNCC(my_image_convoultion2));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Convolution2   \t" <<
    SAE_convolution2 << "  " <<
    SAE_convolution2 / number_of_pixels << "  " <<
    100.0 * NCC_convolution2 << "\%   " <<
    (std::abs(NCC_convolution2 - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    //======== MEDIAN FILTER ==========
    
    // Median filter on image with salt and pepper noise
    Image my_image_noise_median_filter(image_noise.medianFilter());
    my_image_noise_median_filter.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_noise_median_filter.txt");
    
    // Same filter on ImageJ
    Image imagej_image_noise_median_filter;
    imagej_image_noise_median_filter.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_noise_median_filter.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_median(imagej_image_noise_median_filter.computeSAE(my_image_noise_median_filter));
    double NCC_median(imagej_image_noise_median_filter.computeNCC(my_image_noise_median_filter));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Median      \t" <<
    SAE_median << "  " <<
    SAE_median / number_of_pixels << "  " <<
    100.0 * NCC_median << "\%   " <<
    (std::abs(NCC_median - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    
    
    
    //======== GAUSSIAN FILTER ==========
    
    // Gaussian filter on image with salt and pepper noise
    Image my_image_noise_gaussian_filter(image_noise.gaussianFilter());
    my_image_noise_gaussian_filter.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_noise_gaussian_filter.txt");
    
    // Same filter on ImageJ
    Image imagej_image_noise_gaussian_filter;
    imagej_image_noise_gaussian_filter.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_noise_gaussian_filter.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_gaussian(imagej_image_noise_gaussian_filter.computeSAE(my_image_noise_gaussian_filter));
    double NCC_gaussian(imagej_image_noise_gaussian_filter.computeNCC(my_image_noise_gaussian_filter));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Gaussian      \t" <<
    SAE_gaussian << "  " <<
    SAE_gaussian / number_of_pixels << "  " <<
    100.0 * NCC_gaussian << "\%   " <<
    (std::abs(NCC_gaussian - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    //======== MEAN FILTER ==========
    
    // Mean filter (also called box filter and average filter) on image with salt and pepper noise
    Image my_image_noise_mean_filter(image_noise.meanFilter());
    my_image_noise_mean_filter.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_noise_mean_filter.txt");
    // Same filter on ImageJ
    Image imagej_image_noise_mean_filter;
    imagej_image_noise_mean_filter.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_noise_mean_filter.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_mean(imagej_image_noise_mean_filter.computeSAE(my_image_noise_mean_filter));
    double NCC_mean(imagej_image_noise_mean_filter.computeNCC(my_image_noise_mean_filter));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Mean      \t\t" <<
    SAE_mean << "  " <<
    SAE_mean / number_of_pixels << "  " <<
    100.0 * NCC_mean << "\%   " <<
    (std::abs(NCC_mean - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    //======== LAPLACIAN FILTER ==========
    
    // Laplacian filter on image
    Image my_image_laplacian_filter(image.laplacianFilter());
    my_image_laplacian_filter.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_laplacian_filter.txt");
    // Same filter on ImageJ
    Image imagej_image_laplacian_filter;
    imagej_image_laplacian_filter.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_laplacian_filter.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_laplacian(imagej_image_laplacian_filter.computeSAE(my_image_laplacian_filter));
    double NCC_laplacian(imagej_image_laplacian_filter.computeNCC(my_image_laplacian_filter));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Laplacian      \t" <<
    SAE_laplacian << "  " <<
    SAE_laplacian / number_of_pixels << "  " <<
    100.0 * NCC_laplacian << "\%   " <<
    (std::abs(NCC_laplacian - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    
    //======== SOBEL EDGE DETECTOR ==========
    
    // Sobel edge detector on image
    Image my_image_sobel_edge_detector(image.sobelEdgeDetector());
    my_image_sobel_edge_detector.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_sobel_edge_detector.txt");
    // Same filter on ImageJ
    Image imagej_image_sobel_edge_detector;
    imagej_image_sobel_edge_detector.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_sobel_edge_detector.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_sobel(imagej_image_sobel_edge_detector.computeSAE(my_image_sobel_edge_detector));
    double NCC_sobel(imagej_image_sobel_edge_detector.computeNCC(my_image_sobel_edge_detector));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Sobel      \t\t" <<
    SAE_sobel << "  " <<
    SAE_sobel / number_of_pixels << "  " <<
    100.0 * NCC_sobel << "\%   " <<
    (std::abs(NCC_sobel - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    
    //======== PREWITT EDGE DETECTOR =========
    
    // Prewitt edge detector on image
    Image my_image_prewitt_edge_detector(image.sobelEdgeDetector());
    my_image_prewitt_edge_detector.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_prewitt_edge_detector.txt");
    // Same filter on ImageJ
    Image imagej_image_prewitt_edge_detector;
    imagej_image_prewitt_edge_detector.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_prewitt_edge_detector.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_prewitt(imagej_image_prewitt_edge_detector.computeSAE(my_image_prewitt_edge_detector));
    double NCC_prewitt(imagej_image_prewitt_edge_detector.computeNCC(my_image_prewitt_edge_detector));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Prewitt      \t" <<
    SAE_prewitt << "  " <<
    SAE_prewitt / number_of_pixels << "  " <<
    100.0 * NCC_prewitt << "\%   " <<
    (std::abs(NCC_prewitt - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    
    
    //============== SHARPEN ================
    
    // Sharpen on image, with value 'a' equal to 4.
    Image my_image_sharpen(image.sharpening(4));
    my_image_sharpen.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_sharpen.txt");
    // Same filter on ImageJ
    Image imagej_image_sharpen;
    imagej_image_sharpen.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_sharpen.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_sharpen(imagej_image_sharpen.computeSAE(my_image_sharpen));
    double NCC_sharpen(imagej_image_sharpen.computeNCC(my_image_sharpen));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Sharpen      \t" <<
    SAE_sharpen << "  " <<
    SAE_sharpen / number_of_pixels << "  " <<
    100.0 * NCC_sharpen << "\%   " <<
    (std::abs(NCC_sharpen - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    
    //======== THRESHOLDING ==========
    
    // Change threshold values on image
    Image my_image_threshold(image.segmentationThresholding(125)*255);
    my_image_threshold.saveASCII("img/eeu47d-images/eeu47d-Code Images/my_"+fileName+"_threshold.txt");
    // Same filter on ImageJ
    Image imagej_image_threshold;
    imagej_image_threshold.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/imagej_"+fileName+"_threshold.txt");
    
    // Compute the SAE/NCC between the image produced by ImageJ and the one produced by the code
    double SAE_threshold(imagej_image_threshold.computeSAE(my_image_threshold));
    double NCC_threshold(imagej_image_threshold.computeNCC(my_image_threshold));
    
    // Display image comparison metrics
    std::cout << std::fixed << std::setprecision(2) <<
    "Threshold      \t" <<
    SAE_threshold << "  " <<
    SAE_threshold / number_of_pixels << "  " <<
    100.0 * NCC_threshold << "\%   " <<
    (std::abs(NCC_threshold - 1.0) < 1.0e-2?"SUCCESS":"FAILURE") << std::endl;
    
    
    
    
    //============= BLENDING ================
    
    // Blending between two images
    Image pal;
     if (fileName == "clown")
        pal.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/pigeon.txt");
    else
        pal.loadASCII("img/eeu47d-images/eeu47d-ImageJ Images/PAL.txt");
    
    // Alpha from 0 to 1
    const unsigned int number_of_blended_images(5);
    std::cout << std::endl << "Test for blending: see output images." << std::endl << std::endl;
    for (unsigned int i(0); i < number_of_blended_images; ++i)
    {
        // Convert int to alpha in range [0, 1]
        double alpha(double(i) / double(number_of_blended_images - 1));
        
        // Blending
        Image blended_image(pal.blending(my_image_noise_median_filter, alpha));
        
        // Create a file name
        std::stringstream file_name;
        file_name << "img/eeu47d-images/eeu47d-Code Images/"+fileName+"_blend_" << i << ".txt";
        
        // Save the new image
        blended_image.saveASCII(file_name.str());
    }

    
    
    
    // Free memory
    image.destroy();
    image_noise.destroy();
    
    my_image_noise_median_filter.destroy();
    my_image_noise_gaussian_filter.destroy();
    my_image_sharpen.destroy();
    my_image_threshold.destroy();
    my_image_laplacian_filter.destroy();
    my_image_prewitt_edge_detector.destroy();
    my_image_noise_mean_filter.destroy();
    my_image_sobel_edge_detector.destroy();
    
    imagej_image_noise_median_filter.destroy();
    imagej_image_noise_gaussian_filter.destroy();
    imagej_image_sharpen.destroy();
    imagej_image_threshold.destroy();
    imagej_image_laplacian_filter.destroy();
    imagej_image_prewitt_edge_detector.destroy();
    imagej_image_noise_mean_filter.destroy();
    imagej_image_sobel_edge_detector.destroy();
}
