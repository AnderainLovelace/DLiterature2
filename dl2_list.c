#include "dl2_all.h"

void list_init (list * l)
{
	l->head	= NULL;
	l->last	= NULL;
	l->size	= 0;
}

void list_destory (list * l)
{
	node *line1,*line2;

	line1 = l->head;
	
	while (line1)
	{
		line2 = line1;
		line1 = line1->next ;

		free (line2);
	}

	l->head = l->last = NULL;
	l->size = 0;
}

void list_push (list * l,const char * str)
{
	if (l->size == 0)
	{
		l->head			= (node*)calloc(sizeof(node),1);
		l->last			= l->head;
	}
	else
	{
		l->last->next	= (node*)calloc(sizeof(node),1);
		l->last			= l->last->next;
	}

	strcpy(l->last->str,str);

	l->size ++;

}

