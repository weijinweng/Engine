#include "CVS_GUI.h"

bool checkMouseOver(iAABB aabb, int x, int y)
{
	if(aabb.maxX < x
		|| aabb.minX > x
		|| aabb.maxY < y
		|| aabb.minY > y)
		return true;
	return false;
}


cv_g_simpleElement::cv_g_simpleElement(int x, int y, int w, int h, cv_g_Element* parent, Cvs_Window* window):parent(parent),window(window)
{
	properties.aabb.minX = x;
	properties.aabb.minY = y;
	properties.aabb.maxX = x + w;
	properties.aabb.maxY = y + h;
}

bool cv_g_simpleElement::getMouseDown(SDL_Event* e, int x, int y)
{
	int vx,vy;
	SDL_GetMouseState( &vx, &vy); 

	iAABB aabb = properties.aabb;

	if( checkMouseOver(aabb, vx, vy))
	{
		onMouseDown();
		return true;
	}

	return false;
}

bool cv_g_simpleElement::getMouseUp(SDL_Event* e, int x, int y)
{
	int vx,vy;
	SDL_GetMouseState( &vx, &vy); 

	iAABB aabb = properties.aabb;

	if( checkMouseOver(aabb, vx, vy))
	{
		onMouseUp();
		return true;
	}

	return false;
}

bool cv_g_simpleElement::getHover(SDL_Event* e, int x, int y)
{
	int vx,vy;
	SDL_GetMouseState( &vx, &vy); 

	iAABB aabb = properties.aabb;

	if( checkMouseOver(aabb, vx, vy))
	{
		onHover();
		return true;
	}
	offHover();
	return false;
}

void cv_g_simpleElement::onMouseDown()
{
}

void cv_g_simpleElement::onMouseUp()
{
}

void cv_g_simpleElement::onHover()
{
}

void cv_g_simpleElement::offHover()
{

}

void cv_g_simpleElement::Render(cv_2D_DrawProgram m_2DProgram, int x, int y)
{
	if(properties.BackGroundImage.hasTexture)
		m_2DProgram.drawTextureRect(properties.BackGroundImage.texture, properties.aabb.minX + x, properties.aabb.minY + y, properties.aabb.maxX - properties.aabb.minX, properties.aabb.maxY - properties.aabb.minY);
	else 
		m_2DProgram.drawColorRect(this->properties.color, properties.aabb.minX + x, properties.aabb.minY + y, properties.aabb.maxX - properties.aabb.minX + x, properties.aabb.maxY - properties.aabb.minY + y);
}
cv_g_Element::cv_g_Element(int x, int y, int w, int h, cv_g_Element* parent, Cvs_Window* window):cv_g_simpleElement(x, y, w, h, parent, window)
{

}

bool cv_g_Element::getMouseDown(SDL_Event* e, int x, int y)
{
	int vx,vy;
	SDL_GetMouseState( &vx, &vy); 

	iAABB aabb = properties.aabb;

	if( checkMouseOver(aabb, vx, vy))
	{
		onMouseDown();
		for( int i = children.size()-1; i > 0; --i)
		{
			if(children[i]->getMouseDown(e, aabb.minX + x, properties.aabb.minY + y))
				break;
		}
		return true;
	}

	for( int i = children.size()-1; i > 0; --i)
	{
		if(children[i]->getMouseDown(e, aabb.minX + x, properties.aabb.minY + y))
			break;
	}

	return false;
}

bool cv_g_Element::getMouseUp(SDL_Event* e, int x, int y)
{
	int vx,vy;
	SDL_GetMouseState( &vx, &vy); 

	iAABB aabb = properties.aabb;

	if( checkMouseOver(aabb, vx, vy))
	{
		onMouseUp();
		for( int i = children.size()-1; i > 0; --i)
		{
			children[i]->getMouseUp(e, aabb.minX + x, properties.aabb.minY + y);
		}
		return true;
	}

	for( int i = children.size()-1; i > 0; --i)
	{
		if(children[i]->getMouseUp(e, aabb.minX + x, properties.aabb.minY + y))
			break;
	}

	return false;
}

bool cv_g_Element::getHover(SDL_Event* e, int x, int y)
{
	int vx,vy;
	SDL_GetMouseState( &vx, &vy);

	iAABB aabb = properties.aabb;

	bool hoverDelegated = false;

	if(checkMouseOver(aabb, vx, vy))
	{
		onHover();
		for( int i = children.size()-1; i > 0; --i)
		{
			if(!hoverDelegated)
				if(children[i]->getHover(e, aabb.minX + x, properties.aabb.minY + y))
					break;
				else {
					children[i]->offHover();
				}
			else{
				children[i]->offHover();
			}
		}

		return true;
	}

	for( int i = children.size()-1; i > 0; --i)
	{
		if(!hoverDelegated)
			if(children[i]->getHover(e, aabb.minX + x, properties.aabb.minY + y))
			{
				hoverDelegated = true;
				continue;
			}
			else {
				children[i]->offHover();
			}
		else{
			children[i]->offHover();
		}
	}

	return false;
}

void cv_g_Element::onMouseDown()
{
}

void cv_g_Element::onMouseUp()
{
}

void cv_g_Element::onHover()
{
}

void cv_g_Element::offHover()
{

}

void cv_g_Element::Render(cv_2D_DrawProgram DrawTools, int x, int y)
{
	if(properties.BackGroundImage.hasTexture)
		DrawTools.drawTextureRect(properties.BackGroundImage.texture, properties.aabb.minX + x, properties.aabb.minY + y, properties.aabb.maxX - properties.aabb.minX, properties.aabb.maxY - properties.aabb.minY);
	else DrawTools.drawColorRect(properties.color,properties.aabb.minX + x, properties.aabb.minY + y, properties.aabb.maxX - properties.aabb.minX, properties.aabb.maxY - properties.aabb.minY);

	for(int i = 0; i < children.size(); ++i)
	{
		children[i]->Render(DrawTools, properties.aabb.minX + x, properties.aabb.minY + y);
	}
}