#pragma once

class CPlayer;
class CPlatform;
class CEndDoor;
class CWall;


class CVisitor
{
public:
	virtual ~CVisitor() {}
	virtual void VisitPlayer(CPlayer* player) {}
	virtual void VisitPlatform(CPlatform* plat) {}
	virtual void VisitEndDoor(CEndDoor* end) {}
	virtual void VisitWall(CWall* wall) {}

};

