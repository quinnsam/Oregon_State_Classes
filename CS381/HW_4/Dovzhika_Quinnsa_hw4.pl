% Homework 4 Prolog
% Authors: Sam Quinn, Anton Dovzhik
% 03/10/2015

% Exercise 1 Database Application
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

% Q1 Part a
schedule(W,P,T) :- enroll(W,C), where(C,P), when(C,T).

% Q1 Part b
usage(L,T)  :- where(C,L), when(C,T).

% Q1 Part c
conflict(C1,C2) :- where(C1,E), where(C2,E), when(C1,R), when(C2,R), C1\=C2.

% Q1 Part d
meet(C1,C2) :- enroll(C1,E), enroll(C2,E), C2\=C2.
meet(C1,C2) :- enroll(C1,Z), enroll(C2,X), where(Z,C), where(X,C), when(Z,V), when(X,B), V-B=:=1.
meet(C1,C2) :- enroll(C1,Z), enroll(C2,X), where(Z,C), where(X,C), when(Z,V), when(X,B), B-V=:=1.

% Exercise 2 List Predicates and Arithmetic
% Q2 Part a
rdup([],[]).
rdup([X|Xs],L) :- member(X,Xs), rdup(Xs,L).
rdup([X|Xs],[X|L]) :- not(member(X,Xs)), rdup(Xs,L).

% Q2 Part b
flat([],[]).
flat([X|Xs],F) :- flat(X,A), flat(Xs,B), append(A,B,F).
flat(X,[X]).

% Q2 Part c
project(1,[H|_],[H]).
project(N,[_|T], L) :-
    M is N - 1,
        project(M, T, L).
project([N|Ns],[_|T],L) :-
    project(N,T,L),
    project(Ns,T,L).
