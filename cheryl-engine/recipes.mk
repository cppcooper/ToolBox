export OUTPATH := $(DIR_OBJ)/$(BUILD_PROFILE)-$(BUILD_PROJECT)

export FILE_PCH        = $(DIR_OBJ)/$(BUILD_PROFILE)-$(BUILD_PROJECT)/stdinc.h.pch
export FILE_PCH_SRC   := head/stdinc.h

export STD_ARG_ERRS   := -Wno-missing-declarations

export STD_ARG_MAKE    = --no-print-directory BUILD_PROJECT=$(BUILD_PROJECT)
export STD_ARG_AR     := rcs
export STD_ARG_ALL     = -Wall -fstack-protector-all -g -gdwarf-4 $(shell for i in $(DIR_HEAD_GLBL); do echo -I$(CWD_ROOT)/$$i; done) $(STD_ARG_ERRS)
export STD_ARG_CLANG  := -fcolor-diagnostics -std=c++1z
export STD_ARG_GCC    := -std=c++11
export STD_ARG_CC      =
#export STD_ARG_CXX     = -fno-cxx-exceptions -fno-exceptions -fno-rtti -include-pch $(FILE_PCH)
export STD_ARG_CXX     = -fno-cxx-exceptions -fno-exceptions -fno-rtti
export STD_ARG_PCH    := -fno-cxx-exceptions -fno-exceptions -fno-rtti 
export STD_ARG_LD     := -fno-cxx-exceptions -fno-exceptions -fno-rtti 
export STD_ARG_TAG     =

export AR              = ar                                      $(STD_ARG_AR)
export CC              = clang   $(STD_ARG_CLANG) $(STD_ARG_ALL) $(STD_ARG_CC)
export CXX             = clang++ $(STD_ARG_CLANG) $(STD_ARG_ALL) $(STD_ARG_CXX)
export CXX_DEP         = g++     $(STD_ARG_GCC)   $(STD_ARG_ALL)                -MM
export PCH             = clang++ $(STD_ARG_CLANG) $(STD_ARG_ALL) $(STD_ARG_PCH)
export LD              = clang++ $(STD_ARG_CLANG) $(STD_ARG_ALL) $(STD_ARG_LD)
export TAG             = ctags   $(STD_ARG_TAG)  

# recursive calls

define descend =
	$(eval export BUILD_PROJECT := $(subst recurse-,,$@))
	@echo "* Project $(BUILD_PROJECT)"
	$(MAKE) $(STD_ARG_MAKE) -C $(BUILD_PROJECT) -f makefile-project $(MAKECMDGOALS)
	$(eval undefine BUILD_PROJECT)
endef

# build

define cxx =
	@echo "   * C++        ---> $@"
	$(CXX) -I$(CWD_ROOT)/$(BUILD_PROJECT) -I$(DIR_OBJ)/$(BUILD_PROFILE)-$(BUILD_PROJECT) -c $< -o $@
endef

define cxx-depend =
@echo "   * C++ Depend ---> $(@:.o=.d)"
	$(eval OUT=$(@:.o=))
	$(CXX_DEP) -I$(CWD_ROOT)/$(BUILD_PROJECT) -I$(DIR_OBJ)/$(BUILD_PROFILE)-$(BUILD_PROJECT) $< > $(OUT).d
	mv -f $(OUT).d $(OUT).d.tmp
	sed -e 's|.*:|$*.o:|' \
		< $(OUT).d.tmp \
		> $(OUT).d
	sed -e 's/.*://' -e 's/\\$$//' \
		< $(OUT).d.tmp \
		| fmt -1 \
		| sed -e 's/^ *//' -e 's/$$/:/' \
		>> $(OUT).d
	cat $(OUT).d.tmp \
		| sed -r "/[\.A-Za-z0-9\/[:space:]-]+:[\.A-Za-z0-9\/[:space:]\/-]+\\\?/d" \
		| sed -r "s/[[:space:]]*(.+?)[[:space:]\\\]+/\1/g" \
		> $(OUT).tagsrc.d
	$(eval unexport OUT)
endef

define ld =
	@echo "   * LD         ---> $@"
	$(LD) $^ -o $@
endef

define pch =
	@echo "   * PCH        ---> $@"
	$(PCH) -I$(CWD_ROOT)/$(BUILD_PROJECT) -x c++-header $< -o $@
endef

define pch-depend =
	@echo "   * PCH Depend ---> $(@:.pch=.d)"
	$(eval OUT=$(@:.pch=))
	$(CXX_DEP) -I$(CWD_ROOT)/$(BUILD_PROJECT) -I$(DIR_OBJ)/$(BUILD_PROFILE)-$(BUILD_PROJECT) $< > $(OUT).d
	mv -f $(OUT).d $(OUT).d.tmp
	sed -e 's|.*:|$(OUT).pch:|' < $(OUT).d.tmp > $(OUT).d
	sed -e 's/.*://' -e 's/\\$$//' < $(OUT).d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(OUT).d
	cat $(OUT).d.tmp \
		| sed -r "/[\.A-Za-z0-9\/[:space:]-]+:[\.A-Za-z0-9\/[:space:]\/-]+\\\/d" \
		| sed -r "s/[[:space:]]*(.+?)[[:space:]\\\]+/\1/g" \
		> $(OUT).tagsrc.d

	$(eval unexport OUT)
endef

define lib =
	@echo "   * Lib        ---> $@"
	$(AR) $@ $^
endef

# clean 

define tidy0 =
	@echo "   * Cleaning $(BUILD_PROFILE)-$(BUILD_PROJECT) ..."
	-find $(DIR_OBJ)/$(BUILD_PROFILE)-$(BUILD_PROJECT) \( $(shell for i in $(TYPES_TARGET) $(TYPES_DEP) $(TYPES_LIB) $(TYPES_ACCEL) $(TYPES_OBJ) $(TYPES_GARBAGE); do echo $$([ x"$$n" == x"y" ] && echo "-or") "-iname \"*$$i\""; n="y"; done) \) -and -not -type d -exec echo "   * Delete" \{\} \; -delete 2>/dev/null
	-[[ x"$(BUILD_PROJECT)" != x"*" ]] \
		&& ( rm targets.mk \
		 	; rm os.mk \
			; rm platform.mk \
			)
endef

define tidy1 =
	@echo "   * Cleaning $(BUILD_PROFILE)-$(BUILD_PROJECT) ..."
   -find $(DIR_OBJ)/$(BUILD_PROFILE)-$(BUILD_PROJECT) \( $(shell for i in $(TYPES_TARGET)              $(TYPES_LIB)                $(TYPES_OBJ) $(TYPES_GARBAGE); do echo $$([ x"$$n" == x"y" ] && echo "-or") "-iname \"*$$i\""; n="y"; done) \) -and -not -type d -exec echo "   * Delete" \{\} \; -delete 2>/dev/null
endef

define tidy2 =
	@echo "   * Cleaning $(BUILD_PROFILE)-$(BUILD_PROJECT) ..."
	-find $(DIR_OBJ)/$(BUILD_PROFILE)-$(BUILD_PROJECT) \( $(shell for i in $(TYPES_TARGET)                                          $(TYPES_OBJ) $(TYPES_GARBAGE); do echo $$([ x"$$n" == x"y" ] && echo "-or") "-iname \"*$$i\""; n="y"; done) \) -and -not -type d -exec echo "   * Delete" \{\} \; -delete 2>/dev/null
endef

# create the build tree

define buildtree =
	#@echo "   * Preparing $(BUILD_PROFILE)-$(BUILD_PROJECT) ..."
	#-@rm -r $$(echo $(CWD_ROOT)/$(BUILD_PROJECT) | sed s/$(BUILD_PROJECT)/Build\\/$(BUILD_PROFILE)-$(BUILD_PROJECT)/g)/* &>/dev/null
	find $(CWD_ROOT)/$(BUILD_PROJECT) -type d \
	   -exec sh -c "echo {} | sed s/$(BUILD_PROJECT)/Build\\\/$(BUILD_PROFILE)-$(BUILD_PROJECT)/g | xargs mkdir -p" \; #\
	   #-exec echo -n "      * Directory: " \; \
	   #-exec sh -c "echo {} | sed s/$(BUILD_PROJECT)/Build\\\/$(BUILD_PROFILE)-$(BUILD_PROJECT)/g | sed s/$(subst /,\\\/,$(CWD_ROOT))\\\///g" \;
endef

# tag compilation

define tagcollect =
	@echo "   * Collecting tags $(BUILD_PROFILE)-$(BUILD_PROJECT) ..."
	-find $(OUTPATH) -iname "*.tagsrc.d" -exec sh -c "cat {} >> $(OUTPATH)/tagsrc.d" \; &>/dev/null
	mv $(OUTPATH)/tagsrc.d $(OUTPATH)/tagsrc.d.tmp
	cat $(OUTPATH)/tagsrc.d.tmp | sort | uniq > $(OUTPATH)/tagsrc.d
endef

define tagcollecttop =
	@echo "* Generating tags ..."
	find $(DIR_OBJ) -iname "tagsrc.d" -or -iname "*.tagsrc.d" -exec cat \{\} \; > $(DIR_OBJ)/tagsrc.d.tmp
	cat $(DIR_OBJ)/tagsrc.d.tmp | grep -v _libraries | sort | uniq > $(DIR_OBJ)/tagsrc.d
	cat $(DIR_OBJ)/tagsrc.d.tmp | grep    _libraries | sort | uniq > $(DIR_OBJ)/tagsrc-lib.d
   cat $(DIR_OBJ)/tagsrc.d.tmp                      | sort | uniq > $(DIR_OBJ)/tagsrc-unified.d
	rm $(DIR_OBJ)/tagsrc.d.tmp
endef

define tag =
	$(TAG) -f $(DIR_OBJ)/tags         -L $(DIR_OBJ)/tagsrc.d
	$(TAG) -f $(DIR_OBJ)/tags-lib     -L $(DIR_OBJ)/tagsrc-lib.d
   $(TAG) -f $(DIR_OBJ)/tags-unified -L $(DIR_OBJ)/tagsrc-unified.d
endef

# automagic generation of our project's actual compilation records. please note
# it only currently handles C++ files! 
# Side Effects: tag lists are generated along the way of top level files

define auto-target =
	-find platform/$(BUILD_PLATFORM) -iname "*.cpp" \
		|  sed    "s/\.\//.\/platform\/$(BUILD_PLATFORM)\//g" \
		|  tee    target.mk.tmp \
		|  sed -r "s/^(.+)$$/\$$(OUTPATH)\/\1.o: \1\n\t@\$$(cxx)\n\t@\$$(cxx-depend)/g" \
		>  platform.mk 2>/dev/null \
		&& cat    target.mk.tmp \
		|  tr     '\n' ' ' \
		|  sed -r "s/^(.+)$$/SOURCES_PLATFORM := \1/g" \
		>> platform.mk \
		&& cat    target.mk.tmp >> tagsrc.d.tmp \
		&& rm     target.mk.tmp

	-find os/$(BUILD_OS) -iname "*.cpp" \
		|  sed    "s/\.\//.\/os\/$(BUILD_OS)\//g" \
		|  tee    target.mk.tmp \
		|  sed -r "s/^(.+)$$/\$$(OUTPATH)\/\1.o: \1\n\t@\$$(cxx)\n\t@\$$(cxx-depend)/g" \
		>  os.mk 2>/dev/null \
		&& cat    target.mk.tmp \
		|  tr     '\n' ' ' \
		|  sed -r "s/^(.+)$$/SOURCES_OS := \1/g" \
		>> os.mk \
		&& cat    target.mk.tmp >> tagsrc.d.tmp \
		&& rm     target.mk.tmp

	echo -e "-include platform.mk\n-include os.mk" >  targets.mk

	find . \( -not -path "./head/*"     -and \
	          -not -path "./platform/*" -and \
	          -not -path "./os/*" \
	       \) -iname "*.cpp" \
		|  tee    target.mk.tmp \
		|  sed -r "s/^\.\/(.+)$$/\$$(OUTPATH)\/\1.o: \1\n\t\$$(cxx)\n\t@\$$(cxx-depend)/g" \
		2> /dev/null \
		>> targets.mk

	cat target.mk.tmp \
		|  sed -r "s/^\.\/(.+)$$/\1/g" \
		|  tr     '\n' ' ' \
		|  sed -r "s/^(.+)$$/SOURCES_MAIN := \1/g" \
		>> targets.mk 	

	cat   target.mk.tmp >> tagsrc.d.tmp
	echo -e $$(for x in $$(cat tagsrc.d.tmp); do realpath $$x; echo \\n; done) \
		| sed -r "s/^[[:space:]]*(.*)[[:space:]]*$$/\1/g" \
		| sort \
		| uniq \
		> $(OUTPATH)/tagsrc.d

	rm    tagsrc.d.tmp
	rm    target.mk.tmp
endef

#$(OUTPATH)/%.cpp.o: %.cpp
#	@$(cxx)


