/**
 * \file Element.h
 *
 * \author Team Sprixie
 *
 * Class that represents the base of an element
 */



#pragma once
#include "Entity.h"
#include <memory>
#include<string>

/**
* Base class for UI elements
*/
class CElement :
	public CEntity
{
private:
	/// Default constructor (disabled)
	CElement() = delete;

	/// Copy constructor (disabled)
	CElement(const CElement&) = delete;



public:
	void Draw(Gdiplus::Graphics* graphics) override;

	CElement(CGame* game, const std::wstring& filename);

	/// update function for all onscreen objects
	/// \param elapsed time since last call
	/// \returns void
	virtual void Update(double elapsed) {};
};

