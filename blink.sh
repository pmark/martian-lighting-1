#!/usr/bin/env bash

ACCESS_TOKEN=$(cat access-token)
curl https://api.particle.io/v1/devices/events -d "name=blink" -d access_token=$ACCESS_TOKEN