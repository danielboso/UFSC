% 1950 - 1959
linguagem('Flow-matic'        , 1957).
linguagem('Fortran I'         , 1957).
linguagem('Fortran II'        , 1958).
linguagem('Algol 58'          , 1958).
linguagem('Lisp'              , 1959).

% 1960 - 1969
linguagem('COBOL'             , 1960).
linguagem('Algol 60'          , 1960).
linguagem('CPL'               , 1961).
linguagem('Fortran IV'        , 1962).
linguagem('Simula I'          , 1963).
linguagem('PL/I'              , 1964).
linguagem('Basic'             , 1964).
linguagem('Algol W'           , 1966).
linguagem('Simula 67'         , 1967).
linguagem('Algol 68'          , 1968).
linguagem('BCPL'              , 1969).
linguagem('Smalltalk'         , 1969).

% 1970 - 1979
linguagem('B'                 , 1970).
linguagem('Prolog'            , 1970).
linguagem('Pascal'            , 1971).
linguagem('C'                 , 1971).
linguagem('Smalltalk 72'      , 1972).
linguagem('CLU'               , 1974).
linguagem('Smalltalk 74'      , 1974).
linguagem('Scheme'            , 1975).
linguagem('Modula'            , 1975).
linguagem('Smalltalk 76'      , 1976).
linguagem('S'                 , 1976).
linguagem('Modula-2'          , 1977).
linguagem('ML'                , 1977).
linguagem('Fortran 77'        , 1977).
linguagem('Smalltalk 78'      , 1978).
linguagem('Scheme MIT'        , 1978).
linguagem('CSP'               , 1978).
linguagem('C (K&R)'           , 1978).
linguagem('Ada'               , 1979).

% 1980 - 1989
linguagem('ABC'               , 1980).
linguagem('Smalltalk 80'      , 1980).
linguagem('Ada 83'            , 1983).
linguagem('Pascal AFNOR'      , 1983).
linguagem('Lazy ML'           , 1984).
linguagem('SML'               , 1984).
linguagem('Scheme 84'         , 1984).
linguagem('Common Lisp'       , 1985).
linguagem('Miranda'           , 1985).
linguagem('C++'               , 1985).
linguagem('CLIPS'             , 1985).
linguagem('Scheme R3RS'       , 1986).
linguagem('Objective-C'       , 1986).
linguagem('Eiffel'            , 1986).
linguagem('Scheme R4RS'       , 1988).
linguagem('Erlang'            , 1988).
linguagem('Life'              , 1988).
linguagem('CLOS'              , 1989).
linguagem('Modula-3'          , 1989).
linguagem('ANSI C'            , 1989).
linguagem('Lambda Prolog'     , 1989).

% 1990 - 1999
linguagem('C++ (ARM)'         , 1990).
linguagem('Haskell'           , 1990).
linguagem('SML 90'            , 1990).
linguagem('Fortran 90'        , 1990).
linguagem('Gofer'             , 1991).
linguagem('Python'            , 1991).
linguagem('Perl 4'            , 1991).
linguagem('Oak'               , 1991).
linguagem('Mercury'           , 1993).
linguagem('AppleScript'       , 1993).
linguagem('R'                 , 1993).
linguagem('Lua'               , 1994).
linguagem('Common Lisp (ANSI)', 1994).
linguagem('Perl 5'            , 1994).
linguagem('C 95'              , 1995).
linguagem('Prolog ISO'        , 1995).
linguagem('Ada 95'            , 1995).
linguagem('PHP'               , 1995).
linguagem('Java'              , 1995).
linguagem('Ruby'              , 1995).
linguagem('Squeak'            , 1996).
linguagem('OCaml'             , 1996).
linguagem('Scheme R5RS'       , 1998).
linguagem('C++ (ISO)'         , 1998).
linguagem('Java 2'            , 1998).
linguagem('Haskell 98'        , 1998).
linguagem('.NET'              , 1999).
linguagem('Python 1.5.2'      , 1999).
linguagem('C 99'              , 1999).

% 2000 - 2009
linguagem('Lua 4.0'           , 2000).
linguagem('Python 2.0'        , 2000).
linguagem('C#'                , 2000).
linguagem('GHC 5.00'          , 2001).
linguagem('Python 2.2'        , 2002).
linguagem('Lua 5.0'           , 2003).
linguagem('Io'                , 2003).
linguagem('Fortran 2003'      , 2003).
linguagem('GHC 6.0'           , 2003).
linguagem('Python 2.4'        , 2004).
linguagem('Java 5'            , 2004).
linguagem('Scala'             , 2004).
linguagem('C# 2.0'            , 2005).
linguagem('Python 2.5'        , 2006).
linguagem('Java 6'            , 2006).
linguagem('CAL (Open Quark)'  , 2006).
linguagem('D 1.0'             , 2007).
linguagem('C# 3.0'            , 2007).
linguagem('Fortress 1.0beta'  , 2007).
linguagem('Python 3.0'        , 2008).
linguagem('Go'                , 2009).

% 2010 - dias atuais
linguagem('Rust'              , 2010).
linguagem('Haskell 2010'      , 2010).
linguagem('Java 7'            , 2011).
linguagem('Swift'             , 2014).
linguagem('Java 8'            , 2014).
linguagem('Python 3.6'        , 2016).

% ------------------------------------

predecessora('Haskell 2010'       , 'GHC 6.0'       ).
predecessora('Rust'               , 'C++'           ).
predecessora('Rust'               , 'Erlang'        ).
predecessora('Rust'               , 'OCaml'         ).
predecessora('Rust'               , 'Haskell 98'    ).
predecessora('Rust'               , 'C# 2.0'        ).
predecessora('Lua 5.0'            , 'Lua 4.0'       ).
predecessora('Ada 95'             , 'Ada 83'        ).
predecessora('Scheme R3RS'        , 'Scheme 84'     ).
predecessora('Pascal'             , 'PL/I'          ).
predecessora('Pascal'             , 'Algol W'       ).
predecessora('Python 2.2'         , 'Python 2.0'    ).
predecessora('BCPL'               , 'CPL'           ).
predecessora('SML'                , 'ML'            ).
predecessora('Ada 83'             , 'Ada'           ).
predecessora('C++ (ISO)'          , 'C++ (ARM)'     ).
predecessora('Basic'              , 'Fortran IV'    ).
predecessora('Java 6'             , 'Java 5'        ).
predecessora('Smalltalk 78'       , 'Smalltalk 76'  ).
predecessora('Mercury'            , 'SML 90'        ).
predecessora('Mercury'            , 'Prolog'        ).
predecessora('Mercury'            , 'Haskell'       ).
predecessora('Python'             , 'Modula-3'      ).
predecessora('Python'             , 'ANSI C'        ).
predecessora('Python'             , 'ABC'           ).
predecessora('Scheme'             , 'Algol 60'      ).
predecessora('Scheme'             , 'Lisp'          ).
predecessora('Modula-2'           , 'Modula'        ).
predecessora('CLU'                , 'Pascal'        ).
predecessora('CLU'                , 'Simula 67'     ).
predecessora('CLOS'               , 'Common Lisp'   ).
predecessora('Miranda'            , 'ML'            ).
predecessora('AppleScript'        , 'Smalltalk 80'  ).
predecessora('Java 2'             , 'Java'          ).
predecessora('Perl 5'             , 'Perl 4'        ).
predecessora('Python 2.4'         , 'Python 2.2'    ).
predecessora('Io'                 , 'Lua'           ).
predecessora('Io'                 , 'Smalltalk 80'  ).
predecessora('Common Lisp'        , 'Scheme MIT'    ).
predecessora('Common Lisp'        , 'Lisp'          ).
predecessora('Python 1.5.2'       , 'Python'        ).
predecessora('Fortran II'         , 'Fortran I'     ).
predecessora('D 1.0'              , 'C#'            ).
predecessora('D 1.0'              , 'Java'          ).
predecessora('D 1.0'              , 'C 99'          ).
predecessora('D 1.0'              , 'C++'           ).
predecessora('B'                  , 'BCPL'          ).
predecessora('Python 2.5'         , 'Python 2.4'    ).
predecessora('COBOL'              , 'Flow-matic'    ).
predecessora('Smalltalk 72'       , 'Smalltalk'     ).
predecessora('Swift'              , 'Haskell'       ).
predecessora('Swift'              , 'CLU'           ).
predecessora('Swift'              , 'Objective-C'   ).
predecessora('Swift'              , 'C# 2.0'        ).
predecessora('Swift'              , 'D 1.0'         ).
predecessora('Swift'              , 'Ruby'          ).
predecessora('Swift'              , 'Python 2.0'    ).
predecessora('Swift'              , 'Rust'          ).
predecessora('Gofer'              , 'Haskell'       ).
predecessora('Algol 60'           , 'Algol 58'      ).
predecessora('Squeak'             , 'Smalltalk 80'  ).
predecessora('Python 3.0'         , 'Python 2.5'    ).
predecessora('C++ (ARM)'          , 'C++'           ).
predecessora('C++ (ARM)'          , 'Ada 83'        ).
predecessora('C++ (ARM)'          , 'CLU'           ).
predecessora('Java 8'             , 'Java 7'        ).
predecessora('Scheme R5RS'        , 'Scheme R4RS'   ).
predecessora('C# 3.0'             ,  'C# 2.0'       ).
predecessora('Erlang'             , 'Common Lisp'   ).
predecessora('Erlang'             , 'Prolog'        ).
predecessora('Scheme R4RS'        , 'Scheme R3RS'   ).
predecessora('Haskell'            , 'Lazy ML'       ).
predecessora('Haskell'            , 'Miranda'       ).
predecessora('Common Lisp (ANSI)' , 'Common Lisp'   ).
predecessora('Smalltalk 76'       , 'Smalltalk 74'  ).
predecessora('PL/I'               , 'COBOL'         ).
predecessora('PL/I'               , 'Algol 60'      ).
predecessora('PL/I'               , 'Fortran IV'    ).
predecessora('Prolog ISO'         , 'Prolog'        ).
predecessora('C 95'               , 'ANSI C'        ).
predecessora('Algol 68'           , 'Algol 60'      ).
predecessora('Lua'                , 'Pascal AFNOR'  ).
predecessora('Lua'                , 'Perl 4'        ).
predecessora('Algol 58'           , 'Fortran I'     ).
predecessora('Algol W'            , 'Algol 60'      ).
predecessora('Simula I'           , 'Algol 60'      ).
predecessora('Oak'                , 'C++ (ARM)'     ).
predecessora('Fortran 77'         , 'Fortran IV'    ).
predecessora('Fortress 1.0beta'   , 'Fortran 2003'  ).
predecessora('Fortress 1.0beta'   , 'Scala'         ).
predecessora('Haskell 98'         , 'Gofer'         ).
predecessora('Haskell 98'         , 'Haskell'       ).
predecessora('Smalltalk 74'       , 'Smalltalk 72'  ).
predecessora('Modula'             , 'Pascal'        ).
predecessora('Java 7'             , 'Java 6'        ).
predecessora('Python 3.6'         , 'Python 3.0'    ).
predecessora('Scala'              , 'OCaml'         ).
predecessora('Scala'              , '.NET'          ).
predecessora('Scala'              , 'Java 2'        ).
predecessora('Life'               ,  'Prolog'       ).
predecessora('Ruby'               , 'Smalltalk 80'  ).
predecessora('Ruby'               , 'Perl 4'        ).
predecessora('Ruby'               , 'Python'        ).
predecessora('Java 5'             , 'Java 2'        ).
predecessora('CAL (Open Quark)'   , 'Java 2'        ).
predecessora('CAL (Open Quark)'   , 'Haskell 98'    ).
predecessora('C 99'               , 'C 95'          ).
predecessora('Eiffel'             , 'Simula 67'     ).
predecessora('Eiffel'             , 'Ada 83'        ).
predecessora('Python 2.0'         , 'Python 1.5.2'  ).
predecessora('C'                  , 'B'             ).
predecessora('C'                  , 'Algol 68'      ).
predecessora('Scheme MIT'         , 'Scheme'        ).
predecessora('ANSI C'             , 'C++'           ).
predecessora('ANSI C'             , 'C (K&R)'       ).
predecessora('Modula-3'           , 'Modula-2'      ).
predecessora('GHC 5.00'           , 'Haskell 98'    ).
predecessora('Lua 4.0'            , 'Lua'           ).
predecessora('R'                  , 'S'             ).
predecessora('R'                  , 'Scheme'        ).
predecessora('R'                  , 'Common Lisp'   ).
predecessora('CPL'                , 'Algol 60'      ).
predecessora('Objective-C'        , 'Smalltalk 80'  ).
predecessora('Objective-C'        , 'C (K&R)'       ).
predecessora('PHP'                , 'Perl 5'        ).
predecessora('Java'               , 'Oak'           ).
predecessora('Smalltalk'          , 'Simula 67'     ).
predecessora('Fortran 2003'       , 'Fortran 90'    ).
predecessora('Scheme 84'          , 'Scheme MIT'    ).
predecessora('C# 2.0'             , 'C#'            ).
predecessora('C (K&R)'            , 'C'             ).
predecessora('Smalltalk 80'       , 'Smalltalk 78'  ).
predecessora('C++'                , 'C (K&R)'       ).
predecessora('C++'                , 'Algol 68'      ).
predecessora('C++'                , 'Simula 67'     ).
predecessora('Simula 67'          , 'Simula I'      ).
predecessora('GHC 6.0'            , 'GHC 5.00'      ).
predecessora('C#'                 , 'Java 2'        ).
predecessora('C#'                 , 'C++ (ISO)'     ).
predecessora('Fortran 90'         , 'Fortran 77'    ).
predecessora('Ada'                , 'CSP'           ).
predecessora('Ada'                , 'Pascal'        ).
predecessora('CLIPS'              , 'Prolog'        ).
predecessora('Lambda Prolog'      ,  'Prolog'       ).
predecessora('Lambda Prolog'      , 'SML'           ).
predecessora('Fortran IV'         , 'Fortran II'    ).
predecessora('Go'                 , 'Python 2.0'    ).
predecessora('Go'                 , 'C'             ).
predecessora('Go'                 , 'CSP'           ).
predecessora('Go'                 , 'Smalltalk 80'  ).
predecessora('Go'                 , 'Modula-3'      ).
predecessora('Go'                 , 'Pascal'        ).
predecessora('ANSI C'             , 'C (K&R)'       ).
