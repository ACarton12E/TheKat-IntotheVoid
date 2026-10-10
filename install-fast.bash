#!/usr/bin/env bash

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
CIAN='\033[0;36m'
BROWN='\033[0;33m'
YELLOW='\033[1;33m'
WHITE='\033[1;37m'
NULLC='\033[0m'
BLACK='\033[0;30m'



show_loading() {
    local pid=$1
    local delay=0.1
    local spinstr='|/-\'
    
    while kill -0 "$pid" 2>/dev/null; do
        if [ -s "build/compiler.log" ]; then
            while IFS= read -r line; do
                echo -e "$line"
            done < build/compiler.log
            > build/compiler.log
        fi

        local temp=${spinstr#?}
        printf "\r [%c] Cooking... " "$spinstr"
        spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        printf "\r"
    done
    printf "\r\033[K"
}

GXXVERSION=$(g++ -dumpfullversion)

show_header() {
    clear
    echo ""
    echo -e "${CIAN}⊃⊰⊰──∼∼∼──⊱⊱⊂ ${WHITE}The Katros 0.1a bedul ${CIAN}⊃⊰⊰──∼∼∼──⊱⊱⊂${NULLC}"
    echo -e "g++ version: ${WHITE}$GXXVERSION${NULLC}"
    echo ""
}


CPU=" 
  ${YELLOW}░░  ░░  ░░  ░░       
  ${WHITE}▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒${YELLOW}░░   
░░${WHITE}▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒     
  ▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒${YELLOW}░░${GREEN}███
${YELLOW}░░${WHITE}▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓${GREEN}████  
  ${WHITE}▒▓▓▓▓▓▓▓▓▓▓▓▓${GREEN}████${YELLOW}░   
░░${WHITE}▒▓▓▓▓▓▓▓▓▓▓▓${GREEN}███${WHITE}▒     
  ${WHITE}▒▓▓${GREEN}███${WHITE}▓▓▓▓${GREEN}████${WHITE}▓▒${YELLOW}░░   
░░${WHITE}▒▓▓▓${GREEN}████${WHITE}▓${GREEN}████${WHITE}▓▓▒     
  ${WHITE}▒▓▓▓▓${GREEN}███████${WHITE}▓▓▓▒${YELLOW}░░   
░░${WHITE}▒▓▓▓▓▓▓${GREEN}████${WHITE}▓▓▓▓▒     
  ${WHITE}▒▒▒▒▒▒▒▒${GREEN}███${WHITE}▒▒▒▒▒${YELLOW}░░   
    ░░  ░░ ${GREEN}█${YELLOW}░░  ░░ ${NULLC}    
"



clear

echo ""
echo -e "${CIAN}⊃⊰⊰──∼∼∼──⊱⊱⊂ ${WHITE}The Katros 0.1a bedul ${CIAN}⊃⊰⊰──∼∼∼──⊱⊱⊂${NULLC}"

# --- THE KATROS ASCII ART ---
echo -e "              ┌──┐    ┌──┐              "
echo -e "                                        "
echo -e "              ${YELLOW}▒${WHITE}██      ██${YELLOW}▒${NULLC}              "
echo -e "         ${YELLOW}▒  ▒▒${WHITE}█████   ████${YELLOW}▒▒  ▒${NULLC}         "
echo -e "        ${YELLOW}▒▒ ▒▒${WHITE}██████  ██████${YELLOW}▒▒ ▒▒${NULLC}        "
echo -e "      ${YELLOW}▒▒▒  ${BROWN}░░${NULLC}▓▓${YELLOW}▒▒${BROWN}░░░░░░${YELLOW}▒▒${NULLC}▓▓${BROWN}░░  ${YELLOW}▒▒▒${NULLC}      "
echo -e "      ${YELLOW}▒▒▒▒▒▒▒▒▒${NULLC}${BLUE}███${BROWN}░░░░${BLUE}███${YELLOW}▒▒▒▒▒▒▒▒▒${NULLC}      "
echo -e "     ${YELLOW}▒▒▒▒▒▒▒▒${NULLC}${BLUE}████0█${BROWN}░░${BLUE}█0████${YELLOW}▒▒▒▒▒▒▒▒${BROWN}     "
echo -e "     ${BROWN}░░${YELLOW}▒▒▒▒${NULLC}${BLUE}███▞▞█0█${BROWN}░░${BLUE}█0█▞▞███${YELLOW}▒▒▒▒${BROWN}░░     "
echo -e "     ${BROWN}░░░░░${BLUE}███████0█${BROWN}░░${BLUE}█0███████${BROWN}░░░░░     "
echo -e "      ${BROWN}░░░░${BLUE}█████${WHITE}▓▓▓▓▓▓▓▓▓▓${BLUE}█████${BROWN}░░░░      "
echo -e "        ${BROWN}░░${BLUE}████${WHITE}▓▓▓▓▓▓▓▓▓▓▓▓${BLUE}████${BROWN}░░        "
echo -e "     ${YELLOW}▒${BROWN}░   ░${BLUE}█${WHITE}▓▓▓▓▓▓▓${BLACK}██${WHITE}▓▓▓▓▓▓▓${NULLC}${BLUE}█${BROWN}░   ░${YELLOW}▒${NULLC}     "
echo -e "     ${YELLOW}▒▒${BROWN}░░░░░${WHITE}▓▓▓${BLACK}██████████${WHITE}▓▓▓${BROWN}░░░░░${YELLOW}▒▒${NULLC}     "
echo -e "       ${YELLOW}▒▒▒▒▒▒▒${WHITE}▓▓▓▓▓▓▓▓▓▓▓▓${YELLOW}▒▒▒▒▒▒▒${NULLC}       "
echo -e "          ${YELLOW}▒▒▒▒▒${WHITE}▓▓▓▓▓▓▓▓▓▓${YELLOW}▒▒▒▒▒${NULLC}          "
echo -e "                                        "

echo ""
echo -e "g++ version: ${WHITE}$GXXVERSION${NULLC}"


DEVICE=""
ARCHITECTURE=""
OPEN="true"
RESULT=1

while [ $# -gt 0 ]; do
  case "$1" in
    --ARCHITECTURE=*)
      ARCHITECTURE="${1#*=}"
      ;;
    --DEVICE=*)
      DEVICE="${1#*=}"
      ;;
    --OPEN=*)
      OPEN="${1#*=}"
      ;;
    *)
      echo "...What?: $1"
      exit 1
      ;;
  esac
  shift
done

mkdir -p build

if [ -z "$ARCHITECTURE" ] || [ -z "$DEVICE" ]; then
    echo "
    Hold on, use --DEVICE and --ARCHITECTURE to specify where you want to compile it.

    - Devices: windows, linux
    - Architecture: x86_64, x86

    (if you want it to run immediately after compiling, include -OPEN=\"y\" to execute it)

    "
else

    if [ "$ARCHITECTURE" = "x86_64" ] ; then 
        if [ "$DEVICE" = "linux" ]; then
            mkdir -p build/linux/x86_64
            g++ -v $(find src -type f -name "*.cpp") -O2 -o build/linux/x86_64/TheKatITV -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer &
                    
            show_loading $!

            wait $!
            RESULT=$?

            if [ $RESULT -eq 0 ]; then
                cp -r src/assets build/linux/x86_64/
            fi
        elif [ "$DEVICE" = "windows" ]; then
            mkdir -p build/windows/x86_64
            x86_64-w64-mingw32-g++ -v $(find src -type f -name "*.cpp") -O2 -o build/windows/x86_64/TheKatITV.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -static-libgcc -static-libstdc++ &
                    
            show_loading $!

            wait $!
            RESULT=$?

            if [ $RESULT -eq 0 ]; then
                cp lib/Windows/*.dll build/windows/x86_64/
                cp -r src/assets build/windows/x86_64/
            fi
        fi
    elif [ "$ARCHITECTURE" = "x86" ]; then 
        if [ "$DEVICE" = "linux" ]; then
            mkdir -p build/linux/x86
            g++ -v $(find src -type f -name "*.cpp") -O2 -o build/linux/x86/TheKatITV -m32 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer &
                    
            show_loading $!

            wait $!
            RESULT=$?

            if [ $RESULT -eq 0 ]; then
                cp -r src/assets build/linux/x86/
            fi
        elif [ "$DEVICE" = "windows" ]; then
            mkdir -p build/windows/x86
            i686-w64-mingw32-g++ -v $(find src -type f -name "*.cpp") -O2 -o build/windows/x86/TheKatITV.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -static-libgcc -static-libstdc++ &
                    
            show_loading $!

            wait $!
            RESULT=$?

            if [ $RESULT -eq 0 ]; then
                cp lib/Windows/*.dll build/windows/x86/
                cp -r src/assets build/windows/x86/
            fi
        fi
    fi

    if [ $RESULT -eq 0 ]; then
        show_header
        echo -e "$CPU"
        echo ""
        echo -e "${GREEN}Boom! Now throw in some onion and get cooking!${NULLC}"

        if [ "$DEVICE" = "linux" ]; then
            echo "
                    HOLD ON!!! It's recommended to convert your build into an 
                AppImage to make distribution easier or if you just want it for 
                local use, then no worries. But if you do want to distribute that 
                    binary, you'd better get it ready... or wait, I can 
                        convert it to an AppImage for you want me to?
                    (I might not have actually done it yet, though, hehehe.)
            "

            if [ "$OPEN" = "y" ]; then
                ./build/$DEVICE/$ARCHITECTURE/TheKatITV
            fi
        elif [ "$DEVICE" = "windows" ]; then
            echo "
                HOLD ON A SEC!!! It's recommended to convert your build into a 
                ZIP file to make distribution easier—though if you're keeping 
                it local, then no worries. But if you *do* want to distribute 
                that .exe, you might want to package it up... or wait, I can 
                            convert it to a ZIP for you—want me to? 
                        (I might not have actually done it yet, heh heh).
            "

            if [ "$OPEN" = "y" ]; then
                wine ./build/$DEVICE/$ARCHITECTURE/TheKatITV.exe
            fi
        fi

        echo ""
    else
        echo ""
        if [ "$DEVICE" != "linux" ] && [ "$DEVICE" != "windows" ] && [ "$ARCHITECTURE" != "x86_64" ] && [ "$ARCHITECTURE" != "x86" ]; then
            echo -e "Huh? Well, a little problem... um... did you mean in DEVICE 'linux' or 'windows' and in ARCHITECTURE 'x86_64' or 'x86'?"
        elif [ "$DEVICE" != "linux" ] && [ "$DEVICE" != "windows" ]; then
            echo -e "Huh? Well, a little problem... um... did you mean in DEVICE 'linux' or 'windows'?"
        elif [ "$ARCHITECTURE" != "x86_64" ] && [ "$ARCHITECTURE" != "x86" ]; then
            echo -e "Huh? Well, a little problem... um... did you mean in ARCHITECTURE 'x86_64' or 'x86'?"
        fi
        echo ""
        exit 1
    fi   
fi