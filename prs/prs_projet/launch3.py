import os
import time
import sys
import glob
import subprocess

ip_address= subprocess.check_output(['hostname', '-I']).decode('utf-8')[:-2]
#ip_address = "134.214.202.40"
server_port= "8888"
file_name1= "file1"
file_name2= "file2"
file_name3= "file3"
file_name4= "file4"
output_file= "output.txt"

server_name= "bin/serveur3-LaPaireDeSockets"

name= server_name.split("-")
suffix= name[0][-1:]

client_name= "client1"
copy_file_name1= "./copy_" +file_name1
copy_file_name2= "./copy_" +file_name2
copy_file_name3= "./copy_" +file_name3
copy_file_name4= "./copy_" +file_name4

copy_touch_command1= "touch "+ copy_file_name1
copy_touch_command2= "touch "+ copy_file_name2
copy_touch_command3= "touch "+ copy_file_name3
copy_touch_command4= "touch "+ copy_file_name4
os.system(copy_touch_command1)
os.system(copy_touch_command2)
os.system(copy_touch_command3)
os.system(copy_touch_command4)

output= open(output_file, "a")

server_launch_command= "./" +server_name +" " +server_port +" &"
client_launch_command1= "./" +client_name +" " +ip_address +" " +server_port +" " +file_name1 + " 0" +" &"
client_launch_command2= "./" +client_name +" " +ip_address +" " +server_port +" " +file_name2 + " 0" +" &"
client_launch_command3= "./" +client_name +" " +ip_address +" " +server_port +" " +file_name3 + " 0" +" &"
client_launch_command4= "./" +client_name +" " +ip_address +" " +server_port +" " +file_name4 + " 0"

print("launching "+ str(server_name))

os.system(server_launch_command)
time.sleep(1)
start_time= time.time()
os.system(client_launch_command1)
time.sleep(1)
os.system(client_launch_command2)
time.sleep(1)
os.system(client_launch_command3)
time.sleep(1)
os.system(client_launch_command4)
end_time= time.time()
delta= end_time- start_time- 3

statinfo1= os.stat(copy_file_name1)
statinfo2= os.stat(copy_file_name2)
statinfo3= os.stat(copy_file_name3)
statinfo4= os.stat(copy_file_name4)

stat_sum= statinfo1.st_size+ statinfo2.st_size+ statinfo3.st_size+ statinfo4.st_size

time.sleep(1)

# output.write(str(server_name)+" "+ str(stat_sum)+ " "+ str(delta)+ " "+ str(stat_sum/delta)+ "\n")
print("Débit={}".format(str(stat_sum/delta)))

# output.close()

# remove_command1= "rm "+ copy_file_name1
# remove_command2= "rm "+ copy_file_name2
# remove_command3= "rm "+ copy_file_name3
# remove_command4= "rm "+ copy_file_name4
# os.system(remove_command1)
# os.system(remove_command2)
# os.system(remove_command3)
# os.system(remove_command4)

kill_command= "killall serveur*"
os.system(kill_command)
kill_command= "killall client*"
os.system(kill_command)
