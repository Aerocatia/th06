#pragma once

#include "AnmVm.hpp"
#include "Chain.hpp"
#include "ZunResult.hpp"
#include "ZunTimer.hpp"
#include "inttypes.hpp"

namespace th06
{

#define END_READ_OPCODE '@'
enum EndOpcode
{
    END_OPCODE_FADE_IN_BLACK = '0',
    END_OPCODE_FADE_OUT_BLACK = '1',
    END_OPCODE_FADE_IN = '2',
    END_OPCODE_FADE_OUT = '3',
    END_OPCODE_EXECUTE_ANM = 'a',
    END_OPCODE_BACKGROUND = 'b',
    END_OPCODE_COLOR = 'c',
    END_OPCODE_PLAY_MUSIC = 'm',
    END_OPCODE_WAIT_RESET = 'r',
    END_OPCODE_SET_DELAY = 's',
    END_OPCODE_SET_VERTICAL_SCROLL_POS = 'v',
    END_OPCODE_WAIT = 'w',
    END_OPCODE_END = 'z',
    END_OPCODE_EXEC_END_FILE = 'F',
    END_OPCODE_FADE_MUSIC = 'M',
    END_OPCODE_ROLL_STAFF = 'R',
    END_OPCODE_SCROLL_BACKGROUND = 'V',
};

struct Ending
{
    Ending();
    static ZunResult RegisterChain();
    static ChainCallbackResult OnUpdate(Ending *ending);
    static ChainCallbackResult OnDraw(Ending *ending);
    static ZunResult AddedCallback(Ending *ending);
    static ZunResult DeletedCallback(Ending *ending);

    i32 ReadEndFileParameter();

    ZunResult ParseEndFile();

    ZunResult LoadEnding(char *endFilePath);
    void FadingEffect();

    ChainElem *calcChain;
    ChainElem *drawChain;
    ZunVec2 backgroundPos;
    f32 backgroundScrollSpeed;
    AnmVm sprites[16];
    char *endFileData;
    ZunBool hasSeenEnding;
    ZunTimer timer1;
    ZunTimer timer2;
    ZunTimer timer3;
    i32 minWaitResetFrames;
    i32 minWaitFrames;
    i32 line2Delay;
    i32 topLineDelay;
    i32 unk_1150;
    i32 timesFileParsed;
    ZunColor textColor;
    ZunColor unk_115c;
    i32 timeFading;
    i32 fadeFrames;
    i32 fadeType;
    char *endFileDataPtr;
};
C_ASSERT(sizeof(Ending) == 0x1170);
}; // namespace th06
