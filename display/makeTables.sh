#!/bin/bash\

SRS=( "SR00" "SR01" "SR02" "SR03" "SR04" "SR05" "SR06" "SR07" "SR08" "SR11" "SR12" "SR13" "SR14" "SR15" "SR16" "SR17" "SR18" "SR21" "SR22" "SR23" "SR24" "SR25" "SR26" "SR27" "SR28" "SR31" "SR32" "SR33" "SR34" "SR35" "SR36" "SR37" "SR38" )

PTS=( "high" "low" )
MVAs=( "cut" "mva" )
BTAGs=( "40" "25" "IVF" )

rm cards/tmpFiles/*

for sr in ${SRS[@]}; do

    for im in ${MVAs[@]}; do
	
	mva=$im
	
	for ij in ${BTAGs[@]}; do
	    
	    btag=$ij
	    
	    
	    for ip in ${PTS[@]}; do
		
		pt=$ip
		
		cp cards/tempalteCard.C cards/tmpFiles/susy_${sr}_${pt}_${mva}_${btag}.C
		sed -i 's|SIGNAL|'$sr'|' cards/tmpFiles/susy_${sr}_${pt}_${mva}_${btag}.C
		sed -i 's|PT|'$pt'|' cards/tmpFiles/susy_${sr}_${pt}_${mva}_${btag}.C
		sed -i 's|LEPID|'$mva'|' cards/tmpFiles/susy_${sr}_${pt}_${mva}_${btag}.C
		sed -i 's|BTAG|'$btag'|' cards/tmpFiles/susy_${sr}_${pt}_${mva}_${btag}.C
	
#		root cards/tmpFiles/susy_${sr}_${pt}_${mva}_${btag}.C > /shome/mmarionn/MPAF/workdir/logs/susy_${sr}_${pt}_${mva}_${btag}.log
		qsub -q all.q -N Display_${sr}_${pt}_${mva}_${btag}  -o /shome/mmarionn/MPAF/workdir/logs/log.out -e /shome/mmarionn/MPAF/workdir/logs/log.err /shome/mmarionn/MPAF/display/submit.sh susy_${sr}_${pt}_${mva}_${btag}

	    done

	done
    done

done
