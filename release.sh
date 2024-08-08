#!/bin/bash

docker compose run --rm --build arduino ./build.sh -m GT build -z
docker compose run --rm --build arduino ./build.sh -m GTM build -z
