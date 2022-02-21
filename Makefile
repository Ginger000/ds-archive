# Executable names:
EXE = wiki
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o

# Generated files
CLEAN_RM = wiki test *.o *.d tests/*.o tests/*.d \
			catch/*.o catch/*.d wiki_graph/*.o wiki_graph/*.d util/*.d util/*.o

CPP_FILES += $(wildcard wiki_graph/*.cpp)
CPP_FILES += $(wildcard util/*.cpp)
OBJS += $(CPP_FILES:.cpp=.o)

# Use the cs225 makefile template:
include make/cs225.mk


BFS_OBJS += $(filter-out $(EXE_OBJ), $(OBJS))
BFS_CPP += main_bfs.cpp
BFS_OBJS += $(BFS_CPP:.cpp=.o)

BFS: output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(BFS_OBJS))
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@

DFS_OBJS += $(filter-out $(EXE_OBJ), $(OBJS))
DFS_CPP += main_dfs.cpp
DFS_OBJS += $(DFS_CPP:.cpp=.o)

DFS: output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(DFS_OBJS))
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@

DIJKSTRA_OBJS += $(filter-out $(EXE_OBJ), $(OBJS))
DIJKSTRA_CPP += main_dijkstra.cpp
DIJKSTRA_OBJS += $(DIJKSTRA_CPP:.cpp=.o)

Dijkstra: output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(DIJKSTRA_OBJS))
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@

PAGE_RANK_OBJS += $(filter-out $(EXE_OBJ), $(OBJS))
PAGE_RANK_CPP += main_page_rank.cpp
PAGE_RANK_OBJS += $(PAGE_RANK_CPP:.cpp=.o)

PageRank: output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(PAGE_RANK_OBJS))
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@

STRONGLY_CONNECTED_OBJS += $(filter-out $(EXE_OBJ), $(OBJS))
STRONGLY_CONNECTED_CPP += main_strongly_connected.cpp
STRONGLY_CONNECTED_OBJS += $(STRONGLY_CONNECTED_CPP:.cpp=.o)

StronglyConnected: output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(STRONGLY_CONNECTED_OBJS))
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@