#!/usr/bin/python3.6

#Caleb Scott
#CS 372 - Programming Assignment #1
#Last Modified 2/10/2019 8:20 PM EST

from socket import *
import sys

serverPort = int(sys.argv[1])
#Socket setup initially pulled from CS372 Lecture 15 Slide 9, modified to meet requirements
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)

#Chat loop function sends/receives messages from/to the client
#Pre: Socket connection required for chat loop
#Post: Returns message sent and sends message to client
def chatloop():
    retMessage = None
	#Determine if the user wants to exit the chat
    while retMessage != '\\quit':
		#Receive input from client
        sentence = connectionSocket.recv(1024)
		#Decode the string to remove the byte literal info shown
        sentenceString = sentence.decode('utf-8')
		#Split the string to filter out \quit info from the username
        splitSentence = sentenceString.split('> ', maxsplit = 1)
        if splitSentence[1] == '\\quit':
            print ("Client has ended the connection. Goodbye.")
            connectionSocket.close()
            return
        #Print the string then get input for response and send on the socket    
        print(sentenceString)
        retMessage = input('Server> ')
        retMesPrepend = "Server> " + retMessage
        retMesBytes = str.encode(retMesPrepend)
        connectionSocket.send(retMesBytes)

#Infinite while loop to keep the server running even if the client drops out unless a SIGINT is used 'ctrl+c' for example
while True:
    print('The server is ready to receive')
    connectionSocket, addr = serverSocket.accept()
    chatloop()