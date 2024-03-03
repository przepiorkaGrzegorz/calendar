## Calendar in command window
Application displays calendar of actual date or date specified by user. Current date may be taken from system or from web service - worldtimeapi.org. Web date is returned for local Warsaw timezone.

## Requirements
This project was developed on Ubuntu 22.04 with following tools
* g++ v11.4.0
* Make v4.3
* boost v1.74.0

## Setup
Type `make` to use Makefile and compile program, `make clean` deletes all generated files, `make cleanod` deletes dependencies and object files, `./calendar` runs the application.
