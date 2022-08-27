.PHONY: run
include Loop.mk
scale:= 8e-8
steplen:= 5e-9
steps:= 1
Loop.mk: ./Loop.sh
	./Loop.sh $(steps) $(scale) $(steplen) > $@
a.out: mb.c
	gcc mb.c -lm -O2

run: Loop.mk LoopTargets
ifneq ($(steps),1)
	ffmpeg -framerate 20 -pattern_type glob -i '*.ppm' -c:v libx264 -pix_fmt yuv420p out.mp4
else
	ffmpeg -i *.ppm out.png
endif

.PHONY: clean
clean:
	rm -f a.out out.mp4 Loop.mk *.png
	rm -f *.ppm