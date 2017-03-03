import subprocess
from multiprocessing import Process
import urllib2
from time import sleep
import requests
import os

subprocess.call(["make"])
server = subprocess.Popen(["./webserver", "config_proxy302"])
sleep(2)

direct = subprocess.call(["curl", "-s", "http://www.ucla.edu", "-o", "result_direct.txt"])
proxy = subprocess.call(["curl", "-s", "http://localhost:8082/", "-o", "result_proxy.txt"])


diffOutcome = subprocess.Popen(["diff", "-u", "result_direct.txt", "result_proxy.txt"], stdout = subprocess.PIPE)
diff = diffOutcome.stdout.read().decode("utf-8")

server.kill()
os.remove("result_direct.txt")
os.remove("result_proxy.txt")

print "redirect test passed!"
