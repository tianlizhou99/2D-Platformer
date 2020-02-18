#pragma once

class CPlayer;
class CPlatform;
class CEndDoor;
class CWall;

/**
 * Visitor class
 */
class CVisitor
{
public:
	virtual ~CVisitor() {}
	/** Visit a CPlayer object
	* \param player Player we are visiting
	* \returns void */
	virtual void VisitPlayer(CPlayer* player) {}
	/** Visit a CPlatform object
	* \param plat Platform we are visiting 
	*  \return void */
	virtual void VisitPlatform(CPlatform* plat) {}
	/** Visit a CEndDoor object
	* \param end EndDoor we are visiting 
	* \return void */
	virtual void VisitEndDoor(CEndDoor* end) {}
	/** Visit a CWall object
	* \param wall wall we are visiting 
	*  \return void */
	virtual void VisitWall(CWall* wall) {}

};

