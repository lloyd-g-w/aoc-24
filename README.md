# How to use.

## Build all files
* Run `make`

## Build a single day's files
* Run `make build DAY=X`, where `X` is the day you are looking for.

## Run with **_your_** input
* Change into the `dX` directory, where `X` is the day you seek.
* Add your provided input to a file named 'input'.
* Go out one directory (`cd ..`)
* Run `make run DAY=X`
Alternatively, build for a day and redirect a file to stdin.

## Run with sample input
* Run `make run_sample DAY=X`, where `X` is the day you seek.
