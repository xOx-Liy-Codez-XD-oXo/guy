#ifndef COLORS_H
#define COLORS_H
 
static const GXColor LC_WHITE  = {255, 255, 255, 255}; //"liy color"
static const GXColor LC_RED    = {255, 0,   0,   255};
static const GXColor LC_GREEN  = {0,   255, 0,   255};
static const GXColor LC_BLUE   = {0,   0, 255,   255};
static const GXColor LC_YELLOW = {255, 255, 0,   255};
static const GXColor LC_CYAN   = {0,   255, 255, 255};
static const GXColor LC_MAGENTA= {255, 0,   255, 255};
static const GXColor LC_LIGHTGREY={192,192, 192, 255};
static const GXColor LC_GREY   = {128, 128, 128, 255};
static const GXColor LC_DARKISH ={96,  96,  96,  255};
static const GXColor LC_DARKGREY={64,  64,  64,  255};
static const GXColor LC_DARKER = {32,  32,  32,  255};
static const GXColor LC_DARKDARK={16,16,16,255};
static const GXColor LC_DARKDARKDARK={8,8,8,255};
static const GXColor LC_DARKDARKDARKDARK={4,4,4,255};
static const GXColor LC_DARKDARKDARKDARKDARK={2,2,2,255};
static const GXColor LC_BLACK  = {0,   0,   0,   255};

static const u32 LC_GREY5STEP[5] = {0x000000FF, 0x404040FF, 0x808080FF, 0xC0C0C0FF, 0xFFFFFFFF};
//static const GXColor LC_GREY5STEP[5] = {LC_BLACK, LC_DARKGREY, LC_GREY, LC_LIGHTGREY, LC_WHITE};

#endif