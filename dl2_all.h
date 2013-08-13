#include <fxlib.h>
#include <stdio.h>
#include <string.h>


typedef FONTCHARACTER	fontc;
typedef unsigned char	uchar;
typedef unsigned int	uint;



#define HZK_FILE_NAME	"\\\\fls0\\FONT8X8.hzk"
#define is_chschar(c) ((c) & 0x80)

/*
    file operation
*/

#define		read_file			Bfile_ReadFile
#define		write_file			Bfile_WriteFile
#define		close_file			Bfile_CloseFile
#define		get_file_size		Bfile_GetFileSize
int			open_file			(const char * cfname,int mode);

fontc	* char_to_font (const char * cfname,fontc * ffname);
char	* font_to_char (const fontc *ffname,char *cfname);

int open_font	();
int close_font	();

/*
	key
*/
uint waitkey();
void wait(uint key);

/*
	graph
*/

#define		all_clr		Bdisp_AllClr_VRAM
#define		area_rev	Bdisp_AreaReverseVRAM
#define		printmini	PrintMini
#define		putdisp		Bdisp_PutDisp_DD

void		draw_picture (int x,int y,int width,int height,int mode,uchar * pGraph);
void		print_chs_char (int x,int y,int sel,uchar c1,uchar c2);
void		print_chs_str (int x,int y,int sel,const uchar * str);
void		area_clear (int left,int top,int right,int bottom,int sel);

/*
	dialog
*/


#define DLG_ICON_QUST		1
#define DLG_ICON_WAIT		2
#define DLG_ICON_WARN		3

#define DLG_BTN_YESNO		1
#define DLG_BTN_OK			2

void 	show_dialog(const uchar * caption,const uchar * text,int icon,int btn);
int		file_view (int root,char * cfname);

/*
	list
*/


typedef struct tag_node
{
	char				str[24]	;
	struct tag_node *	next	;
}
node;

typedef struct
{
	node	 	*head,*last	;
	int					size;
}
list;

void list_init		(list * l);
void list_destory	(list * l);
void list_push		(list * l,const char * str); // strlen(str)<24


/*
	pic
*/
extern const uchar PIC_BACK[],PIC_FLS[],PIC_CRD[];
