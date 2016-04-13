##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=GLEngine
ConfigurationName      :=Release
WorkspacePath          :=S:/ToolBox/.projects/Cheryl-Engine
ProjectPath            :=S:/ToolBox/.projects/Cheryl-Engine/glEngine
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Josh
Date                   :=13/04/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
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
OutputFile             :=../../../redistributable_bin/Cheryl-Engine/$(ProjectName)_Release.a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="GLEngine.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -std=c++11 $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/GLEngine.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "S:\ToolBox\.projects\Cheryl-Engine/.build-debug"
	@echo rebuilt > "S:\ToolBox\.projects\Cheryl-Engine/.build-debug/GLEngine"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


./Release:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/GLEngine.cpp$(ObjectSuffix): ../../../cheryl-engine/GLEngine/src/GLEngine.cpp $(IntermediateDirectory)/GLEngine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GLEngine/src/GLEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GLEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GLEngine.cpp$(DependSuffix): ../../../cheryl-engine/GLEngine/src/GLEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GLEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GLEngine.cpp$(DependSuffix) -MM "../../../cheryl-engine/GLEngine/src/GLEngine.cpp"

$(IntermediateDirectory)/GLEngine.cpp$(PreprocessSuffix): ../../../cheryl-engine/GLEngine/src/GLEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GLEngine.cpp$(PreprocessSuffix) "../../../cheryl-engine/GLEngine/src/GLEngine.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


