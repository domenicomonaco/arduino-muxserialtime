## MuxSerialTIME ##
* Author: Domenico Monaco, domenico.monaco[@]kiuz.it
* Site: http://monaco.kiuz.it
* LICENSE: GNU v2 
* Date: 16 / 07 / 2014

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

### Configuration ###

	mux1.config("potentiomeeter", "1","#", 0, 60);
	mux2.config("potentiomeeter", "2","#", 0, 60);

	config(<<TYPE>>, <<ADDRESS>>,<<Value divider>>, <<Skyps of reading>>, <<60s>>);

### Using ###

	mux1.putValue(VALUE1);
	mux2.putValue(VALUE2);

### Example Otputs ###

	0M#CURRENT#1#SINGLE-INSTANT#4.82
	0M#TEMPERATURE#1#SINGLE-INSTANT#23.00
	0M#CURRENT#1#SINGLE-INSTANT#7.85
	0M#CURRENT#1#SINGLE-INSTANT#4.99
	0M#CURRENT#1#SINGLE-INSTANT#7.68
	0M#CURRENT#1#SINGLE-INSTANT#4.87
	1M#TEMPERATURE#1#MULTI-AVG#23.00#23.00#23.00#0.00
	2M#TEMPERATURE#1#MULTI-AVG#23.00#23.00#23.00#0.00
	0M#TEMPERATURE#1#SINGLE-INSTANT#23.00
	0M#CURRENT#1#SINGLE-INSTANT#7.88
	0M#CURRENT#1#SINGLE-INSTANT#4.90
	0M#CURRENT#1#SINGLE-INSTANT#7.80

## Special Thanks, inspiration and forks ##
* nothing

## ChangeLog ## 

* ISSUE #1: Renamed "Temporal Aggregation ID" from 0T,1T...xT into 0M, 1M, 5M ... xM where x are time duration of aggregation