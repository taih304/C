# [Installation](Install.md)
# Telemetry

Telemetry with TCP client has HTTP client. Features:

* Internet isn't connected when program starts: Print ``gethostbyname: Host name lookup failure``
* Internet is connected when program starts: Start the ThingsBoard telemetry process with HTTP request
* While telemetry process is happening, Internet is disconnected: With ``DEBUG`` mode is on, program will get blocked. If Internet is then recovered, program exits.

Program: [tcp_client_for_telemetry.c](tcp_client_for_telemetry.c)

# Server side API

Get JWT and parsed into ``token`` and ``refreshToken``: [raw_api_get_jwt.c](raw_api_get_jwt.c)
 
## [thingsboard](thingsboard) library version 0.1.0

* Build from GCC
* Release: 17th Jan 2023

Source code are built with Bazel with attached [BUILD](BUILD) file and file architecture like below:

```
|--cJSON-1.7.15 //cJSON-1.7.15 folder to store cJSON source code
|--thingsboard //thingsboard folder to store thingsboard source code
|--main.c
|--WORKSPACE
|--BUILD
```
Compile ``main.c`` under that file architecture: ``gcc -I"cJSON-1.7.15" -Ithingsboard main.c thingsboard/thingsboard.c "cJSON-1.7.15"/cJSON.c``
Get JWT and parsed into ``token`` and ``refreshToken``: [thingsboard_get_jwt.c](thingsboard_get_jwt.c)

Read response from ``/api/auth/user``: [thingsboard_auth_user.c](thingsboard_auth_user.c)

Get customer device infos: [thingsboard_get_device_infos.c](thingsboard_get_device_infos.c)

Get all access token from 10 devices: [thingsboard_get_access_token.c](thingsboard_get_access_token.c)

An example of a customer devices info json file: [customer_device_infos.json](customer_device_infos.json)
