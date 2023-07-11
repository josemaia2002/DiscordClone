DIR=~
cd $DIR/.local/share/applications
touch DiscordClone.desktop
chmod +x DiscordClone.desktop
echo "[Desktop Entry]" >> DiscordClone.desktop
echo "Name=DiscordClone" >> DiscordClone.desktop
echo "Type=Application" >> DiscordClone.desktop  
echo "Terminal=true" >> DiscordClone.desktop
echo "Exec=sh $DIR/Documents/LPI/DiscordClone/run.sh" >> DiscordClone.desktop  
echo "Icon=$DIR/Documents/LPI/DiscordClone/data/img/pirate.svg" >> DiscordClone.desktop  
