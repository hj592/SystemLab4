#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
gchar *values[20] = {"7","8","9","/",
			"4","5","6","*",
			"1","2","3","-",
			"0",".","=","+",
				};
				
int count=0;

void quit(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

int carculate(const gchar *str)
{
	char onenum[255];
	int result = 0;
	int temp = 0;
	int i = 0;
	int j = 0;
	int oper = 0;
	int ascii = 0;
	
	memset(onenum, 0,255);
	
	while (*str) {
		
		ascii = (int)*str;
		char cnum = *str;
		
		if(ascii >= 48 && ascii <= 57)
		{
			onenum[j] = cnum;
			j++;
			
		}
		else if(ascii == 43 || ascii == 45 ||ascii == 42 ||ascii == 47) //사칙연산인 경우
		{
			if(i == 0)
			{
				result = atoi(onenum);
				oper = ascii;
			}
			else
			{
				temp = atoi(onenum);
				if( oper == 43) result = result + temp;
				if( oper == 45) result = result - temp;
				if( oper == 42) result = result * temp;
				if( oper == 47) result = result / temp;
				oper = ascii;
			}
			
			i++;
			
			memset(onenum, 0,255);
			j=0;
		}
		*str++;
	}
	
	temp = atoi(onenum);
	if( oper == 43) result = result + temp;
	if( oper == 45) result = result - temp;
	if( oper == 42) result = result * temp;
	if( oper == 47) result = result / temp;
	
	return result;
}


void insert_btn(GtkWidget *button, gpointer data)
{
	const gchar *num = gtk_button_get_label(button);
	const gchar *text = gtk_label_get_text(GTK_LABEL( (GtkWidget *) data));
	char sbuffer[255] = ""; 
	
	if(count == 0)
	{	
		gtk_label_set_text(GTK_LABEL( (GtkWidget *) data), num);
		count++;
	}
	else if(!strcmp(num,"="))
	{	
		int iresult = carculate(text);
		
		sprintf(sbuffer, "결과 : %d", iresult);
		
		gtk_label_set_text(GTK_LABEL( (GtkWidget *) data), sbuffer);
		count=0;
	}
	else
	{
		strcat(text, num);
	
		gtk_label_set_text(GTK_LABEL( (GtkWidget *) data), text);
	}

}

int main(int argc, char *argv[]){
	int i;
	int j;
	int pos = 0;
	GtkWidget *window;
	GtkWidget *table;
	GtkWidget *button[16];
	GtkWidget *result_label;
	GtkWidget *vbox;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),300,200);
	gtk_window_set_title(GTK_WINDOW(window),"HJ calculator");
	g_signal_connect(G_OBJECT(window),"destroy", G_CALLBACK(quit), NULL);
	
	result_label = gtk_label_new("값을 입력하세요...");
	
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);

	//테이블 생성
	table = gtk_table_new(4,4,TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(table),1);
	gtk_table_set_col_spacings(GTK_TABLE(table),1);
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			button[pos] = gtk_button_new_with_label(values[pos]);
			
			g_signal_connect(button[pos], "clicked", G_CALLBACK(insert_btn), result_label);
			
			gtk_table_attach_defaults(GTK_TABLE(table), button[pos], j,j+1,i,i+1);
			pos++;
		}	
	}

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(vbox), result_label, FALSE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, TRUE, 5);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}
