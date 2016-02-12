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
