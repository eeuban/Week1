#Compilers
CC          := g++ -std=c++17
DGEN        := doxygen

#The Target Binary Program
TARGET      := test

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := .
INCDIR      := .
BUILDDIR    := ./build
TARGETDIR   := ./bin
SRCEXT      := cc

#Flags, Libraries and Includes
CFLAGS      := -ggdb
LIB         := -lgtest -lpthread 
INC         := -I$(INCDIR)
INCDEP      := -I$(INCDIR)

#Files
DGENCONFIG  := docs.config
HEADERS     := $(wildcard *.h)
SOURCES     := $(wildcard *.cc)
OBJECTS     := $(patsubst %.cc, $(BUILDDIR)/%.o, $(notdir $(SOURCES)))

#Specific files targets
LR_TARGET		:= regression
LR_OBJECTS		:= $(BUILDDIR)/$(LR_TARGET).o
KMEANS_TARGET	:= kmeans
KMEANS_OBJECTS	:= $(BUILDDIR)/$(KMEANS_TARGET).o

#Defauilt Make
all: directories $(TARGETDIR)/$(TARGET) 

#Remake
remake: cleaner all

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

# Make the documentation
$(DGENCONFIG):
	$(DGEN) -g $(DGENCONFIG)

docs: $(SOURCES) $(HEADERS) $(DGENCONFIG)
	$(DGEN) $(DGENCONFIG)

#Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)/*.o

#Full Clean, Objects and Binaries
spotless: clean
	@$(RM) -rf $(TARGETDIR)/$(TARGET) $(DGENCONFIG) *.db
	@$(RM) -rf build bin html latex

# -------------- Make regression --------------
$(TARGETDIR)/$(LR_TARGET): $(LR_OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGETDIR)/$(LR_TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/$(LR_OBJECTS): $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# -------------- Make Kmeans ------------------
$(TARGETDIR)/$(KMEANS_TARGET): $(KMEANS_OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGETDIR)/$(KMEANS_TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/$(KMEANS_OBJECTS): $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# -------------- Make --------------------------
#Link
$(TARGETDIR)/$(TARGET): $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: directories remake clean cleaner apidocs $(BUILDDIR) $(TARGETDIR)