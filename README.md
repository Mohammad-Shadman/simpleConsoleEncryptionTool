# simpleConsoleEncryptionTool
lets the user encrypt and decrypt using a key entered through the command arguments with -i or stored in a file with -f

Proper use:
                Input the file to encrypt/decrypt, fileToRead
                The type of key to use(-f file -i input) followed by the key, -i keyInput (or) -f keyFile
                The output name of the encrypted/decrypted file.
                
                *optional*
                    replacement flag (-r) to make it so the check for output file does not go through
                
                !!order matters!!
               
               
                Usage:\n"
                encrypter fileToRead -i keyInput outPutFile or
                encrypter fileToRead -f keyFile outPutFile or
                encrypter fileToRead -f keyFile fileToRead -r or


intended purpose is to encrypt and decrypt simply and easly through the command line while also being flexible with it's use
