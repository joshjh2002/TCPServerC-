@echo off
g++ .\TCPServer.cpp -lwsock32 -o Server
g++ .\TCPClient.cpp -lwsock32 -o Client