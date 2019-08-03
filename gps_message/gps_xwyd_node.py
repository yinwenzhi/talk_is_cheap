#!/usr/bin/env python
import sys
from struct import pack,unpack,calcsize

import os,time,signal,serial,threading,sys,select
import math,thread
import rospy
from   eu260_gps.msg import eu260_gps_locator

# gps连接串口并读取数据
class Device(object):
    def __init__(self, name, baud = 115200, timeout= 60): #38400
        if not name.startswith('/dev/'):
            try:
                self.fd = open(name,'r')
            except:
                self.fd = -1
        else:
            try:
                self.fd = serial.Serial(name, baud, timeout=timeout)
                now = time.time()
                x = time.localtime(now)
                logname = time.strftime('%Y-%m-%d-%H-%M-%S',x)
                self.log = open("./log/XingGuangYuDa/"+logname+".txt","w")
            except:
                self.fd = -1

        self.publisher  = rospy.Publisher("eu260_gps_locator_topic", eu260_gps_locator, queue_size = 50)

    # offline log
    def readFile(self,**arg):
        while self.fd > 0:
            data = self.fd.readline()
            print ("origin data:",data)
            data = str(self.fd.readline().strip())

            if data and data.startswith('$GPFPD'):
                data = data.strip()
                fields = data.split(',')
                if len(fields) == 16:
                    try:
                        heading   = float(fields[3])   # 0-360, Clockwise, North:0/360, East:90
                        #print "heading:",heading
                        latitude  = float(fields[6]) 
                        longitude = float(fields[7]) 
                        altitude  = float(fields[8]) 

                        ve        = float(fields[9])
                        vn        = float(fields[10])
                        vu        = 0.0 #float(fields[11])

                        ae        = 0.0 #
                        an        = 0.0 #
                        au        = 0.0 #

                        speed     = math.sqrt(ve*ve + vn*vn + vu*vu)
                        acc       = math.sqrt(ae*ae + an*an + au*au)

                        sat_num_1 = 0 # (fields[19])
                        sat_num_2 = 0 # float(fields[20])
                        #print "status:",fields[15]

                        gpstatus  = int(fields[15].split("*")[0], 16)&0x0f  #low Byte: 5-RTK, B-Diff orientation

                        #print heading, latitude, longitude, altitude, speed, acc, sat_num_1, sat_num_2, gpstatus

                        # for msg
                        location = eu260_gps_locator()
                        
                        location.heading   = heading
                        location.longitude = longitude
                        location.latitude  = latitude
                        location.speed     = speed

                        print (location.heading, latitude, longitude, altitude, speed, acc, sat_num_1, sat_num_2, gpstatus)
                        location.gpsStatus = gpstatus

                        self.publisher.publish(location)
                        time.sleep(0.01)
                    except ValueError:
                        print (ValueError)
                else:
                    print ("********************************************************")
                    print ("Data is Wrong:" + data)
                    print ("********************************************************")
            else:
                if data.strip() == "":
                    print ("catch log end!!!!")
                    sys.exit(1)
        else:
            print ("open file error!")
            self.fd.close()


    #for com device
    def readDev(self,**arg):
        while self.fd > 0:
            self.fd.flushInput()
            data = self.fd.readline()
            data = str(self.fd.readline().strip())
            self.log.writelines(data+"\n")
            #data = data.replace("\\x00","")
            print ("Origin Data:" + data)

            if data and data.startswith('$GPFPD'):
                data = data.strip()
                fields = data.split(',')
                if len(fields) == 16:
                    try:
                        heading   = float(fields[3])

                        latitude  = float(fields[6]) 
                        longitude = float(fields[7]) 
                        altitude  = float(fields[8]) 

                        ve        = float(fields[9])
                        vn        = float(fields[10])
                        vu        = 0.0 #float(fields[11])

                        ae        = 0.0 #
                        an        = 0.0 #
                        au        = 0.0 #

                        speed     = math.sqrt(ve*ve + vn*vn + vu*vu)
                        acc       = math.sqrt(ae*ae + an*an + au*au)

                        sat_num_1 = 0 # 
                        sat_num_2 = 0 #

                        gpstatus  = int(fields[15].split("*")[0], 16)&0x0f  #low Byte: 5-RTK B-Diff orientation

                        # for msg
                        location = eu260_gps_locator()

                        location.heading   = heading
                        location.longitude = longitude
                        location.latitude  = latitude
                        location.speed     = speed
                        location.gpsStatus = gpstatus

                        print (location.heading, latitude, longitude, altitude, speed, acc, sat_num_1, sat_num_2, gpstatus)

                        self.publisher.publish(location)
                        time.sleep(0.01)
                    except ValueError:
                        print (ValueError)
                else:
                    print ("********************************************************")
                    print ("Data is Wrong:" + data)
                    print ("********************************************************")
        else:
            print ("open device error!")
            self.fd.close()

if __name__ == '__main__':
    rospy.init_node('eu260_gps_locator',anonymous=True)

    if len(sys.argv) == 2 and sys.argv[1] == 'file':
        xingGuang = Device('/home/liumeng/workspace/eu260/eu260_ware/log/XingGuangYuDa/position8_2.txt')
        thread.start_new_thread(xingGuang.readFile, ())
    else:
        #may not be /dev/ttyUSB0
        xingGuang = Device('/dev/ttyUSB0')
        thread.start_new_thread(xingGuang.readDev, ())

    rospy.spin()

