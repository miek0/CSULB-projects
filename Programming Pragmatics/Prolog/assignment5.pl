% "Star tricked.pl"
% Mike Zeng
% CECS 424
% Assignment 5

sighting(balloon).
sighting(clothesline).
sighting(frisbee).
sighting(water_tower).

person(barrada).
person(gort).
person(klatu). 
person(nikto).

female(barrada).
female(gort).
male(klatu).
male(nikto).

solve :-
    
    sighting(BarradaSighting), sighting(GortSighting), sighting(KlatuSighting), sighting(NiktoSighting),
	all_different([BarradaSighting, GortSighting, KlatuSighting, NiktoSighting]),
    
	person(Barrada), person(Gort), person(Klatu), person(Nikto),
	all_different([Barrada, Gort, Klatu, Nikto]),
	
	Triples = [ [Barrada, BarradaSighting, tuesday],
				[Gort,    GortSighting,    wednesday],
				[Klatu,   KlatuSighting,   thursday],
				[Nikto,   NiktoSighting,   friday] ],
    
	% 1. Mr.Klatu made his sighting at some point earlier in the week than the one who saw the balloon,
	% 	 but at some point later in the week than the one who spotted the frisbee (who isn't Ms.Gort).
    earlier([klatu,_,_], [_,balloon, _], Triples),
    earlier([_,frisbee,_], [klatu,_, _], Triples),
    \+ member([klatu, frisbee , _], Triples),
    \+ member([klatu, balloon , _], Triples),
	\+ member([gort, frisbee, _], Triples),
	
	% 2. friday's sighting was made by either Ms.Barrada or the one who saw a clothesline (or both).
	(member([barrada, _, friday], Triples);
    member([_, clothesline, friday], Triples)),
	
	% 3. Mr.Nikto did not make his sighting on tuesday.
	\+ member([nikto, _, tuesday], Triples),
	
	% 4. Mr.Klatu isn't the one whose object turned out to be a water_tower.
	\+ member([klatu, water_tower, _], Triples),

	tell(Barrada, BarradaSighting, tuesday),
	tell(Gort,    GortSighting,    wednesday),
	tell(Klatu,   KlatuSighting,   thursday),
	tell(Nikto,   NiktoSighting,   friday).
	
% Succeed if all elements of the argument list are bound and different.
% Fail if any elements are unbound or equal to some other element.
all_different([H | T]) :- member(H, T), !, fail.        % (1)
all_different([_ | T]) :- all_different(T).             % (2)
all_different([_]).        								% (3)

earlier(X, _, [X | _]).
earlier(_, Y, [Y | _]) :- !, fail.
earlier(X, Y, [_ | T]) :- earlier(X, Y, T). 

% Write out an English sentence with the solution.
tell(X, Y, Z) :- 
    ( female(X) -> 
       write('Ms. '), write(X), write(' saw the '), write(Y),
       write(' on '), write(Z), write('.'), nl
    ;  
    male(X) ->  
       write('Mr. '), write(X), write(' saw the '), write(Y),
       write(' on '), write(Z), write('.'), nl
     ).
    