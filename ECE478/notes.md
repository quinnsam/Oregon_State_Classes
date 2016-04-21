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

################################################################################
Tue 04/19
################################################################################
Notation:
    (sk,pk) <- SGN.kg(1^k), k >= 80
    Sigma <- SGN.sig_sk(m)  m exist in {0,1}^*
    {0,1} <- SGN.ver(m, Sigma, pk)


*Lamport OTS (1978)*
    f{0,1}^n -> {0,1}  // f is OWF, m in {0,1}^n m=(m_1,...,m_n)
        1) (sk,pk) 11 (x_1,0,x_i, 1) <-$- {0,1}^n
        2) y_i,0 <- f(x_1,0), y_i,1 <- f(x_1,0)


    sk = (x_1,0,x_2,0,...,x_n,0
          x_1,1,x_2,1,...,x_n,1)
    pk = (y_1,0,y_2,0,...,y_n,0
          y_1,1,y_2,1,...,y_n,1)

    Sigma <- sign(m,sk) m = (m_1,...,m_n) Sigma <- (x_1,m_1,x_2,m_2,...,x_n,m_n)
    {0,1} <- ver(Sigma, m, pk) if f(x_i,m) =?= y_i,m, i = 1,...,n
                return 1, else 0

    Example:
        m = 011
        sk = (x_1,0,x_2,0,x_3,0
              x_1,1,x_2,1,x_3,1)
        pk = (y_1,0,y_2,0,y_3,0
              y_1,1,y_2,1,y_3,1)

        Sigma <- (x_1,0,x_2,1,x_3,1)

        Verify:
            f(x_1,0) =?= y_1,0
            f(x_2,1) =?= y_2,1
            f(x_3,1) =?= y_3,1


        Varient I: O(L)
            h <- H(m)
            |sk| = |pk| = 2 * |h|*|f|
            |Sigma| = |h|*|f|

        Varient II: Sign only O or 1 , because bit flip is detected. Size = 80 + 7
        
        Varient III: Make private key constant size
            * Create a seed value that is passed into CPRNG = Key derivation trick

        Varient IV: Reduce size of public key

################################################################################
Thu 04/21
################################################################################

    Varient VII: Increase rubustenss
        * Inclued multiple pks, in onetime signature
            pk = (pk_{i+1}, ..., pk_{i+k}) <- key(j^k, k)
            Sigma <- sign(m||pk_{i+1}, .., pk_{i+k},sk_i)   // Trade off between communication robustness

        - Another Risk: Packet loss => risk for real-time authentication. 


    Error-correction codes:
        * Turbo codes
        * Victorbi codes
        * Funton codes

        pk <- kg(j^k,k), (pk_bar, r_bar) <- Ecc(pk_bar), |(pk_bar, r_bar)| >> |pk_bar|
            Sigma <- Sig(m||pk_bar||r_bar, sk_i)


    Subset-resilient: The subsets have exactly one unique counterpart. 

*Time-Valid Security*
    * k=80-128, 2^80 ~ 2^128 at adversary side
    * Temparary Security: Guarentee lasting t unit of time
        Trade off:
            2^k -> (|sk| = |pk|, t')
            t   -> (|sk'| = |pk'|, t'')

    Stateful Signature --> Packet loss
                       |
                       --> Resynchronize the network
        
