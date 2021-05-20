#!/bin/bash

if [[ ! -f .env ]]; then
  echo 'ERROR! .env file not found! Clone .env.dist and setup it!'
  exit 1
fi

{
  set -o allexport
  source .env
  set +o allexport
}

set -e

export SSHPASS=${RASPBERRY_PI_PASSWORD}

# passed as env-var
sshpass -e ssh-copy-id -i ~/.ssh/id_rsa.pub -o StrictHostKeyChecking=no ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS}

ssh ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS} mkdir -p /home/${RASPBERRY_PI_LOGIN}/hello-pi

scp -r ./src ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS}:/home/${RASPBERRY_PI_LOGIN}/hello-pi/
scp -r ./bin-pi ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS}:/home/${RASPBERRY_PI_LOGIN}/hello-pi/
scp -r ./Makefile ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS}:/home/${RASPBERRY_PI_LOGIN}/hello-pi/
scp -r ./CMakeLists.txt ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS}:/home/${RASPBERRY_PI_LOGIN}/hello-pi/

ssh ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS} ls -lah /home/${RASPBERRY_PI_LOGIN}/hello-pi

ssh ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS} "cd /home/""${RASPBERRY_PI_LOGIN}""/hello-pi/ && bash bin-pi/bootstrap.sh"
ssh ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS} "cd /home/""${RASPBERRY_PI_LOGIN}""/hello-pi/ && make build"

echo '---------- open terminal to PI, to close - type "exit" and press ENTER ----------'
echo "ssh ${RASPBERRY_PI_LOGIN}@${RASPBERRY_PI_ADDRESS}"
