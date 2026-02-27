#ifndef FIELDLAYOUT_H
#define FIELDLAYOUT_H


#include <unordered_map>  

#define ROW_SIZE 3
#define COL_SIZE 3

enum FieldPos
{
    RearTop,
    CenterTop,
    FrontTop,
    RearMid,
    CenterMid,
    FrontMid,
    RearBot,
    CenterBot,
    FrontBot
};

#define FIELD_SIDE_LEFT 1
#define FIELD_SIDE_RIGHT 2

struct FieldSlot 
{
    int row; 
    int col;
    // int side;
};

class FieldLayout
{
public:
    FieldLayout();
    ~FieldLayout();

    void init(int side);

    FieldSlot * getFieldSlot(int row, int col) { return &m_fieldSlot[row][col]; };
    FieldSlot * getFieldSlot(FieldPos pos) { return &m_fieldSlotMap[pos]; };

private:
    int m_side = 0;
    FieldSlot m_fieldSlot[ROW_SIZE][COL_SIZE];
    std::unordered_map<int, FieldSlot> m_fieldSlotMap;
    

};


#endif // FIELDLAYOUT_H