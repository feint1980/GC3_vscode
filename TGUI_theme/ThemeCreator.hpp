#include <iostream>
#include <filesystem>
#include <fstream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SDL-TTF-OpenGL3.hpp>
#include <TGUI/AllWidgets.hpp>



static void makeAllWidgets(tgui::Gui& gui, const std::string& defaultTheme)
{
    auto widgetHolder = tgui::HorizontalWrap::create();
    auto themeSelector = tgui::ComboBox::create();
    for (auto dir: std::filesystem::directory_iterator("themes"))
    {
        themeSelector->addItem(dir.path().generic_string());
    }
    themeSelector->onItemSelect([](tgui::String selected){
        tgui::Theme::getDefault()->replace(selected);
    });
    themeSelector->setSelectedItem(defaultTheme);
    widgetHolder->add(themeSelector);
    auto scroll = tgui::ScrollablePanel::create();
    scroll->add(widgetHolder);
    widgetHolder->getRenderer()->setSpaceBetweenWidgets(10);

    for (auto widgetName: tgui::WidgetFactory::getWidgetTypes())
    {
        if (widgetName == "RadioButtonGroup") // just look at the radio button
            continue;

        auto panel = tgui::Panel::create();
        auto label = tgui::Label::create(widgetName);
        label->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
        label->setVerticalAlignment(tgui::VerticalAlignment::Center);
        panel->add(label);
        float temp = panel->getWidgets().back()->getSize().y;
        panel->add(tgui::WidgetFactory::getConstructFunction(widgetName)());
        auto lastWidget = panel->getWidgets().back();
        lastWidget->setPosition(0, temp);
        temp += lastWidget->getFullSize().y;
        
        if (widgetName == "ChatBox")
        {
            auto chat = lastWidget->cast<tgui::ChatBox>();
            chat->addLine("Adding 500 random lines");
            chat->setLineLimit(1000);
            for (int i = 0; i < 500; i++)
            {
                tgui::String temp;
                for (int i = 0; i < 10; i++)
                {
                    temp += char(rand()%25+65);
                }
                chat->addLine(temp);
            }
        }
        else if (widgetName == "MessageBox")
        {
            auto msg = lastWidget->cast<tgui::MessageBox>();
            msg->setText("Some random message for the message box");
        }
        else if (auto container = lastWidget->cast<tgui::Container>())
        {
            int maxImages = INT_MAX;
            if (widgetName == "SplitContainer")
            {
                maxImages = 2;
            }
            if (widgetName != "ColorPicker" && widgetName != "FileDialog")
            for (auto file: std::filesystem::directory_iterator{"TestPhotos"})
            {
                if (maxImages <= 0)
                    break;
                auto picture = tgui::Picture::create(tgui::Texture{file.path().generic_string()});
                picture->setSize({100, 100*(picture->getSize().y/picture->getSize().x)});
                container->add(picture); // can have many overlapping photos but we also want to show if the container sorts the widgets
                
                if (widgetName != "SplitContainer")
                {
                    container->updateChildrenWithAutoLayout();
                    float width = 0;
                    float height = 0;
                    for (auto widget: container->getWidgets())
                    {
                        if (widget->getFullSize().x > width)
                            width = widget->getFullSize().x;
                        float temp = widget->getPosition().y + widget->getFullSize().y;
                        if (temp > height)
                            height = temp;
                    }
                    container->setSize({width, height});
                }
                else
                {
                    container->setSize("100%", container->getSize().y < picture->getSize().y ? picture->getSize().y : container->getSize().y);
                }

                maxImages--;
            }
        }
        else if (auto button = lastWidget->cast<tgui::Button>())
        {
            button->setText(widgetName + " Text");
            auto disabled = lastWidget->clone()->cast<tgui::Button>();
            disabled->setPosition({0, temp});
            disabled->setEnabled(false);
            disabled->setText(widgetName + " Text (Disabled)");
            panel->add(disabled);
        }
        else if (widgetName == "ProgressBar")
        {
            auto progress = lastWidget->cast<tgui::ProgressBar>();
            progress->setMaximum(999);
            progress->setValue(rand()%1000);
        }
        else if (widgetName == "ComboBox")
        {
            auto box = lastWidget->cast<tgui::ComboBox>();
            box->addItem("Combo Box");
            box->addItem("Combo Box1");
            box->addItem("Combo Box2");
            box->addItem("Combo Box3");
            box->setSelectedItemByIndex(0);
        }
        else if (widgetName == "Label")
        {
            lastWidget->cast<tgui::Label>()->setText("Epic label");
        }
        else if (widgetName == "RichTextLabel")
        {
            lastWidget->cast<tgui::RichTextLabel>()->setMaximumTextWidth(200);
            lastWidget->cast<tgui::RichTextLabel>()->setText("The RichTextLabel widget supports formatting text with <b>bold</b>, <i>italics</i>, <u>underlined</u> "
                "and even <s>strikethrough</s>. Each letter can have a separate <size=15>size</size> or <color=blue>color</color>. "
                "This allows for some <b><color=#ff0000>C</color><color=#ffbf00>O</color><color=#80ff00>L</color>"
                "<color=#00ff40>O</color><color=#00ffff>R</color><color=#0040ff>F</color><color=#7f00ff>U</color>"
                "<color=#ff00bf>L</color></b> text. Lines that are too long will wrap around and a vertical scrollbar can be included "
                "when there are too many lines!");
        }
        else if (widgetName == "Picture")
        {
            for (auto file: std::filesystem::directory_iterator{"TestPhotos"})
            {
                lastWidget->cast<tgui::Picture>()->getRenderer()->setTexture({file.path().generic_string()});
                if (rand()%2) // pick random breaking point
                    break;
            }
        }
        else if (widgetName == "SeparatorLine")
        {
            lastWidget->setHeight(25);
            lastWidget->setWidth(5);
            lastWidget->setPosition({"50%", lastWidget->getPosition().y});
        }
        else if (widgetName == "RangeSlider")
        {
            auto slider = lastWidget->cast<tgui::RangeSlider>();
            slider->setMinimum(0);
            slider->setMaximum(999);
            slider->setSelectionStart(rand()%500);
            slider->setSelectionEnd(rand()%500+500);
        }
        else if (widgetName == "ListBox")
        {
            auto list = lastWidget->cast<tgui::ListBox>();
            list->addItem("Some Item");
            list->addItem("Another Item");
            list->addItem("I don't know what else to put");
            list->addItem("Something");
            list->addItem("Cat");
        }
        else if (widgetName == "ListView")
        {
            auto list = lastWidget->cast<tgui::ListView>();
            list->setResizableColumns(true);
            list->addColumn("Name");
            list->addColumn("Value");
            list->addColumn("Something Else");
            list->addItem({"Cat", "100", "..."});
            list->addItem({"a item", "13", "something"});
            list->addItem({"something", "54", "..."});
            list->addItem({"i dont know", "67", "who knows"});
            list->addItem({"anything", "62", "..."});
        }
        else if (widgetName == "MenuBar")
        {
            auto bar = lastWidget->cast<tgui::MenuBar>();
            bar->addMenu("Disabled");
            bar->setMenuEnabled("Disabled", false);
            bar->addMenu("Enabled");
            bar->addMenuItem("Enabled", "Menu Item");
            bar->setSize({200, 50});
        }
        else if (widgetName == "Tabs")
        {
            auto tabs = lastWidget->cast<tgui::Tabs>();
            tabs->add("Some Tab");
            tabs->add("Another Tab");
            tabs->add("Cats!");
            tabs->add("Yet Another Tab");
        }
        else if (widgetName == "TreeView")
        {
            auto tree = lastWidget->cast<tgui::TreeView>();
            tree->addItem({"Root", "Branch", "Branch Branch", "Leaf"});
            tree->addItem({"Cats", "more Cats?", "Even more cats", "so many cats"});
            tree->addItem({"Why Cats?", "Cats are cool"});
        }
        
        widgetHolder->add(panel);

        float width = 0;
        float height = 0;
        for (auto widget: panel->getWidgets())
        {
            if (widget->getFullSize().x > width)
                width = widget->getFullSize().x;
            height += widget->getFullSize().y;
        }
        panel->setSize({width + panel->getSharedRenderer()->getPadding().getLeft() + panel->getSharedRenderer()->getPadding().getRight() + 5, 
                        height + panel->getSharedRenderer()->getPadding().getTop() + panel->getSharedRenderer()->getPadding().getBottom() + 5});
    }

    widgetHolder->updateChildrenWithAutoLayout();
    widgetHolder->setSize({"100%", widgetHolder->getWidgets().back()->getPosition().y + widgetHolder->getWidgets().back()->getFullSize().y + 15}); // have to get last widget because size does not update for some reason
    scroll->setContentSize({scroll->getSize().x, widgetHolder->getFullSize().y}); 
    gui.add(scroll);
}

/// @brief creates the cpp class files for the given theme (assumes its loaded from a txt file)
static void createCppTheme(tgui::String name, tgui::Theme theme)
{
    std::string className = name.toStdString() + "Theme";

    assert((!std::filesystem::exists(className + ".hpp")) && "Class already exists");

    {
    std::ofstream header(className + ".hpp");
    header << "#ifndef " << name.toUpper().toStdString() << "_" << "THEME_HPP" << "\n#define " << name.toUpper() << "_" << "THEME_HPP" << "\n#pragma once"; // adding header define stuff
    header << "\n#include \"TGUI/Loading/Theme.hpp\"" << "\nstruct " << className << " : tgui::Theme" << "{" << className << "();" << "};" << "\n"; // defining the class and its constructor
    header << "#endif"; // end of head file
    }

    // making the cpp file
    std::ofstream source(className + ".cpp");
    source << "#include \"" << className << ".hpp" << "\"\n" << className << "::" << className << "()\n{"; // including and starting the constructor

    std::map<tgui::String, tgui::ObjectConverter> globalProperties;

    bool isFirst = true;

    source << "m_renderers = {";
    for (auto widgetName: tgui::WidgetFactory::getWidgetTypes())
    {
        std::map<tgui::String, tgui::ObjectConverter> properties;
        try
        {
            properties = theme.getRenderer(widgetName)->propertyValuePairs;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            source << "})";
        }

        if (!isFirst)
            source << ",";
        else
            isFirst = false;
        source << "{\"" << widgetName.toStdString() << "\", tgui::RendererData::create({";

        bool isFirst2 = true;

        for (auto property: properties)
        {
            if (!isFirst2)
                source << ",";
            else
                isFirst2 = false;
            if (property.second.getType() == tgui::ObjectConverter::Type::RendererData)
                continue;

            if (theme.getGlobalProperty(property.first).getType() != tgui::ObjectConverter::Type::None)
                globalProperties.emplace(property);

            source << "{\"" << property.first << "\",\"" << property.second.getString().toStdString() << "\"}";
        }

        source << "})}";
    }
    source << "};";

    isFirst = true;

    source << "m_globalProperties = {";
    for (auto property: globalProperties)
    {
        if (!isFirst)
            source << ",";
        else
            isFirst = false;

        source << "{\"" << property.first.toStdString() << "\",\"" << property.second.getString().toStdString() << "\"}";
    }
    source << "};";

    source << "}"; // ending the constructor
}