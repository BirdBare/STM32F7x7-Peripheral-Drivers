if [ -z "$1" ];
then

echo "Must Choose Project Name"

else
  if [ ! -d "STM32F767_$1" ];
  then

    cp -r "template"/ "STM32F767_$1"/
    git init "STM32F767_$1"
    echo -e "Debug\nObject\ Files\nmain.bin\nmain.elf" >> "STM32F767_$1"/.gitignore
  
  else
    
    echo "Project Exists! Project Was Not Created. Try Another Project Name"
  
  fi
fi
