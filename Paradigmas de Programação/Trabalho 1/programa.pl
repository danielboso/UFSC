:- consult('linguagens.pl').

%   	Linguagens L que possuem algum predecessor.
lingcompre(L) :- predecessora(L, _).

%   	Linguagens L que possuem algum predecessor, e também são predecessoras de outra
% 	linguagem.
lingprecompre(L) :- predecessora(L, _), predecessora(_, L).

%   	Linguagens precessoras Lp de linguagens desenvolvidas em um determinado ano A.
lingpreano(Lp, A) :- predecessora(X, Lp), linguagem(X, A).

%   	Linguagens que não são precedentes.
lingnaosaopre(L) :- linguagem(L, _), \+predecessora(_, L).

%   	Linguagens L1 e L2 que têm uma predecessora Lp em comum.
lingprecomum(L1, L2, Lp) :- predecessora(L1, Lp), predecessora(L2, Lp), L1 \= L2.

%   	Linguagem Lpp que é predecessora de uma outra linguagem Lp que, por sua vez,
% 	também é predecessora de uma linguagem L.
lingprepre(Lpp, Lp, L) :- predecessora(L, Lp), predecessora(Lp, Lpp).

%   	Linguagem Lpp predecessora de outra linguagem L, mas com diferença de uma
% 	década ou mais de desenvolvimento entre Lp e L.
lingpredecada(Lp, L) :- predecessora(L, Lp), linguagem(L, X), linguagem(Lp, Y), X - Y >= 10.

%   	Linguagem L desenvolvida em uma década D qualquer. Se o argumento D não for
% 	múltiplo de 10, seu dígito mais à direita deve ser substituído por 0 (por exemplo,
% 	1957 deve ser tratato como 1950).
lingdecada(L, D) :- linguagem(L, X), X//10 =:= D//10.

%   	Linguagem L que têm mais de uma disciplina predecessora.
lingcommultipre(L) :- predecessora(L, X), predecessora(L, Y), X \= Y.

%   	Quantidade N de linguagens desenvolvidas em um dado ano A.
qano(A, N) :- findall(L, linguagem(L, A), La), length(La, N).

%   	Quantidade N de predecessoras de uma dada linguagem L.
qsaopre(L, N)   :- findall(L, predecessora(L, _), Lista), length(Lista, N).

%   	Quantidade N de linguagens predecessoras.
qsaopre(N)      :- findall(L, predecessora(_, L), ListaA), sort(ListaA, Lista), length(Lista, N).

%   	Quantidade N de linguagens que têm predecessoras.
qtempre(N)      :- findall(L, predecessora(L, _), ListaCompleta), sort(ListaCompleta, Lista), length(Lista, N).

%   	Quantidade N de linguagens desenvolvidas em uma década D qualquer.
qdecada(D, N)   :- findall(L, (linguagem(_, AnoLinguagem), D // 10 =:= AnoLinguagem // 10), Lista), length(Lista, N).

%   	Quantidade total N de linguagens existentes (no banco de dados) entre os anos
% 	A1 e A2 (incluindo ambos).
qtotal(A1, A2, N) :- findall(L, (linguagem(_, AnoLinguagem), AnoLinguagem >= A1, AnoLinguagem =< A2), Lista), length(Lista, N).

%   	Linguagem mais antiga.
lingmaisantiga_aux([], _, L, L).
lingmaisantiga_aux([H|T], A1, L1, L) :- linguagem(H, A2), A1 =< A2, lingmaisantiga_aux(T, A1, L1, L).
lingmaisantiga_aux([H|T], A1, _ , L) :- linguagem(H, A2), A1 >= A2, lingmaisantiga_aux(T, A2, H , L).

lingmaisantiga(L) :- findall(L1, linguagem(L1, _), Lista), lingmaisantiga_aux(Lista, 9999, _, L).

%   	Linguagem mais recente.
lingmaisrecente_aux([], _, L, L).
lingmaisrecente_aux([H|T], A1, L1, L) :- linguagem(H, A2), A1 >= A2, !, lingmaisrecente_aux(T, A1, L1, L).
lingmaisrecente_aux([H|T], A1, _ , L) :- linguagem(H, A2), A1 =< A2, !, lingmaisrecente_aux(T, A2, H , L).

lingmaisrecente(L) :- findall(L1, linguagem(L1, _), Lista), lingmaisrecente_aux(Lista, 0, _, L).

%   	Linguagem L com mais predecessoras.
lingcommaispre_aux([]   , _  , L, L).
lingcommaispre_aux([H|T], Q1, L1, L) :-	qsaopre(H, Q2), Q1 >= Q2, !, lingcommaispre_aux(T, Q1, L1, L).
lingcommaispre_aux([H|T], Q1, _ , L) :-	qsaopre(H, Q2),	Q1 =< Q2, !, lingcommaispre_aux(T, Q2, H , L).

lingcommaispre(L) :- findall(L1, linguagem(L1, _), Lista), lingcommaispre_aux(Lista, 0, _, L).

%   	Linguagem L que é predecessora da maior quantidade de linguagens.

%   	Ano A em que houve desenvolvimento da maior quantidade de linguagens.

%   	Década D em que houve desenvolvimento da maior quantidade de linguagens.

%   	Encadeamento de predecessoras (lista Lp) a partir de uma linguagem L.
