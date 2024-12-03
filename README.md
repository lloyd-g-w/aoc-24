# How to use.

## Build all files
* Run `make`

## Build a single day's files
* Run `make build DAY=X`, where `X` is a given day (e.g. DAY=1).

## Run with **_your_** input
* Change into the `dX` directory, where `X` is a given day (e.g. DAY=1).
* Add your provided input to a file named 'input'.
* Go out one directory (`cd ..`)
* Run `make run DAY=X`

Alternatively, build a day's code and manually redirect a file to stdin during execution.

## Run with sample input
* Run `make run_sample DAY=X`, where `X` is a given day (e.g. DAY=1).
