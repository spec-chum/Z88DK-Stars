TARGET =	stars.tap

OPTLEVEL =	-SO3
CLIB =		-clib=sdcc_iy
STARTUP =	-startup=31
ALLOCS =	--max-allocs-per-node200000

SOURCES =	stars.c

all:		$(TARGET)

clean:
			del	$(TARGET) \
			del	*.o \
			del	*.bin \
			del	*.def

$(TARGET):$(SOURCES)
			zcc +zx -vn $(OPTLEVEL) $(CLIB) $(STARTUP) $(ALLOCS) $** -o %|fF.o -create-app
