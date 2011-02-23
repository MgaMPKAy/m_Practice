#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <gtk/gtk.h>

#define MALLOC_LINE 500
struct student{
	glong id;
	char name[20];
	gint math;
	gint comp;
	gint engl;
	gint total;
};
enum {
	COLUMN_ID,
	COLUMN_NAME,
	COLUMN_MATH,
	COLUMN_COMP,
	COLUMN_ENGL,
	COLUMN_TOTAL,
	NUM_COLUMNS,
};

static GtkTreeIter *find_student(long id);
static void dialog_add(GtkWidget *, gpointer);
static gboolean add_student(long id, char *, int, int, int);
static void load(void);
static void save(void);

static GtkTreeModel *create_model(void);
static GtkWidget *window;
static GtkTreeModel *model;
static GtkListStore *store;
static GtkWidget *treeview;
static GtkTreeIter iter;
static GtkTreeSelection *selection;

static gboolean
add_student(long id, char * name, int math, int comp, int engl)
{
	struct student *stud;
	static int i = MALLOC_LINE - 1;
	static struct student *buffer;
	static gboolean first_time = TRUE;
	if (first_time) {
		buffer = malloc(sizeof(struct student) * MALLOC_LINE);
		if (buffer == NULL) {
			printf("ERROR: malloc()\n");
			return FALSE;
		}
		first_time = FALSE;
	}
	if (i == 0) {
		free(buffer);
		buffer = malloc(sizeof(struct student) * MALLOC_LINE);
		if (buffer == NULL) {
			printf("ERROR: malloc()\n");
			return FALSE;
		}
		i = MALLOC_LINE - 1;
	}
	stud = buffer + i;
	stud->id = id;
	strncpy(stud->name, name, 20);
	stud->name[19] = '\0';
	stud->math = math;
	stud->comp = comp;
	stud->engl = engl;
	stud->total = engl + math + comp;
	
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter,
			   COLUMN_ID, stud->id,
			   COLUMN_NAME, stud->name,
			   COLUMN_MATH, stud->math,
			   COLUMN_COMP, stud->comp,
			   COLUMN_ENGL, stud->engl,
			   COLUMN_TOTAL,stud->total,
			   -1);
	i--;
	return TRUE;
}

static void
dialog_add(GtkWidget *widget, gpointer data)
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
	gboolean vaild;
	struct student stud;
	dialog = gtk_dialog_new_with_buttons("Add Student",
					     GTK_WINDOW(window),
					     GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_STOCK_OK,
					     GTK_RESPONSE_OK,
					     GTK_STOCK_CANCEL,
					     GTK_RESPONSE_CANCEL,
					     NULL);
	hbox = gtk_hbox_new(FALSE, 3);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox, FALSE, FALSE, 0);

	stock = gtk_image_new_from_stock(GTK_STOCK_DIALOG_QUESTION,
					 GTK_ICON_SIZE_DIALOG);
	gtk_box_pack_start(GTK_BOX(hbox), stock, FALSE, FALSE, 0);

	table = gtk_table_new(5, 2, TRUE);
	gtk_table_set_row_spacings(GTK_TABLE (table), 1);
	gtk_table_set_col_spacings(GTK_TABLE (table), 1);
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
		stud.id = g_ascii_strtoll(gtk_entry_get_text(GTK_ENTRY(entry[0])),
					   NULL, 10);
		if (stud.id == 0 || find_student(stud.id)) {
			gtk_entry_set_text(GTK_ENTRY(entry[0]), "ERROR");
			goto get_input;
		}
		
		strncpy(stud.name, gtk_entry_get_text(GTK_ENTRY(entry[1])), 20);
		stud.name[19] = '\0';
		stud.math = g_ascii_strtoll(gtk_entry_get_text(GTK_ENTRY(entry[2])),
					     NULL, 10);
		if (stud.math <= 0 || stud.math > 100) {
			gtk_entry_set_text(GTK_ENTRY(entry[2]), "ERROR");
			goto get_input;
		}
		
		stud.comp = g_ascii_strtoll(gtk_entry_get_text(GTK_ENTRY(entry[3])),
					     NULL, 10);
		if (stud.comp <= 0 || stud.comp > 100) {
			gtk_entry_set_text(GTK_ENTRY(entry[3]), "ERROR");
			goto get_input;
		}
		
		stud.engl = g_ascii_strtoll(gtk_entry_get_text(GTK_ENTRY(entry[4])),
					     NULL, 10);
		if (stud.engl <= 0 || stud.engl > 100) {
			gtk_entry_set_text(GTK_ENTRY(entry[4]), "ERROR");
			goto get_input;
		}
		
		add_student(stud.id, stud.name, stud.math, stud.comp, stud.engl);
	}
	gtk_widget_destroy (dialog);
}

static GtkTreeIter *
find_student(long id_find)
{
	gboolean vaild;
	glong id;
	static GtkTreeIter iter;

	vaild = gtk_tree_model_get_iter_first(model, &iter);
	while (vaild) {
		gtk_tree_model_get(model, &iter,
				   COLUMN_ID, &id,
				   -1);
		if (id_find == id) {
			return &iter;
		}
		vaild = gtk_tree_model_iter_next(model, &iter);
	}
	return NULL;
}

static void load(void)
{
	gint score[3];
	glong id, pre_id = 0, line = 0, added = 0;
	gchar input[50];
	gchar name[20];
	gboolean vaild;
	GtkTreeIter iter;
	FILE *fd = fopen("./data", "r");
	if (fd == NULL) {
		exit(EXIT_FAILURE);
	}
	
 	vaild = gtk_tree_model_get_iter_first(model, &iter);
	while (vaild) {
		gtk_list_store_remove(GTK_LIST_STORE(store), &iter);
		vaild = gtk_tree_model_get_iter_first(model, &iter);
	}
	
	while (fgets(input, 50, fd) != 0) {
		line++;
		if ((sscanf(input, "%ld %d %d %d %s",
			    &id, score, score + 1,
			    score + 2, name)) != 5) {
			g_print("Error Format: Line %ld %s\n", line, input);
			continue;
		}
		if (id <= pre_id) {
			g_print("Error: ID isn't sequential\n");
			continue;
		}
		if (!add_student(pre_id = id, name, score[0],
				 score[1], score[2])) {
			g_print("Error ADDING: Line %ld\n", line);
		}
		added++;
	}
	fclose(fd);
	g_print("TOTAL: %ld line. ADDED: %ld\n", line, added);
}

static void save(void)
{
	gboolean vaild;
	GtkTreeIter iter;
	long id;
	gchar output[50], *name;
	gint score[3];
	FILE *fd;

	fd = fopen("./data", "w");
	if (fd == NULL) {
		printf("data file open error\n");
		return;
	}
	
	vaild = gtk_tree_model_get_iter_first(model, &iter);
	while (vaild) {
		gtk_tree_model_get(model, &iter,
				   COLUMN_ID, &id,
				   COLUMN_NAME, &name,
				   COLUMN_MATH, score,
				   COLUMN_COMP, score + 1,
				   COLUMN_ENGL, score + 2,
				   -1);
		name[19] = '\0';
		sprintf(output, "%ld %d %d %d %s\n",
			id, score[0], score[1], score[2], name);
		fputs(output, fd);
		g_free(name);
		vaild = gtk_tree_model_iter_next(model, &iter);
	}
	fclose(fd);
}

static void
cell_edited(GtkCellRendererText *cell,
	    const gchar *path_string,
	    const gchar *new_text,
	    gpointer data)
{
	GtkTreeIter iter;
	gint math, comp, engl;
	gint score = atoi(new_text);
	if (score <= 0 || score > 100)
		return;
	gchar *old_text;
	gint column = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(cell),"column"));
	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	gtk_tree_selection_get_selected(selection, NULL, &iter);
	gtk_tree_model_get(model, &iter,
			   column, &old_text,
			   -1);
	//g_free(old_text);
	gtk_list_store_set(GTK_LIST_STORE(store), &iter,
			   column, atoi(new_text),
			   -1);
	gtk_tree_model_get(model, &iter,
			   COLUMN_MATH, &math,
			   COLUMN_COMP, &comp,
			   COLUMN_ENGL, &engl,
			   -1);
	gtk_list_store_set(GTK_LIST_STORE(store), &iter,
			   COLUMN_TOTAL, math + comp + engl,
			   -1);
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
add_columns(GtkTreeView *treeview)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	gint width[] = {100, 180, 90, 90, 90, 90};
	gfloat align[] = {0, 0, 0, 0, 0, 0};
	char *column_title[] = {
		"ID", "Name", "Math", "Computer", "English", "Total"};
	for (int i = 0; i < NUM_COLUMNS; i++) {
		renderer = gtk_cell_renderer_text_new();
		if (i >= COLUMN_ENGL && i <= COLUMN_COMP) {
			g_object_set(renderer,
				     "editable", TRUE,
				     NULL);
			g_signal_connect(renderer, "edited",
					 G_CALLBACK(cell_edited), NULL);
			g_object_set_data(G_OBJECT(renderer), "column",
					  GINT_TO_POINTER(i));
		}
		column = gtk_tree_view_column_new_with_attributes(column_title[i],
								  renderer,
								  "text", i,
								  NULL);
		gtk_tree_view_column_set_sizing(column,
						GTK_TREE_VIEW_COLUMN_FIXED);
		gtk_tree_view_column_set_fixed_width(column, width[i]);
		gtk_tree_view_column_set_alignment(column, align[i]);
		gtk_tree_view_column_set_sort_column_id(column, i);
		gtk_tree_view_append_column(treeview, column);
	}
}

static void
remove_student_cb(GtkWidget *widget, gpointer data)
{
	GtkTreeIter iter;
	GtkTreeView *treeview = (GtkTreeView *)treeview;
	
	if (gtk_tree_selection_get_selected(selection, NULL, &iter)) {
		
		gtk_list_store_remove(GTK_LIST_STORE(store), &iter);
	}
}

int main(int argc, char *argv[])
{
	
	GtkWidget *vbox, *hbox_button;
	GtkWidget *sw;
	GtkWidget *bu_add, *bu_remove, *bu_load, *bu_save;
	gtk_init(&argc, &argv);

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
					 COLUMN_NAME);
	gtk_tree_view_set_fixed_height_mode(GTK_TREE_VIEW(treeview), TRUE);
	g_object_unref (model);

	gtk_container_add (GTK_CONTAINER(sw), treeview);

	add_columns(GTK_TREE_VIEW(treeview));

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	//gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);
	
	/* buttons */
	hbox_button = gtk_hbox_new(TRUE, 3);
	gtk_box_pack_start(GTK_BOX(vbox), hbox_button, FALSE, FALSE, 0);
	
	bu_add = gtk_button_new_from_stock(GTK_STOCK_ADD);
	gtk_box_pack_start(GTK_BOX(hbox_button), bu_add, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(bu_add), "clicked",
			 G_CALLBACK(dialog_add),
			 NULL);
	
	bu_remove = gtk_button_new_from_stock(GTK_STOCK_REMOVE);
	gtk_box_pack_start(GTK_BOX(hbox_button), bu_remove, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(bu_remove), "clicked",
			 G_CALLBACK(remove_student_cb), NULL);
	
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
