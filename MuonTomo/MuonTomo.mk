##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=MuonTomo
ConfigurationName      :=Debug
WorkspacePath          := "/home/vega/NetBeansProjects/Tomography"
ProjectPath            := "/home/vega/NetBeansProjects/Tomography/MuonTomo"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Abhijit
Date                   :=06/07/16
CodeLitePath           :="/home/vega/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="MuonTomo.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  `/usr/local/root-v6/bin/root-config --libs` -lRIO -lMathMore -lm -lGraf -lGpad -lGeom -lCore
IncludePath            := $(IncludeSwitch)/usr/local/root-v6/include  $(IncludeSwitch). $(IncludeSwitch)/usr/local/root-v6/include $(IncludeSwitch)/usr/include $(IncludeSwitch)/usr/local/include $(IncludeSwitch)/usr/local/Anaconda/include $(IncludeSwitch)/usr/local/GSL/include/gsl $(IncludeSwitch)/usr/local/root-v6/include $(IncludeSwitch)/home/vega/NetBeansProjects/Tomography/CC/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                :=$(LibraryPathSwitch)/usr/local/root-v6/lib  $(LibraryPathSwitch)/usr/local/root-v6/lib $(LibraryPathSwitch)/usr/local/lib64 $(LibraryPathSwitch)/usr/local/lib $(LibraryPathSwitch)/usr/lib64 $(LibraryPathSwitch)/usr/local/Anaconda/lib $(LibraryPathSwitch)/usr/local/GSL/lib64 $(LibraryPathSwitch)/usr/local/root-v6/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -std=c++11 -g -O0 -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O0 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
LD_LIBRARY_PATH:=/usr/local/root-v6/lib:${LD_LIBRARY_PATH}
Objects0=$(IntermediateDirectory)/src_muonTomography.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_muonTomography.cpp$(ObjectSuffix): ../CC/src/muonTomography.cpp $(IntermediateDirectory)/src_muonTomography.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/vega/NetBeansProjects/Tomography/CC/src/muonTomography.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_muonTomography.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_muonTomography.cpp$(DependSuffix): ../CC/src/muonTomography.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_muonTomography.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_muonTomography.cpp$(DependSuffix) -MM "../CC/src/muonTomography.cpp"

$(IntermediateDirectory)/src_muonTomography.cpp$(PreprocessSuffix): ../CC/src/muonTomography.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_muonTomography.cpp$(PreprocessSuffix) "../CC/src/muonTomography.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


