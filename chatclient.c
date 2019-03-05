
/************************************
Caleb Scott
CS 372 - Programming Assignment #1
Last Modified 2/10/2019 8:20 PM EST
Client side C program to demonstrate Socket programming through client/server Instant Messaging
************************************/
#include <stdio.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <assert.h>

//Function Declarations
 void prepend(char* s, const char* t);
 int connection(char *hostName, int PORT);
 void getHandle(char handleBuffer[12]);

 struct addrinfo hints, *infoptr;
 
 //Input arguments for hostname and port as command line args
int main(int argc, char *argv[]) 
{ 
	//setting up variables for connection
	char *hostName = argv[1];
	int PORT = atoi(argv[2]);
	int sock = connection(hostName, PORT);
	if(sock == -1)
	{
		return -1;
	}

	char hello[1024];
	char handleBuffer[12];
	//calling the handle buffer function to get the input from the user and format it with the right caret to look like a message
	getHandle(handleBuffer);

	while (strcmp(hello, "\\quit") != 0)
	{
		printf("%s", handleBuffer);
		//Scan f expression derived from the following https://stackoverflow.com/questions/30065675/what-does-scanf-nc-mean
		scanf("%[^\n]%*c", hello);
		
		char buffer[1024] = {0}; 
		
		char* s = malloc(1024);
		strcpy(s, hello);
		//Call prepend to add the user handle to the message
		prepend(s, handleBuffer);

		//Send the message and handle to the server
		send(sock , s , strlen(s) , 0 ); 

		//allow the user to quit
		if (strcmp(hello, "\\quit") == 0)
		{
			break;
		}
		//read the response from the server
		read( sock , buffer, 1024); 
		if (strcmp(buffer, "Server> \\quit") == 0)
		{
			break;
		}

		printf("%s\n",buffer ); 
	}
	printf("quit command received, closing connection\n");
	return 0; 
} 

//Gets user input for handle and formats it properly
//Pre: Requires handle buffer
//Post: Sends appended full handle to the rest of the program
void getHandle(char handleBuffer[12])
{
	char handle[10];
	//User Inputs their IM handle
	printf("Input up to 10 character handle: ");
	scanf("%[^\n]%*c", handle);
	
	//Appends the caret right and space after the handle to make the message easier to read 
	strcpy(handleBuffer, handle);
	strcat(handleBuffer, "> ");
}

/* prepend code sourced from https://stackoverflow.com/questions/2328182/prepending-to-a-string */
/* Prepends t into s. Assumes s has enough space allocated for the combined string.*/
//Pre: Requires message and handlebuffer
//Post: Sends combined string with prepended handle buffer on the message string
void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;

	memmove(s + len, s, strlen(s));

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}

//Connection function initally found at https://www.geeksforgeeks.org/socket-programming-cc/ and then modified for this assignment
//Additional functionality sourced from https://github.com/angrave/SystemProgramming/wiki/Networking,-Part-2:-Using-getaddrinfo
//Pre: Requires hostname and port
//Post: Sets up socket connection with server
int connection(char *hostName, int PORT)
{
	//For DNS lookup to convert flipX.engr.oregonstate.edu to an IP address
	hints.ai_family = AF_INET;
	int result = getaddrinfo(hostName, NULL, &hints, &infoptr);
	struct addrinfo *p;
    char host[256];
	p = infoptr;
    getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof (host), NULL, 0, NI_NUMERICHOST);
    
	
	//to open the socket
	int sock = 0;
	struct sockaddr_in serv_addr; 

	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	if(inet_pton(AF_INET, host, &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	freeaddrinfo(infoptr);
	return sock;
}

