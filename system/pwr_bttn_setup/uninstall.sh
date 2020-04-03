
#! /bin/sh

# from Howchoo/pi-power-button

set -e

cd "$(dirname "$0")/.."

echo "=> Stopping shutdown listener...\n"
sudo update-rc.d listen-for-shutdown.sh remove
sudo /etc/init.d/listen-for-shutdown.sh stop

echo "=> Removing shutdown listener...\n"
sudo rm -rf /usr/local/bin/listen-for-shutdown.py 
sudo rm -rf /etc/init.d/listen-for-shutdown.sh 

echo "Shutdown listener uninstalled.\n"
