%option case-insensitive
%option yylineno
%{
#include <cstdlib>
#include "parser.h"
#include "command.h"
#include <stdio.h>
#include <iostream>
#include <list>

int yylex();
void yyerror(const char *s);
int linea=0; // Para contar lineas
int columna = 1; // para las columnas
int anterior = 0;
std::list<Command*> listCommand;
%}

%option header-file="scanner.h"
%option outfile="scanner.cpp"
%option noyywrap
%option nounput

Commentary "#"[^\r\n]*([\r]|[\n]|[\r\n]|[\n\r])?
letra [a-zñA-ZÑ]+
numero [0-9]+
booleano ("verdadero"|"falso"|"true"|"false")
decimal [0-9]+"."[0-9]+
id ("\/"?({letra}|{numero})*)+({letra}|{numero}|"_"|"."|"\/")*
cadena "\""[^"\""]*"\""


%%
INITIAL
{
{Commentary} {linea++;columna = 0;}
{numero}          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return numero;}
{cadena}          {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return cadena;}
"mkdisk" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pmkdisk;}
"size" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return psize;}
"cont" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pcont;}
"fit" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pfit;}
"unit" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return punit;}
"path" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ppath;}
"rmdisk" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return prmdisk;}
"fdisk" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pfdisk;}
"type" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ptype;}
"allocation" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pallocation;}
"delete" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pdetele;}
"name" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pname;}
"add" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return padd;}
"mount" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pmount;}
"unmount" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return punmount;}
"mkfs" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pmkfs;}
"login" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return plogin;}
"usr" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pusr;}
"pwd" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ppwd;}
"logout" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return plogout;}
"mkgrp" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pmkgrp;}
"rmgrp" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return prmgrp;}
"mkusr" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pmkusr;}
"rmusr" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return prmusr;}
"grp" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pgrp;}
"chmod" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pchmod;}
"mkfile" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pmkfile;}
"mkdir" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pmkdir;}
"r" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pr;}
"ugo" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pugo;}
"id"{numero}* { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pid;}
"rep" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return prep;}
"exec" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pexec;}
"cat" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pcat;}
"file"{numero}* { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pfile;}
"ren" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pren;}
"b" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pb;}
"k" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pk;}
"m" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pm;}
"c" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pc;}
"ix" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pix;}
"bf" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pbf;}
"ff" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pff;}
"fs" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pfs;}
"2fs" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return p2fs;}
"3fs" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return p3fs;}
"wf" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pwf;}
"p" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pp;}
"e" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pe;}
"l" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pl;}
"fast" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pfast;}
"full" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pfull;}
"ruta" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pruta;}
"loss" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ploss;}
"recovery" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return precovery;}
"mbr" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pmbr;}
"disk" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pdisk;}
"bm_arbdir" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pbm_arbdir;}
"bm_detdir" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pbm_detdir;}
"bm_inode" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pbm_inode;}
"bm_block" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pbm_block;}
"bitacora" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pbitacora;}
"directorio" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pdirectorio;}
"tree_file" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ptree_file;}
"sb" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return psb;}
"tree_complete" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ptree_complete;}
"ls" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return pls;}
"tree_directorio" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ptree_directorio;}
"pause" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ppause;}
{id} { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return id;}
"=" { columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return igual;}
"-"         {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return guion; }
">"         {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return mayorQ; }
"&"         {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return ampersand; }
"%"         {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return porcentaje; }
"\t"            {
                    strcpy(yylval.TEXT, yytext); columna=26;
                }
"\r"            {
                    strcpy(yylval.TEXT, yytext); columna=26;
                }
[[:blank:]]     { columna++; }
"\n"            {linea++; columna = 0; anterior = 0;}
.               {
                    columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);
/*                    errorT *nuevoE = new errorT("Lexico",yytext,linea, columna);
*/

                    std::cout <<yytext <<" Error Lexico en la linea "<< linea << " Columna:"<< columna<<  std::endl;
                }
}
%%
