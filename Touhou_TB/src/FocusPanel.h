#ifndef _FOCUS_PANEL_H_
#define _FOCUS_PANEL_H_

#include "../../TGUI_theme/ThemeCreator.hpp"
#include <set>
#include <vector>

class FocusPanel 
{
    public:

    FocusPanel();

    FocusPanel(tgui::Panel::Ptr * panel);

    FocusPanel(tgui::Gui * gui);
    
    ~FocusPanel(); 

    void addLabel(tgui::Label::Ptr * label);

    void removeLabel(tgui::Label::Ptr * label);
    
    tgui::Label::Ptr * getFirstLabel();

    tgui::Label::Ptr * getNextLabel();
    
    tgui::Label::Ptr * getPreviousLabel();
    
    tgui::Panel::Ptr * getPanel() { return m_selfPanel; }

    int getType() 
    {
        int tType = 0;
        if(m_selfPanel)
        {
            tType |= 1;
        }
        if(m_tgui)
        {
            tType |= 2;
        }
        return tType;
    }

    private:

    tgui::Panel::Ptr * m_selfPanel = nullptr;
    tgui::Gui * m_tgui = nullptr;


    std::set<tgui::Label::Ptr *> m_labelSet;
    std::vector<tgui::Label::Ptr *> m_labels;
    int m_currentLabelIndex = -1;

};


#endif