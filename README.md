# CS 130 Web Server

This project is a continuation of a group project I worked on for UCLA's CS 130 class in winter of 2017. 
The class was taught by four visiting software engineers from Google: Greg Billock, James Farrell, Trevor Foucher, and Josh Hyman.
The original class project can be seen here: https://github.com/UCLA-CS130/Razzle-Dazzle

## Installation
Supported systems: Ubuntu 14.04
You will need git and Boost installed to run the web server. You will need Docker installed to build the Docker container and deploy the web server to AWS. You will need gcov to run the test coverage analysis.

Install Boost with the following command:
```
sudo apt-get install libboost-all-dev
```
Use the following command to clone this repository:
```
git clone --recursive https://github.com/RBarank/cs130-Webserver.git
```

## Usage
### Running:
Build the web server by issuing the command `make` and run it with the command `./webserver config_file`.
Or build and run with one simple command: `make run`.

### Tests:
To run the unit tests, issue the command `make test`.
To run the integration test, issue the command `make integration`.

### Coverage
To get an analysis of the test coverage, run `make coverage`.

### Deployment:
To build the server inside a Docker container, issue the command `make deploy`.
To deploy the server to AWS, change the Makefile's 'push_deploy' target so that it uses your AWS .pem key file and pushes to the url of your AWS server. Then issue the command `make push_deploy`.

## Project Organization
  


## Source Code Layout

1. The server is primarily run by two classes, namely server and connection. The server class takes in a semi-processed config file in the form of child blocks. The server constructor parses these blocks to pull out the port number and initialize a map of request handlers requested by the config file. It then starts up the server on the desired port, and initializes a connection, that processes everything that is sent to the server over the socket.
  
  2. The server constructs a unordered_map from uri_prefixes to RequestHandler pointers of the correct type. These are used by the connection to point requests to the correct handler type. The connection class checks the return status of the HandleRequest of the handler, which if not OK sets response to bad request/file not found depending on the situation.
  
  3. All request handlers share a common API and inherit from a RequestHandler class that defines this API. Handlers are created on basis of a prefix matching done between the handler names in the config file and the names of the handlers we have available. 

  4. Handlers:
	-EchoHandler: Echo's back the sent request into the body of the response in plain text.
	-StaticHandler: Used for serving files. Fetches files on the basis of prefix called. Each prefix matches to a source directory. There is a separate instance of each StaticHandler for each source directory.
	-StatusHandler: Returns in plain text data about the previous requests received by the server.
	-NotFoundHandler: Sets response to a 404 Not Found with a standard HTML.
  -ProxyHandler: Issue requests and parse the responses 
  

## Contributions:
- Abineet Das Sharma and Suchit Panjiyar, who were my team members and who wrote the original project with me
- Po-Hsun Wu, Yanzun Huang, and Evelyn Chen, who were members of a separate team that contributed to my team's code for one of the class's asignments.
- Parser for nginx config files written by James Farrell and inspired by https://github.com/fatiherikli/nginxparser.
- Includes code from googletest-1.7.0. See https://code.google.com/p/googletest/
- Partly based on the examples shown here: www.boost.org/doc/libs/1_63_0/doc/html/boost_asio/examples.html
