##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=AssetFaculties
ConfigurationName      :=Release
WorkspacePath          :=S:/ToolBox/.projects/Cheryl-Engine
ProjectPath            :=S:/ToolBox/.projects/Cheryl-Engine/GameFaculties
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
ObjectsFileList        :="AssetFaculties.txt"
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
Objects0=$(IntermediateDirectory)/InterAccess.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_AssetAbstract.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_AssetMgr.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_File_Mgr.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Loader.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Pool.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Storage.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_2dtools.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_BasicTypes.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Font.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_Graphic.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Mesh.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_SceneNodes.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_Sprite.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_TileSet.cpp$(ObjectSuffix) 



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
	@echo rebuilt > "S:\ToolBox\.projects\Cheryl-Engine/.build-debug/AssetFaculties"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


./Release:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/InterAccess.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/src/InterAccess.cpp $(IntermediateDirectory)/InterAccess.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/src/InterAccess.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/InterAccess.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/InterAccess.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/src/InterAccess.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/InterAccess.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/InterAccess.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/src/InterAccess.cpp"

$(IntermediateDirectory)/InterAccess.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/src/InterAccess.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/InterAccess.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/src/InterAccess.cpp"

$(IntermediateDirectory)/src_AssetAbstract.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/AssetAbstract.cpp $(IntermediateDirectory)/src_AssetAbstract.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/Components/src/AssetAbstract.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_AssetAbstract.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_AssetAbstract.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/AssetAbstract.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_AssetAbstract.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_AssetAbstract.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/Components/src/AssetAbstract.cpp"

$(IntermediateDirectory)/src_AssetAbstract.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/AssetAbstract.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_AssetAbstract.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/Components/src/AssetAbstract.cpp"

$(IntermediateDirectory)/src_AssetMgr.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/AssetMgr.cpp $(IntermediateDirectory)/src_AssetMgr.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/Components/src/AssetMgr.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_AssetMgr.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_AssetMgr.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/AssetMgr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_AssetMgr.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_AssetMgr.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/Components/src/AssetMgr.cpp"

$(IntermediateDirectory)/src_AssetMgr.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/AssetMgr.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_AssetMgr.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/Components/src/AssetMgr.cpp"

$(IntermediateDirectory)/src_File_Mgr.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/File_Mgr.cpp $(IntermediateDirectory)/src_File_Mgr.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/Components/src/File_Mgr.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_File_Mgr.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_File_Mgr.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/File_Mgr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_File_Mgr.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_File_Mgr.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/Components/src/File_Mgr.cpp"

$(IntermediateDirectory)/src_File_Mgr.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/File_Mgr.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_File_Mgr.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/Components/src/File_Mgr.cpp"

$(IntermediateDirectory)/src_Loader.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Loader.cpp $(IntermediateDirectory)/src_Loader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/Components/src/Loader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Loader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Loader.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Loader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Loader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Loader.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/Components/src/Loader.cpp"

$(IntermediateDirectory)/src_Loader.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Loader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Loader.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/Components/src/Loader.cpp"

$(IntermediateDirectory)/src_Pool.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Pool.cpp $(IntermediateDirectory)/src_Pool.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/Components/src/Pool.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Pool.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Pool.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Pool.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Pool.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Pool.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/Components/src/Pool.cpp"

$(IntermediateDirectory)/src_Pool.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Pool.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Pool.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/Components/src/Pool.cpp"

$(IntermediateDirectory)/src_Storage.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Storage.cpp $(IntermediateDirectory)/src_Storage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/Components/src/Storage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Storage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Storage.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Storage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Storage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Storage.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/Components/src/Storage.cpp"

$(IntermediateDirectory)/src_Storage.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/Components/src/Storage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Storage.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/Components/src/Storage.cpp"

$(IntermediateDirectory)/src_2dtools.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/2dtools.cpp $(IntermediateDirectory)/src_2dtools.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/AssetTypes/src/2dtools.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_2dtools.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_2dtools.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/2dtools.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_2dtools.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_2dtools.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/AssetTypes/src/2dtools.cpp"

$(IntermediateDirectory)/src_2dtools.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/2dtools.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_2dtools.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/AssetTypes/src/2dtools.cpp"

$(IntermediateDirectory)/src_BasicTypes.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/BasicTypes.cpp $(IntermediateDirectory)/src_BasicTypes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/AssetTypes/src/BasicTypes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_BasicTypes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_BasicTypes.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/BasicTypes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_BasicTypes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_BasicTypes.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/AssetTypes/src/BasicTypes.cpp"

$(IntermediateDirectory)/src_BasicTypes.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/BasicTypes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_BasicTypes.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/AssetTypes/src/BasicTypes.cpp"

$(IntermediateDirectory)/src_Font.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Font.cpp $(IntermediateDirectory)/src_Font.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/AssetTypes/src/Font.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Font.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Font.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Font.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Font.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Font.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/AssetTypes/src/Font.cpp"

$(IntermediateDirectory)/src_Font.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Font.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Font.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/AssetTypes/src/Font.cpp"

$(IntermediateDirectory)/src_Graphic.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Graphic.cpp $(IntermediateDirectory)/src_Graphic.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/AssetTypes/src/Graphic.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Graphic.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Graphic.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Graphic.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Graphic.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Graphic.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/AssetTypes/src/Graphic.cpp"

$(IntermediateDirectory)/src_Graphic.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Graphic.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Graphic.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/AssetTypes/src/Graphic.cpp"

$(IntermediateDirectory)/src_Mesh.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Mesh.cpp $(IntermediateDirectory)/src_Mesh.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/AssetTypes/src/Mesh.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Mesh.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Mesh.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Mesh.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Mesh.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Mesh.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/AssetTypes/src/Mesh.cpp"

$(IntermediateDirectory)/src_Mesh.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Mesh.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Mesh.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/AssetTypes/src/Mesh.cpp"

$(IntermediateDirectory)/src_SceneNodes.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/SceneNodes.cpp $(IntermediateDirectory)/src_SceneNodes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/AssetTypes/src/SceneNodes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_SceneNodes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_SceneNodes.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/SceneNodes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_SceneNodes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_SceneNodes.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/AssetTypes/src/SceneNodes.cpp"

$(IntermediateDirectory)/src_SceneNodes.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/SceneNodes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_SceneNodes.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/AssetTypes/src/SceneNodes.cpp"

$(IntermediateDirectory)/src_Sprite.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Sprite.cpp $(IntermediateDirectory)/src_Sprite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/AssetTypes/src/Sprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Sprite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Sprite.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Sprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Sprite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Sprite.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/AssetTypes/src/Sprite.cpp"

$(IntermediateDirectory)/src_Sprite.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/Sprite.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Sprite.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/AssetTypes/src/Sprite.cpp"

$(IntermediateDirectory)/src_TileSet.cpp$(ObjectSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/TileSet.cpp $(IntermediateDirectory)/src_TileSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "S:/ToolBox/cheryl-engine/AssetFaculties/AssetTypes/src/TileSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_TileSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_TileSet.cpp$(DependSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/TileSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_TileSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_TileSet.cpp$(DependSuffix) -MM "../../../cheryl-engine/AssetFaculties/AssetTypes/src/TileSet.cpp"

$(IntermediateDirectory)/src_TileSet.cpp$(PreprocessSuffix): ../../../cheryl-engine/AssetFaculties/AssetTypes/src/TileSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_TileSet.cpp$(PreprocessSuffix) "../../../cheryl-engine/AssetFaculties/AssetTypes/src/TileSet.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


