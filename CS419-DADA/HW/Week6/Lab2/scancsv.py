from CSVPacket import Packet, CSVPackets
import sys
import operator

IPProtos = [0 for x in range(256)]
numBytes = 0
numPackets = 0
pports = 0
pcount = 0
connto = 0

TCPPorts = [0 for x in range(1024)]
UDPPorts = [0 for x in range(1024)]

IPDst = {}
IPSrc = {}

IPSEC = {}
GRE = {}
OSPF = {}

CON = {}
class IpStruct:
    def __init__(self):
        self.countT = {}
        self.countU = {}
        self.count = 0

csvfile = open(sys.argv[1],'r')

for arg in sys.argv:
    if arg == "-stats":
        pports = 1

    if arg == "-countip":
        pcount = 1

    if arg == "-connto":
        connto = 1


for pkt in CSVPackets(csvfile):
    # pkt.__str__ is defined...
    #print pkt
    numBytes += pkt.length
    numPackets += 1
    proto = pkt.proto & 0xff
    IPProtos[proto] += 1

    if pports:
        # TCP Port Scanner
        if (pkt.proto == 6):
            if (pkt.tcpdport < 1024):
                TCPPorts[pkt.tcpdport] += 1

        # UDP Port Scanner
        if (pkt.proto == 17):
            if (pkt.udpdport < 1024):
                UDPPorts[pkt.udpdport] += 1
    if pcount:
        if(pkt.ipdst in IPDst):
            IPDst[pkt.ipdst] += 1
        else:
            IPDst[pkt.ipdst] = 1

        if(pkt.ipsrc in IPSrc):
            IPSrc[pkt.ipsrc] += 1
        else:
            IPSrc[pkt.ipsrc] = 1

        if(pkt.proto == 47):
            if(pkt.ipdst in GRE):
                GRE[pkt.ipdst] += 1
            else:
                GRE[pkt.ipdst] = 1
        if(pkt.proto == 50):
            if(pkt.ipdst in IPSEC):
                IPSEC[pkt.ipdst] += 1
            else:
                IPSEC[pkt.ipdst] = 1
        if(pkt.proto == 89):
            if(pkt.ipdst in OSPF):
                OSPF[pkt.ipdst] += 1
            else:
                OSPF[pkt.ipdst] = 1

    if connto:
        if(pkt.ipdst not in CON):
            CON[pkt.ipdst] = IpStruct()
        t = None
        if(pkt.proto == 6):
            if (pkt.tcpdport < 1024):
                t = (proto, pkt.tcpdport)
        if(pkt.proto == 17):
            if (pkt.udpdport < 1024):
                t = (proto, pkt.udpdport)

        if(t != None):
            if(pkt.proto == 6):
                if( t in CON[pkt.ipdst].countT):
                    CON[pkt.ipdst].countT[t] += 1
                else:
                    CON[pkt.ipdst].countT[t] = 1
            if(pkt.proto == 17):
                if( t in CON[pkt.ipdst].countU):
                    CON[pkt.ipdst].countU[t] += 1
                else:
                    CON[pkt.ipdst].countU[t] = 1



#
#
#
#            CON[pkt.ipdst][0] += 1
#        else:
#            CON[pkt.ipdst] = (0, [])
#
#        if(pkt.proto == 17):
#            buf = "UDP/%d" % (pkt.udpdport)
#            if buf not in CON[pkt.ipdst][1]:
#                CON[pkt.ipdst][1].append(buf)
#        el
#            buf = "TCP/%d" % (pkt.tcpdport)
#            if buf not in CON[pkt.ipdst][1]:
#                CON[pkt.ipdst][1].append(buf)
#






if pports:
    print "numPackets:%u numBytes:%u" % (numPackets,numBytes)
    for i in range(256):
        if IPProtos[i] != 0:
            print "%3u: %9u" % (i, IPProtos[i])



    print "------------------TCP-------------------"
    for x in range(0, len(TCPPorts)):
        if (TCPPorts[x] > 0):
            print x, ":\t", TCPPorts[x]

    print "------------------UDP-------------------"
    for x in range(0, len(UDPPorts)):
        if (UDPPorts[x] > 0):
            print x, ":\t", UDPPorts[x]


if pcount:
    print "-----------------IP-DST---------------"
    print "Count\t:  Address"
    print "--------------------------------------"
    sorted_Dips = sorted(IPDst.items(), key=operator.itemgetter(1), reverse=True)
    for ip in sorted_Dips:
        print ip[1], "\t: ", ip[0]

    print "-----------------IP-SRC---------------"
    print "Count\t:  Address"
    print "--------------------------------------"
    sorted_Sips = sorted(IPSrc.items(), key=operator.itemgetter(1), reverse=True)
    for ip in sorted_Sips:
        print ip[1], "\t: ", ip[0]
    print "----------------PORTS-----------------"
    print "------------------GRE-----------------"
    for ip in sorted(GRE.items(), key=operator.itemgetter(1), reverse=True):
        print ip[1], "\t: ", ip[0]
    print "------------------OSPF----------------"
    for ip in sorted(OSPF.items(), key=operator.itemgetter(1), reverse=True):
        print ip[1], "\t: ", ip[0]
    print "------------------IPSEC---------------"
    for ip in sorted(IPSEC.items(), key=operator.itemgetter(1), reverse=True):
        print ip[1], "\t: ", ip[0]

if connto:
    print "IP Connections"
    for ip in CON:
        for tcp in CON[ip].countT:
            CON[ip].count += CON[ip].countT[tcp]
        for udp in CON[ip].countU:
            CON[ip].count += CON[ip].countU[udp]

    for ip in sorted(CON.items(), key= lambda x: x[1].count, reverse=True):
        print "ipdst", ip[0], "\thas", ip[1].count, " sources on ports: ",
        for tcp in ip[1].countT:
            print "tcp/"+ str(tcp[1]),
        for udp in ip[1].countU:
            print "udp/"+ str(udp[1]),
        print ""

