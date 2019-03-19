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
%return new list by recursively adding each item one by one and its sqrt as a pair
sqrt_list([],[]).
sqrt_list([Head|Tail],[[Head,S]|ResultofTail]):-
    S is sqrt(Head),
    sqrt_list(Tail,ResultofTail).

%q4:
% concat([],List2,List2).
% concat([Head|Tail],NewList,[Head|Concat_Tail_List2]):-
%     concat(Tail,NewList,Concat_Tail_List2).

% sign_runs([],[]).
% sign_runs([H|T],[[H|[HHofrest|THofrest]]|Tofrest]):-
%     (H*HHofrest =< 0 *-> HHofrest = [],THofrest = [];true),
%     sign_runs(T,[[HHofrest|THofrest]|Tofrest]).

%method2:error in line 51: Arguments are not sufficiently instantiated
% sign_runs([H|T],[HofRest|TofRest]):-
%     [HH|TT] = HofRest,
%     Temp = [HH|TT],
%     (H*HH =< 0 *-> HofRest is [[H]|Temp];
%     (Temp = [] *-> HofRest is [[H]|Temp];HofRest is [H|Temp])),
%     sign_runs(T,[Temp|TofRest]).

% sign_runs([Head|Tail],Result):-
%     Temp = Result,
%     (Temp = [] *-> Result is [Head];
%     [Head2|Tail2] = Result,
%     [Head3|_Tail3] = Head2,
%     Temp2 = [Head2|Tail2],
%     (Head*Head3 =< 0 *-> Result is [[Head]|Temp2];
%     Temp3 = [Head|Head2], Result is [Temp3|Tail2])),
    %[Head4|Tail4] = Tail,
    %sign_runs(Tail4,).


%test
sign_runs([],[]).
sign_runs([Head | Tail], [E, O | S]):-
   positive([Head | Tail], E, Last),
   negative(Last, O, Last1),
   sign_runs(Last1, S).

positive([Head | Tail], [], [Head | Tail]):-
   Head < 0.
positive([Head | Tail], [Head | L], Last):-
   Head >= 0,
   positive(Tail, L, Last).
positive([],[],[]).

negative([Head | Tail], [], [Head | Tail]) :- 
   Head >= 0.
negative([Head | Tail], [Head | L], Last) :-
   Head < 0,
   negative(Tail, L, Last).
negative([],[],[]).