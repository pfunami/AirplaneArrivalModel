# AirplaneArrivalModel
H30情報特別演習1（Special Exercise in Information Science1）

This program simulates, by multi agent simulation, the process until an airplane heading for Haneda Airport autonomously navigates according to its own algorithm and arrives at the destination at Haneda Airport.  
The initial state data (data.csv) is the location and speed of the aircraft flying near the Kanto, Tokai, and southern Tohoku regions heading for Haneda Airport (North Wind) at 17:40 (JST) on January 13, 2019 , Altitude, flight number, departing airport.  

<img width="1440" alt="2019-02-01 2 09 22" src="https://user-images.githubusercontent.com/40795078/52071471-7056cd80-25c6-11e9-9f49-423a16c5e218.png">

## How to  

In the first case, in the directory where these files are located, execute the following on the command line:  
`$ cmake .; make; ./Program`  
In other cases it can be executed with `. / Program`.

## Function

- Enter key: pause, execute  
- Space key: HOLD command ON / OFF  
- N key: North wind (initially configurable)  
- S key: South wind (initially configurable)  
- 0 key: Return viewpoint to initial  
- Right click + Mouse up / down move: Scale  
- Left click + Mouse move: Move point of view

