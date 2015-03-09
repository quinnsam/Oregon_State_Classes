% Set vim to Prolog

when(275,10).
when(261,12).
when(381,11).
when(398,12).
when(399,12).

where(275,owen102).
where(261,dear118).
where(381,cov216).
where(398,dear118).
where(399,cov216).

enroll(mary,275).
enroll(john,275).
enroll(mary,261).
enroll(john,381).
enroll(jim, 399).

schedule(W,P,T) :- enroll(W,C), where(C,P), when(C,T).

usage(L,T)  :- where(C,L), when(C,T).

conflict(C1,C2) :- where(C1,E), where(C2,E), when(C1,R), when(C2,R), C1\=C2.

meet(C1,C2) :- enroll(C1,E), enroll(C2,E), C2\=C2.
meet(C1,C2) :- enroll(C1,Z), enroll(C2,X), where(Z,C), where(X,C), when(Z,V), when(X,B), V-B=:=1.
meet(C1,C2) :- enroll(C1,Z), enroll(C2,X), where(Z,C), where(X,C), when(Z,V), when(X,B), B-V=:=1.
