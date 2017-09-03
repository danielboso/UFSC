
% Linguagens L que possuem algum predecessor
lingcompre(L) :- predecessora(L, _).

% Linguagens L que possuem algum predecessor, e também são predecessoras de outra
% linguagem
lingprecompre(L) :- predecessora(L, _), predecessora(_, L).

% Linguagens precessoras Lp de linguagens desenvolvidas em um determinado ano A
lingpreano(Lp, A) :- predecessora(X, Lp), linguagem(X, A).
