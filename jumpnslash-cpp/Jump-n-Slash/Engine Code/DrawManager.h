#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <list>

// forward declarations
class DrawObject;

class DrawManager
{
public:
	DrawManager() = default;
	DrawManager(const DrawManager& dm) = delete;
	DrawManager& operator=(const DrawManager& dm) = delete;
	virtual ~DrawManager();

private:
	using DrawList = std::list<DrawObject*>;
public:
	using DrawListRef = DrawList::iterator;

	/*!
	* \brief	Adds \c DrawObject to draw list.
	*
	* Adds a \c DrawObject to the DrawManager's list of DrawObjects.
	*
	* \note		This function is primarily called through use of the draw registration system.
	*
	* \param[in]	pDrawable	A \c DrawObject.
	*
	* \return	Returns an iterator pointing to the DrawObjects position in the DrawList.
	*
	* \see DrawObject::RequestDrawRegistration
	* \see DrawObject::RequestDrawDeregistration
	*/	DrawListRef Register(DrawObject* pDrawable);
	
	/*!
	* \brief	Removes \c DrawObject from draw list.
	* 
	* Removes a \c DrawObject from the DrawManager's list of DrawObjects.  
	* 
	* \note		This function is primarily called through use of the draw deregistration system. 
	* 
	* \param[in]	drawListRef		A DrawList iterator.  
	* 
	* \return	Does not return anything. 
	* 
	* \see DrawObject::RequestDrawRegistration
	* \see DrawObject::RequestDrawDeregistration
	*/
	void Deregister(DrawListRef drawListRef); 

	void Draw();

private:
	DrawList drawList;
};

#endif