import subprocess
from multiprocessing import Process
from time import sleep
import requests
from telnetlib import Telnet


def threadExec():
	subprocess.call(["./webserver", "config_file"])


def multi_thread_check():
	req = ["GET /echo HTTP/1.1", "Host: localhost:3000", "Connection: keep-alive", "Upgrade-Insecure-Requests: 1"]
	req += ["User-Agent: telnet", "Accept: */*"]
	req = "\r\n".join(req)
	req += "\r\n\r\n"
	# print req

	connection1 = Telnet('localhost', 3000)
	connection1.write(req.split('Accept')[0])

	connection2 = Telnet('localhost', 3000)
	connection2.write(req)
	res2 = connection2.read_all()

	connection1.write("Accept: */*\r\n\r\n")
	res1 = connection1.read_all()

	print res1
	print res2

# print "Building binary"
# subprocess.call(["make"])

serverProcess = Process(target=threadExec)
serverProcess.start()

sleep(5)

# req = requests.get('http://localhost:3000')

# if req.status_code != 200:
# 	print "Error: Wrong Status Code."
# 	exit(1)
# else:
# 	print "Status Code Correct: 200"

# if req.headers['content-type'] != 'text/plain':
# 	print "Incorrect content-type"
# 	exit(2)
# else:
# 	print "Content Type Correct: text/plain"

# if req.headers['content-length'] != str(len(req.content)):
# 	print "Error: Length Header Invalid"
# 	exit(3)
# else: 
# 	print "Content Length Correct"

# print "Integration Test Passed!"

# print "Shutting down web server"
# subprocess.call(["fuser", "-k", "3000/tcp"])

# print "Cleaning previous build"
# subprocess.call(["make", "clean"])

# serverProcess.terminate()
#exit(0)

multi_thread_check()






















