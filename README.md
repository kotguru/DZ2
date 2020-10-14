This program emulates the operation of a car key fob that opens a car using an EDS (I have not yet had time to figure out the openssl library).

Communication protocol stages:
1) a request to establish a connection from the keychain to the car
2) generation of a challenge from a car to a keychain (generating a random number, calculating a hash, encryption with a public key of a car keychain)
3) decryption of the received challenge with a key fob using a secret key
4) signature confirmation
5) opening the door / denying access


Sample program output:
 --- CAR: Private and public keys recorded ---
 --- TRINKET: Private and public keys recorded ---
 --- REGISTRATION: creating a keychain and a car, recording a public key of a keychain in a car ---
 --- TRINKET -> CAR: connection request ---
 --- CAR -> TRINKET: sending a challenge to verify a signature ---
 --- TRINKET -> CAR: sending an decrypted challenge for confirmation ---
 --- The door is open ---