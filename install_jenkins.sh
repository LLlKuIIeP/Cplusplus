sudo apt-get update
sudo apt-get install openjdk-8-jre -y
java -version
wget -q -O - https://pkg.jenkins.io/debian/jenkins.io.key | sudo apt-key add -
sudo sh -c 'echo deb https://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list'
sudo apt-get update
sudo apt-get install jenkins -y
sudo service jenkins status
sudo cat /var/lib/jenkins/secrets/initialAdminPassword
