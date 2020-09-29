Primitives of cryptography:

a. Confidentiality, to scramble human readable text (or message) to giberish.
   And then back to text.
b. Integrity, ss in, the message is not tampered with.
c. Authentication, to add authentication to message, to confirm the author
   and/or source of the message.
d. Stenography, also called invisible water-marking, to make the message
   invisible.
e. Non-repudiation, to ensure that an author/entity cannot refuse the
   ownership of a previous commitment or an action.
f. Diffie–Hellman key exchange scheme.
g. Avalanche effect.
h. Completeness.
i. Zero Knowledge Proof.

Services:

1. Encryption and Decryption.
2. Hash functions.
3. Message authentication code aka MAC.
4. Digital Signatures.
5. Random number generator.

-----------------+------------+---------------+---------+------------------
Service          | Encryption | Hash-function | MAC     | Digital-signature
Premitives       |            |               |         |
-----------------+------------+---------------+---------+------------------
Confidentiality  |     yes    |    no         | no      |  no
Integrity        |     no     |    partial    | yes     |  yes
Authentication   |     no     |    no         | yes     |  yes
Non-repudiation  |     no     |    no         | partial |  yes
Stenography      |     -      |    -          | -       |  -
-----------------+------------+---------------+---------+------------------

Nomenclature:
-------------

Random Seed.
Block cipher. Padding. Feistel Cipher.
Stream cipher.
Secure Socket Layer (SSL).
Transport Layer Security (TLS).
Pretty Good Privacy (PGP).
Variable key length.

Symmetric Key Cryptography:
ECB, CBC, CFB, OFB, CTR
* Source Authentication
* Error propogation
* Stream cipher
* No decryption
DES, 3DES, Blowfish, Twofish, IDEA, Serpent.
a. Block length.
b. Key length.
c. Number of rounds (efficiency or security).
d. Initial Permutation
e. Final Permutaion.
f. Initial Vector - CBC, 

    DES     3TDES   2TDES   AES

a.  64      64      64      128
b.  56/48   56\*3   56\*2   128/192/256
c.  16      16      16      10/12/14
d.  yes     yes     yes     ?
e.  yes     yes     yes     ?


Asymmetric Key Cryptography:
- Public Key and Private Key.
- Public Key authentication.
  - Public Key Infrastructure.
- RSA.
  - p, q prime numbers
  - Public key (n, e)
    - n = p\*q
    - 1 < e < (p-1)(q-1); e & (p-1)(q-1) are coprime
  - Private key (n, d)
    - d = inverse of e modulo (p - 1)(q – 1)
  - plaintext as a series of numbers less than n.
  - encryption => C = (P^e) mod n
  - decryption => Plaintext = Cd mod n
- ElGamal Keypair.
  - X, Private Key
  - Y, Public Key = (g^X) mod p
    - p, prime modulus
    - g, generator

Vigenere Coding.
Shift Cipher.
Substitution Cipher.
Playfair Cipher.
One Time Pad.
