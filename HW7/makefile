.PHONY: clean

CC:= gcc

all: single_lane_bridge

single_lane_bridge: single_lane_bridge.c
	$(CC) $< -o $@ -lpthread

clean:
	rm -f *.o
