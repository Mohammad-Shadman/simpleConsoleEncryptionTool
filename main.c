#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct m_str{
    char* str;
    int len;
}m_str;

//uses xor encryption
void decrypt_encrypt(m_str* buff, m_str key){
    for(int i = 0; i < buff->len; i++){
        for (int j = 0; j < key.len; j++){
            buff->str[i] = (buff->str[i]^key.str[j]);
        }
    }
}


//gets everything from a file with unknown size and places it into a buffer
m_str parser(FILE* filePtr){
    int buffSize = 1024;
    char* buff = malloc(buffSize*sizeof(char));
    int len = 0;
    int n;
    do{
        n = fread(buff+len, sizeof(char), buffSize-len, filePtr);
        len += n;

        if (len == buffSize) {
            buffSize *= 2;
            buff = realloc(buff, buffSize);
        }
    }while(n!=0);

    return (m_str){buff, len};
}


int main(int argc, char** argv) {
    
    //check if the args are good and displays help otherwise
    if(argc < 5 || argc > 6){
        printf("Proper use:\n"
               "Input the file to encrypt/decrypt, fileToRead \n"
               "The type of key to use(-f file -i input) followed by the key, -i keyInput (or) -f keyFile\n"
               "The output name of the encrypted/decrypted file.\n"
               "*optional*\n"
               "replacement flag (-r) to make it so the check for output file does not go through\n"
               "!!order matters!!\n"
               "Usage:\n"
               "encrypter fileToRead -i keyInput outPutFile\nor\n"
               "encrypter fileToRead -f keyFile outPutFile\nor\n"
               "encrypter fileToRead -f keyFile fileToRead -r\nor\n"

              );
        return 0;
    }
    //if the -r flag is set and is it done properly
    if(argc == 6 && argv[5][1]!='r'){
        printf("\"%s\" replace flag(-r) not set properly\n",argv[5]);
        exit(6);

    }

    // test to see if the out file already exists and if so, checks if the user intends to overwrite the file with the decrypted/encrypted data
    FILE *outFileTesterPtr = fopen(argv[4],"r");
    if(outFileTesterPtr != NULL && argc != 6){
        printf("\"%s\" already exists and replace flag(-r) not set to replace the file, use another name or delete the file and retry\n",argv[4]);
        exit(5);

    }
    fclose(outFileTesterPtr);

    //starts opening and parsing data from here
    FILE *filePtr = fopen(argv[1],"r");
    if(filePtr == NULL){
        printf("\"%s\" does not already exists, recheck the name of the file and retry\n",argv[1]);
        exit(1);
    }
    

    m_str key;
    int needFreeBool = 0;

    if(argv[2][1] == 'f'){
        FILE *keyFile = fopen(argv[3],"r");
    
        if(keyFile == NULL){
            printf("\"%s\" is an invalid file, recheck the name of the file and ensure it's existance, then retry\n",argv[3]);
            exit(2);
        }

        key = parser(keyFile);
        fclose(keyFile);
        needFreeBool = 1;
    }
    else if(argv[2][1] == 'i'){
        
        key = (m_str){argv[3],strlen(argv[3])};
    }
    else{
        printf("\"%s\" is not a valid key type: -f , -i\n",argv[2]);
        exit(2);
    }
    if (key.len % 2 == 0 && key.len >= 2){
        key.str[0]+=key.str[key.len-1];
    }

    
    m_str buff = parser(filePtr);
    fclose(filePtr);


    //actual decryption/encryption
    decrypt_encrypt(&buff,key);
    
    //send to outputfile
    FILE *outFilePtr = fopen(argv[4],"w");
        
    fwrite(buff.str, sizeof(char), buff.len, outFilePtr);
    
    //free if was dynamically allocated
    if (needFreeBool){
        free(key.str);
    }
    
    free(buff.str);
    
    fclose(outFilePtr);

    

    return 0;
}