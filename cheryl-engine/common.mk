.PHONY: all
all: build-tree $(TARGET)
#all: build-tree $(FILE_PCH) $(TARGET)

-include targets.mk

targets.mk: 
	@$(buildtree)
	@$(auto-target)

-include $(DEPENDENCIES)

.PHONY: clean
clean:
	@$(tidy2)

.PHONY: moreclean
moreclean:
	@$(tidy1)

.PHONY: mostclean
mostclean:
	@$(tidy0)

.PHONY: build-tree
build-tree:
	@$(buildtree)

.PHONY: tags
tags:
	@$(tagcollect)

$(FILE_PCH): $(FILE_PCH_SRC)
	@$(pch)
	@$(pch-depend)
