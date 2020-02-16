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

protected:
	CElement(CGame* game, const std::wstring& filename);

	virtual void Update(double elpased) {};

public:
	virtual void Draw(Gdiplus::Graphics* graphics) {};
};

