

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


struct FieldSlot 
{
    int row; 
    int col;
    int side;
};

class FieldLayout
{
public:
    FieldLayout();
    ~FieldLayout();

private:
    FieldSlot fieldSlot[ROW_SIZE][COL_SIZE];

};