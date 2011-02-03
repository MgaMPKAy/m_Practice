/*  简单的井字游戏 
 *  Tested on GTK+2.22.0
 */  

#include<gtk/gtk.h>
#include<time.h>
#include<stdlib.h>

void judge(void);
gboolean iswin(void);
void drawox(GtkWidget *widget, gpointer *i);
void reset(GtkWidget *widget, gpointer *button);
void ai_toggle(GtkWidget *widget, gpointer *data);
void ai_easy(GtkWidget *widget, gpointer *data);
void popup(gint);

GtkWidget *window, *vbox, *hbox[3], *hbox_menu;
GtkWidget *button[10], *reset_button;
gint ischanged[9];
gulong sid_ai[10];
GtkWidget *ai_on;
gint count, win;
gint player = 1;

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	window = gtk_window_new( GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), "Txx-Txx-Txx...2.1");
	g_signal_connect(GTK_OBJECT(window), "destroy",
			 G_CALLBACK(gtk_main_quit), NULL);
	
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hbox_menu = gtk_hbox_new(FALSE,0);
	gtk_box_pack_end(GTK_BOX(vbox), hbox_menu, TRUE, TRUE, 3);
	
	for(int i = 0; i < 3; i++) {
		hbox[i] = gtk_hbox_new(FALSE,0);
		gtk_box_pack_start(GTK_BOX(vbox),hbox[i],TRUE, TRUE, 3);
		for(int j = 0; j < 3; j++) {
			button[i * 3 + j] = gtk_button_new_with_label(" ");
			gtk_box_pack_start(GTK_BOX(hbox[i]),button[i * 3 + j],
					   TRUE, TRUE, 3);
			/* 按钮接受到clicked信号，就执行drawox(),画园或叉 */
			g_signal_connect(button[i * 3 + j], "clicked",
					 G_CALLBACK(drawox),
					 GINT_TO_POINTER(i * 3 + j));
		}
	}
	
	reset_button = gtk_button_new_with_label("RESET");
	g_signal_connect(reset_button,"clicked", G_CALLBACK(reset), button);
	gtk_box_pack_start(GTK_BOX(hbox_menu), reset_button, TRUE, TRUE, 3);
	
	ai_on = gtk_check_button_new_with_label(" AI?");
	g_signal_connect(ai_on,"clicked", G_CALLBACK(ai_toggle), button);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ai_on),TRUE);
	gtk_box_pack_start(GTK_BOX(hbox_menu), ai_on, FALSE, FALSE, 3);
	button[9] = reset_button;
	
	gtk_widget_show_all(window);
	
	gtk_main();
	return 0;
}


/* ai_toggle
 * 打开/关闭电脑玩家
 * 通过g_signal_handler_disconnect()和g_signal_connect()
 */
void ai_toggle(GtkWidget *widget, gpointer *data)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		for(int i = 0; i < 9 ; i++)
			/* 打开电脑电脑玩家，点击按钮后执行ai_easy() */
			sid_ai[i] = g_signal_connect(button[i], "clicked",
						     G_CALLBACK(ai_easy),
						     GINT_TO_POINTER(i));
	} else {
		for(int i = 0; i < 9 ; i++)
			/* 关闭电脑电脑玩家，点击按钮后不执行ai_easy() */
			g_signal_handler_disconnect(button[i], sid_ai[i]);
	}
}

/* judge()
 * 判断是否有玩家胜利并设置按钮
 */
void judge(void)
{
	if (win == 1)
		return;
	if (iswin()) {
		gtk_widget_set_sensitive(button[9], FALSE);
		gtk_widget_set_sensitive(ai_on, FALSE);
		if (player == 1) {
			popup(2);
		} else {
			popup(1);
		}
		for (int i = 0; i < 9; i++)
			gtk_widget_set_sensitive(button[i], FALSE);
		win = 1;
	}
	if ((count == 9)&&(win == 0)) {
		gtk_widget_set_sensitive(button[9], FALSE);
		gtk_widget_set_sensitive(ai_on, FALSE);
		popup(0);
	}
}

/* reset()
 * 重置所有按钮和状态
 * @widget 没用， @data 没用
 */
void reset(GtkWidget *widget, gpointer *data)
{
	for(int i = 0; i < 9; i++) {
		ischanged[i] = 0;
		gtk_button_set_label(GTK_BUTTON(button[i]), "  ");
	} 
	count = 0;
	gtk_button_set_label(GTK_BUTTON(button[9]), "RESET");
	win = 0;
	player = 1;
	for(int i = 0; i < 10 ; i++)
		gtk_widget_set_sensitive(button[i], TRUE);
	gtk_widget_set_sensitive(ai_on, TRUE);
}

/* drawox()
 * 交替画园和叉
 * @i :要画的方格
 */
void drawox(GtkWidget *widget, gpointer *i)
{
	if(ischanged[GPOINTER_TO_INT(i)] != 0)
		return;
	else ischanged[GPOINTER_TO_INT(i)] = player;
  
	if (player == 1) {
		gtk_button_set_label(GTK_BUTTON(widget), "X");     
		gtk_widget_set_sensitive(widget, FALSE);
		count++;
		player = 2;
	}
	else {
		gtk_button_set_label(GTK_BUTTON(widget), "O");
		gtk_widget_set_sensitive(widget, FALSE);
		count++;
		player = 1; 
	}
	judge();
}

/* iswin()
 * 判断是否有玩家胜利
 */
gboolean iswin(void)
{
	int *a = ischanged;
	if(
	   ((a[0] == a[1]) && (a[0] == a[2]) && (a[0] != 0))
	   ||((a[3] == a[4]) && (a[3] == a[5]) && (a[3] != 0))
	   ||((a[6] == a[7]) && (a[6] == a[8]) && (a[6] != 0))
	   ||((a[0] == a[4]) && (a[0] == a[8]) && (a[0] != 0))
	   ||((a[2] == a[4]) && (a[2] == a[6]) && (a[2] != 0))
	   ||((a[0] == a[3]) && (a[0] == a[6]) && (a[0] != 0))
	   ||((a[1] == a[4]) && (a[1] == a[7]) && (a[1] != 0))
	   || ((a[2] == a[5]) && (a[2] == a[8]) && (a[2] != 0))
	   )
		return TRUE;
	else
		return FALSE;
}

/* ai_easy()
 * 简单的电脑玩家，通过遍历所以可以下的方格，决定最佳方案
 */
void ai_easy(GtkWidget *widget, gpointer *data)
{
	srand((unsigned)time(NULL));
	gint tmpp = player;
	gint best_move[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
	gint move;
	gint a, b, t;

	/* 如果已经没方格或着对方已经获胜 */
	if(count == 9 || iswin())
		return;
	/* 如果还差一步对方就能赢，则阻止对方下 */	
	for (int i = 0; i < 9; i++) {
		/* 跳过已经被画了的方格 */
		if(ischanged[i] != 0) continue;
		/* 画对方的图案 */
		ischanged[i] = tmpp;
		/* 如果对方能胜利，阻止 */
		if(iswin()) {
			ischanged[i] = 0;
			drawox(button[i],GINT_TO_POINTER(i));
			return;
		} else {
			ischanged[i] = 0;
		}
	}
	
	tmpp = 3 - tmpp;

	/* 如过还要一步自己就胜利，则下这一步 */
	for (int i = 0; i < 9; i++) {
		if(ischanged[i] != 0) continue;
		ischanged[i] = tmpp;
		
		if(iswin()) {
			ischanged[i] = 0;
			drawox(button[i],GINT_TO_POINTER(i));
			return;
		} else
			ischanged[i] = 0;
		}
	
	/* 先画正中，再画4个角，最后是十字 */
	/* 交换顺序，避免重复 */
	for (int i = 0; i < 10; i++) { 
		a = rand() % 4;
		b = rand() % 4;
		t = best_move[1+a];
		best_move[1 + a] = best_move[1 + b];
		best_move[1 + b] = t;
		t = best_move[5 + a];
		best_move[5 + a] = best_move[5 + b];
		best_move[5 + b] = t;
	}
	for (int i = 0; i < 9; i++) {
		move = best_move[i];
		
		if (ischanged[move] == 0) {
			drawox(button[move],GINT_TO_POINTER(move));
			return;
		}
	}  
}
/* popup()
 * 弹出窗口显示结果
 * @i :显示的信息编号
 */
void popup(gint i)
{
	GtkWidget *dialog, *label, *content_area;
	gchar *message[] = {"Draw",
			    "Player 1 win !!!",
			    "Player 2 win !!!",
			    "AI is on"};

	dialog = gtk_dialog_new_with_buttons("Result!!!",
					     GTK_WINDOW(window),
					     GTK_DIALOG_DESTROY_WITH_PARENT,
					     "Again!",
					     GTK_RESPONSE_NONE,
					     NULL);
	gtk_window_set_default_size(GTK_WINDOW(dialog), 120, 70);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	label = gtk_label_new(message[i]);

	g_signal_connect_swapped(dialog, "response", G_CALLBACK(reset),
				 dialog);
	g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy),
				 dialog);
	gtk_container_add(GTK_CONTAINER(content_area), label);
	gtk_widget_show_all(dialog);
}
