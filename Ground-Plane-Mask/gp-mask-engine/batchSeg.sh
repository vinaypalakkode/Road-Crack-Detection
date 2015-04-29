#!/bin/bash

IN=$1
#creating output dir
mkdir out_$1
echo $IN.ppm
for sigma in `seq 1 5 `;
do

  mkdir out_$1/$sigma
  for i in `seq 1 10 `;
        do
       
          
          #var=$((5 +  $i)) 
          

          k=$((100 * $i)) 
          min=$((20 ))

          echo ====================================================
          echo run params: sigma "=" $sigma,  k "=" $k, min "=" $min
          echo generating outputs 
          ./segment $sigma $k $min $IN.ppm out_$1/$sigma/$1_$i.ppm
        
        #echo  out_$1/$sigma/$1_$i.ppm
          echo
          echo ===================================================

       #run the segmentation binary 
        
        done 
      done
