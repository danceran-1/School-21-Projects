#!/bin/bash


yellow='\033[1;33m'        
yellow_bg='\033[43m'       
magenta='\033[1;35m' 
magenta_bg='\033[45m'       
reset='\033[0m'            


echo -e "${yellow_bg} ${reset} ${yellow}Pies${reset} ${magenta_bg} ${reset} ${magenta}Bars${reset}"


termgraph data.txt --color {yellow,magenta}
