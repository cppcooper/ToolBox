##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=GameFramework
ConfigurationName      :=Release
WorkspacePath          :=S:/ToolBox/.projects/Cheryl-Engine
ProjectPath            :=S:/ToolBox/.projects/Cheryl-Engine/GameFramework
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
ObjectsFileList        :="GameFramework.txt"
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
Objects0=$(IntermediateDirectory)/ControlModule.cpp$(ObjectSuffix) $(IntermediateDirectory)/GameFramework.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_InputBinding.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_InputContext.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_InputMapper.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_InputState_SteamController.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_InputSystem.cpp$(ObjectSuffix) 



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
	@echo rebuilt > "S:\ToolBox\.projects\Cheryl-Engine/.build-debug/GameFramework"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


./Release:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/ControlModule.cpp$(ObjectSuffix): ../../../cheryl-engine/GameFramework/src/ControlModule.cpp $(IntermediateDirectory)/ControlModule.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GameFramework/src/ControlModule.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ControlModule.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ControlModule.cpp$(DependSuffix): ../../../cheryl-engine/GameFramework/src/ControlModule.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ControlModule.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ControlModule.cpp$(DependSuffix) -MM "../../../cheryl-engine/GameFramework/src/ControlModule.cpp"

$(IntermediateDirectory)/ControlModule.cpp$(PreprocessSuffix): ../../../cheryl-engine/GameFramework/src/ControlModule.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ControlModule.cpp$(PreprocessSuffix) "../../../cheryl-engine/GameFramework/src/ControlModule.cpp"

$(IntermediateDirectory)/GameFramework.cpp$(ObjectSuffix): ../../../cheryl-engine/GameFramework/src/GameFramework.cpp $(IntermediateDirectory)/GameFramework.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GameFramework/src/GameFramework.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameFramework.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameFramework.cpp$(DependSuffix): ../../../cheryl-engine/GameFramework/src/GameFramework.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameFramework.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GameFramework.cpp$(DependSuffix) -MM "../../../cheryl-engine/GameFramework/src/GameFramework.cpp"

$(IntermediateDirectory)/GameFramework.cpp$(PreprocessSuffix): ../../../cheryl-engine/GameFramework/src/GameFramework.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameFramework.cpp$(PreprocessSuffix) "../../../cheryl-engine/GameFramework/src/GameFramework.cpp"

$(IntermediateDirectory)/src_InputBinding.cpp$(ObjectSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputBinding.cpp $(IntermediateDirectory)/src_InputBinding.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GameFramework/Input/src/InputBinding.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_InputBinding.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_InputBinding.cpp$(DependSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputBinding.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_InputBinding.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_InputBinding.cpp$(DependSuffix) -MM "../../../cheryl-engine/GameFramework/Input/src/InputBinding.cpp"

$(IntermediateDirectory)/src_InputBinding.cpp$(PreprocessSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputBinding.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_InputBinding.cpp$(PreprocessSuffix) "../../../cheryl-engine/GameFramework/Input/src/InputBinding.cpp"

$(IntermediateDirectory)/src_InputContext.cpp$(ObjectSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputContext.cpp $(IntermediateDirectory)/src_InputContext.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GameFramework/Input/src/InputContext.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_InputContext.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_InputContext.cpp$(DependSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputContext.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_InputContext.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_InputContext.cpp$(DependSuffix) -MM "../../../cheryl-engine/GameFramework/Input/src/InputContext.cpp"

$(IntermediateDirectory)/src_InputContext.cpp$(PreprocessSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputContext.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_InputContext.cpp$(PreprocessSuffix) "../../../cheryl-engine/GameFramework/Input/src/InputContext.cpp"

$(IntermediateDirectory)/src_InputMapper.cpp$(ObjectSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputMapper.cpp $(IntermediateDirectory)/src_InputMapper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GameFramework/Input/src/InputMapper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_InputMapper.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_InputMapper.cpp$(DependSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputMapper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_InputMapper.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_InputMapper.cpp$(DependSuffix) -MM "../../../cheryl-engine/GameFramework/Input/src/InputMapper.cpp"

$(IntermediateDirectory)/src_InputMapper.cpp$(PreprocessSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputMapper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_InputMapper.cpp$(PreprocessSuffix) "../../../cheryl-engine/GameFramework/Input/src/InputMapper.cpp"

$(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(ObjectSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputState_KeyboardMouse.cpp $(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GameFramework/Input/src/InputState_KeyboardMouse.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(DependSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputState_KeyboardMouse.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(DependSuffix) -MM "../../../cheryl-engine/GameFramework/Input/src/InputState_KeyboardMouse.cpp"

$(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(PreprocessSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputState_KeyboardMouse.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_InputState_KeyboardMouse.cpp$(PreprocessSuffix) "../../../cheryl-engine/GameFramework/Input/src/InputState_KeyboardMouse.cpp"

$(IntermediateDirectory)/src_InputState_SteamController.cpp$(ObjectSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputState_SteamController.cpp $(IntermediateDirectory)/src_InputState_SteamController.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GameFramework/Input/src/InputState_SteamController.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_InputState_SteamController.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_InputState_SteamController.cpp$(DependSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputState_SteamController.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_InputState_SteamController.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_InputState_SteamController.cpp$(DependSuffix) -MM "../../../cheryl-engine/GameFramework/Input/src/InputState_SteamController.cpp"

$(IntermediateDirectory)/src_InputState_SteamController.cpp$(PreprocessSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputState_SteamController.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_InputState_SteamController.cpp$(PreprocessSuffix) "../../../cheryl-engine/GameFramework/Input/src/InputState_SteamController.cpp"

$(IntermediateDirectory)/src_InputSystem.cpp$(ObjectSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputSystem.cpp $(IntermediateDirectory)/src_InputSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/GameFramework/Input/src/InputSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_InputSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_InputSystem.cpp$(DependSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_InputSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_InputSystem.cpp$(DependSuffix) -MM "../../../cheryl-engine/GameFramework/Input/src/InputSystem.cpp"

$(IntermediateDirectory)/src_InputSystem.cpp$(PreprocessSuffix): ../../../cheryl-engine/GameFramework/Input/src/InputSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_InputSystem.cpp$(PreprocessSuffix) "../../../cheryl-engine/GameFramework/Input/src/InputSystem.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


