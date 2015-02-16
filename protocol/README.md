# Crash+Burn Communications Protocol

## Message Naming Conventions

* `Query`: A message sent for the sake of getting a message back. Queries contain no information, they are simply a prompt for information from whoever the query was sent to.
* `Info`: Replies to queries and general information messages — not used to direct specific behaviour but simply used to inform (which may or may not result in action).
* `Event`: An event that occurred on the sender, the message exists to inform others that it occurred.
* `Cmd`: A command, sent from the party demanding an action be taken by the receiving party.


## Car to Server

`CarCollisionEvent(accX, accY, accZ)`
 > Occurs when a car detects that it has collided with something. If this is a collision between two or more cars then the server will get an event from each car.
 * `accX, accY, accZ` are the normalized acceleration vector in x, y, and z.

`FireShotEvent(location, fireType)`
 > Occurs when a car shoots fire out of a flame effect.
 * `location` The location of the flame effect (e.g., rearFlameEffect)
 * `fireType` The type of fire that was shot (e.g., LongBurst)

`TippingOverEvent()`
 > Occurs when the car detects that it is tipping over.

`LocalDeadmanEvent(isFireOn)`
 > Occurs when a car enables or disables its safety switch (e.g., pressure sensor in the seat).
    * `isFireOn` true if fire is live, false if not.

`CarStatusInfo(carId, isActive, isFireLive, colour, isTippingOver, team)`
 > Status update from the car, holds all the basic information pertaining to the car, used by the server for syncing information in the GUI (or other such things).
 * `carId` The unique identifier of the car
 * `isActive` The car is active, it can be driven and if the local deadman is enabling fire, fire is also on.
 * `isFireLive` If the local deadman is enabling fire this will be true, otherwise false. It doesn’t necessarily mean fire is completely active through, the car must still be active for fire to be shot.
 * `colour` The colour value of the car’s LEDs
 * `isTippingOver` Whether the car is detected to be tipping over or not.
 * `team` An enumeration describing the team of the car (relevant in teamplay matches)

### Still to consider
 * `ButtonPressEvent(buttonId)` Occurs when a button on the car is pressed (if there are other buttons available to car operators)


# Server to Car

`StatusQuery()`
 > Used to ask a car to reply with its status

`SetLEDColourCmd(colour)`
> Tell a car to set all its LEDs to the specified colour.

`SetIsActiveCmd(isActive)`
> Tell a car to activate or deactivate.

> `ShootFireCmd(location, fireType)`
Tell a car to shoot fire.

> `CarCollisionInfo(rewardCarId, punishCarId, isFriendlyFire)`
Inform cars of a collision between two cars, who instigated it and who didn’t and whether it was a “friendly” collision. NOTE: This might not be necessary if cars just passively receive instruction/commands from the server.

### Still to consider
 * Discovery and Response


## How to use Protobuf

Step 1: Create a .proto file defining your messages.

Step 2: Build a .pb file
```bash
protoc -omessage.pb message.proto
```

Step 3: Run the .pb file through the nanopb generator script
```bash
python nanopb/generator/nanopb_generator.py message.pb
```
