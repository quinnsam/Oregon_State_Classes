*One Time Pad*
_Encryption_ scheme consists of 3 algorithms:
1. keygen: outputs a key (k)
2. Enc(k,m): takes in plaintext (ptxt) outputs cipher text c (ctxt)
3. Dec(k,c): outputs plaintext 

k = key space
e = ciphertext space
m = ptxt space

_CorrectnessProperty:_ Enc is inverse of Dec both ways. 

"Correctness" = Something that doesn't involve adversaries
"security" = Something that does involve adversaries.

Lambda = length of a key. 
{0,1} = set of lambda-bit strings


Security Defs:
goal: Pretect against an adversary who
    .. sees ctxt
    .. doesn't know key
    .. shouldn't learn ptxt / not even partial!

What about an adv who learns partial infio about ptxt?
    e.g: learns the 1st bit of ptxt
         learns whether ptxt is encoding of prime #

*Formal Definition of Security Table 1*
idea: Adv sees ctxt, which is a sample from the distribution below
    mydist(m):
        k <- keygen {0,1}^lambda
        return k xor m

claim: For all ptxt m, mydist(m) is the uniform distribution
proof: uniform dist. assigns prob. 1/2^lambda to each outcome c in {0,1}^lambda
    pick arbitrary m,c in {0,1}^lambda then it suffices to show Pr[mydist(m)] / 1/2^lambda
    mydist(m) = c <=> k xor m = c           m,c fixed
                  <=> k = m xor c
        i.e, there is unique k that causes mydist(m)=c but k chosen uniformly. So this particular k=m xor c chosen w/probability 1/2^lambda
                                                                ####

*Formal Definition of Security Table 2*
idea: Define 2 libraries

[otp-real]    query(m):
                k <- keygen {0,1}^lambda
                return k xor m


[otp-rand]    query(m):
                c <- keygen {0,1}^lambda
                return c

Adv is an arbitrary calling program. 
Claim: For all adversary A
    Pr[A linked-to otp-real => 1] = Pr[A linked-to otp-rand => 1]
    <There is no way to tell what function you are using, They are interchange able>

Notes:
    - Adv can choose m
    - Adv can "know everything" about the 2 libraries
    - Only thing the adv does not know
        ~ Which function he is currently linked to
        ~ values of privately scoped varibles
    - Kerchhoff's principle = Assume adv knows everything about your computer except the key.

Q: What happents if adv sees 2 ctxt under the same key k?

query(m):
    k <- keygen {0,1}^lambda
    return k xor m

query(m):
    c1 <- keygen {0,1}^lambda
    c2 <- keygen {0,1}^lambda
    return c

Claim: != , need to show A that behaves differetly when linked to left/right 1
    A:  (c1, c2) <-- ctxt(m1, m2)   m1=0's m2=1's
        // if in "real world", c1 = k, c2 = k xor 1^lambda
        return c1 xor c2 if? 1^lambda

BIG PICTURE Breaking Security:
    - Write down the code of adv (calling program)
    - Show that OTP-Real != OTP-Rand.


Idea: When k chossen uniformly, F(k, .) :{0,1}^in -> {0,1}^out should "look like" randomly chosen function.

Attacks:
    Let F be a secure PRF
    Define F'(k,x = F(k,x) xor F(k,x@) @Flip every bit

Claim: F' is not a secure PRF, even if F is

Hint: Dont't try to break F

    Outputs of F on distinct inputs look random
    -> try to get same input into F twice (by querying F')

Adv: 
    Pick any x
    z1 = query(x)
    z2 = query(xbar)

    "Real Wold"
        z1 = F(k,x) xor F(k,xbar)
        z2 = F(k,xbar) xor F(k,x)
        z1 = z2 always
        pr[output true] = 1

    "Ideal World"
        z1 <- {0,1}^out
        z2 <- {0,1}^out
        pr[z1=z2] = 1/(2^out) ---- Not negilible

    ** In a secure world PR's would be simmilar **

*PsudoRandom Pormutations (PRPs)* - Block Cipher

Basically a PRF, but 
    in = out = blen (block lenght)
and
    there exists F^-1:                  F(k,x) and F^-'(k,x) are inverses
    for each k: F^-1(k,F(k,x))=x

PRP swithching lemma: 
    If blen = lambda, then ideal permutation is indistinguishable from ideal rand func ( only diff is sampling with/without replacment)
    (Construntions that require PRF con use PRP)

Challenge:
    A PRF F(k,x) somehow "scrambles" x
    A PRP F(k,x) "scrambles" x but in a way that x is still recoverable via F^-1(k,x)

Feistel Cipher: (Way to convert a PRF -> PRP)
    (e.g. DES uses this idea)

    Simplest idea:
        Suppose F:{0,1}^n -> {0,1}^n F may not have an inverse
        Def     Fhat:{0,1}^2n -> {0,1}^2n
                Fhat(L,R)    = (R, F(R) xor L)
                             = (x,y)                    ** Both use F in the forward direction, but is still inversable **
                Fhat^-1(x,y) = (F(x) xor y, x)
                             = (L, R)



_MACS_
(Msg authentication codes)

good: CCA secure scheme

MAC syntax:
    - Keygen: outpts key k
    - MAC(k,m): outputs a "tag" / MAC

Idea:
    Someone who doesn't know k (secret key) can't produce the MAC of a a new msg even after seeing many MACs of chosen msgs.. [orgery]

Note: Authencicity vs privacy (hiding info) 

_Security Def_:

#------------------------------------------------------------------------------#
World 1 "real":    
    k <-- keygen
    GETMAC(m):
        t = MAC(k,m)
        return t

    VER(m,t):
        ret t ?= MAC(k,m) 
#------------------------------------------------------------------------------#
World 2 "fake":
    k <-- keygen
    SEEN = 0 // Set of messages that have been seen
    GETMAC(m):
        t = MAC(k,m)
        add (m,t) to SEEN
        return t

    VER(m,t):
        ret (m,t) in SEEN 
#------------------------------------------------------------------------------#
Discuss:
   libraries hide internal differences
   libraries hide wheather MAC is actually checked for Adv-generated (m,t)

   ==> only way to get diff behavior from libs is to find (m,t) not generated by lib and yet t=MAC(k,m)
   
   "real" -> lib says VER(m,t) = 1
   "fake" -> lib says VER(m,t) = 0

MAC constructions:
    - MAC(k,m) = PRF(k,m)   Good MAC scheme but for short messages
        idea: if you never query F(k,m^*), then F(k,m^*) "looks random", hence hard to guess

    - MAC for long messages?
        idea: MAC(k, m1, m2,..., ml) = F(k, m1 (xor) ... (xor) ml)

        Obs: if m1 (xor) m2 (xor) ... (xor) ml = m1' (xor) m2' (xor) ...
             then these 2 msgs have same MAC

        Attack:                                             Real                                        fake
            t = GETMAC(0^lambda 1^lambda)                 t = MAC(0^lambda 1^lambda)                   (1^lambda)
            return VER( 1^lambda 0^lambda, t)               = MAC(1^lambda 0^lambda)                    not in SEEN
                                                            returns true                                = returns false

CBC-MAC:
    is secure on msgs of a single lenght.
    If you ask for MACs with a certain lenght you could forge message.

**Hash functions**
H:{0,1}^\* --> {0,1}^n

idea: "If H(x) = H(x') then x=x'" is the definiton of a 1 to 1 function.

H:{0,1}^\* --> {0,1}^n
   |             |\_\_ finite # of outputs    {injectly is impossible}
infinite inputs

Def: x,x' are a collision if x!=x', H(x)=H(x')
Crypto: It's ok if collisions exist in principle as long as they are hard to find. 

Flavors of security
    * Collision resistance: Given H, find any collision x!=x', H(x)=H(x')
    * Target-Collision resistance:
        Given H(x) for unknon x, find x' (possibly equal to x) S.T. H(x')=H(x)
    * Second preimage resistance
        Given x, find x'!=x S.T. H(x')=H(x)

Cost of finding collisions:
    Q: How long does it take to break collison-resistance?
    A: If H:{0,1}^\* --> {0,1}^n then need to evaluate H on ~ 2^(n/2) values te get good probability of collision (birthady bound)

    Q: Break second-preimage?
    A:

Merkl-Damgard, Length Extension:
    Application of hash funcitos
    - MAC is a MAC scheme for {0,1}^n
    - Define new MAC scheme for {0,1}^\*
        MAC^\*(k, m (exists) {0,1}^\*) = MAC(k, H(m))

Claim: if underlying MAC is secure, and H is collision-resistant, then MAC^\* is secure.

Idea: Adv (attacknig MAC^\*) sees 
        t1 = MAC^\*(k, m1) = MAC(k, H(m1))
        tq = MAC^\*(k, mq) = MAC(k, H(mq))
    supose Adv produces forgery: (m^\*, t^\*)
        t^\* = MAC^\*(k, m^\*) / MAC(k, H(m^\*))
            where m^\* (not in) { m1 .., mq}

        case 1: H(m^\*) = H(mi) for some mi 
            => adv found collision in H
        case 2: H(m^\*) (not in) { H(m1), ..., H(mq)}
            => Adv knows MAC(k, H(m^\*))
               after seeing MAC(k, X)
               for many X != H(m^\*)

        *Forgery of underlying MAC*

Common Pitfall:
    Construct MAC(k, m) = H(k||m)
     %(Socure if H=SHA-3, insecure if H=MD5, SHA-1)%

Merkle-Damgard Consturction:
    * Design a "Compression function" h: {0,1}^(n+t) -> {0,1}^n (not "compression" like ZIP, gZIP, etc)
    * Extend h to a full-fledge Hash function: 
        H(x): 
                x1      x2      x3      x4      x5      Each block is t bits
            x   |       |                           len(x)
                v       v   ...                      |
    y0 = 0^n -> H ----> H                         -> H -->  H(x)

Security: If h is collison-resistant, then H is too. 
    Idea: If H(x) = H(x') then within these 2 computaitons, a colision under h is guaranteed to exist. 

Ex: Suppose MAC(k, m) = H(k||m), where H is Merkle-Damgard.
    n = 16 bytes
    t = 2  bytes
    k = e93a3527 (4 bytes)    (key)
    m = 7d6 (12 bits)

    H(k||m):    len(k||m) = 88bits = "58" in hex
        e93a | 3527 | 7d6(0)| --> H(k, m)

    Q: how is H(k||m) related to H(k||m||00058)?

**NumberTheory & RSA:**
    Notation:
        Z(int)_n = {0,..., n-1}     "integers mod n"

        x % n               = remainder when dividing x by n
        x | n               = x divides n, n is a multiple of x
        x =(congurent)_n y  = x & y are congrunt mod n n|(x-y)

Pari/GP:    (installed on ENGR servers)
   "Division" mod n:
        Bezout theorem: let d = gcd(x,y)
            you can write d = ax+by where a &  are integers

        Pari: bezout()

        Suposse gcd(x,n) = 1
        then 1 = ax + bn for integers a,b
               |
               v
    1 (congurent)_n ax + 0
    So x has a multiplicative inverse mod n which is "a" (can write a =_n x ^(-1)

Def:
    Z_n^\* = { x in Z_n | gcd(x,n) = 1 }
    Then every element in Z_n^\* has amultiplicative inverse mod n; actually Z_n^\* = {x in Z_n | x has mult inverse}
    so mltiplication & division make sense in Z_n^\*


Euler Totient function:
    phi(n) = |Z_n^\*| = # of x in Z_n relitivly prime to n

    Ex: phi(11) = 10                                   Z_11 = {1, ..., 10}
        phi(p)  = p-1  if p prime => Z_p^\* = {1,...,p-1}
        
        phi(15) = ?
        Z_15 =  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
                  1 2   4 5   7 8   10 11    13 14  //Threw away multiples of 3
                  1 2   4     7 8      11    13 14  //Threw away multiples of 5
        if p,q primes (p != q) then 
            phi(pq) = -- (# multiples of p)
                      -- (# multiples of q)
                      + 1 (because 0 is double counted)
                    = pq - q - p + 1
                phi(pq) = (p-1)(q-1)

LaGrange Theorem:
    For all x in Z_n^\*, x ^(p(n)) =_n 1


RSA: 
    p !=    q,      primes
    N =     p*q     "RSA modulus"
    e,d wher e e*d =_phi(n) 1       ( ed,d multiplicitave inversese mod phi(N))

    (N,e) is public key
    (N,d) is private key

    RSA Function: M in Z_n ---> m^e in Z_n
    RSA Inverse:  C in Z_n ---> c^d in Z_n

    Proof:  ed =_phi(N) 1 => ed = k*phi(N) + 1 for some int k

        (m^e)^d = m^(ed) = m^(k*phi(N)+1) = (m^phi(N))^k * m
        =_N 1^k * m = m

Chinese Remainder theorem:
    Let p,q be relatively prime (gcd(p,q) = 1), then
    for all u, v, there is a soultion for x in 

                system of eq's
        x =_p u         ex: x =_5 2
        x =_q v             x =_7 3

    Also, solution is unique mod pq

Alternatively:
    x in Z_pq  -crt-> (x % p, x % q) in Z_p x Z_q
    this function is a bijection! (1-to-1 correspondence)

Ex: p=3, q=5

Mathematically: Z_pq and Z_p x Z_q are isomorphic 2 sets of "names" for same objects. (encodings)

Application to RSA:
    RSA inverse c |--> c^d mod N=p*q

        Z_pq world          Z_p x Z_q world
          c -> d               (c % p, c % q) -> d 

RSA vs. Factoring:
    The following problems are equivalent:
        1. Given N = pq, compute p, q
        2. Given N=pq, compute phi(N) = (p-1)(q-1)
        3. Given N=pq, e, compute d where ed =_phi(N) 1
        4. Given N=pq, compuet any x !=_N +- 1 where x^2 =_N 1

    "equivalent" = Means either all have poly-time algos, or none of them do.

How to show equivalence: ("reduction")
    * if a poly-time algo exists for #1, I could use it as a subroutine to solve #2 in poly-time
    * #2 => #3, #3 => #4, #4 => #1

    Note: #1 => #2, #2 => #3 are trivial. 

(#4 => #1)
    Def: x is a square root of unity mod N if x^2 =_N 1
        if x =_N +- 1 then x is a trivial sqrt unity, otherwise nontrivial sqrt unity

    ex: N = 15
        Z^*_15     = { 1 2 4 7 8 11 13 14 }
        x^2 mod 15 = ( 1 4 1 4 4 1 4 1 }

    Claim: If N=pq (RSA modulus) then there are 4 sqrts of unity mod N
    
    Proof: 
                       x^2 =_p 1 <=> x =_p +- 1
        x^2 =_N 1 <=>  && 
                       x^2 =_q 1 <=> x =_q +- 1

        x =_p  1    x =_p 1     x =_p -1    x =_p -1
        x =_q  1    x =_q -1    x =_q 1     x =_q -1

        There are 4 values of x

    Claim: if you can find nontrivial squrt unity x mod N=pq then gcd(x+-1,N) are the factors of N

    Ex: N=15, x=4 (non trivial sqrt of unity)
            gcd(4+1, 15) = 5
            gcd(4-1, 15) = 3

Proof: 
    x^2 =_N 1  <=> x^2 -1 is a multiple of N
               <=> N divides (x^2 -1) = (x -1) (x+1)
    x !=_N +-1 <=> x +- 1 is not multiple of N
               <=> N doesn't divide x+1 or x-1

    So (x-1)(x+1) has foctors of p and q both, bet p and q not both factors of either term 
        -> p|x-1 but q !| x-1
        -> gcd(x-1, pq) = p

(#3 => #4) if you can find d given N=pq, e. Then you can find nontrivial sqrt untity
    idea: Given (N,e)
          Compute d =_phi(N) e^(-1)     (by assumtion)

          write ed-1 = Z^s * r where r is even ("ed-1" is the number of 0's on the right)

          Choose w <- Z_N
          compute -1, w^r, w^2r, w^4r, w^8r, ..., w^(2^(s)r) all (mod N)

    Claim: Eventually this sequence reaches "1"
           W^(2^(s)r) = w^(ed-1) = (w^(ed)(w^(-1)) = w(w^(-1)) = 1

    Therefore: Item before first "1" in sequence is a sqrt of unity





