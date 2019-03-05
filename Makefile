chatclient: chatclient.c
	gcc -o chatclient chatclient.c
clean:
	rm -f *.o chatclient
