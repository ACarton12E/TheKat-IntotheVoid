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
echo -e "g++ version: ${WHITE}$GXXVERSION${NULLC}... I have ${RED}2 ${BLUE}pills${NULLC}..."
echo ""

DEVICE=""
ARCHITECTURE=""

while true; do
    echo "1) Linux"
    echo "2) Windows"
    echo ""
    echo "Choose wisely... or simply select your device :|"

    echo ""
    read -p "Come on... choose: " option

    case "$option" in
        1)
            show_header

            # --- TUX ASCII ART ---
            echo -e "     ${BLACK}▒▒▒▒▒▒${NULLC}     "
            echo -e "    ${BLACK}▒${WHITE}██${BLACK}▒▒${WHITE}██${BLACK}▒    "
            echo -e "    ${BLACK}▒${WHITE}█${BLACK}▓▒▒▓${WHITE}█${BLACK}▒    "
            echo -e "    ${BLACK}▒${WHITE}█${YELLOW}████${WHITE}█${BLACK}▒${NULLC}    "
            echo -e "   ${BLACK}▒▒▒▒${YELLOW}██${BLACK}▒▒▒▒${NULLC}   "
            echo -e " ${BLACK}░▒▒${WHITE}▓▓▓▓▓▓▓▓${BLACK}▒▒░${NULLC} "
            echo -e "${BLACK}░▒${WHITE}▓▓▓▓▓▓▓▓▓▓▓▓${BLACK}▒░${NULLC}"
            echo -e "${BLACK}░${YELLOW}██${WHITE}▓${YELLOW}██${WHITE}▓▓▓▓${YELLOW}██${WHITE}▓${YELLOW}██${BLACK}░${NULLC}"
            echo -e "${YELLOW}███████${WHITE}▓▓${YELLOW}███████${NULLC}"
            echo -e " ${YELLOW}██████${WHITE}▓▓${YELLOW}██████${NULLC} "
            echo -e "  ${YELLOW}█████${BLACK}▒▒${YELLOW}█████${NULLC}"
            echo ""

            echo "Linux? Wow, good choice."
            DEVICE="linux"
            break
            ;;
        2)
            show_header
            echo -e "${CIAN} 
 █████ ██████████ 
██████ ███████████
▀▀▀▀▀▀ ███████████
██████ ███████████
██████ ▀▀▀▀▀▀▀▀▀▀▀
██████ ███████████
 █████ ██████████ 
            ${NULLC}
            "
            echo "Windows?... Open the windows! A little more work."
            DEVICE="windows"
            break
            ;;
        *)
            show_header
            echo ""
            echo "Come on! Select one."
            echo ""
            ;;
    esac
done


echo "Alright! $DEVICE was selected—let's get to work! ...Wait, what architecture are you going to use?"

while true; do
    if [ "$DEVICE" = "linux" ]; then
        echo "1) x86_64"
        echo "2) x86"
        echo "(Soon) ARM64 (armv8)"

        read -p "Okay! I'll be waiting: " archlinux

        case "$archlinux" in
            1) 
                show_header
                echo -e "$CPU"
                echo ""
                echo "The classic! x86_64!"
                ARCHITECTURE="x86_64"
                break
                ;;
            2) 
                show_header
                echo -e "$CPU"
                echo ""
                echo "Wow, a toaster? Well, x86."
                ARCHITECTURE="x86"
                break
                ;;
            ##3) 
                #clear
                #echo -e "$CPU"
                #echo ""
                #echo "Hmm, Raspberry? PinePhone?... I don't know."
                #ARCHITECTURE="ARMv8"
                #break
                #;;
            *)
                show_header
                echo -e "$CPU"
                echo ""
                echo "Huh? Did you fall asleep?"
                echo ""
                ;;
        esac
    elif [ "$DEVICE" = "windows" ]; then
        echo "1) x86_64"
        echo "2) x86"

        read -p "Okay! I'll be waiting: " archwindows

        case "$archwindows" in
            1)  
                show_header
                echo -e "$CPU"
                echo ""
                echo "The classic! x86_64!"
                ARCHITECTURE="x86_64"
                break
                ;;
            2)
                show_header
                echo -e "$CPU"
                echo ""
                echo "Wow, a toaster? Well, x86."
                ARCHITECTURE="x86"
                break
                ;;
            x) 
                if command -v cmatrix >/dev/null 2>&1; then
                    cmatrix 
                    show_header
                    echo -e "$CPU"
                    echo ""
                    echo "hehehe, Easter Egg!!"
                else
                    show_header
                fi
                echo ""
                ;;
            *)
                show_header
                echo -e "$CPU"
                echo ""
                echo "Huh? Did you fall asleep?"
                echo ""
                ;;
        esac
    fi
done


echo "Are you sure? Here is the data: arch $ARCHITECTURE, device $DEVICE"
read -p "[Y/n] " confirm

confirm=$(echo "$confirm" | tr '[:upper:]' '[:lower:]')

case "$confirm" in
    y|"")
        show_header
        mkdir -p build
        echo ""
        echo "Let's go! Get your tomato sauce ready; I'm going to compile now... just a sec..."
        echo ""

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
            echo -e "${GREEN}Boom! Now throw in some onion and get cooking!${NULLC} Do you want to open it and try it out right now?"

            if [ "$DEVICE" = "linux" ]; then
                echo "
                       HOLD ON!!! It's recommended to convert your build into an 
                    AppImage to make distribution easier or if you just want it for 
                    local use, then no worries. But if you do want to distribute that 
                        binary, you'd better get it ready... or wait, I can 
                            convert it to an AppImage for you want me to?
                        (I might not have actually done it yet, though, hehehe.)
                "
            elif [ "$DEVICE" = "windows" ]; then
                echo "
                    HOLD ON A SEC!!! It's recommended to convert your build into a 
                    ZIP file to make distribution easier—though if you're keeping 
                    it local, then no worries. But if you *do* want to distribute 
                    that .exe, you might want to package it up... or wait, I can 
                                convert it to a ZIP for you—want me to? 
                           (I might not have actually done it yet, heh heh).
                "
            fi

            echo ""
        else
            echo ""
            echo -e "Huh? Well, a little problem... um... I don't know, ${RED}sorry :(${NULLC}"
            echo ""
            exit 1
        fi
        ;;
    n)
        clear
        echo -e "Oh, okay :( See you soon."
        exit 1
        ;;
    *)
        clear
        echo -e "${RED}Huh? PANIC!! AHHH!"
        exit 1
        ;;
esac

read -p "Open? [y/N]: " open

case "$open" in
    n|"")
        exit 1
        ;;
    y)
        echo -e "${GREEN}Opening!...${NULLC}"
        if [ "$DEVICE" = "linux" ]; then
            ./build/$DEVICE/$ARCHITECTURE/TheKatITV
        elif [ "$DEVICE" = "windows" ]; then
            wine ./build/$DEVICE/$ARCHITECTURE/TheKatITV.exe
        fi
        ;;  
    *)
        exit 1
esac