#!/bin/bash

echo -e "\n\tinstall docker\n"
sudo apt-get update
sudo apt-get remove docker docker-engine docker.io
sudo apt install docker.io
sudo systemctl start docker
sudo systemctl enable docker
docker --version

echo -e "\n\n\tinstall docker-compose\n"
sudo apt-get remove docker-compose
VERSION=$(curl --silent https://api.github.com/repos/docker/compose/releases/latest | jq .name -r)
DESTINATION=/usr/local/bin/docker-compose
sudo curl -L https://github.com/docker/compose/releases/download/${VERSION}/docker-compose-$(uname -s)-$(uname -m) -o $DESTINATION
sudo chmod +x $DESTINATION
docker-compose --version

echo -e "\n\n\tbuild and run cdash-docker\n"
cd ~/
git clone https://github.com/Kitware/CDash.git
cd CDash
sudo docker-compose up -d
