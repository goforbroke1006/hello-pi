#!/bin/bash

CURRENT_VERSION=1

VERSION_FILENAME=./.pi.bootstrap.sh.done
if [[ -f ${VERSION_FILENAME} ]]; then
  ACTUAL_VERSION=$(head -1 ${VERSION_FILENAME} | tr -d '[:space:]')
else
  ACTUAL_VERSION=0
fi

set -e

if [ "${CURRENT_VERSION}" = "${ACTUAL_VERSION}" ]; then
  echo 'Already installed'
  exit 0
fi

sudo apt-get update

sudo apt-get install -y wiringpi
sudo apt-get install -y cmake
sudo apt-get install -y pigpio
#sudo apt-get install python-pigpio python3-pigpio

sudo apt install -y python3-gpiozero

sudo apt-get install -y python3-pip
sudo apt-get install -y python3-setuptools

touch "${VERSION_FILENAME}"
echo "${CURRENT_VERSION}" >"${VERSION_FILENAME}"
