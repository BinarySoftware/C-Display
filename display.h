#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

///=============================================================================
///==== Structure for keeping size properties of Terminal ======================
///=============================================================================
struct Size {
    int lines;
    int columns;
};

struct Size getTerminalSize(void);

///=============================================================================
///==== Structure for keeping data of Display ==================================
///=============================================================================
struct Display {
    struct Size size;
    char** array;
};

struct Display initializeDisplay();

///=============================================================================
///==== Display array management and building ==================================
///=============================================================================
char** initializeArray(int m, int n);

void destroyDisplay(struct Display d);

void makeEmptyDisplay(struct Display d);

void buildDisplay(struct Display d);


///=============================================================================
///==== Methods for creating shapes on display =================================
///=============================================================================
void pushCharToPoint(char c, int ln, int col, struct Display d);

void createLine(char c, struct Display d, int ln, int beg, int end);

void createColumn(char c, struct Display d, int col, int beg, int end);

void createDiagonal(char c, struct Display d, int xBeg, int yBeg, int xEnd, int yEnd);

void createLineText(char* c, struct Display d, int ln, int beg);

void createColumnText(char* c, struct Display d, int col, int beg);

void createBox(char c, struct Display d, int xBeg, int yBeg, int xEnd, int yEnd);

void createFrame(char c, struct Display d);


///=============================================================================
///==== DEPRECATED Methods =====================================================
///=============================================================================
__deprecated void createFrameDeprecated(char c, struct Display d);