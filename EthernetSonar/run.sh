#!/bin/bash
while true
do
	python -m SimpleHTTPServer 80 & # If server is dead, try to start again. If port is taken this will default to exit.
	./EthernetSonar 100 output 1
	sleep 10s
done
