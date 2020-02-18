/**
 * \file Wall.h
 *
 * \author Team Sprixie
 *
 * Class that implements a wall
 */

#pragma once
#include "Level.h"

 /**
  * class that represents a wall to crash into
  */
class CWall :
	public CLevel
{
public:
    CWall(CGame* game);

    /// Default constructor (disabled)
    CWall() = delete;

    /// Copy constructor (disabled)
    CWall(const CWall&) = delete;

    void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);


private:
    /// Height of wall
    double mHeight = 0;

    /// Width of wall
    double mWidth = 0;
};

