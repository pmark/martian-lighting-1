#!/usr/bin/env bash

ACCESS_TOKEN=$(cat access-token)
curl https://api.particle.io/v1/devices/events -d "name=noblink" -d access_token=$ACCESS_TOKEN