Crash+Burn
============

Full source code for Charnival's fire spewing bumper cars aptly named Crash+Burn.

This project will have the following, distinct, design components:

* Bumper Car Controller (i.e., microcontroller code)
* Communications Protocol
* Server Coordinator
* Server Graphical User Interface (GUI)

Here are the basic responsibilities I envision for each of these components:

Bumper Car Controller
---------------------
* Reads the Inertial Measurement Unit (IMU) / Sensor data, performs filtering, reacts to state changes appropriately
* Reads misc. not-yet-specified sensors (buttons?) on the car and reacts to their state changes appropriately
* Reads and reacts to incoming serial data from the Server Coordinator, data adheres to the Communications Protocol
* Writes serial data output to the Server Coordinator, data adheres to the Communications Protocol
* Controls the Flame Effect System (solenoid, spark-gap/ignitor, coordination of gas and ignition)
* Controls the LED "Screen" System (mapping, colour assignment, etc.)
* Shortcut safety control/reaction system (e.g., car tips over => stop fire/shut down immediately)
* Holds functionality for a set of pre-scripted display routines for the LEDs (... or not: depends if we want the server to do this and just play them back via the network)

Overall, the Bumper Car Controller is a slave to the Server Coordinator. Any non-slavey-type-stuff that it does stays local (i.e., a bumper car never tells the server what to do).

Communications Protocol
---------------------

The protocol is a specification for the functionality that will be present in both the Bumper Car Controllers and the Server Coordinator.

See details in the [protocol folder](https://github.com/S3FA/CrashAndBurn/tree/master/protocol).

Server Coordinator
------------------

* Discovers and assigns identification Bumper Car Controllers (other option is to hardcode this, as mentioned above)
* Tracks addresses/endpoints and sessions for bumper car communications
* Reads and reacts to incoming data from one or more Bumper Car Controllers, data adheres to the Communications Protocol
* Writes outgoing events/commands/queries to one or more Bumper Car Controllers, data adheres to the Communications Protocol
* Assesses the likelihood of collisions between bumper cars and utilizes the Communications Protocol to inform colliding cars of their respective colliders and/or sends the effects for reacting to the collision
* Maintains an updated version of the state information for all known Bumper Car Controllers

Overall, the Server Coordinator acts as a layer between the network and the Server GUI, providing the interface and logic responsible for communicating with and coordinating the Bumper Car Controllers.

Server GUI
----------

* Updates its visual state based off the state of the Server Coordinator
* Control panel featuring the display and control widgets for all discovered bumper cars and their respective states
* Buttons for Activating/Deactivating individual cars
* Buttons for Activating all cars and Deactivating all cars
* Paint canvas for car LEDs?

The GUI is both a view into the Server Coordinator and a (hopefully user-friendly) method of updating the entire system's state via visual information / files / etc.
