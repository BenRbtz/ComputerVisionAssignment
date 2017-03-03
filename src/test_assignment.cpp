/**
********************************************************************************
*
*	@file		test_assignment.cpp
*
*	@brief		Testing the code for the first assingmen.
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
#include <exception>

#include "Image.h"


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    // Return code
    int error_code(0);
    
    // Catch exceptions
    try
    {
        Image test_image1;
        test_image1.loadPGM("/Users/Ben/Dropbox/CS/Year 3/Semester 1/ICP 3038/Assignments/Assignment2/test_image_original.pgm");
        
        Image test_image2;
        test_image2.loadPGM("/Users/Ben/Dropbox/CS/Year 3/Semester 1/ICP 3038/Assignments/Assignment2/test_image_negative.pgm");
        
        // Subtracting and assigning image1 pixel values from itself
        Image test_a = test_image1;
        test_a -= test_image1;
        test_a.savePGM("test_image_a.pgm");
        
        // Subtract and assigning image2 pixel values from image1 pixel values
        Image test_b = test_image1;
        test_b -= test_image2;
        test_b.savePGM("test_image_b.pgm");
        
        // Adding and assigning image1 pixel values to itself
        Image test_c = test_image1;
        test_c += test_image1;
        test_c.savePGM("test_image_c.pgm");
        
        // Adding and assigning image2 pixel values to image1 pixel values
        Image test_d = test_image1;
        test_d += test_image2;
        test_d.savePGM("test_image_d.pgm");
        
        Image test_e = !test_image1;
        test_e.savePGM("test_image_d.pgm");
        
		// Load an image
		Image input_1;
		input_1.loadPGM("/Users/Ben/Dropbox/CS/Year 3/Semester 1/ICP 3038/Assignments/Assignment2/input1.pgm");
		input_1.savePGM("output1.pgm");
    
        
        Image negative;
        negative = !input_1;
        negative.savePGM("negative1.pgm");

        std::cout << input_1.getMinValue() << "\t" << input_1.getMaxValue() << std::endl;
        std::cout << negative.getMinValue() << "\t" << negative.getMaxValue() << std::endl;

		Image input_2;
		input_2.loadPGM("/Users/Ben/Dropbox/CS/Year 3/Semester 1/ICP 3038/Assignments/Assignment2/input2.pgm");

        negative = !input_2;
        negative.savePGM("negative2.pgm");

        std::cout << input_2.getMinValue() << "\t" << input_2.getMaxValue() << std::endl;
        std::cout << negative.getMinValue() << "\t" << negative.getMaxValue() << std::endl;

		input_2.savePGM("output2.pgm");
        input_2.getROI(0, 0, 400, 400).savePGM("ROI1.pgm");
        input_2.getROI(100, 100, 300, 300).savePGM("ROI2.pgm");
    
		// Test the copy constructor
		Image test_image(input_1);
		if (input_1 != test_image)
		{
			std::cerr << "The image are different" << std::endl;
		}

        // Normalisation (contrast enhancement)
        test_image.normalise(); // Rescale the image dynamic between 0 and 1
        test_image *= 255.0; // Rescale the image dynamic between 0 and 255 to save it as a bitmap
        test_image.savePGM("normalise.pgm");

		// Test the assignment operator
		test_image = input_1;
		if (input_1 != test_image)
		{
			std::cerr << "The image are different" << std::endl;
		}

		// Test the save/load ASCII
		input_1.saveASCII("test1.mat");
		test_image.loadASCII("test1.mat");
		if (input_1 != test_image)
		{
			std::cerr << "The image are different" << std::endl;
		}

		// Test the save/load RAW
		input_1.saveRaw("test1.raw");
		test_image.loadRaw("test1.raw", input_1.getWidth(), input_1.getHeight());
		if (input_1 != test_image)
		{
			std::cerr << "The image are different" << std::endl;
		}
    
        // Test some operators
    	test_image = input_1 * 0.5 + input_2 * 0.5;

		Image temp_image1(input_1);
		Image temp_image2(input_2);
    
        temp_image1 *= 0.5;
        temp_image2 *= 0.5;
        temp_image1 += temp_image2;
		if (temp_image1 != test_image)
		{
			std::cerr << "The image are different" << std::endl;
		}
		test_image.savePGM("operator1.pgm");
    
        test_image = input_1 - input_2; // Values may be negative
        test_image.saveASCII("operator2.mat"); // Can be imported in ImageJ or Matlab
        test_image.normalise(); // Rescale the image dynamic between 0 and 1
        test_image *= 255; // Rescale the image dynamic between 0 and 255
        test_image.savePGM("operator2.pgm"); // Save the bitmap
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
