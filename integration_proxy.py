import subprocess
from multiprocessing import Process
import urllib2
from time import sleep
import requests

PROXY_CONFIG_NAME = "config_file"

def proxyThreadExec():
    subprocess.call(["./webserver", PROXY_CONFIG_NAME])

def proxyTest():
    print "Proxy integration test:"
    subprocess.call(["make"])
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

    print "Shutting down web server"
    subprocess.call(["fuser", "-k", "3000/tcp"])
    subprocess.call(["make", "clean"])

    proxyProcess.terminate()
    print "Proxy integration test passed!"

def main():
    proxyTest()
    
if __name__ == "__main__":
    main()
