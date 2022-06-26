include_dir = ../inc
src_dir = ../src

ifeq ($(OS),Windows_NT)
	TARGET = difftool.exe
	REMOVE = del
else
	TARGET = difftool
	REMOVE = rm
endif

CFLAGS = -c -MD $(addprefix -I,$(include_dir)) -g

src_search_wildcards = $(addsuffix /*.c,$(src_dir))

all: $(TARGET)

$(TARGET): $(notdir $(patsubst %.c,%.o,$(wildcard $(src_search_wildcards))))
	$(CC) $^ -o $@

vpath %.h $(include_dir)
vpath %.c $(src_dir)

%.o: %.c
	$(CC) $(CFLAGS) $<

include $(wildcard *.d)


.PHONY: clean

clean:
	$(REMOVE) $(TARGET) *.d *.o
