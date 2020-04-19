# watts
watts mobile robot 
04/18/2020
Updated README for this repository.
Watts is a commercial four wheeled robot from Elegoo that is being hacked to 
create a lab for exploring the implementation of subsumption architectures as
popularized by Rodney Brooks at MIT and later at iRobot.  My implementations 
here are inspired by the book Mobile Robots by Joseph Jones and Anita Flynn. 

The subsumption architecture ideas are further extended by the ideas of Marvin
Minsky as he published a layered AI architecture in The Emotional Machine as 
well as implementation of ideas taken from Tiny ML by Daniel Situnayake and Pete 
Warden and using Visual ML features of JeVois cameras and ML engine.

The project also includes some hardware hacking.  So far I've added current/
voltage/power sensors, wireless charging, upgraded battery power, and plan to 
add pan-tilt servo platform for the JeVois camera, while using the provided
line tracker and ultrasonic distance sensor as provided in the stock robot.

I've included some infrastructure for this project that I've thought about
for many years and finally can take the time to implement. Building the 
subsumption architecture around a messsage bus (MQTT) to allow communication
between processes on both the UNO, the on board Rpi Zero and an Rpi 3 B+ 
named RpiSky because it is the "cloud" consumer of all of the data on the
message bus for presentation in a set of Prometheus-Grafana dashboards 
accessible via web pages hosted on RpiSky.

What I hope for the platform is that it can be a long term laboratory for
exploring building complex behaviors that at least hint at capabilities in 
the framework Minsky describes in imitation of intelligence in nature that
we observe.
