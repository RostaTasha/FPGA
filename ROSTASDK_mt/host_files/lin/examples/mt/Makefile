CC=g++
CFLAGS = -g -Wall  -O3 -fopenmp -Wno-uninitialized
#CFLAGS = -g -Wall -Wimplicit-function-declaration -O3
ifdef PLX_SDK_DIR 
CFLAGS += -DUSE_PLX
endif

RINC = $(ROSTA_SDK_DIR)/lin/ApiLib/include
RLIB = $(ROSTA_SDK_DIR)/lin/ApiLib

PINC = $(PLX_SDK_DIR)/Include
PLIB = $(PLX_SDK_DIR)/PlxApi/Library

FLIB = -L$(RLIB)  -lRostaPCIeAPI -lRC47 
ifdef PLX_SDK_DIR 
FLIB += -L$(PLIB)  -l:PlxApi.a -lm -ldl -lrt
endif


ILIB = -I$(RINC)
ifdef PLX_SDK_DIR 
ILIB += -I$(PINC)
endif


TEST1=rc47_mt_11
TEST2=rc47_mt_12


all: $(TEST1) $(TEST2)

clean:
	-rm -f $(TEST1)
	-rm -f $(TEST2)
	
$(TEST1): $(TEST1).cpp mt_cpu.cpp
	$(CC) $(ILIB) $(CFLAGS) -o $@ $(TEST1).cpp mt_cpu.cpp $(FLIB)	 

	
$(TEST2): $(TEST2).cpp mt_cpu.cpp
	$(CC) $(ILIB) $(CFLAGS) -o $@ $(TEST2).cpp mt_cpu.cpp $(FLIB)	 


