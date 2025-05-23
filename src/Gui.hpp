#pragma once

#include "AnmVm.hpp"
#include "Chain.hpp"
#include "Enemy.hpp"
#include "ZunTimer.hpp"
#include "diffbuild.hpp"
#include "inttypes.hpp"
#include <Windows.h>

namespace th06
{
enum MsgOps
{
    MSG_OPCODE_MSGDELETE,
    MSG_OPCODE_PORTRAITANMSCRIPT,
    MSG_OPCODE_PORTRAITANMSPRITE,
    MSG_OPCODE_TEXTDIALOGUE,
    MSG_OPCODE_WAIT,
    MSG_OPCODE_ANMINTERRUPT,
    MSG_OPCODE_ECLRESUME,
    MSG_OPCODE_MUSIC,
    MSG_OPCODE_TEXTINTRO,
    MSG_OPCODE_STAGERESULTS,
    MSG_OPCODE_MSGHALT,
    MSG_OPCODE_STAGEEND,
    MSG_OPCODE_MUSICFADEOUT,
    MSG_OPCODE_WAITSKIPPABLE,
};

struct MsgRawInstrArgPortraitAnmScript
{
    i16 portraitIdx;
    i16 anmScriptIdx;
};
struct MsgRawInstrArgText
{
    i16 textColor;
    i16 textLine;
    char text[1];
};
struct MsgRawInstrArgAnmInterrupt
{
    i16 unk1;
    u8 unk2;
};
union MsgRawInstrArgs {
    MsgRawInstrArgPortraitAnmScript portraitAnmScript;
    MsgRawInstrArgText text;
    i32 dialogueSkippable;
    i32 wait;
    MsgRawInstrArgAnmInterrupt anmInterrupt;
    i32 music;
};
struct MsgRawInstr
{
    u16 time;
    u8 opcode;
    u8 argSize;
    MsgRawInstrArgs args;
};

struct MsgRawHeader
{
    i32 numInstrs;
    MsgRawInstr *instrs[1];
};
ZUN_ASSERT_SIZE(MsgRawHeader, 0x8);

struct GuiMsgVm
{
    MsgRawHeader *msgFile;
    MsgRawInstr *currentInstr;
    i32 currentMsgIdx;
    ZunTimer timer;
    i32 framesElapsedDuringPause;
    AnmVm portraits[2];
    AnmVm dialogueLines[2];
    AnmVm introLines[2];
    D3DCOLOR textColorsA[4];
    D3DCOLOR textColorsB[4];
    u32 fontSize;
    u32 ignoreWaitCounter;
    u8 dialogueSkippable;
};
ZUN_ASSERT_SIZE(GuiMsgVm, 0x6a8);

struct GuiFormattedText
{
    D3DXVECTOR3 pos;
    i32 fmtArg;
    i32 isShown;
    ZunTimer timer;
};
ZUN_ASSERT_SIZE(GuiFormattedText, 0x20);

struct GuiImpl
{
    GuiImpl();
    ZunResult RunMsg();
    ZunResult DrawDialogue();
    void MsgRead(i32 msgIdx);

    AnmVm vms[26];
    u8 bossHealthBarState;
    AnmVm stageNameSprite;
    AnmVm songNameSprite;
    AnmVm playerSpellcardPortrait;
    AnmVm enemySpellcardPortrait;
    AnmVm bombSpellcardName;
    AnmVm enemySpellcardName;
    AnmVm bombSpellcardBackground;
    AnmVm enemySpellcardBackground;
    AnmVm loadingScreenSprite;
    GuiMsgVm msg;
    u32 finishedStage;
    u32 stageScore;
    GuiFormattedText bonusScore;
    GuiFormattedText fullPowerMode;
    GuiFormattedText spellCardBonus;
};
ZUN_ASSERT_SIZE(GuiImpl, 0x2c44);
struct GuiFlags
{
    u32 flag0 : 2;
    u32 flag1 : 2;
    u32 flag2 : 2;
    u32 flag3 : 2;
    u32 flag4 : 2;
};

struct Gui
{
    static ZunResult RegisterChain();
    static void CutChain();
    static ZunResult AddedCallback(Gui *);
    static ZunResult DeletedCallback(Gui *);
    static ChainCallbackResult OnUpdate(Gui *);
    static ChainCallbackResult OnDraw(Gui *);

    ZunResult ActualAddedCallback();
    ZunResult LoadMsg(char *path);
    void FreeMsgFile();

    ZunBool IsStageFinished();

    void UpdateStageElements();
    ZunBool HasCurrentMsgIdx();

    void DrawStageElements();
    void DrawGameScene();

    void MsgRead(i32 msgIdx);
    ZunBool MsgWait();

    void ShowSpellcard(i32 spellcardSprite, char *spellcardName);
    void ShowSpellcardBonus(u32 spellcardScore);
    void ShowBombNamePortrait(u32 sprite, char *bombName);
    void ShowBonusScore(u32 bonusScore);
    void EndEnemySpellcard();
    void EndPlayerSpellcard();
    ZunBool IsDialogueSkippable();

    void ShowFullPowerMode(i32 fmtArg);

    void SetBossHealthBar(f32 val)
    {
        this->bossHealthBar1 = val;
    }

    bool BossPresent()
    {
        return this->bossPresent;
    }

    void SetSpellcardSeconds(i32 val)
    {
        this->spellcardSecondsRemaining = val;
    }

    i32 SpellcardSecondsRemaining()
    {
        return this->spellcardSecondsRemaining;
    }

    void TickTimer(ZunTimer *timer)
    {
        timer->NextTick();
    }

    GuiFlags flags;
    GuiImpl *impl;
    f32 bombSpellcardBarLength;
    f32 blueSpellcardBarLength;
    u32 bossUIOpacity;
    i32 eclSetLives;
    i32 spellcardSecondsRemaining;
    i32 lastSpellcardSecondsRemaining;
    bool bossPresent;
    f32 bossHealthBar1;
    f32 bossHealthBar2;
};
ZUN_ASSERT_SIZE(Gui, 0x2c);

DIFFABLE_EXTERN(Gui, g_Gui);
}; // namespace th06
