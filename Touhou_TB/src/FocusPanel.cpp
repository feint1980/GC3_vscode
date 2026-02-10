#include "FocusPanel.h"

FocusPanel::FocusPanel()
{

}

FocusPanel::FocusPanel(tgui::Panel::Ptr * panel)
{
    m_selfPanel = panel;
}


FocusPanel::FocusPanel(tgui::Gui * gui)
{
    m_tgui = gui;
}

FocusPanel::~FocusPanel()
{

}

void FocusPanel::addLabel(tgui::Label::Ptr * label) 
{
    if(label) 
    {
        // std::cout << "FocusPanel addLabel called \n";
        if(m_labelSet.find(label) == m_labelSet.end())
        {
            m_labelSet.insert(label);
            
            // label->get()
            m_labels.push_back(label);
            std::cout << "pushed label " << label->get()->getText() << "\n";
            std::cout << "size " << m_labels.size() << "\n";
        }
    }
}

void FocusPanel::removeLabel(tgui::Label::Ptr * label)
{
    if(label)
    {
        if(m_labelSet.find(label) != m_labelSet.end())
        {
            m_labelSet.erase(label);
        }
        for(int i = 0; i < m_labels.size(); i++)
        {
            if(m_labels[i] == label)
            {
                std::swap(m_labels[i],m_labels.back());
                m_labels.pop_back();
            }
        }
    }
}

tgui::Label::Ptr * FocusPanel::getFirstLabel()
{
    std::cout << "getFirstLabel called \n";
    std::cout << "size is " << m_labels.size() << "\n";
    if(m_labels.size() > 0)
    {
        // m_currentLabelIndex = 0;
        // std::cout << "m_currentLabelIndex: " << m_currentLabelIndex << "\n";

        // std::cout << "m_labels ptr: " << m_labels[m_currentLabelIndex] << "\n";
        return m_labels[m_currentLabelIndex];
    } 
    
    std::cout << "FocusPanel::getFirstLabel return nullptr \n";
    return nullptr;
}

tgui::Label::Ptr * FocusPanel::getNextLabel()
{
    if(m_labels.size() > 1)
    {
        m_currentLabelIndex = (m_currentLabelIndex + 1) % m_labels.size();
        return m_labels[m_currentLabelIndex];
    } 
    else if (m_labels.size() == 1) 
    {
        m_currentLabelIndex = 0;
        return m_labels[m_currentLabelIndex];
    }
    return nullptr;
}

tgui::Label::Ptr * FocusPanel::getPreviousLabel()
{
    if(m_labels.size() > 1)
    {
        m_currentLabelIndex = (m_currentLabelIndex - 1 + m_labels.size()) % m_labels.size();
        return m_labels[m_currentLabelIndex];
    } 
    else if (m_labels.size() == 1) 
    {
        m_currentLabelIndex = 0;
        return m_labels[m_currentLabelIndex];
    }
    return nullptr;
}

void FocusPanel::changeLabelIndex(int index)
{
    if(m_labels.size() == 0) return;
    m_currentLabelIndex += index;
    m_currentLabelIndex = m_currentLabelIndex % m_labels.size();
    std::cout << "current index is " << m_currentLabelIndex << "\n";
}
