#!/usr/bin/env python

"""report's job is to report on the perfect numbers found,
 the number tested, and the processes currently computing.
  If invoked with the "-k" switch, it also is used to inform
   the manage process to shut down computation. report will 
   query the server for information, provide that to the caller,
    then shut down."""



import socket 
import sys
import os
import getopt
import signal
import re

host = 'localhost'  #Address of the server
port = 24400        #My port I choose
size = 1024         #Maximum Size of socket to recive or to send
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.connect((host,port)) 
#Handles signals
def handler(signum, frame):
    terminator()
    sys.exit()
    
signal.signal(signal.SIGHUP, handler)
signal.signal(signal.SIGINT, handler)
signal.signal(signal.SIGQUIT, handler)

#Sends handshake to server
def meet_friends():
    s.send('<message type=\"handshake\" from=\"report\"></message>') 
    data = s.recv(size)
    #print 'Received:', data
    if data != '<message type=\"handshake\" from=\"manage\"></message>':
        print 'Mansage didnt like report, they are not freinds... exiting.'
        sys.exit(EXIT_FAILURE)

#prints usage for Report.py
def usage():
    print sys.argv[0], '[-k]\n             -k - Send kill signal to all of the processes.'

#gets reprot from server   
def get_report():
    s.send('<message type=\"report\" from=\"report\"></message>')       #askes for report
    data = s.recv(size)
    #print 'Received:', data
    message = re.split('\"(.*?)\"', data)   #Splits xml using regular expressions
    sender = message[3]
    request = message[1]
    
    perfects = message[5]
    tested = message[7]
    num_pro = message[9]
    
    print perfects, 'Perfect numbers out of ', tested, ' Tested.\nThere are ', num_pro, 'Processes running, excluding myself.\n' 

#Kills every running process  
def terminator():
    s.send('<message type=\"terminate\" from=\"report\"></message>')
    data = s.recv(size)
    print 'Received:', data

#Recieves input from user
def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hk", ["help"])
    except getopt.GetoptError as err:
        # print help information and exit:
        print str(err) # will print something like "option -a not recognized"
        usage()     #Prints usage for report
        sys.exit(2)
    kill = False
    for o, a in opts:
        if o == "-k":   #If the k flag is defined get report then kill all the processes.
            kill = True
        elif o in ("-h", "--help"):     #Prints usage
            usage()
            sys.exit()
        else:
            assert False, "unhandled option"

    meet_friends()  #connect to server and send handshake
    get_report()    #gets the report from server.
    
    if(kill == True):   #Activates das Terminator!
        terminator()    #Kills all processes.
   
    
    s.close() 
    #print 'Received:', data
    

if __name__ == "__main__":
    main()