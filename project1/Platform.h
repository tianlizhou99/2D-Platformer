/**
 * \file Platform.h
 *
 * \author Team Sprixie
 *
 * Class that implements a platform
 */

#pragma once
#include "Level.h"

 /**
  * class that represents a platform to jump on
  */
class CPlatform :
	public CLevel
{
public:
    CPlatform(CGame* game);


    /// Default constructor (disabled)
    CPlatform() = delete;

    /// Copy constructor (disabled)
    CPlatform(const CPlatform&) = delete;

    //bool Left(std::vector<double> distances);

    //bool Right(std::vector<double> distances);

    //virtual void Draw(Gdiplus::Graphics* graphics);

    void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);


private:
    /// Height of platform
    double mHeight = 0;

    /// Width of platform
    double mWidth = 0;

    /// The image object for the platform
    std::unique_ptr<Gdiplus::Bitmap> mPlatformLeft;

    /// The image object for the platform
    std::unique_ptr<Gdiplus::Bitmap> mPlatformRight;

    /// The image object for the platform
    std::unique_ptr<Gdiplus::Bitmap> mPlatform;
};

