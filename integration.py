import subprocess
from multiprocessing import Process
import urllib2
from time import sleep
import requests

def threadExec():
	subprocess.call(["./webserver", "config_file"])
#p = subprocess.Popen("./webserver config_file")

print "Building binary"
subprocess.call(["make"])

t = Process(target=threadExec)
t.start()

sleep(5)

req = requests.get('http://localhost:3000')

if req.status_code != 200:
	print "Error: Wrong Status Code."
	exit()
else:
	print "Status Code Correct: 200"

if req.headers['content-type'] != 'text/plain':
	print "Incorrect content-type"
	exit()
else:
	print "Content Type Correct: text/plain"

if req.headers['content-length'] != str(len(req.content)):
	print "Error: Length Header Invalid"
	exit()
else: 
	print "Content Length Correct"

print "Integration Test Passed!"

print "Shutting down web server"
subprocess.call(["fuser", "-k", "3000/tcp"])

print "Cleaning previous build"
subprocess.call(["make", "clean"])

t.terminate()

