%{
#include "scanner.h"//se importa el header del analisis sintactico
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "exec.h"
#include "fdisk.h"
#include "mkdisk.h"
#include "mount.h"
#include "rep.h"
#include "rmdisk.h"
#include "unmount.h"
#include "command.h"
#include "mkfs.h"
#include "login.h"
#include "logout.h"
#include "rmgrp.h"
#include "mkgrp.h"
#include "mkusr.h"
#include "rmusr.h"
#include "chmod.h"
#include "mkfile.h"
#include "mkdir.h"

extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
extern std::list<Command*> listCommand;
int yyerror(const char* mens)
{
    std::cout << "No se reconoce " <<yytext<<" Linea: "<< yylineno<< " Columna: " << columna << std::endl;
    return 0;
}
%}
%defines "parser.h"
%output "parser.cpp"
%error-verbose
%locations
%union{
int NUM;
char TEXT [256];
class Exec* exec;
class Fdisk* fdisk;
class Mkdisk* mkdisk;
class Mount* mount;
class Rep* rep;
class Rmdisk* rmdisk;
class Unmount* unmount;
class Mkfs* mkfs;
class Login* login;
class Rmgrp* rmgrp;
class Mkgrp* mkgrp;
class Mkusr* mkusr;
class Rmusr* rmusr;
class Chmod* chmod;
class Mkfile* mkfile;
class Mkdir* mkdir;
}
%token<TEXT> numero;
%token<TEXT> cadena;
%token<TEXT> pmkdisk;
%token<TEXT> psize;
%token<TEXT> pfit;
%token<TEXT> punit;
%token<TEXT> ppath;
%token<TEXT> prmdisk;
%token<TEXT> pfdisk;
%token<TEXT> ptype;
%token<TEXT> pdetele;
%token<TEXT> pname;
%token<TEXT> padd;
%token<TEXT> pmount;
%token<TEXT> punmount;
%token<TEXT> pid;
%token<TEXT> prep;
%token<TEXT> pexec;
%token<TEXT> id;
%token<TEXT> igual;
%token<TEXT> guion;
%token<TEXT> pb;
%token<TEXT> pk;
%token<TEXT> pm;
%token<TEXT> pbf;
%token<TEXT> pff;
%token<TEXT> pwf;
%token<TEXT> pp;
%token<TEXT> pe;
%token<TEXT> pl;
%token<TEXT> pfast;
%token<TEXT> pfull;
%token<TEXT> pmbr;
%token<TEXT> pdisk;
%token<TEXT> pmkfs;
%token<TEXT> pfs;
%token<TEXT> p2fs;
%token<TEXT> p3fs;
%token<TEXT> plogin;
%token<TEXT> pusr;
%token<TEXT> ppwd;
%token<TEXT> plogout;
%token<TEXT> prmgrp;
%token<TEXT> pmkgrp;
%token<TEXT> pmkusr;
%token<TEXT> pgrp;
%token<TEXT> prmusr;
%token<TEXT> pchmod;
%token<TEXT> pr;
%token<TEXT> pugo;
%token<TEXT> pmkfile;
%token<TEXT> pcont;
%token<TEXT> pmkdir;
%token<TEXT> ampersand;
%token<TEXT> mayorQ;
%token<TEXT> porcentaje;

/*No terminales*/
%type<TEXT> INICIO;
%type<TEXT> LCOMANDOS;
%type<TEXT> COMANDO;
%type<mkdisk> PROPIEDADESMK;
%type<TEXT> AJUSTE;
%type<TEXT> UNIDAD;
%type<rmdisk> PROPIEDADESRM;
%type<fdisk> PROPIEDADESFD;
%type<TEXT> DELETE;
%type<NUM> E;
%type<mount> PROPIEDADESMOUNT;
%type<unmount> PROPIEDADESUNMOUNT;
%type<rep> PROPIEDADESREP;
%type<TEXT> NAME;
%type<exec> PROPIEDADESEXEC;
%type<TEXT> PATH;
%type<TEXT> TYPE;
%type<mkfs> PROPIEDADESMKFS;
%type<TEXT> FORMAT;
%type<TEXT> VALUE;
%type<login> PROPIEDADESLOGIN;
%type<rmgrp> PROPIEDADESRMGRP;
%type<mkgrp> PROPIEDADESMKGRP;
%type<mkusr> PROPIEDADESMKUSR;
%type<rmusr> PROPIEDADESRMUSR;
%type<chmod> PROPIEDADESCHMOD;
%type<mkfile> PROPIEDADESMKFILE;
%type<mkdir> PROPIEDADESMKDIR;

%start INICIO

%%

INICIO : LCOMANDOS;

LCOMANDOS : LCOMANDOS COMANDO
           |COMANDO;

COMANDO : pmkdisk PROPIEDADESMK { listCommand.push_back($2); }
         |prmdisk PROPIEDADESRM { listCommand.push_back($2); }
         |pfdisk PROPIEDADESFD { listCommand.push_back($2); }
         |pmount PROPIEDADESMOUNT { listCommand.push_back($2); }
         |punmount PROPIEDADESUNMOUNT { listCommand.push_back($2); }
         |prep PROPIEDADESREP { listCommand.push_back($2); }
         |pexec PROPIEDADESEXEC { listCommand.push_back($2); }
         |pmkfs PROPIEDADESMKFS { listCommand.push_back($2); }
         |plogin PROPIEDADESLOGIN { listCommand.push_back($2); }
         |plogout { listCommand.push_back(new Logout()); }
         |pmkgrp PROPIEDADESMKGRP { listCommand.push_back($2); }
         |prmgrp PROPIEDADESRMGRP { listCommand.push_back($2); }
         |pmkusr PROPIEDADESMKUSR { listCommand.push_back($2); }
         |prmusr PROPIEDADESRMUSR { listCommand.push_back($2); }
         |pchmod PROPIEDADESCHMOD { listCommand.push_back($2); }
         |pmkfile PROPIEDADESMKFILE { listCommand.push_back($2); }
         |pmkdir PROPIEDADESMKDIR { listCommand.push_back($2); }
         |error;

PROPIEDADESMK : PROPIEDADESMK ampersand psize guion mayorQ numero { $$ = $1; $$->size = std::stoi($6); }
               |PROPIEDADESMK porcentaje punit guion mayorQ UNIDAD { $$ = $1; $$->unit = $6; }
               |PROPIEDADESMK ampersand ppath guion mayorQ PATH { $$ = $1; $$->path = $6; }
               |PROPIEDADESMK ampersand pname guion mayorQ id { $$ = $1; $$->name = $6; }
               |ampersand pname guion mayorQ id { $$ = new Mkdisk(); $$->name = $5; }
               |ampersand psize guion mayorQ numero { $$ =  new Mkdisk(); $$->size = std::stoi($5); }
               |porcentaje punit guion mayorQ UNIDAD { $$ = new Mkdisk(); $$->unit = $5; }
               |ampersand ppath guion mayorQ PATH { $$ = new Mkdisk(); $$->path = $5; };

AJUSTE : pbf { strcpy($$, "bf"); }
        |pff { strcpy($$, "ff"); }
        |pwf { strcpy($$, "wf"); };

UNIDAD : pk { strcpy($$, "k"); }
        |pm { strcpy($$, "m"); };

PATH : cadena { std::string text = $1; text.replace(0,1,""); text.replace(text.length()-1, 1, ""); strcpy($$, text.c_str()); }
      |id { strcpy($$, $1); };

PROPIEDADESRM : guion ppath igual PATH { $$ = new Rmdisk(); $$->path = $4; };

PROPIEDADESFD : PROPIEDADESFD guion psize igual numero { $$ = $1; $$->size = std::stoi($5); }
               |PROPIEDADESFD guion punit igual UNIDAD { $$ = $1; $$->unit = $5; }
               |PROPIEDADESFD guion ppath igual PATH { $$ = $1; $$->path = $5; }
               |PROPIEDADESFD guion ptype igual TYPE { $$ = $1; $$->type = $5; }
               |PROPIEDADESFD guion pdetele igual DELETE { $$ = $1; $$->toDelete = $5; }
               |PROPIEDADESFD guion pname igual PATH { $$ = $1; $$->name = $5; }
               |PROPIEDADESFD guion padd igual E { $$ = $1; $$->add = $5; $$->isAdd = true; }
               |PROPIEDADESFD guion pfit igual AJUSTE { $$ = $1; $$->fit = $5; }
               |guion psize igual numero { $$ = new Fdisk(); $$->size = std::stoi($4); }
               |guion punit igual UNIDAD { $$ = new Fdisk(); $$->unit = $4; }
               |guion ppath igual PATH { $$ = new Fdisk(); $$->path = $4; }
               |guion ptype igual TYPE { $$ = new Fdisk(); $$->type = $4; }
               |guion pdetele igual DELETE { $$ = new Fdisk(); $$->toDelete = $4; }
               |guion pname igual PATH { $$ = new Fdisk(); $$->name = $4; }
               |guion padd igual E { $$ = new Fdisk(); $$->add = $4; $$->isAdd = true; }
               |guion pfit igual AJUSTE { $$ = new Fdisk(); $$->fit = $4; };

DELETE : pfast { strcpy($$, "fast"); }
        |pfull { strcpy($$, "full"); };

E : numero { $$ = std::stoi($1); }
   |guion numero { $$ = (-1) * std::stoi($2); };

TYPE :  pp { strcpy($$, "p"); }
       |pe { strcpy($$, "e"); }
       |pl { strcpy($$, "l"); };

PROPIEDADESMOUNT : PROPIEDADESMOUNT guion ppath igual PATH { $$ = $1; $$->path = $5; }
                  |PROPIEDADESMOUNT guion pname igual PATH { $$ = $1; $$->name = $5; }
                  |guion ppath igual PATH { $$ = new Mount(); $$->path = $4; }
                  |guion pname igual PATH { $$ = new Mount(); $$->name = $4; };

PROPIEDADESUNMOUNT : pid igual id { $$ = new Unmount(); $$->id = $3; };

PROPIEDADESREP : PROPIEDADESREP guion pname igual NAME { $$ = $1; $$->name = $5; }
                |PROPIEDADESREP guion ppath igual PATH { $$ = $1; $$->path = $5; }
                |PROPIEDADESREP guion pid igual id { $$ = $1; $$->id = $5; }
                |guion pname igual NAME { $$ = new Rep(); $$->name = $4; }
                |guion ppath igual PATH { $$ = new Rep(); $$->path = $4; }
                |guion pid igual id { $$ = new Rep(); $$->id = $4; };

NAME : pmbr { strcpy($$, "mbr"); }
      |pdisk { strcpy($$, "disk"); };

FORMAT : p2fs {strcpy($$, "2fs"); }
        |p3fs { strcpy($$, "3fs"); };

VALUE : id { strcpy($$, $1); }
        |cadena { std::string text = $1; text.replace(0,1,""); text.replace(text.length()-1, 1, ""); strcpy($$, text.c_str()); }
        |numero { strcpy($$, $1); };

PROPIEDADESEXEC : guion ppath igual PATH { $$ = new Exec(); $$->path = $4; };

PROPIEDADESMKFS : PROPIEDADESMKFS guion pid igual id { $$ = $1; $$->id = $5; }
                 |PROPIEDADESMKFS guion ptype igual DELETE { $$ = $1; $$->type = $5; }
                 |PROPIEDADESMKFS guion pfs igual FORMAT { $$ = $1; $$->fs = $5; }
                 |guion pid igual id { $$ = new Mkfs(); $$->id = $4; }
                 |guion ptype igual DELETE { $$ = new Mkfs(); $$->type = $4; }
                 |guion pfs igual FORMAT { $$ = new Mkfs(); $$->fs = $4; };

PROPIEDADESLOGIN : PROPIEDADESLOGIN guion pusr igual PATH { $$ = $1; $$->usr = $5; }
                  |PROPIEDADESLOGIN guion ppwd igual VALUE { $$ = $1; $$->pwd = $5; }
                  |PROPIEDADESLOGIN guion pid igual id { $$ = $1; $$->id = $5; }
                  |guion pusr igual PATH { $$ = new Login(); $$->usr = $4; }
                  |guion ppwd igual VALUE { $$ = new Login(); $$->pwd = $4; }
                  |guion pid igual id { $$ = new Login(); $$->id = $4; }

PROPIEDADESRMGRP : guion pname igual PATH { $$ = new Rmgrp(); $$->name = $4; }

PROPIEDADESMKGRP : guion pname igual PATH { $$ = new Mkgrp(); $$->name = $4; }

PROPIEDADESMKUSR : PROPIEDADESMKUSR guion pusr igual VALUE { $$ = $1; $$->usr = $5; }
                  |PROPIEDADESMKUSR guion ppwd igual VALUE { $$ = $1; $$->pwd = $5; }
                  |PROPIEDADESMKUSR guion pgrp igual VALUE { $$ = $1; $$->grp = $5; }
                  |guion pusr igual VALUE { $$ = new Mkusr(); $$->usr = $4; }
                  |guion ppwd igual VALUE { $$ = new Mkusr(); $$->pwd = $4; }
                  |guion pgrp igual VALUE { $$ = new Mkusr(); $$->grp = $4; }

PROPIEDADESRMUSR : guion pusr igual PATH { $$ = new Rmusr(); $$->usr = $4; }

PROPIEDADESCHMOD : PROPIEDADESCHMOD guion ppath igual PATH { $$ = $1; $$->path = $5; }
                  |PROPIEDADESCHMOD guion pugo igual numero { $$ = $1; $$->ugo = std::stoi($5); }
                  |PROPIEDADESCHMOD guion pr { $$ = $1; $$->isRecursive = true; }
                  |guion ppath igual PATH { $$ = new Chmod(); $$->path = $4; }
                  |guion pugo igual numero { $$ = new Chmod(); $$->ugo = std::stoi($4); }
                  |guion pr { $$ = new Chmod(); $$->isRecursive = true; }

PROPIEDADESMKFILE : PROPIEDADESMKFILE guion ppath igual PATH { $$ = $1; $$->path = $5; }
                   |PROPIEDADESMKFILE guion pp { $$ = $1; $$->isP = true; }
                   |PROPIEDADESMKFILE guion psize igual numero { $$ = $1; $$->size = std::stoi($5); }
                   |PROPIEDADESMKFILE guion pcont igual PATH { $$ = $1; $$->cont = $5; }
                   |guion ppath igual PATH { $$ = new Mkfile(); $$->path = $4; }
                   |guion pp { $$ = new Mkfile(); $$->isP = true; }
                   |guion psize igual numero { $$ = new Mkfile(); $$->size = std::stoi($4); }
                   |guion pcont igual PATH { $$ = new Mkfile(); $$->cont = $4; }

PROPIEDADESMKDIR : PROPIEDADESMKDIR guion ppath igual PATH { $$ = $1; $$->path = $5; }
                  |PROPIEDADESMKDIR guion pp { $$ = $1; $$->isP = true; }
                  |guion ppath igual PATH { $$ = new Mkdir(); $$->path = $4; }
                  |guion pp { $$ = new Mkdir(); $$->isP = true; }


%%
