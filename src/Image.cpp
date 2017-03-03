/**
********************************************************************************
*
*   @file       Image.cpp
*
*   @brief      Class to handle a greyscale image.
*
*   @version    1.0
*
*   @todo
*
*   @date       9/12/2016
*
*   @author     Benjamin Roberts
*
*
********************************************************************************
*/


//******************************************************************************
//  Define
//******************************************************************************
#define LINE_SIZE 2048
#define KERNEL_WIDTH 3
#define KERNEL_HEIGHT 3
//******************************************************************************
//  Include
//******************************************************************************
#include <sstream> // Header file for stringstream
#include <iostream> //cout
#include <fstream> // Header file for filestream
#include <algorithm> // Header file for min/max/fill
#include <cmath> // Header file for abs
#include <vector>
#include <numeric> //accumate

#include "Image.h"


//------------------
Image::Image():
//------------------
        m_width(0),
        m_height(0),
        m_p_image(0)
//------------------
{}


//----------------------------------------------
Image::Image(const Image& anImage):
//----------------------------------------------
        m_width(anImage.m_width),
        m_height(anImage.m_height),
        m_p_image(new double[m_width * m_height])
//----------------------------------------------
{
    // Out of memeory
    if (m_width && m_height && !m_p_image)
    {
        throw "Out of memory";
    }
    
    // Copy the data
    std::copy(anImage.m_p_image, anImage.m_p_image + m_width * m_height, m_p_image);
}


//----------------------------------------------
Image::Image(const double* apData,
             unsigned int aWidth,
             unsigned int aHeight):
//----------------------------------------------
        m_width(aWidth),
        m_height(aHeight),
        m_p_image(new double[m_width * m_height])
//----------------------------------------------
{
    // Out of memeory
    if (m_width && m_height && !m_p_image)
    {
        throw "Out of memory";
    }

    // Copy the data
    std::copy(apData, apData + m_width * m_height, m_p_image);
}


//----------------------------------------------
Image::Image(unsigned int aWidth,
             unsigned int aHeight):
//----------------------------------------------
        m_width(aWidth),
        m_height(aHeight),
        m_p_image(new double[m_width * m_height])
//----------------------------------------------
{
    // Out of memeory
    if (m_width && m_height && !m_p_image)
    {
        throw "Out of memory";
    }

    // Initialise the data
    std::fill_n(m_p_image, m_width * m_height, 0);
}


//-------------
Image::~Image()
//-------------
{
    // Release memory
    destroy();
}


//-------------------
void Image::destroy()
//-------------------
{
    // Memory has been dynamically allocated
    if (m_p_image)
    {
        // Release the memory
        delete [] m_p_image;
    
        // Make sure the pointer is reset to NULL
        m_p_image = 0;
    }
    
    // There is no pixel in the image
    m_width  = 0;
    m_height = 0;
}


//---------------------------------------------
Image Image::getROI(unsigned int i,
                    unsigned int j,
                    unsigned int aWidth,
                    unsigned int aHeight) const
//---------------------------------------------
{
    // Create a black image
    Image roi(aWidth, aHeight);

    // Process every row of the ROI
    for (unsigned y(0); y < aHeight; ++y)
    {
        // Process every column of the ROI
        for (unsigned x(0); x < aWidth; ++x)
        {
            unsigned int index_i(x + i);
            unsigned int index_j(y +j);

            // The pixel index is valid
            if ((index_i < m_width) && (index_j < m_height))
            {
                // Get the pixel intensity from the current instance
                double intensity(getPixel(index_i, index_j));

                // Set the pixel of the ROI
                roi.setPixel(x, y, intensity);
            }
        }
    }
    
    return (roi);
}


//----------------------------------------------------------------
void Image::setPixel(unsigned int i, unsigned int j, double aValue)
//----------------------------------------------------------------
{
    
    // The pixel index is not valid
    if (i >= m_width || j >= m_height)
    {
        std::cout<< "x axis: " << i <<" y axis " << j<< std::endl;
        throw "Invalid pixel coordinate";
    }
    
    // Change the pixel value
    m_p_image[j * m_width + i] = aValue;
}


//---------------------------------------------------------
double Image::getPixel(unsigned int i, unsigned int j) const
//---------------------------------------------------------
{
    // The pixel index is valid
    if (i >= m_width || j >= m_height)
    {
        throw "Invalid pixel coordinate";
    }
    
    // Return the pixel value
    return (m_p_image[j * m_width + i]);
}


//-------------------------------------------
Image& Image::operator=(const Image& anImage)
//-------------------------------------------
{
    // The images different
    if (this != &anImage)
    {
        // Release memory
        destroy();

        // Copy the image properites
        m_width   = anImage.m_width;
        m_height  = anImage.m_height;
        m_p_image = new double[m_width * m_height];

        // Out of memeory
        if (m_width && m_height && !m_p_image)
        {
            throw "Out of memory";
        }
        
        // Copy the data
        std::copy(anImage.m_p_image, anImage.m_p_image + m_width * m_height, m_p_image);
    }

    // Return the instance
    return (*this);
}


//------------------------------------------
Image Image::operator+(const Image& anImage)
//------------------------------------------
{
    // Deal with images of different sizes
    unsigned int min_width(std::min(m_width, anImage.m_width));
    unsigned int min_height(std::min(m_height, anImage.m_height));
    
    // Copy the instance into a temporary variable
    Image temp(getROI(0, 0, min_width, min_height));
    
    // Copy the data
    for (unsigned int j(0); j < min_height; ++j)
    {
        for (unsigned int i(0); i < min_width; ++i)
        {
            temp.m_p_image[j * temp.m_width + i] += anImage.m_p_image[j * anImage.m_width + i];
        }
    }
    
    // Return the result
    return (temp);
}


//------------------------------------------
Image Image::operator-(const Image& anImage)
//------------------------------------------
{
    // Deal with images of different sizes
    unsigned int min_width(std::min(m_width, anImage.m_width));
    unsigned int min_height(std::min(m_height, anImage.m_height));
    
    // Copy the instance into a temporary variable
    Image temp(getROI(0, 0, min_width, min_height));
    
    // Copy the data
    for (unsigned int j(0); j < min_height; ++j)
    {
        for (unsigned int i(0); i < min_width; ++i)
        {
            temp.m_p_image[j * temp.m_width + i] -= anImage.m_p_image[j * anImage.m_width + i];
        }
    }
    
    // Return the result
    return (temp);
}


//--------------------------------------------
Image& Image::operator+=(const Image& anImage)
//--------------------------------------------
{
    // Re-use operator+
    *this = *this + anImage;
    
    // Return the result
    return (*this);
}


//--------------------------------------------
Image& Image::operator-=(const Image& anImage)
//--------------------------------------------
{
    // Re-use operator-
    *this = *this - anImage;
    
    // Return the result
    return (*this);
}


//----------------------------------
Image Image::operator+(double aValue)
//----------------------------------
{
    // Copy the instance into a temporary variable
    Image temp(*this);

    double* p_temp(temp.m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ += aValue;
    }
    
    // Return the result
    return (temp);
}


//----------------------------------
Image Image::operator-(double aValue)
//----------------------------------
{
    // Copy the instance into a temporary variable
    Image temp(*this);

    double* p_temp(temp.m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ -= aValue;
    }
    
    // Return the result
    return (temp);
}


//----------------------------------
Image Image::operator*(double aValue)
//----------------------------------
{
    // Copy the instance into a temporary variable
    Image temp(*this);

    double* p_temp(temp.m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ *= aValue;
    }
    
    // Return the result
    return (temp);
}


//----------------------------------
Image Image::operator/(double aValue)
//----------------------------------
{
    // Division by zero
    if (std::abs(aValue) < 1.0e-6)
    {
        throw "Division by zero.";
    }
    
    // Copy the instance into a temporary variable
    Image temp(*this);

    double* p_temp(temp.m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ /= aValue;
    }
    
    // Return the result
    return (temp);
}


//-----------------------------------
Image& Image::operator+=(double aValue)
//-----------------------------------
{
    double* p_temp(m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ += aValue;
    }
    
    // Return the result
    return (*this);
}


//------------------------------------
Image& Image::operator-=(double aValue)
//------------------------------------
{
    double* p_temp(m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ -= aValue;
    }
    
    // Return the result
    return (*this);
}


//------------------------------------
Image& Image::operator*=(double aValue)
//------------------------------------
{
    double* p_temp(m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ *= aValue;
    }
    
    // Return the result
    return (*this);
}


//------------------------------------
Image& Image::operator/=(double aValue)
//------------------------------------
{
    // Division by zero
    if (std::abs(aValue) < 1.0e-6)
    {
        throw "Division by zero.";
    }
    
    double* p_temp(m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ /= aValue;
    }
    
    // Return the result
    return (*this);
}


//----------------------
Image Image::operator!()
//----------------------
{
    // Copy the instance into a temporary variable
    Image temp(*this);

    double min_value(getMinValue());
    double max_value(getMaxValue());
    double range(max_value - min_value);
    
    double* p_temp(temp.m_p_image);
    
    // Process every pixel
    for (unsigned int i(0); i < m_width * m_height; ++i, ++p_temp)
    {
        // Take care to preserve the dynamic of the image
        *p_temp = min_value + range * (1.0 - (*p_temp - min_value) / range);
    }
    
    // Return the result
    return (temp);
}


//---------------------------------
double Image::getAspectRatio() const
//---------------------------------
{
    return (double(m_width) / double(m_height));
}


//----------------------------------
unsigned int Image::getWidth() const
//----------------------------------
{
    return (m_width);
}


//-----------------------------------
unsigned int Image::getHeight() const
//-----------------------------------
{
    return (m_height);
}


//------------------------------
double Image::getMinValue() const
//------------------------------
{
    // The image is empty
    if (!m_p_image)
    {
        throw "Empty image";
    }
    // returns min value from image
    return (*std::min_element(&m_p_image[0], &m_p_image[m_width * m_height]));
}


//------------------------------
double Image::getMaxValue() const
//------------------------------
{
    // The image is empty
    if (!m_p_image)
    {
        throw "Empty image";
    }
    // returns max value from image
    return (*std::max_element(&m_p_image[0], &m_p_image[m_width * m_height]));
}


//----------------------------------------------------------------
void Image::shiftScaleFilter(double aShiftValue, double aScaleValue)
//----------------------------------------------------------------
{
    // Process every pixel of the image
    for (unsigned int i = 0; i < m_width * m_height; ++i)
        // Apply the shilft/scale filter
        m_p_image[i] = (m_p_image[i] + aShiftValue) * aScaleValue;
}


//---------------------
void Image::normalise()
//---------------------
{
    shiftScaleFilter(-getMinValue(), 1.0 / (getMaxValue() - getMinValue()));
}


//----------------------------------------
void Image::loadPGM(const char* aFileName)
//----------------------------------------
{
    // Open the file
    std::ifstream input_file(aFileName, std::ifstream::binary);
    
    // The file does not exist
    if (!input_file.is_open())
    {
        // Build the error message
        std::stringstream error_message;
        error_message << "Cannot open the file \"" << aFileName << "\". It does not exist";
    
        // Throw an error
        throw (error_message.str());
    }
    // The file is open
    else
    {
        // Release the memory if necessary
        destroy();
    
        // Variable to store a line
        char p_line_data[LINE_SIZE];
    
        // Get the first line
        input_file.getline(p_line_data, LINE_SIZE);

        // Get the image type
        std::string image_type(p_line_data);
    
        // Valid ASCII format
        if (image_type == "P2")
        {
            // Variable to save the max value
            int max_value(-1);
        
            // There is data to read
            unsigned int pixel_count(0);
            while (input_file.good())
            {
                // Get the new line
                input_file.getline(p_line_data, LINE_SIZE);
    
                // It is not a comment
                if (p_line_data[0] != '#')
                {
                    // Store the line in a stream
                    std::stringstream stream_line;
                    stream_line << std::string(p_line_data);
                
                    // The memory is not allocated
                    if (!m_p_image && !m_width && !m_height)
                    {
                        // Load the image size
                        stream_line >> m_width >> m_height;
                    
                        // Alocate the memory
                        m_p_image = new double[m_width * m_height];
                    
                        // Out of memory
                        if (!m_p_image)
                        {
                            throw ("Out of memory");
                        }
                    }
                    // The max value is not set
                    else if (max_value < 0)
                    {
                        // Get the max value;
                        stream_line >> max_value;
                    }
                    // Read the pixel data
                    else
                    {
                        // Process all the pixels of the line
                        while (stream_line.good())
                        {
                            // Get the pixel value
                            int pixel_value(-1);
                            stream_line >> pixel_value;
                            // The pixel exists
                            if (pixel_count < m_width * m_height)
                            {
                                m_p_image[pixel_count++] = pixel_value;
                            }
                        }
                    }
                }
            }
        }
        // Valid binary format
        else if (image_type == "P5")
        {
            // Variable to save the max value
            int max_value(-1);

            // There is data to read
            while (input_file.good())
            {
            	// Process as an ASCII file
                if (!m_width || !m_height || max_value < 0)
                {
                    // Get the new line
                    input_file.getline(p_line_data, LINE_SIZE);

                    // It is not a comment
                    if (p_line_data[0] != '#')
                    {
                        // Store the line in a stream
                        std::stringstream stream_line;
                        stream_line << std::string(p_line_data);

                        // The memory is not allocated
                        if (!m_p_image && !m_width && !m_height)
                        {
                            // Load the image size
                            stream_line >> m_width >> m_height;

                            // Alocate the memory
                            m_p_image = new double[m_width * m_height];

                            // Out of memory
                            if (!m_p_image)
                            {
                                throw ("Out of memory");
                            }
                        }
                        // The max value is not set
                        else
                        {
                            // Get the max value;
                            stream_line >> max_value;
                        }
                    }
                }
                // Read the pixel data
                else
                {
                	unsigned char* p_temp(new unsigned char[m_width * m_height]);

                    // Out of memory
                    if (!p_temp)
                    {
                        throw ("Out of memory");
                    }

                    input_file.read(reinterpret_cast<char*>(p_temp), m_width * m_height);

                	for (unsigned int i(0); i < m_width * m_height; ++i)
                	{
                		m_p_image[i] = p_temp[i];
                	}
                	delete [] p_temp;
                }
            }
        }
        // Invalid format
        else
        {
            // Build the error message
            std::stringstream error_message;
            error_message << "Invalid file (\"" << aFileName << "\")";

            // Throw an error
            throw (error_message.str());
        }
    }
}


//-----------------------------------------------
void Image::loadPGM(const std::string& aFileName)
//-----------------------------------------------
{
    loadPGM(aFileName.data());
}


//----------------------------------------
void Image::savePGM(const char* aFileName)
//----------------------------------------
{
    // Open the file
    std::ofstream output_file(aFileName);
    
    // The file does not exist
    if (!output_file.is_open())
    {
        // Build the error message
        std::stringstream error_message;
        error_message << "Cannot create the file \"" << aFileName << "\"";
    
        // Throw an error
        throw (error_message.str());
    }
    // The file is open
    else
    {
        // Set the image type
        output_file << "P2" << std::endl;
    
        // Print a comment
        output_file << "# ICP3038 -- Assignment 1 -- 2016/2017" << std::endl;
    
        // The image size
        output_file << m_width << " " << m_height << std::endl;

        // The get the max value
        //output_file << std::min(255, std::max(0, int(getMaxValue()))) << std::endl;
        output_file << std::max(255, int(getMaxValue())) << std::endl;
    
        // Process every line
        for (unsigned int j = 0; j < m_height; ++j)
        {
            // Process every column
            for (unsigned int i = 0; i < m_width; ++i)
            {
                // Process the pixel
                int pixel_value(m_p_image[j * m_width + i]);
                pixel_value = std::max(0, pixel_value);
                pixel_value = std::min(255, pixel_value);
            
                output_file << pixel_value;
            
                // It is not the last pixel of the line
                if (i < (m_width - 1))
                {
                    output_file << " ";
                }
            }
        
            // It is not the last line of the image
            if (j < (m_height - 1))
            {
                output_file << std::endl;
            }
        }
    }
}


//-----------------------------------------------
void Image::savePGM(const std::string& aFileName)
//-----------------------------------------------
{
    savePGM(aFileName.data());
}


//----------------------------------------
void Image::loadRaw(const char* aFileName,
                    unsigned int aWidth,
                    unsigned int aHeight)
//----------------------------------------
{
    // Open the file in binary
    std::ifstream input_file (aFileName, std::ifstream::binary);

    // The file is not open
    if (!input_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") does not exist";

        throw error_message;
    }

    // Get size of file
    input_file.seekg(0, input_file.end);
    unsigned int size(input_file.tellg());

    // The size is not correct
    if (aWidth * aHeight * sizeof(double) != size)
    {
        std::stringstream error_message;
        error_message << "The size of " << aFileName << " is not " <<
                aWidth << "x" << aHeight;

        throw error_message.str();
    }

    // Rewind the file
    input_file.seekg (0);

    // Release the memory
    destroy();

    // Allocate memory for file content
    m_width = aWidth;
    m_height = aHeight;
    m_p_image = new double[m_width * m_height];

    // Read content of input_file
    input_file.read(reinterpret_cast<char*>(m_p_image), size);
}


//-----------------------------------------------
void Image::loadRaw(const std::string& aFileName,
                    unsigned int aWidth,
                    unsigned int aHeight)
//-----------------------------------------------
{
    loadRaw(aFileName.data(), aWidth, aHeight);
}


//----------------------------------------
void Image::saveRaw(const char* aFileName)
//----------------------------------------
{
    // Open the file in binary
    std::ofstream output_file (aFileName, std::ifstream::binary);

    // The file is not open
    if (!output_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") cannot be created";

        throw error_message;
    }

    // Write content to file
    output_file.write(reinterpret_cast<char*>(m_p_image), m_width * m_height * sizeof(double));
}


//-----------------------------------------------
void Image::saveRaw(const std::string& aFileName)
//-----------------------------------------------
{
    saveRaw(aFileName.data());
}


//------------------------------------------
void Image::loadASCII(const char* aFileName)
//------------------------------------------
{
    // Open the file
    std::ifstream input_file (aFileName);

    // The file is not open
    if (!input_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") does not exist";

        throw error_message;
    }

    // Load the data into a vector
    std::vector<double> p_data;
    std::string line;
    int number_of_rows(0);
    int number_of_columns(0);

    // Read evely line
    while (std::getline(input_file, line))
    {
        number_of_columns = 0;
        double intensity;
        std::stringstream line_parser;
        line_parser << line;
        while (line_parser >> intensity)
        {
            p_data.push_back(intensity);
            ++number_of_columns;
        }
        ++number_of_rows;
    }

    // Wrong number of pixels
    if (number_of_rows * number_of_columns != p_data.size())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") is invalid";

        throw error_message;
    }

    // Release the memory
    destroy();

    // Allocate memory for file content
    m_width = number_of_columns;
    m_height = number_of_rows;
    m_p_image = new double[m_width * m_height];

    // Copy the data
    std::copy(p_data.begin(), p_data.end(), m_p_image);
}


//-------------------------------------------------
void Image::loadASCII(const std::string& aFileName)
//-------------------------------------------------
{
    loadASCII(aFileName.data());
}


//------------------------------------------
void Image::saveASCII(const char* aFileName)
//------------------------------------------
{
    // Open the file
    std::ofstream output_file (aFileName);

    // The file is not open
    if (!output_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") cannot be created";

        throw error_message;
    }

    // Write content to file
    double* p_data(m_p_image);
    for (unsigned int j(0); j < m_height; ++j)
    {
        for (unsigned int i(0); i < m_width; ++i)
        {
            output_file << *p_data++;

            // This is not the last pixel of the line
            if (i < m_width - 1)
            {
                output_file << " ";
            }
        }

        // This is not the last line
        if (j < m_height - 1)
        {
            output_file << std::endl;
        }
    }
}


//-------------------------------------------------
void Image::saveASCII(const std::string& aFileName)
//-------------------------------------------------
{
    saveASCII(aFileName.data());
}


//------------------------------------------------
bool Image::operator==(const Image& anImage) const
//------------------------------------------------
{
    if (m_width != anImage.m_width)
    {
        return (false);
    }

    if (m_height != anImage.m_height)
    {
        return (false);
    }

    double const * p_data1(m_p_image);
    double const * p_data2(anImage.m_p_image);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        if (std::abs(*p_data1++ - *p_data2++) > 1.0e-6)
        {
            return (false);
        }
    }

    return (true);
}


//------------------------------------------------
bool Image::operator!=(const Image& anImage) const
//------------------------------------------------
{
    return (!(operator==(anImage)));
}


//----------------------------
Image Image::abs(const Image& aImage)
//----------------------------
{
    // If image is empty
    if(!aImage.m_p_image)
        throw "Image Empty";
    
    Image tempImage(m_width, m_height);
    
    for(int row(0);row<m_height;row++)
        for(int col(0);col<m_width;col++)
            // Add pixels from x and y sobel images together
            tempImage.setPixel(col,row, std::abs(aImage.getPixel(col, row)));
    
    return tempImage;
}


//----------------------------
double Image::getSum() const
//----------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    double pixelSum = 0;
    
    // Adds all pixel values into varaible
    for(unsigned int i(0); i<m_width*m_height; i++)
        pixelSum += m_p_image[i];

    return pixelSum;
}


//--------------------------------
double Image::getAverage() const
//--------------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    // Sum of image pixels divided by
    // amount of pixels
    return getSum() / (m_height * m_width);
}


//---------------------------------
double Image::getVariance() const
//---------------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    double avg = getAverage();
    double variance = 0;
    
    // Loop through each pixel
    for(unsigned int i(0); i<m_width * m_height; i++)
        // Subtract images pixel by mean and multiply agaisnt each other
        variance += (m_p_image[i] - avg) * (m_p_image[i] - avg);
    
    // Divide the Sum by the image size to get variance
    return ( variance / (m_height * m_width) );
}


//------------------------------------------
double Image::getStandardDeviation() const
//------------------------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    double avg = getAverage();
    double standardDeviation = 0.0;
    
    // Loop through each pixel and store the standard deviation
    for(unsigned int i(0); i < m_height*m_width; i++)
        standardDeviation += pow(m_p_image[i] - avg, 2);

    return sqrt(standardDeviation / (m_height * m_width) ) ;
}


//------------------------------------------------
double Image::computeSAE(const Image& aImage) const
//------------------------------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    else if(!aImage.m_p_image)
        throw "aImage Empty";
    
    double saeValue = 0.0;
    
    // Loop through each pixel of two images
    for (unsigned int i(0); i < (m_height*m_width); i++)
        // Minus from each other, store absoutle value
        saeValue += std::abs(m_p_image[i] - aImage.m_p_image[i]);
    
    return saeValue;
}


//------------------------------------------------
double Image::computeNCC(const Image& aImage) const
//------------------------------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    else if(!aImage.m_p_image)
        throw "aImage Empty";
    
    double nccValue = 0.0;
    
    // Mean for both images
    double avg1 = getAverage();
    double avg2 = aImage.getAverage();
    
    // Standard Deviation for both images
    double stanDev1 = getStandardDeviation();
    double stanDev2 = aImage.getStandardDeviation();
    
    // Loop through each pixel of two images
    for (int i = 0; i < (m_height*m_width); i++)
        // Calcualting ncc value
        nccValue += (( (m_p_image[i] - avg1) * (aImage.m_p_image[i] - avg2) ) / (stanDev1 * stanDev2));
    
    return nccValue/ (m_height * m_width) ;
}


//---------------------------
Image Image::convolution(double kernelArray[])
//---------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    Image tempImage(m_width, m_height);
    
    double kernelValue;
    double imageValue;
    double pixelValue;
    double pixelSum;
    
    // Store current (kernel index + imageindex) for row and column, respectively
    int tempRow,tempCol;
    
    // Move kernel through all pixels of the image
    for(int row(0); row < m_height; row++)
        for(int col(0); col < m_width; col++) {
            
            pixelSum = 0.0;
            
            // Move through kernel elements
            for(int kRow(0);kRow<KERNEL_HEIGHT;kRow++)
                for(int kCol(0);kCol<KERNEL_WIDTH;kCol++) {
                    // Image index plus kernel index - Row, Coloumn
                    tempRow = (kRow - 1) + row;
                    tempCol = (kCol - 1) + col;
                    
                    // If a index is less than 0
                    // Resets to 0
                    if (tempRow < 0 && tempCol < 0){
                        tempRow = 0;
                        tempCol = 0;
                    } else if (tempRow < 0)
                        tempRow = 0;
                    else if (tempCol < 0)
                        tempCol = 0;
                    
                    // If a index is greater than the image size
                    // set to highest
                    if(tempRow >= m_height && tempCol >= m_width){
                        tempRow = m_height -1;
                        tempCol = m_width-1;
                    }else if (tempRow >=m_height)
                        tempRow = m_height -1;
                    else if (tempCol >=m_width)
                        tempCol = m_width-1;
                    
                    // multiply pixel value with corresponding kernal value
                    kernelValue = kernelArray[kCol * KERNEL_WIDTH + kRow];
                    imageValue = m_p_image[tempRow * m_width + tempCol];
                    pixelValue = kernelValue * imageValue;
                    pixelSum += pixelValue;
                }
            
            
            // Assign kernel value to pixel
            tempImage.setPixel(col, row, pixelSum);
        }
    
    return tempImage;
}


//------------------------
Image Image::medianFilter()
//------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    Image tempImage(m_width, m_height);
    
    std::vector<double> kernel;
    
    // Store current (kernel index + imageindex) for row and column, respectively
    int tempRow, tempCol;
    
    // Move kernel through all pixels of the image
    for (int row(0);row<m_height;row++) {
        for(int col(0);col<m_width;col++) {
            
            //   Pick up kernel elements
            for (int kRow(row - 1); kRow < row + 2; kRow++)
                for (int kCol(col - 1); kCol < col + 2; kCol++){
 
                    // If the kernel value is within the image
                    // Store image pixel value with corresponding kernal value
                    tempRow = kRow;
                    tempCol = kCol;
                    
                    
                    // If a index is less than 0
                    // Resets to 0
                    if (tempRow < 0 && tempCol < 0){
                        tempRow = 0;
                        tempCol = 0;
                    } else if (tempRow < 0)
                        tempRow = 0;
                    else if (tempCol < 0)
                        tempCol = 0;
                    
                    
                    // If a index is greater than the image size
                    // set to highest
                    if(tempRow >= m_height && tempCol >= m_width){
                        tempRow = m_height -1;
                        tempCol = m_width-1;
                    }else if (tempRow >=m_height)
                        tempRow = m_height -1;
                    else if (tempCol >=m_width)
                        tempCol = m_width-1;
                    
                    // Holds values within kernel indexs
                    kernel.push_back( m_p_image[tempRow * m_width + tempCol] );
                }
            
            // Sort vector
            std::sort(kernel.begin(), kernel.end());
            
            // Assign window median to pixel
            tempImage.setPixel(col, row, kernel[round(kernel.size()/2)]);
            
            // Empty Vector
            kernel.clear();
        }
    }
    
    return tempImage;
}


//---------------------------
Image Image::gaussianFilter()
//---------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    Image tempImage(m_width, m_height);
    
    double gaussianKernel[] = {1, 2, 1,
                                2, 4, 2,
                                1, 2, 1};
    
    // Apply gaussian kernel to image
    tempImage = convolution(gaussianKernel);
    
    return (tempImage / 16);
}


//------------------------
Image Image::meanFilter()
//------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    Image tempImage(m_width, m_height);
    
    double meanKernel[] = {1, 1, 1,
                            1, 1, 1,
                            1, 1, 1};
    
    // Applying box kernel to image
    tempImage = convolution(meanKernel);
    
    return (tempImage / 9);
}


//---------------------------
Image Image::laplacianFilter()
//---------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";

    Image tempImage(m_width, m_height);
    
    double laplacianKernel[] = {0, 1, 0,
                                1, -4, 1,
                                0, 1, 0};
    
    // Applying laplacian kernel to image
    tempImage = convolution(laplacianKernel);
    
    return tempImage;
}


//---------------------------
Image Image::sobelEdgeDetector()
//---------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    double xSobelKernel[] = {1, 0, -1,
                             2, 0, -2,
                             1, 0, -1};
    
    double ySobelKernel[] = {1, 2, 1,
                            0, 0, 0,
                            -1, -2, -1};

    // Applying both sobel kernels to separate images
    // Add absoulte values of both images together
    return abs(convolution(xSobelKernel)) + abs(convolution(ySobelKernel));
}


//---------------------------
Image Image::prewittEdgeDetector()
//---------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    double xPrewittKernel[] = {-1, 0, 1,
                               -1, 0, 1,
                               -1, 0, 1};
    
    double yPrewittKernel[] = {-1, -1, -1,
                                0, 0, 0,
                                1, 1, 1};
    
    // Applying both sobel kernels to separate images
    // Add absoulte values of both images together
    return abs(convolution(xPrewittKernel)) + abs(convolution(yPrewittKernel));
}


//------------------------------------------
Image Image::sharpening(double sharpenValue)
//------------------------------------------
{
    Image originalImage(m_p_image, m_width, m_height);
    
    // Get image detail
    Image gaussianImage = originalImage.gaussianFilter();
    Image imageDetail = originalImage - gaussianImage;
    
    //Sharpen detail
    imageDetail *= sharpenValue;
    
    //return image with sharpened image
    return (originalImage + imageDetail);
}


//-----------------------------------------------------------------
Image Image::segmentationThresholding(double thresholdValue)
//-----------------------------------------------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    Image tempImage(m_width, m_height);
    
    //   Move through all elements of the image
    for (int row(0); row < m_height; row++)
        for (int col(0); col < m_width; col++)
            // Assign 0 if below threshold
            // otherwise assign 1
            if (m_p_image[row * m_width + col] > thresholdValue)
                tempImage.setPixel(col, row, 1);
            else
                tempImage.setPixel(col, row, 0);
    
    return tempImage;
}



//------------------------------------------------------
Image Image::blending(const Image& aImage, double alpha)
//------------------------------------------------------
{
    if(m_width != aImage.m_width || m_height != aImage.m_height)
        throw "Image Sizes are different";
    
    Image tempImage(m_width, m_height);
    double blendValue = 0;
    
    //   Move through all elements of the image
    for (int row(0); row < m_height; row++)
        for (int col(0); col < m_width; col++) {
            
            // Multiple pixel from both images by alpha
            // Add both pixels values together
            blendValue = (1 - alpha)*getPixel(col, row) + alpha* aImage.getPixel(col, row);
            
            tempImage.setPixel(col, row, blendValue);
        }
    
    return tempImage;
}


//-----------------------------------------------------------------------------
std::vector<unsigned int> Image::getHistogram(unsigned int aNumberOfBins) const
//-----------------------------------------------------------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    std::vector<unsigned int> p_histogram_data(aNumberOfBins, 0);
    
    double binMax = getMaxValue();
    double binMin = getMinValue();
    double rangeBin = (binMax - binMin) / aNumberOfBins;
    
    // keeps track of bin values
    double tempBinMin = 0 , tempBinMax = 0;
    tempBinMax = binMin + rangeBin;
    
    for(unsigned int i = 0;  i < (m_height*m_width); i++) {

        
        // Loops through each bin
        for (int j = 0; j < aNumberOfBins; j++)
            // Increase bin if value is within range
            if (j != aNumberOfBins - 1 ){
                if( m_p_image[i] >= tempBinMin  && m_p_image[i] < tempBinMax) {
                    p_histogram_data[j]++;
                    break;
                }
                else {
                    // If not within range
                    // Set range for next bin
                    tempBinMin += rangeBin;
                    tempBinMax += rangeBin;
                }
            }
            else {
                // Catch top value in the last bin
                if( m_p_image[i] >= tempBinMin) {
                    p_histogram_data[j]++;
                    break;
                }
            }

    
        
        // Set bin range
        tempBinMin = binMin;
        tempBinMax = binMin + rangeBin;
    }
    
    return p_histogram_data;
}



//---------------------------------------------------------------------------------
void Image::writeHistogram(unsigned int aNumberOfBins, const char* aFileName) const
//---------------------------------------------------------------------------------
{
    // If image is empty
    if(!m_p_image)
        throw "Image Empty";
    
    std::ofstream output_stream(aFileName); // Open the file
    std::string filename = aFileName;// stores filename as string
    
    // The file is not open
    if (!output_stream.is_open())
    {
        // Throw an error
        std::string error_message("Cannot open file (" + filename + ").");
        throw (error_message);
    }
    else
    {
        // Work out bin range
        double binMax = getMaxValue();
        double binMin = getMinValue();
        double rangeBin = (binMax - binMin) / aNumberOfBins;
        
        std::vector<unsigned int> p_histogram_data = getHistogram(aNumberOfBins);
    
        output_stream <<"\"Min bin value\" \"Count\"" << std::endl;
        
        for (int i = 0; i< aNumberOfBins; i++){
            output_stream << binMin << " " << p_histogram_data[i] << std::endl;
            binMin+= rangeBin;
        }
        
        output_stream.close(); // Close the file
    }
}


//----------------------------------------------------------------------------------------
void Image::writeHistogram(unsigned int aNumberOfBins, const std::string& aFileName) const
//----------------------------------------------------------------------------------------
{
    writeHistogram(aNumberOfBins, aFileName.data());
}
