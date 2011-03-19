powerset(Set, PowerSet) :-
    findall(SubSet, subset(Set, SubSet), PowerSet).

subset([], []).
subset([_|Tail], Set) :- subset(Tail, Set).
subset([Head|Tail], [Head|Set]) :- subset(Tail, Set).