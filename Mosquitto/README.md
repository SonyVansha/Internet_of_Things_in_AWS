## Installation and setup Mosquitto

### MQTT Broker Server

#### Installation Package EPEL (Extra Packages for Enterprise Linux)

```sh
amazon-linux-extras install epel -y
```
#### Installation Mosquitto Broken in IoT

```sh
yum install mosquitto -y
```

#### Running Mosquitto in EC2

This mosquitto running in port 1883, please add port 1883 to your EC2
```sh
mosquitto
```

### Subscribe to Mosquitto Broker Server

Received an incoming message from Mosquitto Broken
```sh
mosquitto_sub.exe -h 34.200.235.118 -t sony
```

#### Example Testing Mosquitto Broken Server
![giphy](https://github.com/SonyVansha/Internet_of_Things_in_AWS/assets/152833966/72f4b8cf-26ea-4f4d-81c7-3b2fbc55c226)

 <!-- -b : run in batch mode to allow passing passwords on the command line.
 -c : create a new password file. This will overwrite existing files.
 -D : delete the username rather than adding/updating its password.
 -U : update a plain text password file to use hashed passwords. -->

### Tshoot 'Error: Address already in use'

#### View PID in use port 1883

```sh
sudo lsof -i :1883
```

#### Stop processing to use port 1883

```sh
kill <PID>
```
