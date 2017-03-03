#ifndef IMAGE_H
#define IMAGE_H


/**
********************************************************************************
*
*   @file       Image.h
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
//  Include
//******************************************************************************
#include <string>
#include <vector>

//==============================================================================
/**
*   @class  Image
*   @brief  Image is a class to manage a greyscale image.
*/
//==============================================================================
class Image
//------------------------------------------------------------------------------
{
//******************************************************************************
public:
    //--------------------------------------------------------------------------
    /// Default constructor.
    //--------------------------------------------------------------------------
    Image();


    //------------------------------------------------------------------------
    /// Copy constructor.
    /**
    * @param anImage: the image to copy
    */
    //------------------------------------------------------------------------
    Image(const Image& anImage);
    
    
    //------------------------------------------------------------------------
    /// Constructor from an array.
    /**
    * @param apData: the array to copy
    * @param aWidth: the width of the image
    * @param aHeight: the height of the image
    */
    //------------------------------------------------------------------------
    Image(const double* apData,
                 unsigned int aWidth,
                 unsigned int aHeight);


    //------------------------------------------------------------------------
    /// Constructor to build a black image.
    /**
    * @param aWidth: the width of the image
    * @param aHeight: the height of the image
    */
    //------------------------------------------------------------------------
    Image(unsigned int aWidth,
                 unsigned int aHeight);


    //------------------------------------------------------------------------
    /// Destructor.
    //------------------------------------------------------------------------
    ~Image();
    
    
    //------------------------------------------------------------------------
    /// Assignment operator (also called copy operator).
    /**
    * @param anImage: the image to copy
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    Image& operator=(const Image& anImage);
    
    
    //------------------------------------------------------------------------
    /// Release the memory.
    //------------------------------------------------------------------------
    void destroy();
    
    
    //------------------------------------------------------------------------
    /// Compute a region of interest (ROI).
    /**
    * @param i: the position of the first pixel of the ROI along the horizontal axis
    * @param j: the position of the first pixel of the ROI along the vertical axis
    * @param aWidth: the width of the ROI (in number of pixels)
    * @param aHeight: the height of the ROI (in number of pixels)
    * @return the ROI
    */
    //------------------------------------------------------------------------
    Image getROI(unsigned int i,
            unsigned int j,
            unsigned int aWidth,
            unsigned int aHeight) const;


    //------------------------------------------------------------------------
    /// Set a pixel.
    /**
    * @param i: the position of the pixel along the horizontal axis
    * @param j: the position of the pixel along the vertical axis
    * @param aValue: the new pixel value
    */
    //------------------------------------------------------------------------
    void setPixel(unsigned int i, unsigned int j, double aValue);
    
    
    //------------------------------------------------------------------------
    /// Accessor on a pixel value.
    /**
    * @param i: the position of the pixel along the horizontal axis
    * @param j: the position of the pixel along the vertical axis
    * @return the pixel value
    */
    //------------------------------------------------------------------------
    double getPixel(unsigned int i, unsigned int j) const;
    
    
    //------------------------------------------------------------------------
    /// Addition operator. Add anImage
    /**
    * @param anImage: the image to add
    * @return the resulting image
    */
    //------------------------------------------------------------------------
    Image operator+(const Image& anImage);
    
    
    //------------------------------------------------------------------------
    /// Subtraction operator. Add anImage
    /**
    * @param anImage: the image to subtract
    * @return the resulting image
    */
    //------------------------------------------------------------------------
    Image operator-(const Image& anImage);


    //------------------------------------------------------------------------
    /// Addition assignment operator. Add anImage
    /**
    * @param anImage: the image to add
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    Image& operator+=(const Image& anImage);


    //------------------------------------------------------------------------
    /// Subraction assignment operator. Add anImage
    /**
    * @param anImage: the image to subtract
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    Image& operator-=(const Image& anImage);
    
    
    //------------------------------------------------------------------------
    /// Addition operator. Add aValue to every pixel of the image
    /**
    * @param aValue: the value to add
    * @return the resulting image
    */
    //------------------------------------------------------------------------
    Image operator+(double aValue);


    //------------------------------------------------------------------------
    /// Subtraction operator. Subtract aValue to every pixel of the image
    /**
    * @param aValue: the value to subtract
    * @return the resulting image
    */
    //------------------------------------------------------------------------
    Image operator-(double aValue);


    //------------------------------------------------------------------------
    /// Multiplication operator. Multiply every pixel of the image by aValue
    /**
    * @param aValue: the value for the multiplication
    * @return the resulting image
    */
    //------------------------------------------------------------------------
    Image operator*(double aValue);
    
    
    //------------------------------------------------------------------------
    /// Division operator. Divide every pixel of the image by aValue
    /**
    * @param aValue: the value for the division
    * @return the resulting image
    */
    //------------------------------------------------------------------------
    Image operator/(double aValue);


    //------------------------------------------------------------------------
    /// Addition operator. Add aValue to every pixel of the image
    /**
    * @param aValue: the value to add
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    Image& operator+=(double aValue);


    //------------------------------------------------------------------------
    /// Subtraction operator. Subtract aValue to every pixel of the image
    /**
    * @param aValue: the value to subtract
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    Image& operator-=(double aValue);


    //------------------------------------------------------------------------
    /// Multiplication operator. Multiply every pixel of the image by aValue
    /**
    * @param aValue: the value for the multiplication
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    Image& operator*=(double aValue);


    //------------------------------------------------------------------------
    /// Division operator. Divide every pixel of the image by aValue
    /**
    * @param aValue: the value for the division
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    Image& operator/=(double aValue);


    //------------------------------------------------------------------------
    /// Negation operator. Compute the negative of the current image.
    /**
    * @return the negative image
    */
    //------------------------------------------------------------------------
    Image operator!();
    

    //------------------------------------------------------------------------
    /// Compute the aspect ratio
    /**
    * @return the aspect ratio
    */
    //------------------------------------------------------------------------
    double getAspectRatio() const;


    //------------------------------------------------------------------------
    /// Number of pixels along the horizontal axis
    /**
    * @return the width
    */
    //------------------------------------------------------------------------
    unsigned int getWidth() const;
    

    //------------------------------------------------------------------------
    /// Number of pixels along the vertical axis
    /**
    * @return the height
    */
    //------------------------------------------------------------------------
    unsigned int getHeight() const;
    

    //------------------------------------------------------------------------
    /// Compute the minimum pixel value in the image
    /**
    * @return the minimum pixel
    */
    //------------------------------------------------------------------------
    double getMinValue() const;
    

    //------------------------------------------------------------------------
    /// Compute the maximum pixel value in the image
    /**
    * @return the maximum pixel
    */
    //------------------------------------------------------------------------
    double getMaxValue() const;
    

    //------------------------------------------------------------------------
    /// Add aShiftValue to every pixel, then multiply every pixel
    /// by aScaleValue
    /**
    * @param aShiftValue: the shift parameter of the filter
    * @param aScaleValue: the scale parameter of the filter
    */
    //------------------------------------------------------------------------
    void shiftScaleFilter(double aShiftValue, double aScaleValue);
    
    
    //------------------------------------------------------------------------
    /// Normalise the image between 0 and 1
    //------------------------------------------------------------------------
    void normalise();
    
    
    //------------------------------------------------------------------------
    /// Normalize the image between 0 and 1
    //------------------------------------------------------------------------
    void normalize();
    
    
    //------------------------------------------------------------------------
    /// Load an image from a PGM file
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    void loadPGM(const char* aFileName);
    
    
    //------------------------------------------------------------------------
    /// Load an image from a PGM file
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    void loadPGM(const std::string& aFileName);
    
    
    //------------------------------------------------------------------------
    /// Save the image in a PGM file
    /**
    * @param aFileName: the name of the file to write
    */
    //------------------------------------------------------------------------
    void savePGM(const char* aFileName);
    
    
    //------------------------------------------------------------------------
    /// Save the image in a PGM file
    /**
    * @param aFileName: the name of the file to write
    */
    //------------------------------------------------------------------------
    void savePGM(const std::string& aFileName);
    

    //------------------------------------------------------------------------
    /// Load an image from a Raw file
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    void loadRaw(const char* aFileName,
            unsigned int aWidth,
            unsigned int aHeight);
    
    
    //------------------------------------------------------------------------
    /// Load an image from a Raw file
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    void loadRaw(const std::string& aFileName,
            unsigned int aWidth,
            unsigned int aHeight);
    
    
    //------------------------------------------------------------------------
    /// Save the image in a Raw file
    /**
    * @param aFileName: the name of the file to write
    */
    //------------------------------------------------------------------------
    void saveRaw(const char* aFileName);
    
    
    //------------------------------------------------------------------------
    /// Save the image in a Raw file
    /**
    * @param aFileName: the name of the file to write
    */
    //------------------------------------------------------------------------
    void saveRaw(const std::string& aFileName);
    

    //------------------------------------------------------------------------
    /// Load an image from an ASCII file
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    void loadASCII(const char* aFileName);
    
    
    //------------------------------------------------------------------------
    /// Load an image from an ASCII file
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    void loadASCII(const std::string& aFileName);
    
    
    //------------------------------------------------------------------------
    /// Save the image in an ASCII file
    /**
    * @param aFileName: the name of the file to write
    */
    //------------------------------------------------------------------------
    void saveASCII(const char* aFileName);
    
    
    //------------------------------------------------------------------------
    /// Save the image in an ASCII file
    /**
    * @param aFileName: the name of the file to write
    */
    //------------------------------------------------------------------------
    void saveASCII(const std::string& aFileName);
   
   
    //------------------------------------------------------------------------
    /// Operator Equal to
    /**
    * @param anImage: the image to compare with
    * @return true if the images are similar,
    *         false if they are different
    */
    //------------------------------------------------------------------------
    bool operator==(const Image& anImage) const;


    //------------------------------------------------------------------------
    /// Operator Not equal to
    /**
    * @param anImage: the image to compare with
    * @return true if the images are different,
    *         false if they are similar
    */
    //------------------------------------------------------------------------
	bool operator!=(const Image& anImage) const;
    
    
    //------------------------------------------------------------------------
    /// Image with absoulte pixel values
    /**
     * @param anImage: the image manipulate
     * @return image with absoulte pixel values,
     */
    //------------------------------------------------------------------------
    Image abs(const Image& aImage);
    
    
    //------------------------------------------------------------------------
    /// Compute the sum of all the elements.
    /**
     * @return the sum of all the elements
     */
    //------------------------------------------------------------------------
    double getSum() const;
    
    
    //------------------------------------------------------------------------
    /// Compute the average.
    /**
     * @return the average
     */
    //------------------------------------------------------------------------
    double getAverage() const;
    
    
    //------------------------------------------------------------------------
    /// Compute the variance.
    /**
     * @return the variance
     */
    //------------------------------------------------------------------------
    double getVariance() const;
    
    
    //------------------------------------------------------------------------
    /// Compute the standard deviation.
    /**
     * @return the standard deviation
     */
    //------------------------------------------------------------------------
    double getStandardDeviation() const;
    
    
    //------------------------------------------------------------------------
    /// Compute the sum of absolute errors (SAE) between two vectors.
    /**
     * @param aVector: the vector to use in the comparison
     * @return the SAE
     */
    //------------------------------------------------------------------------
    double computeSAE(const Image& aImage) const;
    
    
    //------------------------------------------------------------------------
    /// Compute the normalised-cross correlation (NCC) between two vectors.
    /**
     * @param aVector: the vector to use in the comparison
     * @return the NCC
     */
    //------------------------------------------------------------------------
    double computeNCC(const Image& aImage) const;
    
    
    //------------------------------------------------------------------------
    /// Compute the convoultion of an image with provided kernel.
    /**
     * @param kernelArray: 3x3 kernel
     * @return image with provided kernel
     */
    //------------------------------------------------------------------------
    Image convolution(double kernelArray[]);

    
    //------------------------------------------------------------------------
    /// Compute the median filter to an image.
    /**
     * @return image with median filter applied
     */
    //------------------------------------------------------------------------
    Image medianFilter();
    
    
    //------------------------------------------------------------------------
    /// Compute the mean filter to an image.
    /**
     * @return image with mean filter applied
     */
    //------------------------------------------------------------------------
    Image meanFilter();
    
    
    //------------------------------------------------------------------------
    /// Compute the gaussian filter to an image.
    /**
     * @return image with gaussian filter applied
     */
    //------------------------------------------------------------------------
    Image gaussianFilter();
    
    
    //------------------------------------------------------------------------
    /// Compute the laplacian filter to an image.
    /**
     * @return image with laplacian filter applied
     */
    //------------------------------------------------------------------------
    Image laplacianFilter();
    
    
    //------------------------------------------------------------------------
    /// Compute the sobel edge detection to an image.
    /**
     * @return image with sobel edge detection filter applied
     */
    //------------------------------------------------------------------------
    Image sobelEdgeDetector();
    
    
    //------------------------------------------------------------------------
    /// Compute the prewitt edge detection to an image.
    /**
     * @return image with prewitt edge detection filter applied
     */
    //------------------------------------------------------------------------
    Image prewittEdgeDetector();
    
    
    //------------------------------------------------------------------------
    ///  Sharpens an image.
    /**
     * @param sharpenValue: amount the image is sharpened
     * @return image thats been sharpened
     */
    //------------------------------------------------------------------------
    Image sharpening(double sharpenValue);
    
    
    //------------------------------------------------------------------------
    /// Replaces values above threshold with 1 and 0 for value below
    /**
     * @param thresholdValue: lowest value in the threshold
     * @return image with applied threshold
     */
    //------------------------------------------------------------------------
    Image segmentationThresholding(double thresholdValue);
    
    
    //------------------------------------------------------------------------
    /// Blends two images together
    /**
     * @param aImage: image to blend with
     * @param alpha: how transparent one image is
     * @return image with applied threshold
     */
    //------------------------------------------------------------------------
    Image blending(const Image& aImage, double alpha);
    
    
    //------------------------------------------------------------------------
    /// Generated a histogram depending on the amount of bins the user wants
    /**
     * @param aNumberOfBins: Number of bins to a histogram
     * @return vector containing the amount of values in each bin
     */
    //------------------------------------------------------------------------
    std::vector<unsigned int> getHistogram(unsigned int aNumberOfBins) const;
    
    
    //------------------------------------------------------------------------
    /// Writes histogram to txt file
    /**
     * @param aNumberOfBins: Number of bins to a histogram
     * @param aFileName: name of the txt file
     * @return vector containing the amount of values in each bin
     */
    //------------------------------------------------------------------------
    void writeHistogram(unsigned int aNumberOfBins, const std::string& aFileName) const;
    
    
    //------------------------------------------------------------------------
    /// Writes histogram to txt file
    /**
     * @param aNumberOfBins: Number of bins to a histogram
     * @param aFileName: name of the txt file
     * @return vector containing the amount of values in each bin
     */
    //------------------------------------------------------------------------
    void writeHistogram(unsigned int aNumberOfBins, const char* aFileName) const;
//******************************************************************************
private:
    /// Number of pixel along the horizontal axis
    unsigned int m_width;


    /// Number of pixel along the vertical axis
    unsigned int m_height;

    
    /// The pixel data
    double* m_p_image;
};

#endif
