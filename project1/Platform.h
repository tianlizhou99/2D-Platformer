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

    CPlatform(CGame* game, const std::wstring& filename);

    CPlatform(CGame* game, const std::wstring& filename1, const std::wstring& filename2, const std::wstring& filename3);

private:
    wstring mLeftImage;
    wstring mMidImage;
    wstring mRightImage;
};

