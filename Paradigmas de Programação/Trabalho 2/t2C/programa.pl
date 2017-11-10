/*
   Programacao Logica - Prof. Alexandre G. Silva - 30set2015
     Versao inicial     : 30set2015
     Adicao de gramatica: 15out2015
     Atualizacao        : 12out2016
     Atualizacao        : 10mai2017
     Ultima atualizacao : 12set2017

   RECOMENDACOES:

   - O nome deste arquivo deve ser 'programa.pl'
   - O nome do banco de dados deve ser 'desenhos.pl'
   - O nome do arquivo de gramatica deve ser 'gramatica.pl'

   - Dicas de uso podem ser obtidas na execucação:
     ?- menu.

   - Exemplo de uso:
     ?- load.
     ?- searchAll(1).

   - Exemplos de uso da gramatica:
     ?- comando([pf, '10'], []).
     Ou simplesmente:
     ?- cmd("pf 10").

     ?- comando([repita, '5', '[', pf, '50', gd, '45', ']'], []).
     Ou simplesmente:
     ?- cmd("repita 5[pf 50 gd 45]").

   - Colocar o nome e matricula de cada integrante do grupo
     nestes comentarios iniciais do programa
*/

:- set_prolog_flag(double_quotes, codes).
:- initialization(load).

% Exibe menu principal
menu :-
    write('load.         -> Carrega todos os desenhos do banco de dados para a memoria'), nl,
    write('commit.       -> Grava alteracoes de todos os desenhos no banco de dados'), nl,
    write('new(Id,X,Y).  -> Insere ponto/deslocamento no desenho com identificador <Id>'), nl,
    write('search.       -> Consulta pontos/deslocamentos dos desenhos'), nl,
    write('remove.       -> Remove pontos/deslocamentos dos desenhos'), nl,
    write('svg.          -> Cria um arquivo de imagem vetorial SVG (aplica "commit." antes'), nl.

% Apaga os predicados 'xy' da memoria e carrega os desenhos a partir de um arquivo de banco de dados
load :-
    consult('gramatica.pl'),
    retractall(xy(_,_,_)),
    retractall(xylast(_,_,_)),
    retractall(angle(_)),
    retractall(active(_)),
    open('desenhos.pl', read, Stream),
    repeat,
        read(Stream, Data),
        (Data == end_of_file -> true ; assert(Data), fail),
        !,
        close(Stream).

% Grava os desenhos da memoria em arquivo
commit :-
    open('desenhos.pl', write, Stream),
    telling(Screen),
    tell(Stream),
    listing(xylast),  %listagem dos predicados 'xylast'
    listing(angle),   %listagem dos predicados 'angle'
    listing(active),  %listagem dos predicados 'active'
    listing(xy),      %listagem dos predicados 'xy'
    tell(Screen),
    close(Stream).

% Ponto de deslocamento, se <Id> existente
new(Id,X,Y) :-
    xy(Id,_,_),
    assertz(xy(Id,X,Y)),
    !.

% Ponto inicial, caso contrario
new(Id,X,Y) :-
    asserta(xy(Id,X,Y)),
    !.

% Exibe opcoes de busca
search :-
    write('searchId(Id,L).  -> Monta lista <L> com ponto inicial e todos os deslocamentos de <Id>'), nl,
    write('searchFirst(L).  -> Monta lista <L> com pontos iniciais de cada <Id>'), nl,
    write('searchLast(L).   -> Monta lista <L> com pontos/deslocamentos finais de cada <Id>'), nl.
%------------------------------------
% Exibe opcoes de remocao
remove :-
    write('removeLast.      -> Remove todos os pontos/deslocamentos de <Id>'), nl,
    write('removeLast(Id).  -> Remove o ultimo ponto de <Id>'), nl.

% Grava os desenhos em SVG
svg :-
    commit,
    open('desenhos.svg', write, Stream),
    telling(Screen),
    tell(Stream),
    consult('db2svg.pl'),  %programa para conversao
    tell(Screen),
    close(Stream).

%------------------------------------
% t2A
% -----------------------------------

% Questao 1 (resolvida)
% Monta lista <L> com ponto inicial e todos os deslocamentos de <Id>
searchId(Id,L) :-
    bagof([X,Y], xy(Id,X,Y), L).

% Questao 2
% Monta lista <L> com pontos iniciais de cada <Id>
firstElement([H|F], H).
searchFirst_aux(Aux, Aux, Id) :-
	\+searchId(Id, _),
	!.

searchFirst_aux(L, Aux, Id) :-
	Id_novo is Id +1,
	searchId(Id, Lista),
	firstElement(Lista, F),
	append(Aux, [F], Lista_nova),
	searchFirst_aux(L, Lista_nova, Id_novo).
searchFirst(L) :- searchFirst_aux(L, [], 1).

% Questao 3
% Monta lista <L> com pontos ou deslocamentos finais de cada <Id>
lastElement([E|[]], E):- !.
lastElement([H|T] , E):- lastElement(T, E).

searchLast_aux(Aux, Aux, Id) :-
	\+searchId(Id, _), !.

searchLast_aux(L, Aux, Id) :-
	searchId(Id, Lista),
	Id_novo is Id +1,
	lastElement(Lista, F),
	append(Aux, [F], Lista_nova),
	searchLast_aux(L, Lista_nova, Id_novo).
searchLast(L) :- searchLast_aux(L, [], 1).

% Questao 4
% Remove todos os pontos ou deslocamentos do ultimo <Id>
lastId_aux(Aux, Id) :-
	\+searchId(Aux, _), !, Id is Aux-1.
lastId_aux(Aux, Id) :-
	Id_novo is Aux + 1,
	lastId_aux(Id_novo, Id).
lastId(Id) :-
	lastId_aux(1, Id).

removePointsLastId([H|[]]) :-
	[Id,X,Y] = H,
	!,
	retract(xy(Id,X,Y)).


removePointsLastId([H|T]) :-
	[Id,X,Y] = H,
	retract(xy(Id,X,Y)),
	!,
	removePointsLastId(T).

removeLast() :-
	lastId(Id),
	bagof([Id, X,Y], xy(Id,X,Y), L),
	!,
	removePointsLastId(L).

% Questao 5
% Remove o ultimo ponto ou deslocamento de <Id>
removeLast_aux([H|[]]) :-
	[Id,X,Y] = H,
	retract(xy(Id,X,Y)),
	!.

removeLast_aux([H|T]) :-
	removeLast_aux(T).
removeLast(Id) :-
	bagof([Id, X,Y], xy(Id,X,Y), L),
	removeLast_aux(L).

% Questao 6
% De	termina um novo <Id> na sequencia numerica existente
newId_aux(Aux, Id) :-
	\+searchId(Aux, _), !, Id is Aux.

newId_aux(Aux, Id) :-
	Id_novo is Aux + 1,
	newId_aux(Id_novo, Id).

newId(Id) :-
	newId_aux(1, Id).

% Questao 7
% Duplica a figura com <Id> a partir de um nova posicao (X,Y)
% Deve ser criado um <Id_novo> conforme a sequencia (questao 6)
removeFirstElement([H|T], T).

cloneId_aux(Id, []).

cloneId_aux(Id, [H|T]) :-
	[X_e, Y_e] = H,
	assert(xy(Id, X_e, Y_e)),
	cloneId_aux(Id, T),!.

cloneId(Id,X,Y) :-
	newId(Id_novo),
	searchId(Id, Lista),
	firstElement(Lista, Elemento),
	[X_e, Y_e] = Elemento,
	X_clone is (X + X_e),
	Y_clone is (Y + Y_e),
	assert(xy(Id_novo, X_clone, Y_clone)),
	removeFirstElement(Lista, Lista_nova),
	cloneId_aux(Id_novo, Lista_nova),
	!.
%------------------------------------

%------------------------------------
% t2B
% -----------------------------------

% Questao 1 (resolvida, mas pode ser alterada se necessario)
% Limpa os desenhos e reinicia no centro da tela (de 1000x1000)
tartaruga :-
    retractall(xy(_,_,_)),
    retractall(xylast(_,_,_)),
    retractall(angle(_)),
    retractall(active(_)),
    asserta(xylast(1, 500, 500)),
    assertz(angle(90)),
    assertz(active(1)).

% Questao 2
% Para frente N passos (conforme angulo atual)
marcainicio :-
	xylast(Id, X_l, Y_l),
	findall(Id, xy(Id, _, _), Lista),
	length(Lista, N),
	N = 0,
	new(Id, X_l, Y_l), !.

marcainicio.

parafrente(N) :-
	active(Active),
	Active is 1,
	marcainicio,
	angle(A),
	Alfa is A*pi/180,
	X is N * cos(Alfa),
	Y is -1 *  N * sin(Alfa),
	xylast(Id, X_l, Y_l),
	X_last is X_l + X,
	Y_last is Y_l + Y,
	retractall(xylast(_, _, _)),
	assert(xylast(Id, X_last, Y_last)),
	new(Id, X, Y),
	!.

parafrente(N) :-
	active(Active),
	Active is 0,
	marcainicio,
	angle(A),
	Alfa is A*pi/180,
	X is N * cos(Alfa),
	Y is -1 *  N * sin(Alfa),
	xylast(Id, X_l, Y_l),
	X_last is X_l + X,
	Y_last is Y_l + Y,
	retractall(xylast(_, _, _)),
	assert(xylast(Id, X_last, Y_last)),
	!.

% Questao 3
% Para tras N passos (conforme angulo atual)
paratras(N) :-
	active(Active),
	Active is 1,
	marcainicio,
	angle(A),
	Alfa is A*pi/180,
    X is -1* N * cos(Alfa),
	Y is N * sin(Alfa),
	xylast(Id, X_l, Y_l),
	X_last is X_l - X,
	Y_last is Y_l + Y,
	retractall(xylast(_, _, _)),
	assert(xylast(Id, X_last, Y_last)),
	new(Id, X, Y),
	!.

paratras(N) :-
	active(Active),
	Active is 0,
	marcainicio,
	angle(A),
	Alfa is A*pi/180,
    X is N * cos(Alfa),
	Y is N * sin(Alfa),
	xylast(Id, X_l, Y_l),
	X_last is X_l - X,
	Y_last is Y_l + Y,
	retractall(xylast(_, _, _)),
	assert(xylast(Id, X_last, Y_last)),
	!.

% Questao 4
% Gira a direita G graus
giradireita(G) :-
	angle(A),
	Novo_angulo is A - G,
	retractall(angle(_)),
	assert(angle(Novo_angulo)),
	!.

% Questao 5
% Gira a esquerda G graus
giraesquerda(G) :-
	angle(A),
	Novo_angulo is A + G,
	retractall(angle(_)),
	assert(angle(Novo_angulo)),
	!.

% Questao 6
% Use nada (levanta lapis)
usenada :-
	retractall(active(_)),
	assert(active(0)).

% Questao 7
% Use lapis
uselapis :-
	retractall(active(_)),
	xylast(Id, X_l, Y_l),
	NovoId is Id + 1,
	retractall(xylast(_, _, _)),
	assert(xylast(NovoId, X_l, Y_l)),
	assert(active(1)).
%------------------------------------

%------------------------------------
% t2C
% -----------------------------------

% Questao 1
% Duplica a figura <id> (criando um novo identificador), considerando a nova
% coordenada absoluta inicial como sendo <X, Y>
figuraclone_aux(Id, []).

figuraclone_aux(Id, [H|T]) :-
	[X_e, Y_e] = H,
	assert(xy(Id, X_e, Y_e)),
	figuraclone_aux(Id, T),!.

figuraclone(Id,X,Y) :-
	newId(Id_novo),
	searchId(Id, Lista),
	firstElement(Lista, Elemento),
	assert(xy(Id_novo, X, Y)),
	removeFirstElement(Lista, Lista_nova),
	figuraclone_aux(Id_novo, Lista_nova),
	!.

% Questao 2
% translada a figura <Id> para <N> passos à frente
figuraparafrente(Id, N) :-
	angle(A),
	Alfa is A*pi/180,
	X is N * cos(Alfa),
	Y is -1 *  N * sin(Alfa),
	searchId(Id, Lista),
	firstElement(Lista, Elemento),
	[X_e, Y_e] = Elemento,
	X_novo is (X_e + X),
	Y_novo is (Y_e + Y),
	retractall(xy(Id, X_e, Y_e)),
	asserta(xy(Id, X_novo, Y_novo)),
	!.

% Questao 3
% translada a figura <Id> para <N> passos para trás
figuraparatras(Id, N) :-
	angle(A),
	Alfa is A*pi/180,
    X is -1* N * cos(Alfa),
	write(x = X),nl,
	Y is N * sin(Alfa),
	write(y = Y),nl,
	searchId(Id, Lista),
	firstElement(Lista, Elemento),
	[X_e, Y_e] = Elemento,
	X_novo is X_e - X,
	Y_novo is Y_e + Y,
	retractall(xy(Id, X_e, Y_e)),
	asserta(xy(Id, X_novo, Y_novo)),
	!.

% Questao 4
% rotaciona a figura <Id> em <A> graus no sentido horário a partir de sua coordenada
% absoluta inicial

figuragiradireita_aux(Id, A, []).

figuragiradireita_aux(Id, A, [H|T]) :-
	[X_e, Y_e] = H,
	N is sqrt(X_e**2 + Y_e**2),
	B is atan(Y_e/X_e),
	write(b = B), nl,
	Alfa is (B-A)*pi/180,
	X is N * cos(Alfa),
	Y is -1*N * sin(Alfa),
	Distancia_X is (X_e - X),
	Distancia_Y is (Y - Y_e),
	X_final is X_e - Distancia_X,
	Y_final is Y_e + Distancia_Y,
	assertz(xy(Id, X_final, Y_final)),
	figuragiradireita_aux(Id, A, T).

figuragiradireita(Id, A) :-
	searchId(Id, Lista),
	retractall(xy(Id, _, _)),
	[F|Lista_coord_rel] = Lista,
	[X, Y] = F,
	assert(xy(Id, X, Y)),
	figuragiradireita_aux(Id, A, Lista_coord_rel),
	!.

% Questao 5
% rotaciona a figura <Id> em <A> graus no sentido anti-horário a partir de sua
% coordenada absoluta inicial
figuragiraesquerda(Id, A).


testes :-
	cmd("pf 54 ge 37 pt 28 gd 95 pf 54 ge 37 pt 28 gd 95 pf 54 ge 37 pt 28 gd 95 pf 54 ge 37 pt 28 gd 95 pf 54 ge 37 pt 28 gd 95 pf 54 ge 37 pt 28 gd 95"), %estrela de seis pontas
	cmd("un pt 200 ge 90 pf 200 ul"),
	cmd("repita 36 [ gd 150 repita 8 [ pf 50 ge 45 ] ]"), %flor grande
	cmd("un pt 400 ul"),
	cmd("repita 72 [ ge 10 pf 5 ]"), %circunferencia
	cmd("un pt 150 ul"),
	cmd("repita 12 [ pf 100 gd 150 ]"), % estrela ‘a direita
	svg.
