%Student: YAOYE LU
%ID: z5188093
%Assignment1 of COMP9331

%q1: return the sum of squres of even number in the list, if no any, return 0.
sumsq_even([],0).
sumsq_even([Head|Tail], Sum):-
    sumsq_even(Tail,SumOfTail),
    (0 =:= Head mod 2 *-> Sum is Head*Head + SumOfTail; Sum is SumOfTail).

%q2: 
%return true if Person1 is a father of Person2.
isfather(Person1,Person2):-
    male(Person1),
    parent(Person1,Person2).

%return true if Person1 and Person2 are siblings.
issibling(Person1,Person2):-
    isfather(_,Person1),
    isfather(_,Person2),
    Person1 \= Person2.

%return true if they have same family name which is promised by that they are either father and son(daughter) or siblings.
same_name(Person1,Person2):-
    (isfather(Person1,Person2);issibling(Person1,Person2)).


%q3:

sqrt_list([],[]).
sqrt_list([Head|Tail],[[Head,S]|ResultofTail]):-
    S is sqrt(Head),
    sqrt_list(Tail,ResultofTail).