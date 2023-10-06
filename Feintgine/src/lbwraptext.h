/* Taken From Anepsosis */
#ifndef LBWrapText_H
#define LBWrapText_H

#include <vector>
#include "GUI.h"
#include "feint_common.h"
using namespace std;

class LBWrapText
{
public:

	
	LBWrapText();
	~LBWrapText();

	bool isInRange(CEGUI::Listbox *lb, std::string message);
	std::vector<CEGUI::ListboxTextItem*> strToItemList(CEGUI::Listbox *lb, std::string message);

private:
};
#endif