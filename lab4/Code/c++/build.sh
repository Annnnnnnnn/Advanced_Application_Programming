#!/bin/sh

#emcc --bind -lwebsocket -o client.js -v -O2 client.cpp 

#emcc --bind -lwebsocket -o client.html -v -O2 client.cpp -s MODULARIZE -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' 

emcc -lwebsocket -o client.js -v client.cpp 


