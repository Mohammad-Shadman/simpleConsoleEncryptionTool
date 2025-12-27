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
    //int n = fread(buff, sizeof(char),buffSize,filePtr);
    int n;
    do{
        n = fread(buff+len, sizeof(char), buffSize-len, filePtr);
        len += n;

        if (len == buffSize) {
            buffSize *= 2;
            buff = realloc(buff, buffSize);
        }
    }while(n!=0);

    return (m_str){buff, (int)len};
}


int main(int argc, char** argv) {
    if(argc !=5){
        printf("Proper use:\n"
               "input the file to encrypt/decrypt, \n"
               "the type of key to use(-f file -i input) followed by the key, \n"
               "the output name of the encrypted/decrypted file\n"
              );
        return 0;
    }

    
    FILE *outFileTesterPtr = fopen(argv[4],"r");
    if(outFileTesterPtr != NULL){
        printf("\"%s\" already exists, use another name or delete the file and retry\n",argv[4]);
        exit(5);
    }
    fclose(outFileTesterPtr);
    

    FILE *filePtr = fopen(argv[1],"r");
    if(filePtr == NULL){
        printf("\"%s\" does not already exists, recheck the name of the file and retry\n",argv[1]);
        exit(1);
    }
    
    

    m_str key;
    int needFreeBool = 0;

    if(argv[2][1] == 'f'){
        FILE *keyFile = fopen(argv[3],"r");
    
        if(keyFile == NULL)
            exit(2);

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

    
    m_str buff = parser(filePtr);
    

    decrypt_encrypt(&buff,key);

    FILE *outFilePtr = fopen(argv[4],"w");
    
    fwrite(buff.str, sizeof(char), buff.len, outFilePtr);
    
    if (needFreeBool){
        free(key.str);
    }
    free(buff.str);
    
    

    fclose(outFilePtr);
    fclose(filePtr);
    

    return 0;
}