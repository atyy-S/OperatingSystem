#!/bin/bash

#Log file 
LOGFILE="script.log"

log(){
    echo "[$(date '+%Y-%m-%d %H-%M-%S')] $1" | tee -a "$LOGFILE"
}

log "Started" 

#create main directory wih the current time dan date

Main_dir=$(date +"%Y-%m-%d_ %H-%M-%S")
mkdir "$Main_dir"
log "Create main directory: $Main_dir"

#Add list of 10 programming languages
languages=("Java" "Python" "C" "C++" "JavaScript" "CSS" "HTML" "Kotlin" "Go" "Swift")

#make subdirectory-- LOOP them 
for i in {101..110}; do 
    subdirectory="$Main_dir/files$i"
    mkdir "$subdirectory"
    log "Subdirectory created: $subdirectory" 

#make file.txt-- LOOP em
    for j in {501..510}; do 
        file="$subdirectory/tuser$j.txt"    
        index=$((j-501))    
        echo "${languages[$index]}" > "$file" 
        log "file created: $file"
    done
done

log "Done?"
