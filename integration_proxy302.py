import subprocess
from multiprocessing import Process
import urllib2
from time import sleep
import requests
import os

subprocess.call(["make"])
server = subprocess.Popen(["./webserver", "config_proxy302"])
sleep(2)

direct = subprocess.call(["curl", "-s", "http://ucla.edu", "-o", "result_direct.txt"])
proxy = subprocess.call(["curl", "-s", "http://localhost:8082/", "-o", "result_proxy.txt"])
sleep(10)

diffOutcome = subprocess.Popen(["diff", "-u", "result_direct.txt", "result_proxy.txt"], stdout = subprocess.PIPE)
diff = diffOutcome.stdout.read().decode("utf-8")

server.kill()


print "length of original result is "
print os.stat("result_direct.txt").st_size
print "length of redirect proxy result is "
print os.stat("result_proxy.txt").st_size

os.remove("result_direct.txt")
os.remove("result_proxy.txt")

print "redirect test passed!"
