all:
	gcc PuddleJump.c -o PuddleJump.so -fPIC -shared -ldl -D_GNU_SOURCE
