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

