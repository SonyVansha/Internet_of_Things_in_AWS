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

### Testing connection Mosquitto

#### Subscribe to Mosquitto Broker Server

Received an incoming message from Mosquitto Broken
```sh
mosquitto_sub.exe -h 34.200.235.118 -t sony
```

#### Publisher to Mosquitto Broker Server

Sent an incoming message from Mosquitto Broken
```sh
mosquitto_pub.exe -h 34.200.235.118 -t sony -m "Hello Sony"
```

#### Example Testing Mosquitto Broken Server
![giphy](https://github.com/SonyVansha/Internet_of_Things_in_AWS/assets/152833966/72f4b8cf-26ea-4f4d-81c7-3b2fbc55c226)

### User Authentication in Mosquitto Server

#### Create a new user

- `-b` : run in batch mode to allow passing passwords on the command line.
- `-c` : create a new password file. This will overwrite existing files.
- `-D` : delete the username rather than adding/updating its password.
- `-U` : update a plain text password file to use hashed passwords.
```sh
touch /etc/mosquitto/user.txt
mosquitto_passwd -b /etc/mosquitto/user.txt <username> <password>
```

#### Create a new user

```sh
touch /etc/mosquitto/user.txt
mosquitto_passwd -b /etc/mosquitto/user.txt <username> <password>
```

#### Add configuration for User Anonymous not acces but user can access

```sh
printf "allow_anonymous false\n" >> /etc/mosquitto/mosquitto.conf
printf "password_file /etc/mosquitto/user.txt\n" >> /etc/mosquitto/mosquitto.conf
```

#### Test connection for Received Message with

```sh
mosquitto_sub -h <Host> -u <username> -P <password> -t <topic>
```

### Tshoot 'Error: Address already in use'

#### View PID in use port 1883

```sh
sudo lsof -i :1883
```

#### Stop processing to use port 1883

```sh
kill <PID>
```
