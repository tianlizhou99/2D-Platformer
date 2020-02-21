#pragma once
#include "Entity.h"
#include <memory>
#include<string>
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
	virtual void Update(double elpased) {};
};
