if [ -z "$1" ];
then

echo "Must Choose Project Name"

else
  if [ ! -d "STM32F767_$1" ];
  then
    cp -r "template"/ "STM32F767_$1"/
  else
    echo "Project Exists! Project Was Not Created. Try Another Project Name"
  fi
fi
