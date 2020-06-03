iCoffee.exe: principal.o menus.o funcionesAdmin.o funcionesMesero.o funcionesBaristaCocinero.o
	gcc -o iCoffee.exe principal.o menus.o funcionesAdmin.o funcionesMesero.o funcionesBaristaCocinero.o

principal.o: principal.c
	gcc -c principal.c

menus.o: menus.c 
	gcc -c menus.c

funcionesAdmin.o: funcionesAdmin.c 
	gcc -c funcionesAdmin.c

funcionesMesero.o: funcionesMesero.c
	gcc -c funcionesMesero.c

funcionesBaristaCocinero.o: funcionesBaristaCocinero.c
	gcc -c funcionesBaristaCocinero.c

clean:
	rm *.o