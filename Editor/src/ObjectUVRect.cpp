#include "ObjectUVRect.h"



ObjectUVRect::ObjectUVRect()
{
}


ObjectUVRect::~ObjectUVRect()
{
}

void ObjectUVRect::create(glm::vec2 pos, glm::vec2 dim)
{
	m_pos = pos;
	m_dims = dim;

	updateVertices();
	


}


void ObjectUVRect::setDim(glm::vec2 dim)
{
	m_dims = dim;

// 	glm::vec2 r_pos;
// // 	glm::vec2 r_dim;
// // 	r_dim.x = tr.getPos().x - tl.getPos().x;
// // 	r_dim.y = tl.getPos().y - bl.getPos().y;
// 
// 	r_pos.x = bl.getPos().x + dim.x / 2.0f;
// 	r_pos.y = bl.getPos().y + dim.y / 2.0f;
// 	m_pos = r_pos;


	//updateVertices();
// 	recalculateDim();
}

void ObjectUVRect::draw(Feintgine::DebugRender &renderer)
{
	renderer.drawBox(tl.getPos() , tr.getPos() , br.getPos() , bl.getPos(), Feintgine::Color(0, 255, 255, 255), 0);
} 


glm::vec2 ObjectUVRect::getPos()
{
	glm::vec2 r_pos;
	glm::vec2 r_dim;
	r_dim.x = tr.getPos().x - tl.getPos().x;
	r_dim.y = tl.getPos().y - bl.getPos().y;

	r_pos.x = bl.getPos().x + r_dim.x / 2.0f;
	r_pos.y = bl.getPos().y + r_dim.y / 2.0f;

	
	return r_pos;
}

glm::vec2 ObjectUVRect::getDim()
{
	glm::vec2 r_dim;
	r_dim.x = tr.getPos().x - tl.getPos().x;
	r_dim.y = tl.getPos().y - bl.getPos().y;
	return r_dim;
}

void ObjectUVRect::updateVertices()
{


	tl.init(glm::vec2(0, 0) , glm::vec2(coliderWidth));
	bl.init(glm::vec2(0, -m_dims.y), glm::vec2(coliderWidth));
	br.init(glm::vec2(m_dims.x, -m_dims.y), glm::vec2(coliderWidth));
	tr.init(glm::vec2(m_dims.x, 0), glm::vec2(coliderWidth));
 	tl.add(m_pos);
 	bl.add(m_pos);
 	br.add(m_pos);
	tr.add(m_pos);


// 
// 	tl.add(-glm::vec2(coliderWidth/2));
// 	bl.add(-glm::vec2(coliderWidth/2));
// 	br.add(-glm::vec2(coliderWidth/2));
// 	tr.add(-glm::vec2(coliderWidth/2));

// 	std::cout << feint_common::Instance()->convertVec2toString(tl.getPos()) << "tl \n";
// 	std::cout << feint_common::Instance()->convertVec2toString(bl.getPos()) << "bl \n";
// 	std::cout << feint_common::Instance()->convertVec2toString(br.getPos()) << "br \n";
// 	std::cout << feint_common::Instance()->convertVec2toString(tr.getPos()) << "tr \n";
}

glm::vec4 ObjectUVRect::getCalculatedUV(const glm::vec2 & spriteSheetDim)
{
	glm::vec2 halfDim = spriteSheetDim/2.0f;
	updateVertices();
	glm::vec2 tlz = tl.getPos();
	glm::vec2 blz = bl.getPos();
	glm::vec2 brz = br.getPos();
	glm::vec2 trz = tr.getPos();

	tlz += - halfDim ;
	blz += - halfDim ;
	brz += - halfDim;
	trz += - halfDim ;
	
// 
// 	std::cout << "top left " << tlz.x << " " << tlz.y << "\n";
// 	std::cout << "top right " << trz.x << " " << trz.y << "\n";
// 	std::cout << "bottom left " << blz.x << " " << blz.y << "\n";
// 	std::cout << "bottm right " << brz.x << " " << brz.y << "\n";

	glm::vec2 uvcord;
	uvcord.x = blz.x / spriteSheetDim.x;
	uvcord.y = blz.y / spriteSheetDim.y;
// 	uvcord.x /= spriteSheetDim.x;
// 	uvcord.y /= spriteSheetDim.y;
	glm::vec2 uvmap;
	uvmap.x = (trz.x - tlz.x) / spriteSheetDim.x;
	//uvmap.x = m_dims.x / spriteSheetDim.x;
	uvmap.y = (tlz.y - blz.y) / spriteSheetDim.y;

//  	std::cout << feint_common::Instance()->convertVec2toString(uvcord) << "\n";
//  	std::cout << feint_common::Instance()->convertVec2toString(uvmap) << "\n";

	return glm::vec4(uvcord ,uvmap);
}

void ObjectUVRect::calculateOffset(glm::vec2 mousePos)
{

	m_offset = mousePos - m_pos;
}

bool ObjectUVRect::isMouseInside(const glm::vec2 & mousePos)
{


	if (mousePos.x > m_pos.x && mousePos.x < m_pos.x + m_dims.x && mousePos.y < m_pos.y && mousePos.y > m_pos.y - m_dims.y)
	{
		return true;
	}

	return false;
}


void ObjectUVRect::checkPoint(const glm::vec2& mousePos, Feintgine::DebugRender &renderer)
{

	bool found = false;
	if (mousePos.x > tl.getPos().x - coliderWidth && mousePos.x < tl.getPos().x + coliderWidth && mousePos.y < tl.getPos().y + coliderWidth && mousePos.y > tl.getPos().y - coliderWidth)
	{
		if (point_pointer == nullptr)
		{
			point_pointer = &tl;
			
		}
		found = true;
	//	tl.draw(renderer);
		//renderer.drawBox(glm::vec4(tl.getPos(), glm::vec2(coliderWidth*2)), Feintgine::Color(255, 200, 255, 255), 0);
		
	}
	if (mousePos.x > tr.getPos().x - coliderWidth && mousePos.x < tr.getPos().x + coliderWidth && mousePos.y < tr.getPos().y + coliderWidth && mousePos.y > tr.getPos().y - coliderWidth)
	{
		if (point_pointer == nullptr)
		{
			point_pointer = &tr;
		}
	//	tr.draw(renderer);
		found = true;
		//renderer.drawBox(glm::vec4(tr.getPos(), glm::vec2(coliderWidth*2)), Feintgine::Color(255, 200, 255, 255), 0);
	}
	if (mousePos.x > bl.getPos().x - coliderWidth && mousePos.x < bl.getPos().x + coliderWidth && mousePos.y < bl.getPos().y + coliderWidth && mousePos.y > bl.getPos().y - coliderWidth)
	{
		if (point_pointer == nullptr)
		{
			point_pointer = &bl;
		}
		found = true;
		//bl.draw(renderer);
		//renderer.drawBox(glm::vec4(bl.getPos(), glm::vec2(coliderWidth*2)), Feintgine::Color(255, 200, 255, 255), 0);
	}
	if (mousePos.x > br.getPos().x - coliderWidth && mousePos.x < br.getPos().x + coliderWidth && mousePos.y < br.getPos().y + coliderWidth && mousePos.y > br.getPos().y - coliderWidth)
	{
		if (point_pointer == nullptr)
		{
			point_pointer = &br;
		}
		found = true;
		//br.draw(renderer);
		//renderer.drawBox(glm::vec4(br.getPos], glm::vec2(coliderWidth*2)), Feintgine::Color(255, 200, 255, 255), 0);
	}
	if (!found)
	{
		point_pointer = nullptr;
	}
	else
	{
		point_pointer->draw(renderer);
	}

}

void ObjectUVRect::dragPoint(const glm::vec2 &mousePos)
{
	if (point_pointer != nullptr)
	{
		if (point_pointer->checkInside(mousePos))
		{
			if (!point_pointer->isDraged())
			{
				calculateOffset(mousePos);
				point_pointer->setDrag(true);
			}
			else
			{
				glm::vec2 newPos = mousePos ;
				point_pointer->setPoswithTrack(newPos);
				recalculateDim();
			}
				
		}
		else
		{
			point_pointer->setDrag(false);
		}
	}
}

void ObjectUVRect::recalculateDim()
{
	if (point_pointer != nullptr)
	{
 		if (point_pointer == &br)
		{
			
			tr.setX(point_pointer->getPos().x);
			bl.setY(point_pointer->getPos().y);
			glm::vec2 calculate;
			calculate = point_pointer->getPos() -point_pointer->getLastPos();
			m_dims.x += calculate.x;
			m_dims.y -= calculate.y;
			//std::cout << "recalulate " << feint_common::Instance()->convertVec2toString(calculate) << "\n";
			updateVertices();
		}
// 		if (point_pointer == &tr)
// 		{
// 			std::cout << " is top right \n";
// 		}
// 		if (point_pointer == &bl)
// 		{
// 			std::cout << " is bottom left \n";
// 		}
// 		if (point_pointer == &br)
// 		{
// 			std::cout << " is bottom right \n";
// 		}
	}
}

