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



