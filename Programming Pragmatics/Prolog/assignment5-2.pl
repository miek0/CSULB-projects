% "Star tricked.pl"
% Mike Zeng
% CECS 424
% Assignment 5

sighting(balloon).
sighting(clothesline).
sighting(frisbee).
sighting(water_tower).

day(tuesday).
day(wednesday).
day(thursday).
day(friday).

%earlier(tuesday, wednesday).
earlier(tuesday, thursday).
earlier(tuesday, friday).
earlier(wednesday, thursday).
earlier(wednesday, friday).
earlier(thursday, friday).

female(barrada).
female(gort).
male(klatu).
male(nikto).

solve :-
    
    sighting(BarradaSighting), sighting(GortSighting), sighting(KlatuSighting), sighting(NiktoSighting),
	all_different([BarradaSighting, GortSighting, KlatuSighting, NiktoSighting]),
    
	day(BarradaDay), day(GortDay), day(KlatuDay), day(NiktoDay),
	all_different([BarradaDay, GortDay, KlatuDay, NiktoDay]),
	
	Triples = [ [barrada, BarradaSighting, BarradaDay],
				[gort,    GortSighting,    GortDay],
				[klatu,   KlatuSighting,   KlatuDay],
				[nikto,   NiktoSighting,   NiktoDay] ],
    
	% 1. Mr.Klatu made his sighting at some point earlier in the week than the one who saw the balloon,
	% 	 but at some point later in the week than the one who spotted the frisbee (who isn't Ms.Gort).
    
    earlier(_, KlatuDay),	% klatu can't be on tues or fri AND klatu must be after frisbee
    earlier(KlatuDay, _),   % klatu can't be after ballon AND can't be on friday
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

	tell(barrada, BarradaSighting, BarradaDay),
	tell(gort,    GortSighting,    GortDay),
	tell(klatu,   KlatuSighting,   KlatuDay),
	tell(nikto,   NiktoSighting,   NiktoDay).
	
% Succeed if all elements of the argument list are bound and different.
% Fail if any elements are unbound or equal to some other element.
all_different([H | T]) :- member(H, T), !, fail.        % (1)
all_different([_ | T]) :- all_different(T).             % (2)
all_different([_]).        								% (3)

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
    