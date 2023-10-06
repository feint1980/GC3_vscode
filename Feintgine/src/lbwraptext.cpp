/* Taken From Anepsosis */

#include <iostream>
#include <vector>
#include "lbwraptext.h"

using namespace std;

LBWrapText::LBWrapText()
{
}

LBWrapText::~LBWrapText()
{
}


// Method Used Just To Check If The String Is Too Long Or Not
bool LBWrapText::isInRange(CEGUI::Listbox *lb, std::string message)
{
	// Get The Size Of The Message In Pixels
	CEGUI::ListboxTextItem *chatItem = new CEGUI::ListboxTextItem(message);


	CEGUI::Sizef lbti = chatItem->getPixelSize();

	// Get The Widths Of The Listbox And Item In Floats
	float lblength = lb->getListRenderArea().getWidth();
	float itemlen = lbti.d_width;


	// Clean Up Our Mess, And Check If The 
	// ListboxItem is Too Long
	delete chatItem;
	if (itemlen < lblength) {
		return true;
	}
	else {
		return false;
	}
}

std::vector<CEGUI::ListboxTextItem*> LBWrapText::strToItemList(CEGUI::Listbox *lb, std::string message)
{
	// Clear The Vector, And Get The Number Of Needed Splits
	std::vector<CEGUI::ListboxTextItem*> lstItems;
	std::vector<std::string> msgparts;
	CEGUI::ListboxTextItem *chatItem;

	// CAUTION!!! This Line Might Cause An UnknownObjectException
	// You Need To Ensure That You Have Vertical ScrollBar Always 
	// Visible With: setShowVertScrollbar (bool setting)
	CEGUI::Window *lbscrollbar = static_cast<CEGUI::Window*>(lb->getVertScrollbar());
	CEGUI::UDim sbwidth = lbscrollbar->getWidth();
	CEGUI::Sizef lbti;

	// Empty Our Vectors
	lstItems.clear();
	msgparts.clear();

	// Get Some Float Values For The Listbox / Item
	float lblength = lb->getListRenderArea().getWidth();
	float lbsbwidth = sbwidth.d_offset;
	float itemlen = 0;

	int charlen = 0;
	int ccount = 0;

	// Create Listbox Item Or Items
	if (this->isInRange(lb, message) == false) {

		// Get The Max Length Of Characters Of The Listbox
		std::string tmpbuf = "";
		for (size_t i = 0; i < message.length(); i++) {
			tmpbuf += message[i];
			chatItem = new CEGUI::ListboxTextItem((CEGUI::utf8*)tmpbuf.c_str());
			lbti = chatItem->getPixelSize();
			itemlen = lbti.d_width;

			// If We've Reached The End Of The Listbox
			// (Taking Into Account For The Scrollbar 
			if (itemlen*1.1f >= (lblength - lbsbwidth)) {
				size_t pos;
				pos = i;

				// If We Landed On A Space
				if (message[pos] == ' ') {
					msgparts.push_back(message.substr(0, i));
					message.erase(0, i + 1);
				}
				else {
					// If Not, Loop Until We Find One, 
					// Or Our String Runs Out
					if (message.find(" ") != std::string::npos) {
						while (message[pos] != ' ') {
							if (pos >= 0) {
								// Finally Found A Previous Space
								if (message[pos] == ' ') {
									msgparts.push_back(message.substr(0, pos));
									message.erase(0, pos + 1);
									break;
								}
								else {
									pos--;
								}
							}
							else {
								// No Space Found Behind Us... Cut It Here
								msgparts.push_back(message.substr(0, i));
								message.erase(0, i + 1);
								pos--;
								break;
							}
						}
					}
					else {
						// No Space In The String... Cut It By Letter
						msgparts.push_back(message.substr(0, i));
						message.erase(0, i);
					}
				}

				// Clean Up Used Heap
				delete chatItem;
			}
		}

		// Gather The Remaining Chunks Of Message
		msgparts.push_back(message);

		// Generate The ListboxTextItems   
		for (size_t i = 0; i < msgparts.size(); i++) {
			lstItems.push_back(new CEGUI::ListboxTextItem((CEGUI::utf8*)msgparts[i].c_str()));
		}
	}
	else {
		lstItems.push_back(new CEGUI::ListboxTextItem((CEGUI::utf8*)message.c_str()));
	}

	// Return The Vector
	return lstItems;
}