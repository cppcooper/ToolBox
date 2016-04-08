export CWD_ROOT       := $(shell pwd)

export BUILD_TYPE     := Debug
export BUILD_PLATFORM := x64
export BUILD_OS       := lin
export BUILD_PROFILE  := $(BUILD_TYPE)-$(BUILD_PLATFORM)-$(BUILD_OS)

export BUILD_PROJECTS := util AssetFaculties GameFramework GLEngine test

export DIR_OBJ        := $(CWD_ROOT)/Build
export DIR_HEAD_GLBL  := $(CWD_ROOT) $(CWD_ROOT)/util

export TYPES_OBJ      := .o .obj
export TYPES_DEP      := .dep .d
export TYPES_LIB      := .a .lib
export TYPES_ACCEL    := .pch .tag
export TYPES_TARGET   := .elf
export TYPES_GARBAGE  := .tlog .log .cache .sbr .pdb .tmp

include recipes.mk

# recursive rules

.PHONY: all
all: $(foreach x,$(BUILD_PROJECTS),recurse-$x) tags $(DIR_OBJ)/tags $(DIR_OBJ)/tags-lib $(DIR_OBJ)/tags-unified

$(DIR_OBJ)/tags $(DIR_OBJ)/tags-lib $(DIR_OBJ)/tags-unified: $(DIR_OBJ)/tagsrc.d $(DIR_OBJ)/tagsrc-lib.d $(DIR_OBJ)/tagsrc-unified.d
	@$(tag)

$(DIR_OBJ)/tagsrc.d $(DIR_OBJ)/tagsrc-lib.d $(DIR_OBJ)/tagsrc-unified.d: $(shell find $(DIR_OBJ)/$(BUILD_PROFILE)-* -iname "*.tagsrc.d" -or -iname "tagsrc.d")
	@$(tagcollecttop)

.PHONY: tags
tags: $(foreach x,$(BUILD_PROJECTS),recurse-$x) $(DIR_OBJ)/tags $(DIR_OBJ)/tags-lib $(DIR_OBJ)/tags-unified

.PHONY: clean
clean: $(foreach x,$(BUILD_PROJECTS),recurse-$x) build-tree

.PHONY: moreclean
moreclean: $(foreach x,$(BUILD_PROJECTS),recurse-$x) build-tree

.PHONY: mostclean
mostclean: $(foreach x,$(BUILD_PROJECTS),recurse-$x) build-tree

.PHONY: build-tree
build-tree: $(foreach x,$(BUILD_PROJECTS),recurse-$x)

# global

.PHONY: clean-all
clean-all: 
	$(eval BUILD_PROJECT := *)	
	@$(tidy0)
	@-for x in $(BUILD_PROJECTS); do rm $$x/{targets.mk,platform.mk,os.mk}; done
	$(eval undefine BUILD_PROJECT)

# recurse specific projects

.PHONY: recurse-util
recurse-util:
	@$(descend)

.PHONY: recurse-AssetFaculties
recurse-AssetFaculties:
	@$(descend)

.PHONY: recurse-GameFramework
recurse-GameFramework:
	@$(descend)

.PHONY: recurse-GLEngine
recurse-GLEngine:
	@$(descend)

.PHONY: recurse-test
recurse-test:
	@$(descend)
