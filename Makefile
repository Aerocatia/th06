# This makefile is made to only run inside the devenv by nmake.
!include <win32.mak>

CPP=cl.exe
LINK32=link.exe
RSC=rc.exe

CFLAGS=/nologo /MT /GS /Od /Oi /Ob1 /DNDEBUG /Zi
LINK32_BASE_LIBS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
LINK32_LIBS=dxguid.lib d3dx8.lib d3d8.lib winmm.lib $(LINK32_BASE_LIBS)
LINK32_FLAGS=/nologo /subsystem:windows /machine:X86 /filealign:4096 /incremental:no
LINK_LIBS=

OBJ_DIR=build
RES_DIR=resources
SRC_DIR=src

.SUFFIXES : .cpp .obj

TH06E_OBJS=	$(OBJ_DIR)\main.obj \
			$(OBJ_DIR)\Chain.obj \
			$(OBJ_DIR)\GameContext.obj \
			$(OBJ_DIR)\GameErrorContext.obj \
			$(OBJ_DIR)\GameWindow.obj \
			$(OBJ_DIR)\SoundPlayer.obj \
			$(OBJ_DIR)\VeryBigStruct.obj \
			$(OBJ_DIR)\utils.obj \
			$(OBJ_DIR)\th06.res

all: $(OBJ_DIR)\th06e.exe

$(OBJ_DIR)\th06.res: "$(OBJ_DIR)\icon.ico"

"$(OBJ_DIR)":
	-@if not exist "$(OBJ_DIR)/$(NULL)" mkdir "$(OBJ_DIR)"

"$(OBJ_DIR)\icon.ico":
	-@if exist "$(RES_DIR)\icon.ico" copy "$(RES_DIR)\icon.ico" "$(OBJ_DIR)\icon.ico"
	-@if not exist "$(RES_DIR)\icon.ico" copy "$(RES_DIR)\placeholder.ico" "$(OBJ_DIR)\icon.ico"

"$(OBJ_DIR)\th06e.exe": $(OBJ_DIR) $(TH06E_OBJS)
	-@$(LINK32) /out:$@ $(LINK32_FLAGS) /debug /pdb:"$(OBJ_DIR)\th06e.pdb" $(LINK32_LIBS) $(TH06E_OBJS)

{$(SRC_DIR)}.cpp{$(OBJ_DIR)}.obj:
	-@$(CPP) $(CFLAGS) /c $< /Fo$@

{$(RES_DIR)}.rc{$(OBJ_DIR)}.res:
	-@echo $<
	-@$(RSC) /fo $@ $<

clean:
	-@erase $(TH06E_OBJS) "$(OBJ_DIR)\th06e.exe" "$(OBJ_DIR)\th06e.pdb" "$(OBJ_DIR)\icon.ico"
	-@rmdir $(OBJ_DIR)

