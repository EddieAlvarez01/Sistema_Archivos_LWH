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
#include "loss.h"
#include "recovery.h"
#include "pause.h"
#include "cat.h"
#include "ren.h"

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
class Loss* loss;
class Recovery* recovery;
class Pause* pause;
class Cat* cat;
class Ren* ren;
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
%token<TEXT> pallocation;
%token<TEXT> pc;
%token<TEXT> pix;
%token<TEXT> pruta;
%token<TEXT> pbm_arbdir;
%token<TEXT> pbm_detdir;
%token<TEXT> pbm_inode;
%token<TEXT> pbm_block;
%token<TEXT> ploss;
%token<TEXT> precovery;
%token<TEXT> pbitacora;
%token<TEXT> pdirectorio;
%token<TEXT> ptree_file;
%token<TEXT> psb;
%token<TEXT> ptree_complete;
%token<TEXT> pls;
%token<TEXT> ptree_directorio;
%token<TEXT> ppause;
%token<TEXT> pcat;
%token<TEXT> pfile;
%token<TEXT> pren;

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
%type<TEXT> VALUE;
%type<TEXT> ALLOCATION;
%type<login> PROPIEDADESLOGIN;
%type<rmgrp> PROPIEDADESRMGRP;
%type<mkgrp> PROPIEDADESMKGRP;
%type<mkusr> PROPIEDADESMKUSR;
%type<rmusr> PROPIEDADESRMUSR;
%type<chmod> PROPIEDADESCHMOD;
%type<mkfile> PROPIEDADESMKFILE;
%type<mkdir> PROPIEDADESMKDIR;
%type<loss> PROPIEDADESLOSS;
%type<recovery> PROPIEDADESRECOVERY;
%type<cat> PROPIEDADESCAT;
%type<ren> PROPIEDADESREN;

%start INICIO

%%

INICIO : LCOMANDOS;

LCOMANDOS : LCOMANDOS COMANDO
           |COMANDO;

COMANDO : pmkdisk PROPIEDADESMK { listCommand.push_back($2); }
         |prmdisk PROPIEDADESRM { listCommand.push_back($2); }
         |pfdisk PROPIEDADESFD { listCommand.push_back($2); }
         |pmount PROPIEDADESMOUNT { listCommand.push_back($2); }
         |pmount { listCommand.push_back(new Mount()); }
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
         |ploss PROPIEDADESLOSS { listCommand.push_back($2); }
         |precovery PROPIEDADESRECOVERY { listCommand.push_back($2); }
         |ppause { listCommand.push_back(new Pause()); }
         |pcat PROPIEDADESCAT { listCommand.push_back($2); }
         |pren PROPIEDADESREN { listCommand.push_back($2); }
         |error;

PROPIEDADESMK : PROPIEDADESMK ampersand psize guion mayorQ numero { $$ = $1; $$->size = std::stoi($6); }
               |PROPIEDADESMK ampersand punit guion mayorQ UNIDAD { $$ = $1; $$->unit = $6; }
               |PROPIEDADESMK ampersand ppath guion mayorQ PATH { $$ = $1; $$->path = $6; }
               |PROPIEDADESMK ampersand pname guion mayorQ id { $$ = $1; $$->name = $6; }
               |ampersand pname guion mayorQ id { $$ = new Mkdisk(); $$->name = $5; }
               |ampersand psize guion mayorQ numero { $$ =  new Mkdisk(); $$->size = std::stoi($5); }
               |ampersand punit guion mayorQ UNIDAD { $$ = new Mkdisk(); $$->unit = $5; }
               |ampersand ppath guion mayorQ PATH { $$ = new Mkdisk(); $$->path = $5; };

AJUSTE : pbf { strcpy($$, "bf"); }
        |pff { strcpy($$, "ff"); }
        |pwf { strcpy($$, "wf"); };

UNIDAD : pb { strcpy($$, "b"); }
        |pk { strcpy($$, "k"); }
        |pm { strcpy($$, "m"); };

PATH : cadena { std::string text = $1; text.replace(0,1,""); text.replace(text.length()-1, 1, ""); strcpy($$, text.c_str()); }
      |id { strcpy($$, $1); };

PROPIEDADESRM :  ampersand ppath guion mayorQ PATH { $$ = new Rmdisk(); $$->path = $5; };

PROPIEDADESFD : PROPIEDADESFD ampersand psize guion mayorQ numero { $$ = $1; $$->size = std::stoi($6); }
               |PROPIEDADESFD ampersand punit guion mayorQ UNIDAD { $$ = $1; $$->unit = $6; }
               |PROPIEDADESFD ampersand ppath guion mayorQ PATH { $$ = $1; $$->path = $6; }
               |PROPIEDADESFD ampersand ptype guion mayorQ TYPE { $$ = $1; $$->type = $6; }
               |PROPIEDADESFD ampersand pdetele guion mayorQ DELETE { $$ = $1; $$->toDelete = $6; }
               |PROPIEDADESFD ampersand pname guion mayorQ PATH { $$ = $1; $$->name = $6; }
               |PROPIEDADESFD ampersand padd guion mayorQ E { $$ = $1; $$->add = $6; $$->isAdd = true; }
               |PROPIEDADESFD ampersand pfit guion mayorQ AJUSTE { $$ = $1; $$->fit = $6; }
               |PROPIEDADESFD ampersand pallocation guion mayorQ ALLOCATION { $$ = $1; $$->allocation = $6; }
               |ampersand psize guion mayorQ numero { $$ = new Fdisk(); $$->size = std::stoi($5); }
               |ampersand punit guion mayorQ UNIDAD { $$ = new Fdisk(); $$->unit = $5; }
               |ampersand ppath guion mayorQ PATH { $$ = new Fdisk(); $$->path = $5; }
               |ampersand ptype guion mayorQ TYPE { $$ = new Fdisk(); $$->type = $5; }
               |ampersand pdetele guion mayorQ DELETE { $$ = new Fdisk(); $$->toDelete = $5; }
               |ampersand pname guion mayorQ PATH { $$ = new Fdisk(); $$->name = $5; }
               |ampersand padd guion mayorQ E { $$ = new Fdisk(); $$->add = $5; $$->isAdd = true; }
               |ampersand pfit guion mayorQ AJUSTE { $$ = new Fdisk(); $$->fit = $5; }
               |ampersand pallocation guion mayorQ ALLOCATION { $$ = new Fdisk(); $$->fit = $5; };

DELETE : pfast { strcpy($$, "fast"); }
        |pfull { strcpy($$, "full"); };

ALLOCATION : pc { strcpy($$, "c"); }
            |pe { strcpy($$, "e"); }
            |pix { strcpy($$, "ix"); };

E : numero { $$ = std::stoi($1); }
   |guion numero { $$ = (-1) * std::stoi($2); };

TYPE :  pp { strcpy($$, "p"); }
       |pe { strcpy($$, "e"); }
       |pl { strcpy($$, "l"); };

PROPIEDADESMOUNT : PROPIEDADESMOUNT ampersand ppath guion mayorQ PATH { $$ = $1; $$->path = $6; }
                  |PROPIEDADESMOUNT ampersand pname guion mayorQ PATH { $$ = $1; $$->name = $6; }
                  |ampersand ppath guion mayorQ PATH { $$ = new Mount(); $$->path = $5; }
                  |ampersand pname guion mayorQ PATH { $$ = new Mount(); $$->name = $5; };

PROPIEDADESUNMOUNT : PROPIEDADESUNMOUNT ampersand pid guion mayorQ id { $$ = $1; $$->id += "|" + std::string($6); }
                    |ampersand pid guion mayorQ id { $$ = new Unmount(); $$->id = $5; };

PROPIEDADESREP : PROPIEDADESREP ampersand pname guion mayorQ NAME { $$ = $1; $$->name = $6; }
                |PROPIEDADESREP ampersand ppath guion mayorQ PATH { $$ = $1; $$->path = $6; }
                |PROPIEDADESREP ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                |PROPIEDADESREP ampersand pruta guion mayorQ PATH { $$ = $1; $$->route = $6; }
                |ampersand pname guion mayorQ NAME { $$ = new Rep(); $$->name = $5; }
                |ampersand ppath guion mayorQ PATH { $$ = new Rep(); $$->path = $5; }
                |ampersand pid guion mayorQ id { $$ = new Rep(); $$->id = $5; }
                |ampersand pruta guion mayorQ PATH { $$ = new Rep(); $$->route = $5; };

NAME : pmbr { strcpy($$, "mbr"); }
      |pdisk { strcpy($$, "disk"); }
      |pbm_arbdir { strcpy($$, "bm_arbdir"); }
      |pbm_detdir { strcpy($$, "bm_detdir"); }
      |pbm_inode { strcpy($$, "bm_inode"); }
      |pbm_block { strcpy($$, "bm_block"); }
      |pbitacora { strcpy($$, "bitacora"); }
      |pdirectorio { strcpy($$, "directorio"); }
      |ptree_file { strcpy($$, "tree_file"); }
      |psb { strcpy($$, "sb"); }
      |ptree_complete { strcpy($$, "tree_complete"); }
      |pls { strcpy($$, "ls"); }
      |ptree_directorio { strcpy($$, "tree_directorio"); };

VALUE : id { strcpy($$, $1); }
        |cadena { std::string text = $1; text.replace(0,1,""); text.replace(text.length()-1, 1, ""); strcpy($$, text.c_str()); }
        |numero { strcpy($$, $1); };

PROPIEDADESEXEC : ampersand ppath guion mayorQ PATH { $$ = new Exec(); $$->path = $5; };

PROPIEDADESMKFS : PROPIEDADESMKFS ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                 |PROPIEDADESMKFS ampersand ptype guion mayorQ DELETE { $$ = $1; $$->type = $6; }
                 |PROPIEDADESMKFS ampersand padd guion mayorQ E { $$ = $1; $$->add = $6; $$->isAdd = true; }
                 |PROPIEDADESMKFS ampersand ptype guion mayorQ UNIDAD { $$ = $1; $$->unit = $6; }
                 |ampersand pid guion mayorQ id { $$ = new Mkfs(); $$->id = $5; }
                 |ampersand ptype guion mayorQ DELETE { $$ = new Mkfs(); $$->type = $5; }
                 |ampersand padd guion mayorQ E { $$ = new Mkfs(); $$->add = $5; $$->isAdd = true; }
                 |ampersand ptype guion mayorQ UNIDAD { $$ = new Mkfs(); $$->unit = $5; };

PROPIEDADESLOGIN : PROPIEDADESLOGIN ampersand pusr guion mayorQ PATH { $$ = $1; $$->usr = $6; }
                  |PROPIEDADESLOGIN ampersand ppwd guion mayorQ VALUE { $$ = $1; $$->pwd = $6; }
                  |PROPIEDADESLOGIN ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                  |ampersand pusr guion mayorQ PATH { $$ = new Login(); $$->usr = $5; }
                  |ampersand ppwd guion mayorQ VALUE { $$ = new Login(); $$->pwd = $5; }
                  |ampersand pid guion mayorQ id { $$ = new Login(); $$->id = $5; }

PROPIEDADESRMGRP : PROPIEDADESRMGRP ampersand pname guion mayorQ PATH { $$ = $1; $$->name = $6; }
                  |PROPIEDADESRMGRP ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                  |ampersand pname guion mayorQ PATH { $$ = new Rmgrp(); $$->name = $5; }
                  |ampersand pid guion mayorQ id { $$ = new Rmgrp(); $$->id = $5; }

PROPIEDADESMKGRP : PROPIEDADESMKGRP ampersand pname guion mayorQ PATH { $$ = $1; $$->name = $6; }
                  |PROPIEDADESMKGRP ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                  |ampersand pname guion mayorQ PATH { $$ = new Mkgrp(); $$->name = $5; }
                  |ampersand pid guion mayorQ id { $$ = new Mkgrp(); $$->id = $5; }

PROPIEDADESMKUSR : PROPIEDADESMKUSR ampersand pusr guion mayorQ VALUE { $$ = $1; $$->usr = $6; }
                  |PROPIEDADESMKUSR ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                  |PROPIEDADESMKUSR ampersand ppwd guion mayorQ VALUE { $$ = $1; $$->pwd = $6; }
                  |PROPIEDADESMKUSR ampersand pgrp guion mayorQ VALUE { $$ = $1; $$->grp = $6; }
                  |ampersand pusr guion mayorQ VALUE { $$ = new Mkusr(); $$->usr = $5; }
                  |ampersand ppwd guion mayorQ VALUE { $$ = new Mkusr(); $$->pwd = $5; }
                  |ampersand pgrp guion mayorQ VALUE { $$ = new Mkusr(); $$->grp = $5; }
                  |ampersand pid guion mayorQ id { $$ = new Mkusr(); $1; $$->id = $5; };

PROPIEDADESRMUSR : PROPIEDADESRMUSR ampersand pusr guion mayorQ PATH { $$ = $1; $$->usr = $6; }
                  |PROPIEDADESRMUSR ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                  |ampersand pusr guion mayorQ PATH { $$ = new Rmusr(); $$->usr = $5; }
                  |ampersand pid guion mayorQ id { $$ = new Rmusr(); $$->id = $5; };

PROPIEDADESCHMOD : PROPIEDADESCHMOD guion ppath igual PATH { $$ = $1; $$->path = $5; }
                  |PROPIEDADESCHMOD guion pugo igual numero { $$ = $1; $$->ugo = std::stoi($5); }
                  |PROPIEDADESCHMOD guion pr { $$ = $1; $$->isRecursive = true; }
                  |guion ppath igual PATH { $$ = new Chmod(); $$->path = $4; }
                  |guion pugo igual numero { $$ = new Chmod(); $$->ugo = std::stoi($4); }
                  |guion pr { $$ = new Chmod(); $$->isRecursive = true; }

PROPIEDADESMKFILE : PROPIEDADESMKFILE ampersand ppath guion mayorQ PATH { $$ = $1; $$->path = $6; }
                   |PROPIEDADESMKFILE ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                   |PROPIEDADESMKFILE ampersand pp { $$ = $1; $$->isP = true; }
                   |PROPIEDADESMKFILE ampersand psize guion mayorQ numero { $$ = $1; $$->size = std::stoi($6); }
                   |PROPIEDADESMKFILE ampersand pcont guion mayorQ PATH { $$ = $1; $$->cont = $6; }
                   |ampersand ppath guion mayorQ PATH { $$ = new Mkfile(); $$->path = $5; }
                   |ampersand pp { $$ = new Mkfile(); $$->isP = true; }
                   |ampersand pid guion mayorQ id { $$ = new Mkfile(); $$->id = $5; }
                   |ampersand psize guion mayorQ numero { $$ = new Mkfile(); $$->size = std::stoi($5); }
                   |ampersand pcont guion mayorQ PATH { $$ = new Mkfile(); $$->cont = $5; }

PROPIEDADESMKDIR : PROPIEDADESMKDIR ampersand ppath guion mayorQ PATH { $$ = $1; $$->path = $6; }
                  |PROPIEDADESMKDIR ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                  |PROPIEDADESMKDIR ampersand pp { $$ = $1; $$->isP = true; }
                  |ampersand ppath guion mayorQ PATH { $$ = new Mkdir(); $$->path = $5; }
                  |ampersand pp { $$ = new Mkdir(); $$->isP = true; }
                  |ampersand pid guion mayorQ id { $$ = new Mkdir(); $$->id = $5; };

PROPIEDADESLOSS : ampersand pid guion mayorQ id { $$ = new Loss(); $$->id = $5; };

PROPIEDADESRECOVERY : ampersand pid guion mayorQ id { $$ = new Recovery(); $$->id = $5; };

PROPIEDADESCAT : PROPIEDADESCAT ampersand pid guion mayorQ id { $$ = $1; $$->id = $6; }
                |PROPIEDADESCAT ampersand pfile guion mayorQ PATH { $$ = $1; $$->file.push_back($6); }
                |ampersand pid guion mayorQ id { $$ = new Cat(); $$->id = $5; }
                |ampersand pfile guion mayorQ PATH { $$ = new Cat(); $$->file.push_back($5); };

PROPIEDADESREN : PROPIEDADESREN ampersand pid guion mayorQ id { $$ = $1; $$->id = $6;  }
                |PROPIEDADESREN ampersand ppath guion mayorQ PATH { $$ = $1; $$->path = $6;  }
                |PROPIEDADESREN ampersand pname guion mayorQ PATH { $$ = $1; $$->name = $6;  }
                |ampersand pid guion mayorQ id { $$ = new Ren(); $$->id = $5;  }
                |ampersand ppath guion mayorQ PATH { $$ = new Ren(); $$->path = $5;  }
                |ampersand pname guion mayorQ PATH { $$ = new Ren(); $$->name = $5;  };

%%
