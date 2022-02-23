all : snake


snake : snake.c linkedList.c collisionChecks.c
	gcc -o $@ $^ -lX11 -lm -lpthread -lXext -lGL -g -DCNFGRASTERIZER -Wall

clean :
	rm -rf *.o *~ rawdraw.exe rawdraw ontop rawdraw_mac rawdraw_mac_soft rawdraw_mac_cg rawdraw_mac_ogl ogltest ogltest.exe rawdraw_egl fontsize fontsize_ogl fontsize.exe

