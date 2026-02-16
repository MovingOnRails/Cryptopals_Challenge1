#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// https://en.wikipedia.org/wiki/Base64

char* hexString = NULL;
int main(int argc,char* argv[]){
    //printf("%s", argv[1]);
    if(argc < 2){
        printf("Must pass one argument\n");
        exit(EXIT_SUCCESS);
    }

    uint8_t dictionaryHexToRaw[128] = {
        ['0'] = 0,
        ['1'] = 1,
        ['2'] = 2,
        ['3'] = 3,
        ['4'] = 4,
        ['5'] = 5,
        ['6'] = 6,
        ['7'] = 7,
        ['8'] = 8,
        ['9'] = 9,
        ['a'] = 10,
        ['b'] = 11,
        ['c'] = 12,
        ['d'] = 13,
        ['e'] = 14,
        ['f'] = 15
    };

    uint8_t dictionaryRawToBase64[64] = {
        [0] = 'A',
        [1] = 'B',
        [2] = 'C',
        [3] = 'D',
        [4] = 'E',
        [5] = 'F',
        [6] = 'G',
        [7] = 'H',
        [8] = 'I',
        [9] = 'J',
        [10] = 'K',
        [11] = 'L',
        [12] = 'M',
        [13] = 'N',
        [14] = 'O',
        [15] = 'P',
        [16] = 'Q',
        [17] = 'R',
        [18] = 'S',
        [19] = 'T',
        [20] = 'U',
        [21] = 'V',
        [22] = 'W',
        [23] = 'X',
        [24] = 'Y',
        [25] = 'Z',
        [26] = 'a',
        [27] = 'b',
        [28] = 'c',
        [29] = 'd',
        [30] = 'e',
        [31] = 'f',
        [32] = 'g',
        [33] = 'h',
        [34] = 'i',
        [35] = 'j',
        [36] = 'k',
        [37] = 'l',
        [38] = 'm',
        [39] = 'n',
        [40] = 'o',
        [41] = 'p',
        [42] = 'q',
        [43] = 'r',
        [44] = 's',
        [45] = 't',
        [46] = 'u',
        [47] = 'v',
        [48] = 'w',
        [49] = 'x',
        [50] = 'y',
        [51] = 'z',
        [52] = '0',
        [53] = '1',
        [54] = '2',
        [55] = '3',
        [56] = '4',
        [57] = '5',
        [58] = '6',
        [59] = '7',
        [60] = '8',
        [61] = '9',
        [62] = '+',
        [63] = '/',

    };

    hexString = argv[1];
    int base64StringLength = 0;
    /*for(int i=0; hexString[i] != NULL; i+=6){
        base64StringLength+= 4;
    }*/
   for(int i =0; hexString[i] != NULL; i+=3){
        if(hexString[i] == NULL){
            break;
        } else if(hexString[i+1] == NULL || hexString[i+2] == NULL){
            base64StringLength += 4;
            break;
        } else {
            base64StringLength += 4;
        }
    }
    printf("base64StringLength = %i\n",base64StringLength);

    int currentHexStringIndex = 0;
    int currentBase64StringIndex = 0;
    
    char firstChar = 0;
    char secondChar = 0;
    char thirdChar = 0;

    char firstHex = hexString[0];
    char secondHex = 0;
    char thirdHex = 0;
    char fourthHex = 0;
    char fifthHex = 0;
    char sixthHex = 0;

    char firstRaw = 0;
    char secondRaw = 0;
    char thirdRaw = 0;
    char fourthRaw = 0;
    char fifthRaw = 0;
    char sixthRaw = 0;

    char base64String[base64StringLength+1];
    base64String[base64StringLength] = NULL;

    uint8_t index = 0;

    while(true){
        firstChar = hexString[currentHexStringIndex];
        if(firstChar == NULL){
            break;
        }
        currentHexStringIndex++;
        secondChar = hexString[currentHexStringIndex];
        if(secondChar == NULL){
            index = (firstChar >> 2);
            base64String[currentBase64StringIndex] = dictionaryRawToBase64[(firstChar >> 2)];
            currentBase64StringIndex++;

            index = ((firstChar & 0b00000011) << 4) | (secondChar >> 4);
            base64String[currentBase64StringIndex] = dictionaryRawToBase64[index];
            currentBase64StringIndex++;

            base64String[currentBase64StringIndex] = '=';
            currentBase64StringIndex++;

            base64String[currentBase64StringIndex] = '=';
            break;
        }
        currentHexStringIndex++;
        thirdChar = hexString[currentHexStringIndex];
        if(thirdChar == NULL){
            index = (firstChar >> 2);
            base64String[currentBase64StringIndex] = dictionaryRawToBase64[(firstChar >> 2)];
            currentBase64StringIndex++;

            index = ((firstChar & 0b00000011) << 4) | (secondChar >> 4);
            base64String[currentBase64StringIndex] = dictionaryRawToBase64[index];
            currentBase64StringIndex++;

            index = ((secondChar & 0b00001111) << 2) | (thirdChar >> 6);
            base64String[currentBase64StringIndex] = dictionaryRawToBase64[index];
            currentBase64StringIndex++;

            base64String[currentBase64StringIndex] = '=';
            break;
        }
        index = (firstChar >> 2);
        base64String[currentBase64StringIndex] = dictionaryRawToBase64[(firstChar >> 2)];
        currentBase64StringIndex++;

        index = ((firstChar & 0b00000011) << 4) | (secondChar >> 4);
        base64String[currentBase64StringIndex] = dictionaryRawToBase64[index];
        currentBase64StringIndex++;
        
        index = ((secondChar & 0b00001111) << 2) | (thirdChar >> 6);
        base64String[currentBase64StringIndex] = dictionaryRawToBase64[index];
        currentBase64StringIndex++;

        index = (thirdChar & 0b00111111);
        base64String[currentBase64StringIndex] = dictionaryRawToBase64[index];
        currentBase64StringIndex++;

        currentHexStringIndex++;
    }
    printf("base64String: %s\n", base64String);

}