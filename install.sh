#!/bin/bash

INPUT=`cmake --version`
SUBSTRING=$(echo $INPUT| cut -d' ' -f 3)

echo "cmake_minimum_required(VERSION $SUBSTRING)"
CMAKE_VERSION="cmake_minimum_required(VERSION $SUBSTRING)"
	
lineNo=1
sed -i "${lineNo}s/.*/$CMAKE_VERSION/" CMakeLists.txt



DIR=`pwd`/build
if [ -d "$DIR" ]; then
	cd build
        cmake --build .
    	cd .. 
else
	mkdir build
    	cd build
    	cmake ..
    	cmake --build .
    	cd ..   	       
fi

FILE=`pwd`/run.sh
if [ -f "$FILE" ]; then
        echo "Already installed!"
else		
	touch run.sh
      	chmod +x run.sh
    	echo "#!/bin/bash" >> run.sh
    	echo "cd $DIR" >> run.sh
    	echo "./program" >> run.sh      
    	
    	echo "Finishing the installation"
    	sleep 1 
	
	echo -ne '###                       [10%]\r'
	sleep 1
	echo -ne '#####                     [20%]\r'
	sleep 1
	echo -ne '########                  [30%]\r'
	sleep 1
	echo -ne '############              [40%]\r'
	sleep 1
	echo -ne '###############           [50%]\r'
	sleep 1
	echo -ne '##################        [60%]\r'
	sleep 1
	echo -ne '####################      [70%]\r'
	sleep 1
	echo -ne '######################    [80%]\r'
	sleep 1
	echo -ne '########################  [90%]\r'
	sleep 1
	echo -ne '##########################[100%]\r'
	echo -ne '\n'

	echo "DiscordCLone3.1 installed"
fi


DIR_ENTRY=~
DIR_ROOT=`pwd`
cd $DIR_ENTRY/.local/share/applications
touch DiscordClone.desktop
chmod +x DiscordClone.desktop
echo "[Desktop Entry]" >> DiscordClone.desktop
echo "Name=DiscordClone" >> DiscordClone.desktop
echo "Type=Application" >> DiscordClone.desktop  
echo "Terminal=true" >> DiscordClone.desktop
echo "Exec=sh $DIR_ROOT/run.sh" >> DiscordClone.desktop  
echo "Icon=$DIR_ROOT/data/img/pirate.svg" >> DiscordClone.desktop






