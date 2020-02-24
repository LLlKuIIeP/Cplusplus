#!/bin/bash

sudo apt-get update
sudo apt-get install nginx -y

sudo ufw app list
sudo ufw allow 'Nginx HTTP'
sudo ufw status

#systemctl status nginx

sudo mkdir -p /var/www/doxygen
sudo chown -R $USER:$USER /var/www/doxygen
sudo chmod a+rwx -R /var/www/doxygen

local_ip=ifconfig | grep -o "inet [0-9]*\.[0-9]*\.[0-9]*\.[0-9]*" | grep -o "[0-9]*\.[0-9]*\.[0-9]*\.[0-9]*" | head -n1

sudo touch /etc/nginx/sites-available/doxygen
sudo chmod a+rw /etc/nginx/sites-available/doxygen

local_ip=`ifconfig | grep -o "inet [0-9]*\.[0-9]*\.[0-9]*\.[0-9]*" | grep -o "[0-9]*\.[0-9]*\.[0-9]*\.[0-9]*" | head -n1`
sudo echo -e "#log_format simple '\$remote_addr \$request \$status';\n" > /etc/nginx/sites-available/doxygen
sudo echo -e "server {\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\tlisten 80;\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\tlisten [::]:80;\n\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\tindex index.html index.htm index.nginx-debian.html;\n\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\tserver_name $local_ip;\n\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\t#error_log /var/log/nginx/error.log info;\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\t#access_log /var/log/nginx/access.log simple;\n\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\tlocation /doxygen {\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\t\t#access_log /var/log/nginx/access.log simple;\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\t\troot /var/www;\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\t\tindex index.html index.htm;\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\t\ttry_files \$uri \$uri/ =404;\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "\t}\n" >> /etc/nginx/sites-available/doxygen
sudo echo -e "}\n" >> /etc/nginx/sites-available/doxygen

sudo ln -s /etc/nginx/sites-available/doxygen /etc/nginx/sites-enabled/

sudo nginx -t

sudo systemctl restart nginx

sudo mkdir /var/www/doxygen/peaq/
sudo touch /var/www/doxygen/peaq/index.html
sudo chmod a+rwx -R /var/www/doxygen

sudo echo -e "<h1>\nHello peaq\n</h1>" > /var/www/doxygen/peaq/index.html
