import os
import time
import sys
import subprocess

if len(sys.argv) != 2:
    print("usage: python launch.py <file>")
    quit()

server_name= 'bin/serveur1-LaPaireDeSockets'
ip_address= subprocess.check_output(['hostname', '-I']).decode('utf-8')[:-2]
#ip_address= "134.214.202.40"
server_port= '8888'
file_name= sys.argv[1]

name= server_name.split("-")
suffix= name[0][-1:]

client_name= "client1"

server_launch_command= "./" +server_name +" " +server_port +" &"
client_launch_command= "./" +client_name +" " +ip_address +" " +server_port +" " +file_name + " 0"

os.system(server_launch_command)
time.sleep(1)
start_time= time.time()
os.system(client_launch_command)
end_time= time.time()
delta= end_time- start_time

copy_file_name= "./copy_" +file_name
statinfo= os.stat(copy_file_name)

time.sleep(1)

print("Débit="+str(statinfo.st_size/delta)+" o/s")

remove_command= "rm "+ copy_file_name
#os.system(remove_command)
