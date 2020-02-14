#pragma once
#include "Entity.h"
#include "Game.h"
class CCharacter :public CEntity
{
public:
    /** loads the items from xml
    * \param node the item to load
    */
    void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    /** saves the items to xml
    * \param node the item to save
    * \return a shared pointer to an object to save
    */
    std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Default constructor (disabled)
    CCharacter() = delete;

    /// Copy constructor (disabled)
    CCharacter(const CCharacter&) = delete;
    /** sets the fishes speed in the x direction
    * \param x is speed of fish
    */
    void SetSpeedX(double x);
    /** sets the fishes speed in the y direction
    * \param y is speed of fish
    */
    void SetSpeedY(double y);


protected:
    /** Constructor for fish
    * \param aquarium is the aquarium fish is held in
    */
    CCharacter(CGame* game, const std::wstring& filename);
private:
    ///  speed in the X direction
    double mSpeedX;

    ///  speed in the Y direction
    double mSpeedY;
};


