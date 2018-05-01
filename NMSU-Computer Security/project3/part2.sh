#! /bin/bash

make clean
make part2
./part2 -Plain plain.txt -EncryptedSessionKey encrypted_session.key -ThirdPartyPublic TApubkey.pem -Private privkey.pem
