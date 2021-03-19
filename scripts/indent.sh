#! /bin/bash

echo "Hello"

files=$(ls -R ../ | awk '/:$/&&f{s=$0;f=0}/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}NF&&f{ print s"/"$0 }')
for file in $files; do\
  if [ -d $file ] 
  then 
    echo "This is a directory";
  else
    if [[ $file == *.c ]]
    then
      echo "This is a c file";
      vim -s indent_file $file
    fi
    #if [[ $file == *.cpp ]]
    #then
      #echo "This is a cpp file";
      #vim -s indent_file $file
    #fi
    #if [[ $file == *.h ]]
    #then
      #echo "This is a h file";
      #vim -s indent_file $file
    #fi

    #if [[ $file == *.hpp ]]
    #then
      #echo "This is a hpp file";
      #vim -s indent_file $file
    #fi
  fi
done

