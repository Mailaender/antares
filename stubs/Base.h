#ifndef ANTARES_STUB_BASE_H_
#define ANTARES_STUB_BASE_H_

#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <Stub.h>

#define pascal

enum {
    noErr = 0,
    paramErr = 1,
    memFullErr = 2,

    maxSize = 100,

    plainDBox = 200,

    nullEvent = 0,
    everyEvent = 300,
    updateEvt = 301,
    mouseDown = 303,
    mouseUp = 304,
    keyDown = 305,
    autoKey = 306,
    osEvt = 307,
    kHighLevelEvent = 308,

    inMenuBar = 400,
    inSysWindow = 401,
    inContent = 402,
    inDrag = 403,
    inGoAway = 404,

    cmdKey = 500,
    optionKey = 501,
    shiftKey = 502,
    alphaLock = 503,
    smKCHRCache = 504,

    charCodeMask = 600,
    keyCodeMask = 601,
    resumeFlag = 602,
    convertClipboardFlag = 603,

    noGrowDocProc = 700,

    mouseMovedMessage = 800,
    suspendResumeMessage = 801,
};

typedef short ShortBoolean;
typedef bool Boolean;
typedef int16_t OSErr;

typedef int8_t SignedByte;
typedef uint8_t Byte;
typedef int8_t SInt8;
typedef uint8_t UInt8;
typedef int16_t SInt16;
typedef uint16_t UInt16;
typedef int32_t SInt32;
typedef uint32_t UInt32;
typedef struct { SInt32 hi; UInt32 lo; } wide;
typedef struct { UInt32 hi; UInt32 lo; } UnsignedWide;

void WideAdd(wide* value, wide* summand);
void WideSubtract(wide* value, wide* difference);
void WideMultiply(long a, long b, wide* c);

typedef int32_t Fixed;
typedef long Size;

typedef char* Ptr;
STUB1(NewPtr, Ptr(size_t size), new char[a0]);
STUB1(DisposePtr, void(Ptr ptr));

typedef Ptr* Handle;
Handle NewHandle(size_t size);
int GetHandleSize(Handle handle);
STUB1(DisposeHandle, void(Handle handle));
STUB2(SetHandleSize, void(Handle handle, Size size));
STUB1(MoveHHi, void(Handle handle));
STUB1(HLock, void(Handle handle));
STUB1(HLockHi, void(Handle handle));
STUB1(HUnlock, void(Handle handle));
STUB1(HGetState, int8_t(Handle handle), 0);
STUB2(HSetState, void(Handle handle, int8_t state));
STUB1(HNoPurge, void(Handle handle));
OSErr PtrToHand(void* ptr, Handle* handle, int len);

STUB1(HiWord, int(long value), 0);
STUB1(LoWord, int(long value), 0);

void Microseconds(UnsignedWide* wide);

STUB1(MaxMem, Size(Size*), 0);
STUB1(CompactMem, Size(int), 100 * 1024 * 1024);  // 100MB
void BlockMove(void* src, void* dst, size_t size);
STUB1(HandToHand, OSErr(Handle* handle), noErr);
STUB2(HandAndHand, void(Handle src, Handle dst));

typedef void* AddrBlock;

#define nil NULL

typedef unsigned char Str255[256];
typedef unsigned char Str63[64];
typedef unsigned char Str31[32];
typedef unsigned char* StringPtr;
typedef const unsigned char* ConstStringPtr;
typedef const unsigned char* ConstStr255Param;
typedef const unsigned char* ConstStr31Param;
typedef Str63 StrFileName;

typedef uint32_t FourCharCode;
typedef FourCharCode OSType;
typedef FourCharCode ResType;

STUB0(MemError, OSErr(), noErr);
STUB0(ResError, OSErr(), noErr);

enum {
    TRUE = true,
    FALSE = false,
};

typedef struct {
    int v;
    int h;
} Point;

typedef struct {
    int left;
    int top;
    int right;
    int bottom;
} Rect;

void SetRect(Rect*, int, int, int, int);
void MacSetRect(Rect*, int, int, int, int);
void OffsetRect(Rect*, int, int);
void MacOffsetRect(Rect*, int, int);
bool MacPtInRect(Point, Rect*);
void MacInsetRect(Rect*, int, int);

////////////////////////////

struct Window;
typedef Window* WindowPtr;
typedef Window** WindowRef;

extern Window fakeWindow;
STUB1(BeginUpdate, void(Window* window));
STUB1(EndUpdate, void(Window* window));
STUB8(NewWindow, Window*(void*, Rect*, const unsigned char* title, bool, int,
      Window* behind, bool, int), &fakeWindow)
STUB1(MacShowWindow, void(Window*));
STUB1(DisposeWindow, void(Window*));
STUB2(MacFindWindow, short(Point where, Window** window), 0);
STUB4(MacMoveWindow, void(Window*, int x, int y, bool));
STUB2(ShowHide, void(Window*, bool hide));
STUB3(DragWindow, void(Window*, Point where, Rect* bounds));
STUB2(TrackGoAway, bool(Window*, Point where), false);
STUB1(GlobalToLocal, void(Point*));
STUB1(SelectWindow, void(Window*));

typedef Window CWindow;
typedef CWindow* CWindowPtr;

STUB8(NewCWindow,
    CWindow*(void*, Rect* size, const unsigned char* title, bool, int,
      Window* behind, bool, int id),
    &fakeWindow);

typedef struct {
    int red;
    int green;
    int blue;
} RGBColor;

typedef struct {
    int value;
    RGBColor rgb;
} ColorSpec;
typedef ColorSpec* ColorSpecPtr;

typedef struct {
    ColorSpecPtr ctTable;
    int ctSize;
} CTab;
typedef CTab* CTabPtr;
typedef CTab** CTabHandle;

extern CTab* fakeCTabPtr;

STUB1(GetCTable, CTab**(int id), &fakeCTabPtr);
STUB1(DisposeCTable, void(CTab** handle));
STUB1(CTabChanged, void(CTab** handle));
void Index2Color(long index, RGBColor* color);

typedef CTab** WCTabHandle;

typedef struct {
    WCTabHandle awCTable;
} AuxWin;
typedef AuxWin** AuxWinHandle;

typedef int KeyMap[4];

void GetKeys(KeyMap keys);

typedef struct { } ICInstance;

typedef struct {
    int what;
    int message;
    Point where;
    int modifiers;
} EventRecord;

struct Rgn { };
typedef Rgn* RgnPtr;
typedef Rgn** RgnHandle;

STUB2(FlushEvents, void(int mask, int));
STUB1(SetEventMask, void(int mask));
bool WaitNextEvent(long mask, EventRecord* evt, unsigned long sleep, Rgn** mouseRgn);

typedef Handle MenuHandle;

STUB1(GetNewMBar, MenuHandle(int id), NULL);
STUB1(SetMenuBar, void(MenuHandle menu));
STUB1(GetMenuHandle, MenuHandle(int id), NULL);
STUB2(AppendResMenu, void(MenuHandle handle, FourCharCode));
STUB0(MacDrawMenuBar, void());
STUB1(HiliteMenu, void(int));
STUB1(MenuSelect, long(Point where), 0);
STUB2(SystemClick, void(EventRecord* event, Window* window));
STUB3(GetMenuItemText, void(MenuHandle, int item, unsigned char* name));
STUB1(HandleMenuChoice, bool(int), false);
STUB1(MenuKey, int(char which_char), 0);
STUB1(OpenDeskAcc, int(const unsigned char* name), 0);

STUB2(NoteAlert, void(int type, void*));

// Gets STR# from resource fork
void GetIndString(unsigned char* result, int id, int index);

STUB2(GetIndResource, Handle(FourCharCode type, int id), NULL);

STUB0(Debugger, void());

STUB6(Munger, int(Handle, int, const unsigned char* dest, size_t dest_length,
      const void* source, size_t source_length), 0);

STUB1(SysBeep, void(int));

STUB0(ExitToShell, void());

STUB1(GetDateTime, void(unsigned long* time));

STUB0(InitCursor, void());
STUB0(MacShowCursor, void());
STUB0(HideCursor, void());
STUB2(ShieldCursor, void(Rect* rect, Point point));
void GetMouse(Point* point);

STUB0(InitWindows, void());
STUB0(InitMenus, void());
STUB1(InitDialogs, void(void*));
STUB0(MoreMasters, void());
STUB0(MaxApplZone, void());

int TickCount();

STUB4(GetResInfo, void(Handle resource, short* id, FourCharCode* type, unsigned char* name));
STUB1(RemoveResource, void(Handle resource));
STUB1(UpdateResFile, void(int file));
STUB4(AddResource, void(Handle resource, FourCharCode type, int id, const unsigned char* name));
STUB1(ChangedResource, void(Handle resource));
STUB1(WriteResource, void(Handle resource));

bool Button();
STUB0(GetDblTime, double(), 0.0);

extern AuxWin* fakeAuxWinPtr;
void GetAuxWin(Window*, AuxWinHandle* handle);
STUB2(SetWinColor, void(Window* window, WCTabHandle handle));

typedef struct { } NumVersion;

STUB4(EasyOpenPreferenceFile,
    bool(const unsigned char* file_name, int creator, int type, short* ref_num), true);

STUB1(mAssert, void(bool condition));

STUB4(ParamText, void(const unsigned char*, const unsigned char*,
      const unsigned char*, const unsigned char*));

STUB2(StopAlert, void(int id, void*));

STUB1(DebugStr, void(const unsigned char* str));

typedef struct { } Dialog;
typedef Dialog* DialogPtr;

STUB3(GetNewDialog, Dialog*(int id, void*, Window* window), NULL);
STUB3(SetDialogFontAndSize, void(Dialog* dialog, int font, int size));
STUB2(SetDialogDefaultItem, void(Dialog*, int item));
STUB5(GetDialogItem, void(Dialog*, int item, short* type, Handle* handle, Rect* rect));
void ModalDialog(void*, short* item);
STUB1(DisposeDialog, void(Dialog* dialog));
STUB1(DrawDialog, void(Dialog* dialog));

typedef struct { } Control;
typedef Control* ControlPtr;
typedef Control** ControlHandle;

STUB2(HiliteControl, void(Control**, int));

STUB2(SetWRefCon, void(Dialog*, long));

long AngleFromSlope(Fixed slope);
long Random();

STUB2(StringToNum, void(unsigned char* string, long* value));

STUB1(GetScriptManagerVariable, Ptr(int cache), NULL);
STUB3(KeyTranslate, long(Ptr kchr, short keyCode, unsigned long* keyTranslateState), 0);

typedef struct {
    Rect bounds;
    CTabHandle pmTable;
    long rowBytes;
    char* baseAddr;
    int pixelSize;
} PixMap;
typedef PixMap* PixMapPtr;
typedef PixMap** PixMapHandle;
typedef PixMap BitMap;

struct Window {
    Rect portRect;
    BitMap portBits;
};

#endif // ANTARES_STUB_BASE_H_
