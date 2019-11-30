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
///==== Structure for keeping and managing Display =============================
///=============================================================================
struct Display {
    struct Size size;
    char** array;
};

struct Display initializeDisplay();

char** initializeArray(int m, int n);

void destroyDisplay(struct Display d);

void makeEmptyDisplay(struct Display d);

void createFrameDeprecated(char c, struct Display d);

void createFrame(char c, struct Display d);

void createLine(char c, struct Display d, int ln, int beg, int end);

void createColumn(char c, struct Display d, int col, int beg, int end);

void createLineText(char* c, struct Display d, int ln, int beg, int len);

void createColumnText(char* c, struct Display d, int col, int beg, int len);

void buildDisplay(struct Display d);