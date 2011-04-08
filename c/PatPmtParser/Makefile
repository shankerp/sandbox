SOURCES = tsheaderparse.c \
		  UnitTest/main.c

INCLUDES = -I include/

bin_PROGRAMS = psiParser.out

# -DMDSR_SAL_FILE_DUMP_ENABLE
LDFLAGS += -O3 -g

default:
	@echo "USAGE:"
	@echo "======"
	@echo "   Make [clean | build ]"
	@echo "   Where,"
	@echo "      Make clean   : Cleans the executables and shared objectes"
	@echo "      Make build   : Builds Test Exe - psiParser.out"

build:
	gcc $(SOURCES) $(LDFLAGS) $(INCLUDES) -o $(bin_PROGRAMS)

clean:
	rm -f *.so
	rm -f *.out

