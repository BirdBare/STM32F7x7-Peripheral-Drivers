if [ -z $1 ]
then
  
  echo "Must Choose Filename!"

else
  
  val=$(echo "$1" | tr '[:lower:]' '[:upper:]')
  if [ ! -f "STM32F767_${val}.c" ]
  then
    echo "//
//
//
//
//



#include \"STM32F767_$val.h\"











" > STM32F767_$val.c
  else

    echo "C Source File Exists! Not Created. Choose New Source Name"
  
  fi
fi
