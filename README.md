CrashAndBurn
============

Full source code for Charcade's "Crash + Burn" (fire spewing bumper cars).

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
* Events
 * OnCollision(forceVec) -- car => server
 * OnCollision(car1_id, car2_id) -- server => cars  *NOTE: This may not be necessary since the server can just send a render frame to tell the relevant cars to react in a (GUI programmable?) way
 * OnFire(fire_type) -- car => server
 * OnTippingOver(gyroVec) -- car => server
 * OnButtonPress(button_type) -- car => server (if there are other buttons available to car operators)
* Commands (always sent from server to one or more bumper cars):
 * Frame rendering for full refresh of an LED screen
 * Frame rendering for LED rendering routines (e.g., nyan cat)
 * Set default player colour
 * Activate/Deactivate (for safety purposes and in case someone tries to drive off with one of our cars)
 * Shoot Fire (various types e.g., sm/md/lg burst, rapid fire)
* Query and Response
 * RequestState -- server => car
 * StateInfo(is_activated, default_colour, ...) -- car => server
 * Discovery and Response
 * Discover(server_endpoint_info) -- server => *broadcast*
 * HereIAm(car_endpoint_info) -- car => server

The protocol is a specification for the functionality that will be present in both the Bumper Car Controllers and the Server Coordinator. I think all communications should be done over TCP/IP to start off. If we find responsiveness to be an issue for certain commands (and guaranteed arrival is not an issue) we can move those over to UDP as we see fit. Protocol will be implemented as basic ASCII over serial. Each package will have a starting identifier character, a command identifying character, and some easy-to-read parsable tuple of relevant parameters.

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
