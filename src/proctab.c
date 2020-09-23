#include <stdio.h>
#include "awk.h"
#include "awkgram.tab.h"

static const char * const printname[96] = {
	"FIRSTTOKEN",	/* 258 */
	"PROGRAM",	/* 259 */
	"PASTAT",	/* 260 */
	"PASTAT2",	/* 261 */
	"XBEGIN",	/* 262 */
	"XEND",	/* 263 */
	"NL",	/* 264 */
	"ARRAY",	/* 265 */
	"MATCH",	/* 266 */
	"NOTMATCH",	/* 267 */
	"MATCHOP",	/* 268 */
	"FINAL",	/* 269 */
	"DOT",	/* 270 */
	"ALL",	/* 271 */
	"CCL",	/* 272 */
	"NCCL",	/* 273 */
	"CHAR",	/* 274 */
	"OR",	/* 275 */
	"STAR",	/* 276 */
	"QUEST",	/* 277 */
	"PLUS",	/* 278 */
	"EMPTYRE",	/* 279 */
	"ZERO",	/* 280 */
	"IGNORE_PRIOR_ATOM",	/* 281 */
	"AND",	/* 282 */
	"BOR",	/* 283 */
	"APPEND",	/* 284 */
	"EQ",	/* 285 */
	"GE",	/* 286 */
	"GT",	/* 287 */
	"LE",	/* 288 */
	"LT",	/* 289 */
	"NE",	/* 290 */
	"IN",	/* 291 */
	"ARG",	/* 292 */
	"BLTIN",	/* 293 */
	"BREAK",	/* 294 */
	"CLOSE",	/* 295 */
	"CONTINUE",	/* 296 */
	"DELETE",	/* 297 */
	"DO",	/* 298 */
	"EXIT",	/* 299 */
	"FOR",	/* 300 */
	"FUNC",	/* 301 */
	"SUB",	/* 302 */
	"GSUB",	/* 303 */
	"IF",	/* 304 */
	"INDEX",	/* 305 */
	"LSUBSTR",	/* 306 */
	"MATCHFCN",	/* 307 */
	"NEXT",	/* 308 */
	"NEXTFILE",	/* 309 */
	"ADD",	/* 310 */
	"MINUS",	/* 311 */
	"MULT",	/* 312 */
	"DIVIDE",	/* 313 */
	"MOD",	/* 314 */
	"ASSIGN",	/* 315 */
	"ASGNOP",	/* 316 */
	"ADDEQ",	/* 317 */
	"SUBEQ",	/* 318 */
	"MULTEQ",	/* 319 */
	"DIVEQ",	/* 320 */
	"MODEQ",	/* 321 */
	"POWEQ",	/* 322 */
	"PRINT",	/* 323 */
	"PRINTF",	/* 324 */
	"SPRINTF",	/* 325 */
	"ELSE",	/* 326 */
	"INTEST",	/* 327 */
	"CONDEXPR",	/* 328 */
	"POSTINCR",	/* 329 */
	"PREINCR",	/* 330 */
	"POSTDECR",	/* 331 */
	"PREDECR",	/* 332 */
	"VAR",	/* 333 */
	"IVAR",	/* 334 */
	"VARNF",	/* 335 */
	"CALL",	/* 336 */
	"NUMBER",	/* 337 */
	"STRING",	/* 338 */
	"REGEXPR",	/* 339 */
	"GETLINE",	/* 340 */
	"SUBSTR",	/* 341 */
	"SPLIT",	/* 342 */
	"RETURN",	/* 343 */
	"WHILE",	/* 344 */
	"CAT",	/* 345 */
	"UPLUS",	/* 346 */
	"UMINUS",	/* 347 */
	"NOT",	/* 348 */
	"POWER",	/* 349 */
	"INCR",	/* 350 */
	"DECR",	/* 351 */
	"INDIRECT",	/* 352 */
	"LASTTOKEN",	/* 353 */
};


Cell *(*proctab[96])(Node **, int) = {
	nullproc,	/* FIRSTTOKEN */
	program,	/* PROGRAM */
	pastat,	/* PASTAT */
	dopa2,	/* PASTAT2 */
	nullproc,	/* XBEGIN */
	nullproc,	/* XEND */
	nullproc,	/* NL */
	array,	/* ARRAY */
	matchop,	/* MATCH */
	matchop,	/* NOTMATCH */
	nullproc,	/* MATCHOP */
	nullproc,	/* FINAL */
	nullproc,	/* DOT */
	nullproc,	/* ALL */
	nullproc,	/* CCL */
	nullproc,	/* NCCL */
	nullproc,	/* CHAR */
	nullproc,	/* OR */
	nullproc,	/* STAR */
	nullproc,	/* QUEST */
	nullproc,	/* PLUS */
	nullproc,	/* EMPTYRE */
	nullproc,	/* ZERO */
	nullproc,	/* IGNORE_PRIOR_ATOM */
	boolop,	/* AND */
	boolop,	/* BOR */
	nullproc,	/* APPEND */
	relop,	/* EQ */
	relop,	/* GE */
	relop,	/* GT */
	relop,	/* LE */
	relop,	/* LT */
	relop,	/* NE */
	instat,	/* IN */
	arg,	/* ARG */
	bltin,	/* BLTIN */
	jump,	/* BREAK */
	closefile,	/* CLOSE */
	jump,	/* CONTINUE */
	awkdelete,	/* DELETE */
	dostat,	/* DO */
	jump,	/* EXIT */
	forstat,	/* FOR */
	nullproc,	/* FUNC */
	sub,	/* SUB */
	gsub,	/* GSUB */
	ifstat,	/* IF */
	sindex,	/* INDEX */
	nullproc,	/* LSUBSTR */
	matchop,	/* MATCHFCN */
	jump,	/* NEXT */
	jump,	/* NEXTFILE */
	arith,	/* ADD */
	arith,	/* MINUS */
	arith,	/* MULT */
	arith,	/* DIVIDE */
	arith,	/* MOD */
	assign,	/* ASSIGN */
	nullproc,	/* ASGNOP */
	assign,	/* ADDEQ */
	assign,	/* SUBEQ */
	assign,	/* MULTEQ */
	assign,	/* DIVEQ */
	assign,	/* MODEQ */
	assign,	/* POWEQ */
	printstat,	/* PRINT */
	awkprintf,	/* PRINTF */
	awksprintf,	/* SPRINTF */
	nullproc,	/* ELSE */
	intest,	/* INTEST */
	condexpr,	/* CONDEXPR */
	incrdecr,	/* POSTINCR */
	incrdecr,	/* PREINCR */
	incrdecr,	/* POSTDECR */
	incrdecr,	/* PREDECR */
	nullproc,	/* VAR */
	nullproc,	/* IVAR */
	getnf,	/* VARNF */
	call,	/* CALL */
	nullproc,	/* NUMBER */
	nullproc,	/* STRING */
	nullproc,	/* REGEXPR */
	awkgetline,	/* GETLINE */
	substr,	/* SUBSTR */
	split,	/* SPLIT */
	jump,	/* RETURN */
	whilestat,	/* WHILE */
	cat,	/* CAT */
	arith,	/* UPLUS */
	arith,	/* UMINUS */
	boolop,	/* NOT */
	arith,	/* POWER */
	nullproc,	/* INCR */
	nullproc,	/* DECR */
	indirect,	/* INDIRECT */
	nullproc,	/* LASTTOKEN */
};

const char *tokname(int n)
{
	static char buf[100];

	if (n < FIRSTTOKEN || n > LASTTOKEN) {
		snprintf(buf, sizeof(buf), "token %d", n);
		return buf;
	}
	return printname[n-FIRSTTOKEN];
}