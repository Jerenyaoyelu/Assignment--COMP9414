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

%return the first male ancester of a Person
maleancester(A,B):-
    isfather(A,B).
maleancester(Ancester, Person):-
    isfather(Temp, Person),
    maleancester(Ancester,Temp).
    
%return ture if two people have the same family name which is promised by that they have the same male ancester.
same_name(Person1,Person2):-
    maleancester(Ancester1,Person1),
    maleancester(Ancester2,Person2),
    Ancester1 = Ancester2.


%q3:

sqrt_list([],[]).
sqrt_list([Head|Tail],[[Head,S]|ResultofTail]):-
    S is sqrt(Head),
    sqrt_list(Tail,ResultofTail).