#include "Editor_GUI.h"

handleBar::handleBar(int v, bool horizontal, handleBar* bar1, handleBar* bar2, LayoutGUI* parent, Cvs_Window* window):cv_g_simpleElement(0,0,10,100, parent, window),movable(true), horizontal(horizontal)
{
	if(horizontal)
	{
		handleBar* biggerBar = bar1->properties.aabb.minX < bar2->properties.aabb.minX? bar2 : bar1;
		handleBar* smallerBar = bar1->properties.aabb.minX < bar2->properties.aabb.minX? bar1 : bar1;

		setUpperDelimiter(biggerBar);
		setLowerDelimiter(smallerBar);
	} else {
		handleBar* biggerBar = bar1->properties.aabb.minY < bar2->properties.aabb.minY? bar2 : bar1;
		handleBar* smallerBar = bar1->properties.aabb.minY < bar2->properties.aabb.minY? bar1 : bar1;

		setUpperDelimiter(biggerBar);
		setLowerDelimiter(smallerBar);
	}
}

handleBar::handleBar(int type, LayoutGUI* parent, Cvs_Window* window):cv_g_simpleElement(0,0, 10, 100, parent, window),movable(false)
{


	switch(type)
	{
	case 0:
		horizontal = true;
		properties.aabb.minX = parent->properties.aabb.minX;
		properties.aabb.maxX = parent->properties.aabb.maxX;
		properties.aabb.maxY = parent->properties.aabb.maxY;
		properties.aabb.minY = parent->properties.aabb.maxY - 2;
	case 1:
		horizontal = false;
		properties.aabb.maxY = parent->properties.aabb.maxY;
		properties.aabb.minY = parent->properties.aabb.minY;
		properties.aabb.maxX = parent->properties.aabb.maxX;
		properties.aabb.minX = parent->properties.aabb.maxX - 2;
	case 2:
		horizontal = true;
		properties.aabb.minX = parent->properties.aabb.minX;
		properties.aabb.maxX = parent->properties.aabb.maxX;
		properties.aabb.maxY = parent->properties.aabb.minY;
		properties.aabb.minY = parent->properties.aabb.minY + 2;
	case 3:
		horizontal = false;
		properties.aabb.maxY = parent->properties.aabb.maxY;
		properties.aabb.minY = parent->properties.aabb.minY;
		properties.aabb.maxX = parent->properties.aabb.minX;
		properties.aabb.minX = parent->properties.aabb.minX + 2;
	}
	
}

void handleBar::setLowerDelimiter(handleBar* bar)
{
	if(horizontal == bar->horizontal)
	{
		printf("Same handlebars\n");
		return;
	}
	if(horizontal)
	{
		bar->addInt(&properties.aabb.minX);
	} else {
		bar->addInt(&properties.aabb.minY);
	}
}

void handleBar::setUpperDelimiter(handleBar* bar)
{
	if(horizontal == bar->horizontal)
	{
		printf("Same handlebars\n");
		return;
	}
	if(horizontal)
	{
		bar->addInt(&properties.aabb.maxX);
	} else {
		bar->addInt(&properties.aabb.maxY);
	}
}

void handleBar::onMouseDown()
{
	if(!onDrag)
	{
		onDrag = true;
		int x, y;
		SDL_GetMouseState(&x, &y);
		this->lastX = x;
		this->lastY = y;
	} else {
		int x, y;
		SDL_GetMouseState(&x, &y);
		this->move(x - lastX, y - lastY);
	}
}

void handleBar::move(int x, int y)
{
	if(horizontal)
	{
		for(int i = 0; i < values.size(); ++i)
		{
			(*values[i]) += x;
		}
		properties.aabb.maxX += x;
		properties.aabb.minX += x;
	} else {
		for(int i = 0; i < values.size(); ++i)
		{
			(*values[i]) += x;
		}
		properties.aabb.maxY += y;
		properties.aabb.minY += y;
	}
}

void handleBar::onMouseUp()
{
	onDrag = false;
}

void handleBar::onHover()
{
	if(onDrag)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		this->move(x - lastX, y - lastY);
	}
}

void handleBar::offHover()
{
	if(onDrag)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		this->move(x - lastX, y - lastY);
	}
}
void handleBar::addInt(int* v)
{
	values.push_back(v);
}

void handleBar::Render(cv_2D_DrawProgram DrawProgam, int x, int y)
{
	DrawProgam.drawColorRect(properties.color, properties.aabb.minX + x, properties.aabb.minY + y, properties.aabb.maxX - properties.aabb.minX + x, properties.aabb.maxY - properties.aabb.minY + y);
}

LayoutGUI::LayoutGUI(float x, float y, float w, float h, cv_g_Element* parent, Cvs_Window* window):cv_g_Element(x , y, w, h, parent, window), topBar(0, this, window), rightBar(1, this, window), botBar(2, this, window), leftBar(3, this, window)
{

}

bool LayoutGUI::getMouseDown(SDL_Event* e, int x, int y)
{
	int vx,vy;
	SDL_GetMouseState( &vx, &vy); 

	iAABB aabb = properties.aabb;

	if( checkMouseOver(aabb, vx, vy))
	{
		onMouseDown();
		for( int i = children.size()-1; i > 0; --i)
		{
			if(children[i]->getMouseDown(e, properties.aabb.minX + x, properties.aabb.minY + y))
				return true;
		}
		return true;
	}

	for( int i = children.size()-1; i > 0; --i)
	{
		if(children[i]->getMouseDown(e, properties.aabb.minX + x, properties.aabb.minY + y))
			break;
	}

	return false;
}

bool LayoutGUI::getMouseUp(SDL_Event* e, int x, int y)
{
	int vx,vy;
	SDL_GetMouseState( &vx, &vy); 

	iAABB aabb = properties.aabb;

	if( checkMouseOver(aabb, vx, vy))
	{
		onMouseUp();
		for( int i = children.size()-1; i > 0; --i)
		{
			if(children[i]->getMouseUp(e, properties.aabb.minX + x, properties.aabb.minY + y))
				return true;
		}
		return true;
	}

	for( int i = children.size()-1; i > 0; --i)
	{
		if(children[i]->getMouseUp(e, properties.aabb.minX + x, properties.aabb.minY + y))
			break;
	}

	return false;
}

bool LayoutGUI::getHover(SDL_Event* e, int x, int y)
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
				if(children[i]->getHover(e, properties.aabb.minX + x, properties.aabb.minY + y))
					hoverDelegated = true;
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
			if(children[i]->getHover(e, properties.aabb.minX + x, properties.aabb.minY + y))
				hoverDelegated = true;
			else {
				children[i]->offHover();
			}
		else{
			children[i]->offHover();
		}
	}
	return false;
}


void LayoutGUI::setLeftSet(handleBar* bar)
{
	bar->addInt(&properties.aabb.minX);
	properties.aabb.maxY = bar->properties.aabb.minY;
}

void LayoutGUI::setTopSet(handleBar* bar)
{
	bar->addInt(&properties.aabb.minY);
	properties.aabb.minY = properties.aabb.maxY;
}

void LayoutGUI::setRightSet(handleBar* bar)
{
	bar->addInt(&properties.aabb.maxX);
	properties.aabb.maxX = bar->properties.aabb.minX;
}

void LayoutGUI::setBotSet(handleBar* bar)
{
	bar->addInt(&properties.aabb.maxY);
	properties.aabb.maxY = bar->properties.aabb.minY;
}


void LayoutGUI::onMouseDown()
{
}

void LayoutGUI::onMouseUp()
{
}

void LayoutGUI::onHover()
{
}

void LayoutGUI::offHover()
{
}

handleBar* LayoutGUI::createNewHandleBar(handleBar* bar1, handleBar* bar2, int position)
{
	if(bar1->horizontal != bar2->horizontal)
		return NULL;
	bool horizontal = bar1->horizontal;
	
	handleBar* newbar = new handleBar(position, horizontal, bar1, bar2, this, window);
	this->divisors.push_back(newbar);
	return newbar;
}

void LayoutGUI::Render(cv_2D_DrawProgram DrawTools, int x, int y)
{

	if(properties.BackGroundImage.hasTexture)
		DrawTools.drawTextureRect(properties.BackGroundImage.texture, properties.aabb.minX + x, properties.aabb.minY + y, properties.aabb.maxX - properties.aabb.minX, properties.aabb.maxY - properties.aabb.minY);
	else DrawTools.drawColorRect(properties.color,properties.aabb.minX + x, properties.aabb.minY + y, properties.aabb.maxX - properties.aabb.minX, properties.aabb.maxY - properties.aabb.minY);

	for(int i = 0; i < children.size(); ++i)
	{
		children[i]->Render(DrawTools, properties.aabb.minX + x, properties.aabb.minY + y);
	}

	for(int i = 0; i < children.size(); ++i)
	{
		divisors[i]->Render(DrawTools, properties.aabb.minX + x, properties.aabb.minY + y);
	}
}