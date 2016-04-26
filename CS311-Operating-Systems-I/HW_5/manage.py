#!/usr/bin/env python
"""
*********************************************************************
 *  ** Program Filename: manage.py
 *   ** Author: Sam Quinn
 *    ** Date: 12/8/2013
 *     ** Description: manage's job is to maintain the results
 *        of compute. It also keeps track of the active compute
 *        processes, so that it can signal them to terminate, 
 *        including the host name and performance characteristics.
 *******************************************************************
"""

import re
import socket
import os
from math import sqrt
import select
import sys
import signal


host = ''       # sets the server to use the address of the current machine.
port = 24400    #My port
backlog = 5     #Number of clients can wait
size = 1024     #Max size of socket read and write

global old_limit    #Stores the last used limit
old_limit = 0       
perfect = []        #Stores the perfect numbers

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # Prevent socket from being left in TIME_WAIT state
server.bind((host, port))
server.listen(backlog)
connected = [server]  # Number of connected sockets
commain = []    #Stores the address of the main compute function.

#Send handshake
def introduce(s):
  s.send('<message type=\"handshake\" from=\"manage\"></message>')

#Kills all processes
def terminator():
    if(commain != ''):
        print "Activating THE TERMINATOR!"
        if(commain):
            (main_read, main_write, main_exc) = select.select([], commain, [])
            main_write[0].send("<message type=\"die\" from=\"manage\"></message>")
    sys.exit()
    
#Signal handler
# Refenced http://docs.python.org/2/library/signal.html
def handler(signum, frame):
    terminator()
    sys.exit()
    
signal.signal(signal.SIGHUP, handler)
signal.signal(signal.SIGINT, handler)
signal.signal(signal.SIGQUIT, handler)

#Sends the compute process a new limit to work on
def new_limit(mods):
    #print 'Getting new limit'
    l = 0
    #print 'Newlimit old limit', old_limit
    limit = old_limit + 1
    while(l < (.25*mods)):
        l += sqrt(limit)
        limit += 1
        #print 'L = ', l, 'LIMIT = ', limit
    return limit

#Sends and receives handshakes from all of the clients
def get_friends(s):
  raw = s.recv(size)
  raw = raw.strip()
  #print 'RAW = ', raw

  message = re.split('\"(.*?)\"', raw)
  sender = message[3]
  request = message[1]
  #print 'FRIENDS SENDER = ', sender, ' Request = ', request, ' Message = ', message
  host, port = s.getpeername()

  if request == "handshake":
    if sender == "report":
      print "Report enterd the game", host, ":", port
      introduce(s)
      connected.append(s)
    if sender == "compute":
      print "Compute enterd the game", host, ":", port
      introduce(s)
      connected.append(s)
      # s.send('Hello compute!')
    if sender == "commain":
        print "Commain enterd the game", host, ":", port
        introduce(s)
        commain.append(s)

#Infinite loop to get data from clients
while 1:
  readable, writeable, error = select.select(connected, [], [])
  for sock in readable:
    if(sock == server):  # New client connected
      new_client, address = server.accept()     #accepts the new client
      # send_handshake(newsock)
      get_friends(new_client)   #sends handshake and adds it to the connected list
    else:   #Not a New client
      data = sock.recv(size)
      data = data.strip()
      data = data.split('\n')
      for xml_message in data:  
          if xml_message != '': 
            #print 'Recived: ', xml_message
            #message = xml_message.split('\"')
            message = re.split('\"(.*?)\"', xml_message)    #Splits the XML using regular expressions
            sender = message[3]
            request = message[1]
            #value = message[5]
            #print 'SENDER = ', sender, ' Request = ', request, ' Message = ', message
            
            if(sender == "compute"):
                if(request == "new_limit"): #requesting a new limit
                    
                    mods_15 = long(message[5])
                    old_limit = int(message[7])
                    limit = new_limit(mods_15)
                    sock.send(str(limit))
                    #sock.send('hey i got your thing.')
                    # sock.close()
                elif(request == "perfect"): #Found a new perfect number
                    perfect.append(message[5])
            
            elif(sender == "report"):
                if(request == "report"):    #Request for all the data
                    #sock.send('I will send you my info')
                    #perfect = 120
                    report_buffer = '<message type=\"report\" from=\"manage\" perfects=\"'
                    report_buffer += str(len(perfect))
                    report_buffer += '\" tested=\"'
                    #print'OLD_limit = ', old_limit
                    report_buffer += str(old_limit)
                    report_buffer += '\" processes=\"'
                    report_buffer += str(len(connected))
                    report_buffer += '\"></message>'
                    sock.send(report_buffer)    #Sends all the data
                
                elif(request == "terminate"):  #Request to terminate all processes. 
                    sock.send('Nukeing everyone! AHHHHHH!')
                    terminator()
          else:     #No data was received delete the client
            sock.close()
            print sock, 'has left the game.'
            connected.remove(sock)
