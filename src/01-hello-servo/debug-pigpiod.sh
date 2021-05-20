#!/bin/bash

sudo pigpiod # start daemon

pigs s 17 1500 # middle
sleep 2

pigs s 17 1000 # safe counterclockwise
sleep 2

pigs s 17 2000 # safe clockwise
sleep 2
