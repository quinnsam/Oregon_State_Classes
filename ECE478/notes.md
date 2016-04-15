################################################################################ 
Tue 03/29/2016
################################################################################ 

Crypto review.

Kerckhoffs's principle - Assume that the adversary knows the encryption and decryption algorithm. 

################################################################################ 
Thu 03/31/2016
################################################################################ 

Message authentication > message integrity

Security parameter: 1/2^k

Confusion: Make the relationship between the ptxt input and the ctxt output as complex as possible.
    - Mainly accomplished by substitutions
Diffusion: Spread the influence of each input bit across many output bits.
    - Mainly accomplised by permutations

Hash functions = 1/2^(k/2)  because of the birthday paradox. 

################################################################################ 
Tue 04/05/2016
################################################################################ 
Weak collision resistance - H(m') = H(m)
Strong collision resistance - H(m1) = H(m2)


*Hashing Security*
    Deterministic hashing       - d=H(M)
    Hashing with a random salt  - d=H(salt,M)
        * Salt is public
    Hashing random messages     - M'=M||r, d=H(M')
        * H(r||ID||File-ID)
    Hashing with as secret key  - d=H(key,M)

Second preimage resistance
    - Given random M, attacker cannot find M' such that H(M)=H(M')
One-wayness
    - Given d=H(M) for a random M, attacker cannot find M' such that H(M')=d
Extraction
    - For random salt, high-entropy M, the digest d=H(salt,M) is close to being uniform.

+ Exam - How to compute HMAC


################################################################################ 
Tue 04/11/2016
################################################################################ 

*One-way Hash Chain*
    * Used for many network security applictions
        - S/key
        - Authenticate data streams
        - Key derivation in crypto schemes
       
    One time password generation. 

    Hash chains are not tollerant to packet loss.

    Weaknesses
    1) All or nothing 
    2) Real time
    3) Packet loss

*Merkel Hash Tree*
    * A binary tree over data values
        - For authentication purpose
    * The root is the commitment of the Merkle tree
        - Known to the verifier


################################################################################ 
Thu 04/14/2016
################################################################################ 
+ What are the leakagese in searchable encryption?
+ what things can you do to prevent leakages in searchable encryption? ORAM

*ORAM*
Needs to hide:
    1) Virtual access patterns
    2) Physical access pattern
ORAM Propertys:
    * Equal block size
    * IND-CPA (randomized encryption)


