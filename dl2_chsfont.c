#include "dl2_all.h"

int fh_HZK = 0;

int open_font()
{
	fh_HZK = open_file(HZK_FILE_NAME,_OPENMODE_READ);
	return fh_HZK;
}

int close_font()
{
	close_file(fh_HZK);
	return 0;
}

void print_chs_char (int x,int y,int sel,uchar c1,uchar c2)
{
	unsigned char mat[8];
	int i,j,k;
	int sec,pot; 
	sec = c1-0xa1;
	pot = c2-0xa1;
	read_file(fh_HZK,mat,8,(94*sec+pot)*8);
	draw_picture(x,y,8,8,sel,mat);
}

void print_chs_str (int x,int y,int sel,const uchar * str)
{
	int		i;
	int		l = 0;
	uchar	temp[] = " ";
	int		cx;

	for (i=0;str[i];l++)
	{
		cx = x+l*8;
		if (is_chschar(str[i]))
		{
			
			print_chs_char (cx,y,sel,str[i],str[i+1]);
			++i,++i;
		}
		else
		{
			temp[0] = str[i];
			PrintXY(cx+1,y,temp,0);

			if(sel) Bdisp_AreaReverseVRAM (cx,y,cx+7,y+7);

			++i;
		}
		
	}
}

