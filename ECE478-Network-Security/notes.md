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

################################################################################
Tue 04/26
################################################################################

*GCD*
    The conguence aX = b(mod n) has a unique x exist in Z_m
Euclid Algorithim
Def
    If a >= 1 

Def 2 
    Euler-phi totient function: The number of integers in km that are relitivly prime to m is defined as Phi(m).

Def 3
    The order of a group Z_m is Phi(m)

Def 4
    Order of an element: Sigma_m^* is a finite multiplicitive group, g existis in Sigma then order of g is the smallest integer x
        g^x = 1 and m


Math terms
    Corallary   - I a claim that is very obvious
    Lemma       - Smaller proof that suports a larger proof.
    Conjecture  - An opinion or conclusion formed on the basis of incomplete information.
    Remark      - A fact that doesn't directly support the claim

Little Fermant theorem: If p is prime, b (in) Z_p then 
                                b^p = b mod p
                                b^(p-1) * b = b mod p
    Phi(p) = p - 1

*RSA*
    y = H(x), lamport -> Replace H with 
    - Asymmetric one-way trapdoor primitive y = x^a mod n
    - Algebraic structure, numder theorecical assumptions.

    Key Generation:
        a) Generate two large primes (p,q) s.t p!=q and |p| ~ |q| \ 2048 bits.
        b) n <- p*q and Phi(n) = (p-1)*(q-1) // Euler-Phi totient under Z_n^*
        c) e <-$- z_n^*
        S.T. 1 <= e <= Phi(n) and GCD(e, Phi(n)) = 1

Discrete Log Problem:
    Given cyclic group G (eg Z_p^*) of order prime q and n generatio a of Simga, let A be an algoritm that returns an element of Z_q^*
        Experment Expt^DL Sigma, a (A)
        y <-$- Z_^^*, y <- a^y mod p 
        y' <- A(y)
        if a^y' mod p = Y then A retun 1, else 0.
            - Extract the exponent

        The DL advanteage of A adv^DL Sigma, a(A) = Pr[Expt^DL_sigma,a (A)= 1]



DSS Signature algorithm
    Key Generation
        sk <- (H,p,q,g,x) pk <- (H,p,q,g,y)
             Signer             verifier

        sign:
            sigma <- sighn_{sk}(m) = m \in {0,1}^*
            1) k <-$- Z_q^*
            2) r <- [g^k mod p] (mod q)
            3) s <- (H(m) * s^-1 mod q 
            4 sigmo <- (n,s)
        verify:
            {0,1} <- Ver_{pk}(m, sigma)
            1) m_1 <- H(m) * s^-1 mod q
            2) m_2 <- r * s^-1 mod q 
            3) output 1 iff: r = [(g^m1 * g^m2 mod p)] mod q

    DSA correctness
    
        u1 = H(m) * s^-1 mod q
        y = g^x mod p
        u2 = r * r^-1 mod q
        s = (H(m) + x * r) * k^-1

        r = (g^u1 * y^u2 mod p) mod q
        let m1 = H(m), the signature is (r,s)

        r = g^(m^1 * s ^-1) * (g^x)^r * s^-1
          = g^m^1 * (m^1 + x * r )^-1 * k
          ...
          g^k = g^k

Schnor Digital Signature

    Keygeneration:
        p = 2*q+1 // Sofie german prime
        1) sk = y <-$- Z_q^*,  pk = Y <- alpah^y  mod p

    Signature:
        sigma <- sch.sig(sk,m) = m \in {0,1}^*
        1) r <-$- Z_q^*
        2) R <- alpha^r mod p
        3) S <- r - H(m||R) * y mod q
        4) sigma = (s,r)

    Verify:
        R =?= alpha^S * Y^{m||R) mod p

KDC: Key distribution center


