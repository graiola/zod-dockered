#!/usr/bin/env bash

docker build -f ./Dockerfile --network=host -t zod .
