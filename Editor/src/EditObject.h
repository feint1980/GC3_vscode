#pragma once

#include <F_Object.h>


class EditObject : public Feintgine::F_Object
{
public:
	EditObject();
	~EditObject();

	std::vector<Feintgine::SelfSprite> getSpriteList() const { return m_sprites; }


	

	void deleteSpriteByID(int ID);
	void deleteColiderByID(int ID);

	Feintgine::SelfSprite * getSpriteByID(int ID);

	int getColiderIndexByID(int ID);

	void setFitScale(float scale);
	void setEnlargeSize(float size);

	int getLightIndexByID(int ID);

	void calculateOffset(const glm::vec2 & pos);



	std::string getFilePath() const {

		return m_filePath;
	}

	glm::vec2 getOffsetPos() const { return savedOffset; }

private:

	glm::vec2 savedOffset;

};

