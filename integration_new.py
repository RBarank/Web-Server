import subprocess
import requests
import urllib2
import os
from telnetlib import Telnet
from multiprocessing import Process
from time import sleep


def threadExec():
	subprocess.call(["./webserver", "config_file"])


def multi_thread_check():
	req = ["GET /echo HTTP/1.1", "Host: localhost:3000", "Connection: keep-alive", "Upgrade-Insecure-Requests: 1"]
	req += ["User-Agent: telnet", "Accept: */*"]
	req = "\r\n".join(req)
	req += "\r\n\r\n"

	print "Starting connection1 with half request"
	connection1 = Telnet('localhost', 3000)
	connection1.write(req.split('Accept')[0])

	print "Starting connection2 with full request"
	connection2 = Telnet('localhost', 3000)
	connection2.write(req)
	res2 = connection2.read_all()

	print "Completing the request of connection1"
	connection1.write("Accept: */*\r\n\r\n")
	res1 = connection1.read_all()


	if res1 != res2:
		print "Same requests are giving different responses"
		exit(4)
	else:
	 	print "Multi threading tests passed."
	 	print "The two connections give the same response."

PROXY_CONFIG_NAME = "config_file"

def proxyThreadExec():
    subprocess.call(["./webserver", PROXY_CONFIG_NAME])

def proxyTest():
    print "Proxy integration test:"
    proxyProcess = Process(target=proxyThreadExec)
    proxyProcess.start()
    sleep(0.01)

    req_server = requests.get('http://www.ucla.edu')
    req_proxy = requests.get('http://localhost:3000/')

    if req_server.status_code != 200 or req_proxy.status_code != 200:
	    print "Error: Wrong Status Code."
    else:
	    print "Status Code Correct: 200"

    print "Length of content from server is "
    print len(req_server.content)
    print "Length of content from proxy is "
    print len(req_proxy.content)

    proxyProcess.terminate()
    print "Proxy integration test passed!"



serverProcess = Process(target=threadExec)
serverProcess.start()

sleep(5)


# ECHO TEST
req = requests.get('http://localhost:3000/echo/')

if req.status_code != 200:
	print "Error: Wrong Status Code."
	exit(1)
else:
	print "Status Code Correct: 200"

if req.headers['content-type'] != 'text/plain':
	print "Incorrect content-type"
	exit(2)
else:
	print "Content Type Correct: text/plain"

# MULTITHREAD TEST
multi_thread_check()


# PROXY TEST
proxyTest()

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


print "Integration Test Passed!"

print "Shutting down web server"
subprocess.call(["fuser", "-k", "3000/tcp"])

print "Cleaning previous build"
subprocess.call(["make", "clean"])

serverProcess.terminate()
exit(0)
