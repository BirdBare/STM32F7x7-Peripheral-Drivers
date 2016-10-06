if [ -z $1 ]
then
  
  echo "Must Choose Filename!"

else
  
  val=$(echo "$1" | tr '[:lower:]' '[:upper:]')
  if [ ! -f "STM32F767_$val.h" ]
  then
    echo "//
//
//
//
//



#ifndef STM32F767_${val}_H
#define STM32F767_${val}_H

#include \"stm32f7xx.h\"
//#include \"STM32F767_xxx.h\"









#endif" > STM32F767_$val.h
  else

    echo "C Header File Exists! Not Created. Choose New Header Name"
  
  fi
fi
