## MuxSerialTIME ##
* Author: Domenico Monaco, domenico.monaco[@]kiuz.it
* Site: http://monaco.kiuz.it
* LICENSE: GNU v2 
* Date: 26 / 06 / 2014

## Goals ##
* Managing outputs of multiple sensor and multiple types of temporal data on single Serial line: "multiplexing on serial line"

I'm working on a simple implementation of Wireless Sensor Network with Arduino and on every node of Sensor Network I need a simple protocol to share values of sensor on single Serial Line. MuxSerialTime class make possible managing the serial prints of each sensor outputs with structured Serial lines.

##Feature ##

* Instant values or average values for each sensor outputs;
* We can set numbers and period of captured AVG Values
* We can set NAME, TYPE and ADDRESS of Sensor outputs

## Requirements ##

* Statistic Arduino library

## Example of use ##

* AnalogMuxSerialTime 

## Special Thanks, inspiration and forks ##
