#define MY_CODE_HIGHLIGHT 1
#include "mylibc.h"
#include "media.h"

const char colorSchemes[][6] = {
	/* Main color param, fg, bg; decor param, fg, bg */ 
	#define C_BLACK 0
	{MY_INTENSE_FG, MY_GRAY + MY_FG, MY_BLACK + MY_BG, MY_DEF, MY_GREEN + MY_FG, MY_BLACK + MY_BG},
	#define C_PASCAL 1
	{MY_INTENSE_FG, MY_BROWN + MY_FG, MY_BLUE + MY_BG, MY_DEF, MY_GRAY + MY_FG, MY_BLUE + MY_BG},
	#define C_WHITE 2
	{MY_DEF, MY_BLACK + MY_FG, MY_GRAY + MY_BG, MY_DEF, MY_GREEN + MY_FG, MY_GRAY + MY_BG},
	#define C_ERROR 3
	{MY_INTENSE_FG, MY_GRAY + MY_FG, MY_RED + MY_BG, MY_INTENSE_FG, MY_BROWN + MY_FG, MY_RED + MY_BG}
};

typedef struct { 
	char* title;
	char* text;
	int colorSchemeId;
	const char* pic;
	int picSize;
} myFrame;

/* Presentations starts here */
#define MY_SHOW_TIMER 1
#define TOP_BANNER "{  LVEE 2016  }"
#define BOTTOM_BANNER "[ DeXPeriX a.k.a. Hrabrov Dmitry ]"

static const myFrame frames[] = {
{
	"Linux Vacation / Eastern Europe 2016", 
" Написание своей StdLibC", 
	C_WHITE, gConfLogo, sizeof(gConfLogo)
},


{
	"Зачем?", 
" 1) printf под ... "cBROWN"Android"cGRAY", микроконтроллеры, микроволновку\n"
"\n"
" 2) без "cBROWN"зависимости"cGRAY" от библиотек:\n" 
"     $ file yourfile.bin:\n"
"         ELF 64-bit LSB executable, x86-64, statically linked\n"
"     $ ldd yourfile.bin:\n"
"         не является динамическим исполняемым файлом\n"
"\n"
" 3) "cBROWN"минимизация"cGRAY" размера исполняемого файла\n"
"\n"
" 4) чтобы понимать, как всё это "cBROWN"устроено!", 
	C_BLACK, gLocomotive, sizeof(gLocomotive)
},


{
	"Вызов функции ядра Linux", 
CI" static long"CT" _syscall3("CI"int"CT" number, "CI"unsigned long"CT" arg1,\n"
CI"               unsigned long"CT" arg2, "CI"unsigned long"CT" arg3){\n"
CI"   long"CT" result;\n"
"     __asm__ "CI"volatile"CT" ("CSs"int "CR"$0x80"CSs""CT"\n"
"     : "CS"\"=a\""CT" (result)\n"
"     : "CSs"0"CSe" (number), "CSs"b"CSe" (arg1), "CSs"c"CSe" (arg2), "CSs"d"CSe" (arg3)\n"
"     : "CSs"memory"CSe", "CSs"cc"CSe");\n"
"   "CI"return"CT" result;\n"
" }\n"
"\n"
CC" /* Зависимость: компилятор с ассемблером */"
,
	C_PASCAL, gCompilerList, sizeof(gCompilerList)
},


{
	"Пример \"стандартных\" функций через функции ядра",
CP" #include <unistd.h> "CC"/* Для ID функций */\n"
"\n"
CI" static int"CT" close("CI"int"CT" fd){\n"
"    "CI"return (int)"CT"syscall1("CR"__NR_close"CT", fd);\n"
" }\n"
"\n"
CI" static ssize_t"CT" read("CI"int"CT" fd, "CI"const void"CT" *buf, "CI"size_t"CT" count){\n"
"    "CI"return (ssize_t)"CT"syscall3("CR"__NR_read"CT", fd, buf, count);\n"
" }\n"
"\n"
CI" static int"CT" execve("CI"const char"CT" *fname, "CI"char *const"CT" argv[], "CI"char *const"CT" envp[]){\n"
CI"    return (int)"CT"syscall3("CR"__NR_execve"CT", fname, argv, envp);\n"
" }",
	C_PASCAL, gUFO, sizeof(gUFO)
},


{
	"Пример \"стандартных\" функций на чистом Си",
CI" char"CT" toupper("CI"char"CT" symb){\n"
"    "CI"return"CT" symb "CI"-"CT" "CS"'a'"CI" + "CS"'A'"CT";\n"
" }\n"
"\n"
CI" size_t"CT" strlen("CI"const char"CT" *str){\n"
CI"    size_t"CT" len"CI" = "CT"0;\n"
CI"    while"CT"( str[len] "CI"!="CS" 0 "CT") len"CI"++"CT";\n"
CI"    return"CT" len;\n"
" }\n"
"\n"
CI" void"CT"* memcpy("CI"void"CT"* dest, "CI"const void"CT"* src, "CI"size_t"CT" count){ \n"
CI"    char"CT"* dst8 = ("CI"char"CT"*)dest;\n"
CI"    char"CT"* src8 = ("CI"char"CT"*)src;\n"
CI"    while"CT"( count"CI"--"CT" ){\n"
"        "CR"*dst8++ = *src8++"CT";\n"
"    }\n"
CI"    return"CT" dest;\n"
" }"
, 
	C_PASCAL, gBirdAndArrow, sizeof(gBirdAndArrow)
},


{
	"Оптимизация функций на чистом Си",
CI" void"CT"* memcpy("CI"void"CT"* dest, "CI"const void"CT"* src, "CI"size_t"CT" count){\n"
CI"    char"CT"* dst8 = ("CI"char"CT"*)dest;\n"
CI"    char"CT"* src8 = ("CI"char"CT"*)src;\n"
CI"    if"CT"( count & "CS"1"CT" ){\n"
"        dst8["CS"0"CT"] = src8["CS"0"CT"];\n"
"        dst8 "CI"+= "CS"1"CT";\n"
"        src8 "CI"+= "CS"1"CT";\n"
"    }\n"
"\n"        
CR"    count /= 2"CT";\n"
CI"    while"CT"( count"CI"--"CT" ){\n"
"        dst8["CS"0"CT"] = src8["CS"0"CT"];\n"
"        dst8["CS"1"CT"] = src8["CS"1"CT"];\n"
"        dst8 "CI"+= "CS"2"CT";\n"
"        src8 "CI"+= "CS"2"CT";\n"
"    }\n"
CI"    return"CT" dest;\n"
" }",
	C_PASCAL, gParrot, sizeof(gParrot)
},


{
	"Функция printf",
CI" void"CT" Myprintf("CI"char"CT"* format, "CI"..."CT"){\n"
CI"   char"CT"* s; "CI"int"CT" i;\n"
CI"   va_list"CT" arg;\n"
CS"   va_start"CT"(arg, format);\n"
CI"   for"CT"(i=0; i<"CR"strlen"CT"(format); i"CI"++"CT"){\n"
CI"     if"CT"( format[i] "CI"== "CS"'%'"CT" )\n"
CI"     switch"CT"( format[i+1] ){\n"
CI"       case "CS"'d'"CT":\n"
CR"         MyPutInt"CT"( va_arg(arg, "CI"int"CT") ); i"CI"++"CT"; "CI"break"CT";\n"
CI"       case "CS"'s'"CT":\n"
"         s = va_arg(arg, "CI"char"CT"*);\n"
CR"         MyWrite"CT"( s, "CR"strlen"CT"(s) ); i"CI"++"CT"; "CI"break;\n"
CI"       case "CS"'c'"CT":\n"
CR"         MyPutchar"CT"( va_arg(arg, "CI"int"CT") ); i"CI"++"CT"; "CI"break"CT";\n"
"     } "CI"else"CR" MyPutchar"CT"( format[i] );\n"
"   }\n"
CS"   va_end"CT"(arg);\n"
" }",
	C_PASCAL, gCactus, sizeof(gCactus)
},


{
	"Что это даёт?",
" 1) Цвета\n"
" 2) Размеры и режимы терминала\n"
" 3) Обработка клавиатуры\n"
" 4) Управление курсором\n"
" 5) Юникод (частично)\n"
" 6) Время и таймеры\n"
" 7) Файлы и папки\n"
" 8) sbrk / mmap\n"
" 9) fork\n"
"\n"
" Пример: данная презентация",
	C_BLACK, gJoy, sizeof(gJoy)
},


{
	"Что НЕ даёт?",
" 1) Мышь\n"
" 2) Звук\n"
" 3) Окна\n"
" 4) OpenGL\n"
" 5) malloc\n"
" 6) Threads"
,
	C_ERROR, gError, sizeof(gError)
},


{
	"Спасибо!",
" Слушателям спасибо за внимание!\n"
" Линусу Торвальдсу за GNU/Linux.\n"
" ASCII-художникам, работы которых использованы в презентации.\n"
" Игре \"Winter Novel\", за идеи. Не забудьте купить её в Steam!\n"
" Microsoft .... данная презентация написана в Windows 10! ;-)\n"
"\n"
"\n"
" Скачать эту презентацию можно по адресу:\n"
cBROWN" https://github.com/DeXP/lvee-2016-tinyc-presentation"
, 
	C_BLACK, gCity, sizeof(gCity)
}

};
static const int framesCount = sizeof(frames) / sizeof( frames[0] );


char getKey(int fd){
	int ch;
	struct termios oldt, newt;
	mytcgetattr(fd, &oldt);
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	mytcsetattr(fd, TCSANOW, &newt);
	ch = mygetchar(fd);
	if( ch == 033 ) ch = mygetchar(fd); /* Esc */
	if( ch == '[' ) ch = mygetchar(fd);
	if( (ch == MY_KEY_PGUP) || (ch == MY_KEY_PGDOWN) ) mygetchar(fd);
	mytcsetattr(fd, TCSANOW, &oldt);
	return ch;
}

void draw_frame(int num, long startTime){
	char buf[2048];	int i;
	struct winsize sz;
	long curTime = mytime() - startTime;
	int colId = frames[num].colorSchemeId;
	int cparam = colorSchemes[colId][0];
	int cfg = colorSchemes[colId][1];
	int cbg = colorSchemes[colId][2];
	int dparam = colorSchemes[colId][3];
	int dfg = colorSchemes[colId][4];
	int dbg = colorSchemes[colId][5];

	mygetsizeterm(MY_STD_IN, &sz);
	myfillterm(MY_STD_OUT, dparam, dfg, dbg);
	for(i=0; i<3*sz.ws_col; i++)
        switch( i % 3 ){
			/* Long dash symbol */
            case 0: buf[i] = 226; break;
            case 1: buf[i] = 148; break;
            case 2: buf[i] = 128; break;
        }
	/* top 1 line */
	mymovecursor(MY_STD_OUT, 2, 1);
	mywritebuf(MY_STD_OUT, buf, 3*sz.ws_col);
	/* bottom 1 line */
	mymovecursor(MY_STD_OUT, sz.ws_row-1, 1);
	mywritebuf(MY_STD_OUT, buf, 3*sz.ws_col);

	mysetcolor(MY_STD_OUT, cparam, cfg, cbg);
	/* Top right banner */
	mymovecursor(MY_STD_OUT, 2, sz.ws_col - sizeof(TOP_BANNER) - 1 );
	mywritebuf(MY_STD_OUT, TOP_BANNER, sizeof(TOP_BANNER) - 1 );
	/* Bottom right banner */
	mymovecursor(MY_STD_OUT, sz.ws_row-1, sz.ws_col - sizeof(BOTTOM_BANNER) - 1 );
	mywritebuf(MY_STD_OUT, BOTTOM_BANNER, sizeof(BOTTOM_BANNER) - 1 );
	/* Pages + Timer */
	mymovecursor(MY_STD_OUT, sz.ws_row-1, 5 );
#if defined(MY_SHOW_TIMER) && MY_SHOW_TIMER
	myprintf(MY_STD_OUT, " %d/%d [ %dm %ds ] ", num+1, framesCount, 
			curTime/60 % 60, curTime % 60 );
#else
	myprintf(MY_STD_OUT, " %d/%d ", num+1, framesCount);
	(void)curTime;
#endif

	/* restore params */
	mymovecursor(MY_STD_OUT, 1, 1);
	mysetcolor(MY_STD_OUT, cparam, cfg, cbg);	

	/* Picture */
	if( frames[num].pic != 0 ){
		mywritebuf(MY_STD_OUT, frames[num].pic, frames[num].picSize);
	}

	/* Texts */
	mymovecursor(MY_STD_OUT, 2, 5);
	mysetcolor(MY_STD_OUT, cparam, cfg, cbg);
	myprintf(MY_STD_OUT, "[ %s ]", frames[num].title);
	mymovecursor(MY_STD_OUT, 5, 1);
	mysetcolor(MY_STD_OUT, cparam, cfg, cbg);
	mywritebuf(MY_STD_OUT, frames[num].text, mystrlen(frames[num].text) );
}

void _start(void){
	long startTime = mytime();
	char key = 0;	
	int num = 0;
	myhidecursor(MY_STD_OUT);
	while( num < framesCount ){
		draw_frame(num, startTime);
		key = getKey(MY_STD_IN);
		if( (key == '4') || /* for disabled numpad */
			(key == MY_KEY_UP) || 
			(key == MY_KEY_LEFT) ||
			(key == MY_KEY_PGUP) ||
			(key == MY_KEY_BACKSPACE)
		  ){
		   	num--; /* Prev slide */
		} else num++; /* Next slide*/
		if( num < 0 ) num = 0;
		if( key == 'q' ) num = framesCount;
	}
	myclearscreen(MY_STD_OUT);
	myshowcursor(MY_STD_OUT);
	myexit(0);
}
