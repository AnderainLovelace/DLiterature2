#include "dl2_all.h"

#define PAGE_MAX (2048*2)

uchar 		page_offset[PAGE_MAX];
uint		page_size	=	0	;
uint		page_now	=	0	;
uint		file_size	=	0	;
uint		file_offset	=	0	;
const char	*file_name			;
int			fh_txt		=	0	;

int split_page ()
{
	int i,x,y,l;
	char c;

	page_offset[0]	= 0;
	page_size		= 0;
	page_now		= 0;
	
	x = 0,y = 8,l = 0;

	for (i=0;i<file_size;)
	{
		read_file (fh_txt,&c,1,i++);l++;

		if (is_chschar(c))
		{
			++i;l++;
		}
		else if (c=='\n')
		{
			x=128;
		}
		x += 8;
		if (x>=128)
		{
			x=0;y+=8;
		}
		if (y>=64 || i>=file_size)
		{
			/* save a offset */
			page_offset[page_size] = l;
			page_size++;
			x = 0;
			y = 8;
			l = 0;
		}
		if (page_size>=PAGE_MAX)
			return 0;

	}/* for */

	return 1;

}

int redraw_screen ()
{
	char	strtemp[16];
	int		x,y;
	uint	i;
	uchar	temp[] = " ",c1,c2;
	

	all_clr();

	printmini(1,1,(const uchar*)file_name,0);
	sprintf(strtemp,"%d/%d",page_now+1,page_size);
	printmini(127-4*strlen(strtemp),1,(const uchar*)strtemp,0);

	area_rev(0,0,127,7);

	x = 0,y = 8;

	for (i = file_offset;i<file_size;)
	{
		read_file (fh_txt,&c1,1,i++);

		if (is_chschar(c1))
		{
			read_file (fh_txt,&c2,1,i++);
			print_chs_char (x,y,0,c1,c2);
		}
		else if (c1=='\n')
		{
			x=128;
		}
		else
		{
			temp[0] = c1;
			PrintXY(x+1,y,temp,0);
		}
		x += 8;
		if (x>=128)
		{
			x=0;y+=8;
			if (y>=64) break;
		}
		
	}
	return 0;
}

int start_read (const char * cfname)
{
	uint key;
	int  refresh=1;

	file_name	= cfname;
	fh_txt		= open_file(cfname,_OPENMODE_READ );
	
	if(fh_txt<=0)
	{
		show_dialog((uchar*)"错误！",(uchar*)"文件打开失败。",DLG_ICON_WARN,DLG_BTN_OK);
		wait(KEY_CTRL_EXE);
		return 0;
	}

	file_size = get_file_size(fh_txt)-1;

	show_dialog((uchar*)"提示",(uchar*)"分页中，请稍等…",2,0);
	putdisp();
	
	if(split_page ()==0)
	{
		show_dialog((uchar*)"错误！",(uchar*)"错误：页数超出限制，无法读取。",DLG_ICON_WARN,DLG_BTN_OK);
		wait(KEY_CTRL_EXE);
		close_file (fh_txt);
		return 0;
	}

	while(1)
	{
		if(refresh = 1)
		{
			redraw_screen ();
			refresh = 0;
		}

		GetKey(&key);

		if (key==KEY_CTRL_UP)
		{
			if (page_now<=0) continue;
			file_offset -= page_offset[--page_now];
			refresh = 1;
		}
		if (key==KEY_CTRL_DOWN)
		{
			if (page_now+1>=page_size) continue;
			file_offset += page_offset[page_now++];
			refresh = 1;
		}
		if (key==KEY_CTRL_EXIT)
		{
			uint key;
			show_dialog((uchar*)"提示",(uchar*)"确定关闭本文件吗？",DLG_ICON_QUST,DLG_BTN_YESNO);
			while(1)
			{
				GetKey(&key);
				if (key==KEY_CTRL_EXE) goto END;
				if (key==KEY_CTRL_EXIT) {refresh = 1;break;}
			}
		}
	}
	END:
	close_file(fh_txt);
	return 0;
}


int AddIn_main(int isAppli, unsigned short OptionNum)
{
	uint key,index = 1;
	int refresh = 1;
	
	all_clr();

	if(open_font()<=0)
	{
		locate(1,1);Print((uchar*)"open hzk error");
		waitkey();
		return 0;
	}
	while(1)
	{
		if (refresh)
		{
			all_clr();
			draw_picture(2,2,128,24,0,PIC_BACK);

			print_chs_str(8,16,0,(uchar*)"打开文本文件从…");
			print_chs_str(76,32,0,(uchar*)"左右键选择 ");
			print_chs_str(76,40,0,(uchar*)(index ? "[闪 存]":"[SD卡]"));

			printmini(72,58,"Anderain 2012",0);
			draw_picture( 8,26,32,32,index==1,PIC_FLS);
			draw_picture(40,26,32,32,index==0,PIC_CRD);
			refresh = 0;
		}

		GetKey(&key);

		if (key==KEY_CTRL_LEFT || key==KEY_CTRL_RIGHT)
		{
			refresh = 1,index=!index;
		}
		if (key==KEY_CTRL_EXE)
		{
			char cfname[32],s[64];
			int	 r;

			refresh = 1;
			r = file_view(index,cfname);

			if (r<0)
			{
				show_dialog((uchar*)"错误！",(uchar*)"没有文本文件！",DLG_ICON_WARN,DLG_BTN_OK);
				wait(KEY_CTRL_EXE);
				continue;
			}
			else if(r==1);
			{
				sprintf(s,"\\\\%s\\%s",(index ? "fls0":"crd0"),cfname);
				start_read(s);
			}

		}
	}
	
    return 1;
}



#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

