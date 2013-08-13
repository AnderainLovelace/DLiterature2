#include "dl2_all.h"

fontc * char_to_font(const char * cfname,fontc * ffname)
{
	int i,len = strlen(cfname);
	for(i=0; i<len ;++i)
		ffname[i] = cfname[i];
	ffname[i]=0;
	return ffname;
}

char * font_to_char(const fontc *ffname,char *cfname)
{
	int i = 0;
	while((cfname[i]=ffname[i])!=0)++i;
	return cfname;
}

int	open_file (const char * cfname,int mode)
{
	fontc ffname[32];

	char_to_font(cfname,ffname);

	return Bfile_OpenFile(ffname,mode);
}
