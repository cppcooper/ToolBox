-include platform.mk
-include os.mk
$(OUTPATH)/src/IOFileChunks/iof_positions.cpp.o: src/IOFileChunks/iof_positions.cpp
	@$(cxx)
	@$(cxx-depend)
$(OUTPATH)/src/IOFileChunks/iof_chunk.cpp.o: src/IOFileChunks/iof_chunk.cpp
	@$(cxx)
	@$(cxx-depend)
$(OUTPATH)/src/tools_logger.cpp.o: src/tools_logger.cpp
	@$(cxx)
	@$(cxx-depend)
$(OUTPATH)/src/tools_utilities.cpp.o: src/tools_utilities.cpp
	@$(cxx)
	@$(cxx-depend)
$(OUTPATH)/src/tools_stacktracer.cpp.o: src/tools_stacktracer.cpp
	@$(cxx)
	@$(cxx-depend)
$(OUTPATH)/src/tools_winfs.cpp.o: src/tools_winfs.cpp
	@$(cxx)
	@$(cxx-depend)
$(OUTPATH)/src/tools_bench.cpp.o: src/tools_bench.cpp
	@$(cxx)
	@$(cxx-depend)
SOURCES_MAIN := src/IOFileChunks/iof_positions.cpp src/IOFileChunks/iof_chunk.cpp src/tools_logger.cpp src/tools_utilities.cpp src/tools_stacktracer.cpp src/tools_winfs.cpp src/tools_bench.cpp 