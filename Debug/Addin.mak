################################################
# Make file for CASIO fx-9860G SDK Addin
#
############################
# Directory defines
TCDIR = C:\Program Files\CASIO\fx-9860G SDK\OS\SH
OSDIR = C:\Program Files\CASIO\fx-9860G SDK\OS
APPDIR = D:\Anderain\fx-9860\DL2
OUTDIR = D:\Anderain\fx-9860\DL2\Debug

################
# Main Defines
SH_EXEDIR=$(TCDIR)\bin

# Hitachi SH C/C++ Compiler02 phase
SHCC02_EXE=shc.exe
SHCC02_DEP="$(OSDIR)\FX\include\fxlib.h" "dl2_all.h"

# Hitachi SH Assembler03 phase
SHASM03_EXE=asmsh.exe

# Hitachi OptLinker04 phase
SHLINK04_EXE=Optlnk.exe
SHLINK04_DEP="$(OSDIR)\FX\lib\fx9860G_library.lib"
SHLINK04_DEP2="$(OSDIR)\FX\lib\setup.obj"

#######################
# Files to build
FILE0=dl2_main
FILESRC0="$(APPDIR)\$(FILE0).c"
FILEOBJ0="$(OUTDIR)\$(FILE0).obj"
FILE1=dl2_chsfont
FILESRC1="$(APPDIR)\$(FILE1).c"
FILEOBJ1="$(OUTDIR)\$(FILE1).obj"
FILE2=dl2_draw
FILESRC2="$(APPDIR)\$(FILE2).c"
FILEOBJ2="$(OUTDIR)\$(FILE2).obj"
FILE3=dl2_key
FILESRC3="$(APPDIR)\$(FILE3).c"
FILEOBJ3="$(OUTDIR)\$(FILE3).obj"
FILE4=dl2_file
FILESRC4="$(APPDIR)\$(FILE4).c"
FILEOBJ4="$(OUTDIR)\$(FILE4).obj"
FILE5=dl2_dialog
FILESRC5="$(APPDIR)\$(FILE5).c"
FILEOBJ5="$(OUTDIR)\$(FILE5).obj"
FILE6=dl2_list
FILESRC6="$(APPDIR)\$(FILE6).c"
FILEOBJ6="$(OUTDIR)\$(FILE6).obj"
FILE7=dl2_pic
FILESRC7="$(APPDIR)\$(FILE7).c"
FILEOBJ7="$(OUTDIR)\$(FILE7).obj"
RFILE=FXADDINror
USERALLOBJ=$(FILEOBJ0) $(FILEOBJ1) $(FILEOBJ2) $(FILEOBJ3) $(FILEOBJ4) $(FILEOBJ5) $(FILEOBJ6) $(FILEOBJ7)

#######################
# nmake "all" statement

ALL:  SH_ENV \
	$(USERALLOBJ) \
	$(OUTDIR)\$(RFILE).bin \

####################
# Description blocks

!MESSAGE %3#C$z`&'0?
!MESSAGE
!MESSAGE Executing Hitachi SH C/C++ Compiler/Assembler phase
!MESSAGE

SH_ENV : 
	set SHC_INC=$(TCDIR)\include
	set PATH=$(TCDIR)\bin
	set SHC_LIB=$(TCDIR)\bin
	set SHC_TMP=$(OUTDIR)

$(FILEOBJ0) : $(FILESRC0) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ0)
-show=source
-listfile="$(OUTDIR)\$(FILE0).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC0)
-lang=c
-nologo
-debug
<<

$(FILEOBJ1) : $(FILESRC1) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ1)
-show=source
-listfile="$(OUTDIR)\$(FILE1).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC1)
-lang=c
-nologo
-debug
<<

$(FILEOBJ2) : $(FILESRC2) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ2)
-show=source
-listfile="$(OUTDIR)\$(FILE2).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC2)
-lang=c
-nologo
-debug
<<

$(FILEOBJ3) : $(FILESRC3) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ3)
-show=source
-listfile="$(OUTDIR)\$(FILE3).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC3)
-lang=c
-nologo
-debug
<<

$(FILEOBJ4) : $(FILESRC4) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ4)
-show=source
-listfile="$(OUTDIR)\$(FILE4).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC4)
-lang=c
-nologo
-debug
<<

$(FILEOBJ5) : $(FILESRC5) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ5)
-show=source
-listfile="$(OUTDIR)\$(FILE5).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC5)
-lang=c
-nologo
-debug
<<

$(FILEOBJ6) : $(FILESRC6) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ6)
-show=source
-listfile="$(OUTDIR)\$(FILE6).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC6)
-lang=c
-nologo
-debug
<<

$(FILEOBJ7) : $(FILESRC7) $(SHCC02_DEP)
	"$(SH_EXEDIR)\$(SHCC02_EXE)" -subcommand=<<
-cpu=sh3
-include="$(OSDIR)\FX\include","$(APPDIR)"
-objectfile=$(FILEOBJ7)
-show=source
-listfile="$(OUTDIR)\$(FILE7).lst"
-size
-noinline
-chgincpath
-errorpath
$(FILESRC7)
-lang=c
-nologo
-debug
<<

!MESSAGE
!MESSAGE Executing Hitachi OptLinker04 phase
!MESSAGE

"$(OUTDIR)\$(RFILE).bin" : $(USERALLOBJ) $(SHLINK04_DEP2) $(SHLINK04_DEP)
	"$(SH_EXEDIR)\$(SHLINK04_EXE)" -subcommand=<<
noprelink
sdebug
rom D=R
nomessage 
list "$(OUTDIR)\$(RFILE).map"
show symbol
nooptimize
start P_TOP,P,C,D,C$VTBL,C$INIT/0300200,B_BR_Size,B,R/08100000
fsymbol P
nologo
input $(USERALLOBJ)
input $(SHLINK04_DEP2)
library $(SHLINK04_DEP)
output "$(OUTDIR)\$(RFILE).abs"
-nomessage=1100
end
input "$(OUTDIR)\$(RFILE).abs"
form binary
output "$(OUTDIR)\$(RFILE).bin"
exit
<<

