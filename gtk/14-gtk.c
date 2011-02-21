#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <gtk/gtk.h>

#define list_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head)				\
	for (pos = (head)->next; pos != NULL; pos = pos->next)

struct list {
	struct list *next;
};
//typedef struct student *link;
struct student{
        long id;
	char name[20];
	int engl;
	int math;
	int comp;
	int total;
	struct list list_id;
};
enum {
	COLUMN_ID,
	COLUMN_NAME,
	COLUMN_ENGL,
	COLUMN_MATH,
	COLUMN_COMP,
	COLUMN_TOTAL,
	NUM_COLUMNS
};
static int init(int *, char ***);
static struct student * find_student(long id);
static void add_student_dialog(GtkWidget *, gpointer);
static int add_student(long id, char *, int, int, int);
static void load(void);
static void save(void);

static FILE *fd;
static struct list *head_id, *head_name, *head_total;

/* gtk */
static GtkTreeModel *create_model(void);
static GtkWidget *window;
static GtkTreeModel *model;
GtkListStore *store;
GtkTreeIter iter;
int list_view(void);

static int init(int *argc, char **argv[])
{
	gtk_init(argc, argv);
	head_id = malloc(sizeof(*head_id));
	head_name = malloc(sizeof(*head_name));
	head_total = malloc(sizeof(head_total));
	if (!head_id || !head_name || !head_total)
		exit(EXIT_FAILURE);
	memset(head_id, 0, sizeof(*head_id));
	memset(head_name, 0, sizeof(*head_name));
	memset(head_total, 0, sizeof(*head_total));
	return 0;
}

int add_student(long id, char * name, int math, int comp, int engl)
{
	struct student *stud = malloc(sizeof(*stud));
	if (stud == NULL) {
		printf("ERROR: malloc()\n");
		return 0;
	}
	if (id < 0 || (math > 100 || math < 0)
	    || (comp > 100 || comp < 0)
	    || (engl > 100 || engl < 0)
	    || find_student(id)) {
		return 0;
	}
	stud->id = id;
	strncpy(stud->name, name, 20);
	stud->name[19] = '\0';
	stud->engl = engl;
	stud->math = math;
	stud->comp = comp;
	stud->total = engl + math + comp;
	
	if (head_id->next == NULL){
		head_id->next = &(stud->list_id);
		stud->list_id.next = NULL;
	}
	else {
		stud->list_id.next = head_id->next;
		head_id->next = &(stud->list_id);
	}
	gtk_list_store_prepend(store, &iter);
	gtk_list_store_set(store, &iter,
			   COLUMN_ID, stud->id,
			   COLUMN_NAME, stud->name,
			   COLUMN_MATH, stud->math,
			   COLUMN_COMP, stud->comp,
			   COLUMN_ENGL, stud->engl,
			   COLUMN_TOTAL,stud->total,
			   -1);
	return 1;
}

void add_student_dialog(GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *hbox;
	GtkWidget *stock;
	GtkWidget *table;
	GtkWidget *entry[5];
	GtkWidget *label[5];
	gchar *label_str[] = {
		"_ID", "_NAME", "_Math", "_Computer", "_English"};
	gint response;
	gboolean vaild = TRUE;
	struct student *stud = malloc(sizeof(*stud));
	if (stud == NULL) {
		printf("ERROR: malloc()\n");
		return;
	}
	dialog = gtk_dialog_new_with_buttons("Add Student",
					     GTK_WINDOW(window),
					     GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_STOCK_OK,
					     GTK_RESPONSE_OK,
					     GTK_STOCK_CANCEL,
					     GTK_RESPONSE_CANCEL,
					     NULL);
	
	
	hbox = gtk_hbox_new(FALSE, 8);
	gtk_container_set_border_width(GTK_CONTAINER(hbox), 8);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox, FALSE, FALSE, 0);

	stock = gtk_image_new_from_stock(GTK_STOCK_DIALOG_QUESTION,
					 GTK_ICON_SIZE_DIALOG);
	gtk_box_pack_start(GTK_BOX(hbox), stock, FALSE, FALSE, 0);

	table = gtk_table_new(5, 2, TRUE);
	gtk_table_set_row_spacings(GTK_TABLE (table), 4);
	gtk_table_set_col_spacings(GTK_TABLE (table), 4);
	gtk_box_pack_start (GTK_BOX (hbox), table, TRUE, TRUE, 0);
	
	for (gint i = 0; i < 5; i++) {
		label[i] = gtk_label_new_with_mnemonic(label_str[i]);
		gtk_table_attach_defaults (GTK_TABLE (table),
					   label[i],
					   0, 1, i, i + 1);
		entry[i] = gtk_entry_new();
		gtk_table_attach_defaults (GTK_TABLE (table), entry[i],
					   1, 2, i, i + 1);
		gtk_label_set_mnemonic_widget (GTK_LABEL (label[i]), entry[i]);
	}
	
	
	gtk_widget_show_all(dialog);

 get_input:
	vaild = TRUE;
	response = gtk_dialog_run (GTK_DIALOG (dialog));
 	if (response == GTK_RESPONSE_OK) {
		stud->id = g_ascii_strtoll(gtk_entry_get_text(GTK_ENTRY(entry[0])),
					   NULL, 10);
		strncpy(stud->name, gtk_entry_get_text(GTK_ENTRY(entry[1])), 20);
		stud->name[19] = '\0';
		stud->math = g_ascii_strtoll(gtk_entry_get_text(GTK_ENTRY(entry[2])),
					     NULL, 10);
		stud->comp = g_ascii_strtoll(gtk_entry_get_text(GTK_ENTRY(entry[3])),
					     NULL, 10);
		stud->engl = g_ascii_strtoll(gtk_entry_get_text(GTK_ENTRY(entry[4])),
					     NULL, 10);
		
		if (stud->id == 0 || find_student(stud->id)) {
			gtk_entry_set_text(GTK_ENTRY(entry[0]), "ERROR");
			vaild = FALSE;
		}
		if (stud->name[0] == '\0') {
			gtk_entry_set_text(GTK_ENTRY(entry[1]), "ERROR");
			vaild = FALSE;
		}
		if (stud->math <= 0 || stud->math > 100) {
			gtk_entry_set_text(GTK_ENTRY(entry[2]), "ERROR");
			vaild = FALSE;
		}
		if (stud->comp <= 0 || stud->comp > 100) {
			gtk_entry_set_text(GTK_ENTRY(entry[3]), "ERROR");
			vaild = FALSE;
		}
		if (stud->engl <= 0 || stud->engl > 100) {
			gtk_entry_set_text(GTK_ENTRY(entry[4]), "ERROR");
			vaild = FALSE;
		}
		if (!vaild)
			goto get_input;
		add_student(stud->id, stud->name, stud->math, stud->comp, stud->engl);
	}
	gtk_widget_destroy (dialog);
}



struct student *find_student(long id)
{
	struct list *iter;
	struct student *stud;
	list_for_each(iter, head_id){
		stud = list_entry(iter, struct student, list_id);
		if (stud->id == id)
			return stud;
	}
	return NULL;
}

static void load(void)
{
	int score[3], line = 0;
	long id;
	char input[80];
	char name[20];
	fd = fopen("./data", "r");
	if (fd == NULL) {
		exit(EXIT_FAILURE);
	}
	if (fd == NULL)
		exit(1);
	while (fgets(input, 80, fd) != 0) {
		line++;
		if ((sscanf(input, "%ld %d %d %d %s",
			    &id, score , score + 1, score + 2, name)) != 5) {
			printf("Error in datafile in line %d\n", line);
			continue;
		}
		if (!add_student(id, name, score[0], score[1], score[2])) {
			printf("Load error\n");
		}
	}
	fclose(fd);
	printf("TOTAL: %d line\n", line);
}

static void save(void)
{
	struct list *iter;
	struct student *stud;
	char output[80];
	fd = fopen("./data", "w");
	if (fd == NULL) {
		exit(EXIT_FAILURE);
	}
	list_for_each(iter, head_id) {
		stud = list_entry(iter, struct student, list_id);
		sprintf(output, "%ld %d %d %d %s\n",
			stud->id, stud->engl, stud->math, stud->comp, stud->name);
		fputs(output, fd);
	}
	fclose(fd);
}

static GtkTreeModel *
create_model(void)
{
		
	store = gtk_list_store_new(NUM_COLUMNS,
				   G_TYPE_LONG,
				   G_TYPE_STRING,
				   G_TYPE_INT,
				   G_TYPE_INT,
				   G_TYPE_INT,
				   G_TYPE_INT);
	return GTK_TREE_MODEL(store);
}

static void
add_columns (GtkTreeView *treeview)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	//GtkTreeModel *model = gtk_tree_view_get_model (treeview);
	char *column_str[] = {
		"ID", "Name", "Math", "Computer", "English", "Total"};
	for (int i = 0; i < NUM_COLUMNS; i++) {
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes (column_str[i],
								   renderer,
								   "text",
								   i,
								   NULL);
		gtk_tree_view_column_set_sort_column_id (column, i);
		gtk_tree_view_append_column (treeview, column);
	}

}

static void
remove_student_cb(GtkWidget *widget, gpointer data)
{
	GtkTreeIter iter;
	GtkTreeView *treeview = (GtkTreeView *)data;
	GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
	
	if (gtk_tree_selection_get_selected(selection, NULL, &iter)) {
		
		gtk_list_store_remove(GTK_LIST_STORE(store), &iter);
	}
}

int main(int argc, char *argv[])
{
	
	GtkWidget *vbox, *hbox_button;
	GtkWidget *sw;
	GtkWidget *treeview;
	GtkWidget *bu_add, *bu_remove, *bu_edit, *bu_load, *bu_save, *bu_find;

	init(&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "LIST");
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
	gtk_container_set_border_width (GTK_CONTAINER (window), 8);
	g_signal_connect (window, "destroy",
			  G_CALLBACK (gtk_main_quit), &window);
	
	vbox = gtk_vbox_new (FALSE, 8);
	gtk_container_add (GTK_CONTAINER (window), vbox);
			
	sw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (sw),
					     GTK_SHADOW_ETCHED_IN);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
					GTK_POLICY_NEVER,
					GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX (vbox), sw, TRUE, TRUE, 0);

	model = create_model ();

	treeview = gtk_tree_view_new_with_model (model);
	gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (treeview), TRUE);
	gtk_tree_view_set_search_column (GTK_TREE_VIEW (treeview),
					 COLUMN_ID);
	g_object_unref (model);

	gtk_container_add (GTK_CONTAINER (sw), treeview);

	add_columns(GTK_TREE_VIEW(treeview));
	
	/* buttons */
	hbox_button = gtk_hbox_new(TRUE, 3);
	gtk_box_pack_start(GTK_BOX(vbox), hbox_button, FALSE, FALSE, 0);
	
	bu_add = gtk_button_new_from_stock(GTK_STOCK_ADD);
	gtk_box_pack_start(GTK_BOX(hbox_button), bu_add, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(bu_add), "clicked",
			 G_CALLBACK(add_student_dialog),
			 NULL);
	
	bu_remove = gtk_button_new_from_stock(GTK_STOCK_REMOVE);
	gtk_box_pack_start(GTK_BOX(hbox_button), bu_remove, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(bu_remove), "clicked",
			 G_CALLBACK(remove_student_cb), treeview);
	
	bu_edit = gtk_button_new_from_stock(GTK_STOCK_EDIT);
	gtk_box_pack_start(GTK_BOX(hbox_button), bu_edit, TRUE, TRUE, 0);

	bu_find = gtk_button_new_from_stock(GTK_STOCK_FIND);
	gtk_box_pack_start(GTK_BOX(hbox_button), bu_find, TRUE, TRUE, 0);
	
	bu_load = gtk_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_box_pack_start(GTK_BOX(hbox_button), bu_load, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(bu_load), "clicked",
			 G_CALLBACK(load), NULL);
	
	bu_save = gtk_button_new_from_stock(GTK_STOCK_SAVE);
	gtk_box_pack_start(GTK_BOX(hbox_button), bu_save, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(bu_save), "clicked",
			 G_CALLBACK(save), NULL);
	
	gtk_widget_show_all (window);
	gtk_main();
	return 0;
}
