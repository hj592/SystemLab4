#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define SUM(X,Y) (X)+(Y)
#define MULT(X,Y) (X)*(Y)
#define DIV(X,Y) (X)/(Y)

typedef struct _Stack{
	char Operator[MAX];
	int Operand[MAX];
	int Opt_top;
	int Opd_top;
}Stack;

Stack stack;

void init(){
	stack.Opd_top = stack.Opt_top = 0;
}

void optPush(char opt){
	stack.Operator[stack.Opt_top++] =opt;
}

void opdPush(int opd){
	stack.Operand[stack.Opd_top++] = opd;
}

char optPop(){
	return stack.Operator[--stack.Opt_top];
}

int opdPop(){
	return stack.Operand[--stack.Opd_top];
}

void resetExpression(char Exp[], int len){
	for(int i=0;i<len;i++){
		Exp[i]='\0';
	}
}

int optCheck(char opt1, char opt2){
	if(opt1 =='*'||opt1=='/'){
		if(opt2=='+'||opt2=='-'||opt2=='/')
			return 1;
		else return 0;
	}
	else
		return 0;
}

int calFunc(int opd1, int opd2, char opt){
	int result;
	switch(opt){
	case '+':
		result = SUM(opd1,opd2);
		break;
	case '*':
		result = MULT(opd1,opd2);
		break;
	case '/':
		result = DIV(opd1,opd2);
		break;
	}
	return result;
}

void calEngine(char Exp[],int len){
	char tmpExp[MAX]={0,};
	char ch, opt;
	int tmpCnt =0,opd1,opd2,res, flag =0;
	for(int i=0;i<len;i++){
		ch = Exp[i];
		opt =0;
		if(ch==' ')
			continue;
		else if(ch>='0'&&ch<='9'){
			tmpExp[tmpCnt++]=ch;
			if(Exp[i+1]=='+'||Exp[i+1]=='-'||Exp[i+1]=='*'||Exp[i+1]=='/'||Exp[i+1]=='='){
				if(flag){
					flag=0;
					opdPush(-atoi(tmpExp));
				}
				else{
					opdPush(atoi(tmpExp));
				}
				resetExpression(tmpExp, tmpCnt);
				tmpCnt=0;
			}
		}
		else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
			if(ch=='-'){
				flag = 1;
				ch='+';
			}
			if(stack.Opt_top==0)
				optPush(ch);
			else{
				opt=optPop();
				if(optCheck(opt,ch)){
					opd2=opdPop();
					opd1=opdPop();
					res=calFunc(opd1,opd2,opt);
					opdPush(res);
					optPush(ch);
				}
				else{
					optPush(opt);
					optPush(ch);
				}
			}
		}
		else if(ch=='=')
			break;
		}
	while(stack.Opt_top!=0){
		opd2 = opdPop();
		opd1 = opdPop();
		opt = optPop();
		res = calFunc(opd1,opd2, opt);
		opdPush(res);
	}
}
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
gchar* carculate(gchar *text)
{
	const gchar *num = "";
	int result = 0;
	int temp = 0;
	int i = 0;
	int oper = 0;
	int ascii = 0;
	printf("a");
	printf("%s",text);
	for(int k =0;k<strlen(text);k++) {//while (text != NULL)
		ascii = atoi((char)text[k]);
		printf("%d",ascii);
		if(ascii >= 48 && ascii<=57)
		{
			num = strcat(num, text[k]);
			
		}
		else if(ascii == 43 || ascii == 45 ||ascii == 42 ||ascii == 47) //사칙연산인 경우
		{
			if(count == 0)
			{
				result = atoi(num);
				oper = ascii;
			}
			else
			{
				temp = atoi(num);
				if( oper == 43) result = result + temp;
				if( oper == 45) result = result - temp;
				if( oper == 42) result = result * temp;
				if( oper == 47) result = result / temp;
				oper = ascii;
			}
			
			num = "";
			i++;
		}
		else //문자열 끝난경우
		{
			temp = atoi(num);
			if( oper == 43) result = result + temp;
			if( oper == 45) result = result - temp;
			if( oper == 42) result = result * temp;
			if( oper == 47) result = result / temp;
		}
	}
	return (char)result;
}

int n=0;
void insert_btn(GtkWidget *button, gpointer data)
{
	const gchar *num = gtk_button_get_label(button);
	const gchar *text = gtk_label_get_text(GTK_LABEL( (GtkWidget *) data));
	//if(!strcmp(num,"+")||!strcmp(num,"-")||!strcmp(num,"*")||!strcmp(num,"/"))
	//{
	//	n++;
	//}
	if(count == 0)
	{	
		gtk_label_set_text(GTK_LABEL( (GtkWidget *) data), num);
		count++;
		printf("%s",text);
	}
	else if(!strcmp(num,"="))//||n!=0
	{	
		/*const gchar *result = carculate(text);
		char Expression[MAX]={0,};
		strcpy(Expression,(char)text);
		calEngine(Expression,strlen(Expression));
		
		*/
		printf("%s",text);
		gchar *result[MAX] = carculate(text);
		//const gchar *result = carculate(text);
		gtk_label_set_text(GTK_LABEL( (GtkWidget *) data), result);
		count=0;
		n=0;
	}
	else
	{
		text = strcat(text, num);
		printf("%s",text);
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
