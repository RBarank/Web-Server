# Hello, Welcome Professors to the Razzle-Dazzle Demo Document!
## Here you shall find instructions to demo our code on your local machine
### We have it deployed on AWS too, but it is easiest to demo some features on your local machine.

## Preface
Please accept our sincere apologies for the messy file setup, We should have had separate folders for our files.

Do run the following on the linux VM. 

AWS link: <http://ec2-35-161-79-255.us-west-2.compute.amazonaws.com:8020/>

### Also available in the github wiki section along with (very) brief design documentation.

Please clone our repository using the following command

    git clone --recursive https://github.com/UCLA-CS130/Razzle-Dazzle.git

Now, Once you are in the Razzle-Dazzle directory, you can build our web server using the following commands

    make clean-all //Clean any previous build
    make //build webserver
    make test //run unit tests on code
    make integration //run integration tests on code
    make coverage //run  gcov to see test coverage

Now to test the web server, you can run it using the following command:

    ./webserver deploy_config

This should start our server on <http://127.0.0.1:8020>.

This URL above calls out proxy handler, and should show you ucla's homepage (www.ucla.edu).

Some of the different url's you can test are given below:

    <http://127.0.0.1:8020/echo> -> echo's request
    <http://127.0.0.1:8020/static/test.jpg> -> Display an image
    <http://127.0.0.1:8020/static/RazzleDazzle.png> -> Display an image
    <http://127.0.0.1:8020/status> -> Display information about the status of the webserver

# Special features and how to demo them

## Updating config file and not needing to run the web server all over again
* Run the webserver
    ./webserver deploy_config
* Demo the feature you're about to change, such as the port number.
* Change it, say make the port number 3000 and save the file
* The server should now be running on port 3000

We do also handle the possibility that a request gets cut off during the config file change.

## Markdown rendering
* Run the webserver
    ./webserver deploy_config
* Go to: <http://127.0.0.1:8020/static/markdown.md>

## HTTP Compression
* Run the webserver
    ./webserver deploy_config
* Send a request, say query:
    <http://127.0.0.1:8020/static/test.jpg>
* Once the response arrives, a file "compressionTest.txt" would have been generated showing the original and compressed response



