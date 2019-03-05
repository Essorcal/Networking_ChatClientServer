Caleb Scott
CS 372 - Programming Assignment #1

Instructions:
[Setting Up Connection]
1. Otherwise begin by unzipping the files to a single directory on the flip server.
2. use the command 'make'
	a. This will compile the chatclient.c file into chatclient with gcc chatclient.c -o chatclient
	b. 'make clean' can be used to deleted the compiled file
3. use the command 'chmod +x chatserve'
	a. This will allow the server application to be executable without the python file extension using ./
4. type in './chatserve [PORT NUMBER]' on one terminal window
5. on another terminal window type in './chatclient [flip#].engr.oregonstate.edu [PORT NUMBER]'
	a. This program will work on any combination of flip servers [1, 2 or 3] so long as the PORT NUMBER is the same and chatserve is started first

[Running the program]
1. On the Client terminal: Input a handle up to 10 characters
2. On the Client terminal: type a message to send to the terminal, send with enter
3. On the Server terminal: You will see the message from the client and can type your response, send with enter
4a. On the Client terminal: You will see the server side response and can continue responding or type '\quit'
4b. On the Server terminal: You can respond or type '\quit'. Quitting can be done from either the client or the server.
5. On the Server terminal: If you quit from either client the server will still await another connection which can be done by starting from step 5 of the [Setting up connection] portion of the instructions

[Notes]
If the chatserve component doesn't work in its present form because of the environment path for python3.6 'mv chatserve chatserve.py' can be used to give it its extension back and 'python chatserve.py [PORT NUMBER]' can be used to start the server


