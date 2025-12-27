#!/bin/bash

rm keyFileDecrypted.txt
rm keyAsABCD-Dencrypted.txt
rm keyFileEncrypted.txt
rm keyAsABCDEncrypted.txt

./encrypter.exe main.c -f key  keyFileEncrypted.txt
./encrypter.exe main.c -i ABCD  keyAsABCDEncrypted.txt
./encrypter.exe keyAsABCDEncrypted.txt -i ABCD  keyAsABCD-Dencrypted.txt
./encrypter.exe keyFileEncrypted.txt -f key  keyFileDecrypted.txt
sleep 5