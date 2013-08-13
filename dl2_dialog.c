#include "dl2_all.h"

/*
	picdata of dialog icon
*/


const uchar ICON_QUST[]=
{0x7,0xE0,0x8,0x10,0x17,0xE8,0x28,0x14,0x53,0xCA,
0xA7,0xE5,0xA6,0x65,0xA0,0xC5,0xA1,0x85,0xA1,0x85,
0xA0,0x5,0x51,0x8A,0x28,0x14,0x17,0xE8,0x8,0x10,0x7,0xE0};

const uchar ICON_WAIT[]= 
{0x1F,0xF8,0x18,0x18,0x1F,0xF8,0x8,0x10,0x8,0x50,
0x5,0x20,0x2,0xC0,0x3,0xC0,0x3,0x40,0x6,0xA0,
0xD,0x50,0xA,0xB0,0xD,0x50,0x1F,0xF8,0x18,0x18,0x1F,0xF8};

const uchar ICON_WARN[]=
{0x1,0x80,0x1,0x80,0x3,0xC0,0x2,0x40,0x6,0x60,0x4,0x20,
0xD,0xB0,0x9,0x90,0x19,0x98,0x11,0x88,0x31,0x8C,0x21,0x84,
0x60,0x6,0x41,0x82,0xC0,0x3,0xFF,0xFF};


/*
	dialog
*/

void show_dialog(const uchar * caption,const uchar * text,int icon,int btn)
{
	int i;
	int left,top,x,y;
	char temp[] = " ";
	uchar *p = NULL;

	area_clear		(6,6,121,57,2);
	print_chs_str	(7,7,0,caption);
	area_rev		(7,7,120,14);

	left = icon ? 32 : 8;
	top  = icon ? 24 : 16;

	x = left,y = top;

	for (i=0;text[i];++i)
	{
		if (is_chschar(text[i]))
		{
			print_chs_char (x,y,0,text[i],text[i+1]);
			++i;
		}
		else if (x='\n') x=120;
		else
		{
			temp[0] = text[i];
			PrintXY(x+1,y,(uchar*)temp,0);
		}
		x+=8;
		if (x>=120) x=left,y+=8;
	}

	switch(icon)
	{
		case DLG_ICON_QUST	:p=ICON_QUST;break;
		case DLG_ICON_WAIT	:p=ICON_WAIT;break;
		case DLG_ICON_WARN	:p=ICON_WARN;break;
		default				:p=0;break;
	}
	if (p)
		draw_picture(12,24,16,16,0,p);

	if (btn==DLG_BTN_YESNO)
		print_chs_str(8,48,1,(uchar*)" 确认EXE  取消EXIT");
	else if (btn==DLG_BTN_OK)
		print_chs_str(32,48,1,(uchar*)" 确定EXE ");
}

/*
	file view
*/

int file_view (int root,char * cfname)
{
	char			strtemp[32];
	fontc			fnttemp[32];
	fontc			fntpath[32];
	char			**clist;
	uint			key;
	list			lfile;
	int				fh_find;
	node			*nnode;
	int				i,top,bottom,index,refresh;
	const int		h_max = 6-1;
	FILE_INFO		file_info;

	list_init(&lfile);

	sprintf(strtemp,"\\\\%s\\*.txt",root ? "fls0":"crd0");
	char_to_font(strtemp,fntpath);

	if(Bfile_FindFirst (fntpath,&fh_find,fnttemp,&file_info)!=0)
	{
		Bfile_FindClose(fh_find);
		return -1;
	}

	do
	{
		list_push(&lfile,font_to_char(fnttemp,strtemp));
	}
	while(Bfile_FindNext(fh_find,fnttemp,&file_info)==0);

	Bfile_FindClose(fh_find);

	clist = (char**)malloc(sizeof(char**)*lfile.size);
	
	for (i=0,nnode=lfile.head;nnode!=NULL;nnode=nnode->next,++i)
	{
		clist[i] = nnode->str;
	}

	/* draw_title & icon */
	{
		char temp[32];
		all_clr();
		sprintf(temp,"打开文件在:%s",root ? "闪存\0":"SD卡");
		print_chs_str(0,0,0,(const uchar*)temp);
		area_rev(0,0,127,7);

		print_chs_str(0,56,0,(uchar*)"[打开EXE] [取消EXIT]");
		area_rev(0,56,127,63);

	}
	/* select file */

	index = 0,refresh = 1;
	while(1)
	{
		if (refresh)
		{
			int y;

			if (bottom-top>h_max)bottom = top + h_max;
			if(top>index)
			{
				top = index;
				bottom = index + h_max;
			}
			if (index>bottom)
			{
				bottom = index;
				top = bottom - h_max;
			}
			if(bottom>lfile.size - 1)bottom = lfile.size - 1;

			area_clear(0,8,127,55,0);

			if(top>0)
				{locate(21,2);Print((uchar*)"\xE6\x92");}
			if(bottom<lfile.size-1)
				{locate(21,7);Print((uchar*)"\xE6\x93");}

			for (i=top;i<=bottom;++i)
			{
				y = i-top+1;
				locate(2,y+1);Print((uchar*)clist[i]);
				if(index==i)area_rev(0,y*8,127,7+y*8);	
			}
		}
		GetKey(&key);

		if (key==KEY_CTRL_UP) 
			{if(--index<0) index = lfile.size - 1;refresh = 1;}
		if (key==KEY_CTRL_DOWN)
			{if(++index>lfile.size - 1) index = 0;refresh = 1;}
		if (key==KEY_CTRL_EXIT)
		{
			free(clist);
			list_destory(&lfile);
		
			return 0;
		}
		if (key==KEY_CTRL_EXE)
		{
			strcpy(cfname,clist[index]);
			free(clist);
			list_destory(&lfile);
		
			return 1;
		}

	}

	free(clist);
	list_destory(&lfile);

	return 0;
}

