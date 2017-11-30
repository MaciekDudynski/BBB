PROJ_NAME=$(p)
LINKER_COMMAND_FILE=common/AM335x_PRU.cmd
LIBS=--library=/usr/lib/ti/pru-software-support-package/lib/rpmsg_lib.lib
INCLUDE=--include_path=/usr/lib/ti/pru-software-support-package/include --include_path=/usr/lib/ti/pru-software-support-package/include/am335x --include_path=common
STACK_SIZE=0x100
HEAP_SIZE=0x100
GEN_DIR=$(PROJ_NAME)/gen

#Common compiler and linker flags (Defined in 'PRU Optimizing C/C++ Compiler User's Guide)
CFLAGS=-v3 -O2 --display_error_number --endian=little --hardware_mac=on --obj_directory=$(GEN_DIR) --pp_directory=$(GEN_DIR) -ppd -ppa
#Linker flags (Defined in 'PRU Optimizing C/C++ Compiler User's Guide)
LFLAGS=--reread_libs --warn_sections --stack_size=$(STACK_SIZE) --heap_size=$(HEAP_SIZE)

TARGET=$(GEN_DIR)/$(PROJ_NAME).out
MAP=$(GEN_DIR)/$(PROJ_NAME).map
SOURCES=$(wildcard $(PROJ_NAME)/*.c)
SOURCES_NAMES=$(patsubst $(PROJ_NAME)/%,%,$(SOURCES))
#Using .object instead of .obj in order to not conflict with the CCS build process
OBJECTS=$(patsubst %,$(GEN_DIR)/%,$(SOURCES_NAMES:.c=.object))

all: printStart $(TARGET) printEnd

printStart:
	@echo ''
	@echo '************************************************************'
	@echo 'Building project: $(PROJ_NAME)'

printEnd:
	@echo ''
	@echo 'Output files can be found in the "$(GEN_DIR)" directory'
	@echo ''
	@echo 'Finished building project: $(PROJ_NAME)'
	@echo '************************************************************'
	@echo ''

# Invokes the linker (-z flag) to make the .out file
$(TARGET): $(OBJECTS) $(LINKER_COMMAND_FILE)
	@echo ''
	@echo 'Building target: $@'
	@echo 'Invoking: PRU Linker'
	clpru $(CFLAGS) -z -i/usr/share/ti/cgt-pru/lib -i/usr/share/ti/cgt-pru/include $(LFLAGS) -o $(TARGET) $(OBJECTS) -m$(MAP) $(LINKER_COMMAND_FILE) --library=libc.a $(LIBS)
	@echo 'Finished building target: $@'

# Invokes the compiler on all c files in the directory to create the object files
$(GEN_DIR)/%.object: $(PROJ_NAME)/%.c
	@mkdir -p $(GEN_DIR)
	@echo ''
	@echo 'Building file: $<'
	@echo 'Invoking: PRU Compiler'
	clpru --include_path=/usr/share/ti/cgt-pru/include $(INCLUDE) $(CFLAGS) -fe $@ $<

.PHONY: all clean

# Remove the $(GEN_DIR) directory
clean:
	@echo ''
	@echo '************************************************************'
	@echo 'Cleaning project: $(PROJ_NAME)'
	@echo ''
	@echo 'Removing files in the "$(GEN_DIR)" directory'
	@rm -rf $(GEN_DIR)
	@echo ''
	@echo 'Finished cleaning project: $(PROJ_NAME)'
	@echo '************************************************************'
	@echo ''

# Includes the dependencies that the compiler creates (-ppd and -ppa flags)
-include $(OBJECTS:%.object=%.pp)

