CHANGE_DIR()
{
cd $1
}

if [ -z $1 ]
then
  
  echo "Must Choose Filename!"

else
  
  val=$(echo "$1" | tr '[:lower:]' '[:upper:]')
  if [ ! -f "STM32F767_$val.s" ]
  then
    echo "//
//
//
//
//

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

    .section .xxx.xxx


  .type xxx, %function
  .global xxx












" > STM32F767_$val.s
    if [ -d "../inc" ]
    then
      CHANGE_DIR ../inc
      inc.sh $val
    fi
  else

    echo "Assembly File Exists! Not Created. Choose New Assembly Name"
  
  fi
fi
