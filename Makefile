OUTFILE = helloWorld
OUTDIR = $(HOME)/cmpt433/public/myApps
CROSS_COMPILE = arm-linux-gnueabihf-
CC_C = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror

help:
	@echo "Build Hello World program for BeagleBone"
	@echo "Targets include all, app, and clean"
all: app done
app:
	$(CC_C) $(CFLAGS) helloWorld.c LED.c joystick.c -o $(OUTDIR)/$(OUTFILE)
#	ls -l $(OUTDIR)/$(OUTFILE)

done:
	@echo "Finished building application."

clean:
	rm $(OUTDIR)/$(OUTFILE)
