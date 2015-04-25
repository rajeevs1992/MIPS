SHELL := /bin/bash
all:
	cc -g -DNOPCODES=45  simulator/simulator.c
