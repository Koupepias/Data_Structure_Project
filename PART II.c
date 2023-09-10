#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024
#define MAX_NAME_LENGTH 64
#define TRUE 1
#define FALSE 0
#define EMPTY_TREE 2
#define HASH_TABLE_SIZE 41
#define DEPTH 4199760
#define CHECK 111439


/// DILWSI TWN STRUCTS---DILWSI TWN STRUCTS---DILWSI TWN STRUCTS---DILWSI TWN STRUCTS---DILWSI TWN STRUCTS---DILWSI TWN STRUCTS---DILWSI TWN STRUCTS---DILWSI TWN STRUCTS---DILWSI TWN STRUCTS///
typedef struct record {
    char direction[16];
    int year;
    char date[11];
    char weekday[10];
    char country[MAX_NAME_LENGTH];
    char commodity[MAX_NAME_LENGTH];
    char transport_mode[MAX_NAME_LENGTH];
    char measure[MAX_NAME_LENGTH];
    double value;
    double cumulative;
}RECORD;

struct AVL_NODE{
   RECORD data;
   struct AVL_NODE *left;
   struct AVL_NODE *right;
   struct AVL_LIST_NODE *list;
   int height;
};

typedef struct AVL_LIST_NODE{
    RECORD data;
    struct avl_list_node *next_list_node;
}*LIST_NODE;

typedef struct list_node {
    RECORD record;
    struct list_node* next;
} Node;

typedef struct hash_table {
    Node* buckets[HASH_TABLE_SIZE];
} HashTable;

///DILWSI TWN TYPEDEF---DILWSI TWN TYPEDEF---DILWSI TWN TYPEDEF---DILWSI TWN TYPEDEF---DILWSI TWN TYPEDEF---DILWSI TWN TYPEDEF---DILWSI TWN TYPEDEF---DILWSI TWN TYPEDEF---DILWSI TWN TYPEDEF///
typedef const char element[11];
typedef struct AVL_NODE AVL_NODE;
typedef struct AVL_NODE *AVL_NODE_PTR;

///DILWSI TWN FUNCTIONS---DILWSI TWN FUNCTIONS---DILWSI TWN FUNCTIONS---DILWSI TWN FUNCTIONS---DILWSI TWN FUNCTIONS---DILWSI TWN FUNCTIONS---DILWSI TWN FUNCTIONS---DILWSI TWN FUNCTIONS///
void menu_bst_sorted_by_date(int users_sort_choice);

void menu_bst_sorted_by_value(int users_sort_choice);

void menu_hashing();

void load_data_to_avl_tree(const char* filename, AVL_NODE_PTR *root, int users_sort_choice);

int insert_avl_root(AVL_NODE_PTR *root, RECORD rec);

int delete_bst_node(AVL_NODE_PTR *root, element users_given_date);

AVL_NODE_PTR rotate_avl_right(AVL_NODE_PTR node);

AVL_NODE_PTR rotate_avl_left(AVL_NODE_PTR node);

AVL_NODE_PTR rotate_avl_left_right(AVL_NODE_PTR node);

AVL_NODE_PTR rotate_avl_right_left(AVL_NODE_PTR node);

AVL_NODE_PTR insert_avl_node_by_date(AVL_NODE_PTR *root, RECORD rec);

AVL_NODE_PTR insert_avl_node_by_value(AVL_NODE_PTR *root, RECORD rec);

int delete_avl_node(AVL_NODE_PTR *root, element users_given_date);

AVL_NODE_PTR search_avl_node(AVL_NODE_PTR root, element users_given_date);

void print_avl_node(AVL_NODE_PTR root);

int height(AVL_NODE_PTR root);

int max(int x, int y);

AVL_NODE_PTR search_max_value(AVL_NODE_PTR tree);

AVL_NODE_PTR search_min_value(AVL_NODE_PTR tree);

void date_input_check(element* date);

int hash_function(element date[11]);

void insert_record_to_hashTable(HashTable* table, RECORD record);

void load_data_to_hashTable(HashTable* table, const char* filename);

Node* search_value_by_date(HashTable* table, element users_given_date);

void delete_hashTable_record(HashTable* table, element users_given_date);

int compare_dates(const char* date1, const char* date2);

///MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN---MAIN///
int main() {
int load_choice;

    while(1){
    printf("\nH fortwsi tou arxeiou na ginete se arxeio BST h se mia domi HASHING? \n");
    printf("\nPliktrologise: \n");
    printf("\n-1 gia BST\n");
    printf("\n-2 gia HASHING\n\n");
    scanf("%d", &load_choice);
    printf("\n");

    int sort_choice;

	switch(load_choice)
	{
	    case 1:
            system("cls");
            printf("H fortwsi tou BST na taksinomite me vasi tin imerominia h to value? \n");
            printf("Pliktrologise: \n");
            printf("\n-1 gia fortwsi me vasi tin imerominia\n");
            printf("\n-2 gia fortwsi me vasi to value\n\n");
            scanf("%d", &sort_choice);
            printf("\n");
                while(sort_choice<1 || sort_choice>2){
                    system("cls");
                    printf("\n----------Lathos eisodos, dwse ksana---------- \n\n");
                    scanf("%d", &sort_choice);
                    printf("\n");
                }

            if(sort_choice==1){
                system("cls");
                printf("LOADIND DATA...\n\n");
                menu_bst_sorted_by_date(sort_choice);
            }else{
                system("cls");
                printf("LOADIND DATA...\n\n");
                menu_bst_sorted_by_value(sort_choice);
            }

            break;

        case 2:
        menu_hashing();
        break;

        default:
            system("cls");
            printf("\n----------Lathos eisodos, dwse ksana---------- \n\n");
            continue;
	}
}
		printf("\n");
		fflush(stdin);

    return 0;
}

void menu_bst_sorted_by_date(int users_sort_choice){ ///MENU BST SORTED BY DATE---MENU BST SORTED BY DATE---MENU BST SORTED BY DATE---MENU BST SORTED BY DATE///

    AVL_NODE_PTR *tree;

    tree=NULL;

    load_data_to_avl_tree("effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv", &tree, users_sort_choice);
    system("cls");

    int menu_choice;
    while (1)
	{
	    printf("            ///////////*MENU*///////////");
	    printf("\n1-Apeikonisi tou BST dendrou");
		printf("\n2-Anazitisi timis vasi tis imerminias");
		printf("\n3-Tropopoiisi timis mias sigkekrimenis imerominias");
		printf("\n4-Diagrafi timis mias sigkekrimenis imerominias");
		printf("\n5-Eksodos");
		printf("\n\n Pliktrologise tin epilogi  sou (1,2,3,4,5) \n");
		scanf("%d", &menu_choice);
		printf("\n");
		fflush(stdin);

    element date_input[11];
    AVL_NODE_PTR found = NULL;
    int deleted;

	    switch(menu_choice)
		{
			case 1:
			     system("cls");
			     printf("\nDATE           VALUE");
				 print_avl_node(tree);
				break;
			case 2:
			    system("cls");
				date_input_check(&date_input);
				found = search_avl_node(tree,date_input);

				if (found!=NULL){
                    printf("\n\nFOUND! %lf \n", found->data.value);
                    while(found->list != NULL){
                        printf("\tDUPLICATE:     %.2lf\n", found->data.value);
                        found = found->list->next_list_node;
                    }
                }else
                    printf("\n\nNOT FOUND");

                fflush(stdin);
				break;
			case 3:
			    system("cls");
				date_input_check(&date_input);
				printf("\n\nPliktrologise neo value. O arithmos prepei na einai thetikos!(value>0)\n");
				double new_value;
				scanf("%lf", &new_value);
				system("cls");
				while (new_value < 0){
                    printf("Lanthasmeni eisodos! O arithmos prepei na einai thetikos!\n");
                    scanf("%lf",new_value);
                    system("cls");
				}

				found = search_avl_node(tree,date_input);
				if(found == NULL){
                    printf("\nH eggrafi den vrethike\n\n");
                    break;
				}

				RECORD* new_rec = malloc(sizeof(RECORD));
                    if (new_rec == NULL) {
                        fprintf(stderr,"Error: adinamia desmefsis mnimis gia na antikatastisi tin iparxousa");
                        exit(0);
                    }

                strcpy(new_rec->direction, found->data.direction);
                new_rec->year = found->data.year;
                strcpy(new_rec->date, date_input);
                strcpy(new_rec->weekday, found->data.weekday);
                strcpy(new_rec->country, found->data.country);
                strcpy(new_rec->commodity, found->data.commodity);
                strcpy(new_rec->transport_mode, found->data.transport_mode);
                strcpy(new_rec->measure, found->data.measure);
                new_rec->value =new_value;
                new_rec->cumulative = found->data.cumulative;

                deleted = delete_avl_node(&tree,date_input);
                system("cls");
                if (deleted != TRUE)
                    break;
                tree = insert_avl_node_by_date(&tree, *new_rec);
                printf("\n\nH tropopoiisi tou record egine me epitixia");
				break;
			case 4:
			    system("cls");
				date_input_check(&date_input);
				deleted = delete_avl_node(&tree,date_input);
				break;
			case 5:
			    system("cls");
				printf("\nEkteleite eksodos apo to programa. Antio!\n");
				fflush(stdin);
				exit(0);
			default:
				system("cls");
                printf("\n----------Lathos eisodos, dwse ksana---------- \n\n");
                continue;
		}

		printf("\n\n");
	}
}

void menu_bst_sorted_by_value(int users_sort_choice){ ///MENU BST SORTED BY VALUE---MENU BST SORTED BY VALUE---MENU BST SORTED BY VALUE---MENU BST SORTED BY VALUE///

    AVL_NODE_PTR *tree;

    tree=NULL;

    load_data_to_avl_tree("effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv", &tree, users_sort_choice);
    system("cls");

    int menu_choice;
    while (1)
	{
	    printf("            ///////////*MENU*///////////");
	    printf("\n1-Evresi imeras/imerwn me elaxisti timi value");
		printf("\n2-Evresi imeras/imerwn me megisti timi value");
		printf("\n3-Eksodos");
		printf("\n\n Pliktrologise tin epilogi  sou (1,2,3) \n");
		scanf("%d", &menu_choice);
		/*elegxos eisodou*/
		while(menu_choice<1 || menu_choice>3){
        printf("\nLathos eisodos, dwse ksana \n");
        scanf("%d", &menu_choice);
		}
		printf("\n");
		fflush(stdin);

		AVL_NODE_PTR max_value;
		AVL_NODE_PTR min_value;

		 switch(menu_choice)
		{
			case 1:
			    system("cls");
			    min_value = search_min_value(tree);
			    if (min_value != NULL) {
                    printf("H elaxisti timi value ine: %.2f\n", min_value->data.value);
                    printf("Ke emfanizete se afti/es tin/s imerominies: \n");
                        while (min_value != NULL) {
                        printf("%s\n", min_value->data.date);
                        min_value = min_value->list->next_list_node;
                        }
                    } else
                    printf("The AVL tree is empty.");

                break;

            case 2:
                system("cls");
                max_value = search_max_value(tree);
			    if (max_value != NULL) {
                    printf("H megisti timi value ine: %.2f\n", max_value->data.value);
                    printf("Ke emfanizete se afti/es tin/s imerominies: \n");
                    while (max_value != NULL) {
                        printf("%s\n", max_value->data.date);
                        max_value = max_value->list->next_list_node;
                        }
    } else
        printf("The AVL tree is empty.");

                break;

            case 3:
                system("cls");
                printf("\nExiting the program. Goodbye!\n");
				fflush(stdin);
				exit(0);
			default:
				system("cls");
                printf("\n----------Lathos eisodos, dwse ksana---------- \n\n");
                continue;
		}

		printf("\n\n");
    }
}

void menu_hashing(){ ///HASHING MENU---HASHING MENU---HASHING MENU---HASHING MENU---HASHING MENU---HASHING MENU---HASHING MENU---HASHING MENU---HASHING MENU///

    HashTable table;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table.buckets[i] = NULL;
    }

    const char* filename = "effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
    load_data_to_hashTable(&table, filename);

    int menu_choice;
    while (1)
	{
	    printf("            ///////////*MENU*///////////");
		printf("\n1-Anazitisi timis vasi tis imerminias");
		printf("\n2-Tropopoiisi timis mias sigkekrimenis imerominias");
		printf("\n3-Diagrafi timis mias sigkekrimenis imerominias");
		printf("\n4-Eksodos");
		printf("\n\n Pliktrologise tin epilogi  sou (1,2,3,4) \n");
		scanf("%d", &menu_choice);
		printf("\n");
		fflush(stdin);

    element date_input[11];
    Node* found;

	    switch(menu_choice)
		{
			case 1:
			    system("cls");
				date_input_check(&date_input);

                found = search_value_by_date(&table, date_input);
                if (found != NULL) {
                    printf("Value for date %s: %lf\n", date_input, found->record.value);
                } else {
                    printf("No value found for date %s\n", date_input);
                }
                fflush(stdin);
				break;

			case 2:
			    system("cls");
				date_input_check(&date_input);

				printf("\n\nPliktrologise neo value. O arithmos prepei na einai thetikos!(value>0)\n");
				double new_value;
				scanf("%lf", &new_value);
				system("cls");
				while (new_value < 0){
                    printf("Lanthasmeni eisodos! O arithmos prepei na einai thetikos!\n");
                    scanf("%lf",new_value);
                    system("cls");
				}
				found = search_value_by_date(&table, date_input);
                if (found == NULL) {
                    printf("No value found for date %s\n", date_input);
                } else
                found->record.value=new_value;
				break;

			case 3:
				system("cls");
				date_input_check(&date_input);

				delete_hashTable_record(&table, date_input);
                fflush(stdin);
				break;

			case 4:
			    system("cls");
				printf("\nExiting the program. Goodbye!\n");
				fflush(stdin);
				exit(0);
			default:
			    system("cls");
                printf("\n----------Lathos eisodos, dwse ksana---------- \n\n");
                continue;
		}
		printf("\n\n");
	}

}

void load_data_to_avl_tree(const char* filename, AVL_NODE_PTR *root, int users_sort_choice) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: could not open file '%s' for reading\n", filename);
        exit(0);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, fp);


    int num_lines = 0;
    int check=0;
    while (fgets(line, MAX_LINE_LENGTH, fp) && check<=CHECK) {
            RECORD record;
         sscanf(line, "%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lf,%lf",
            record.direction,
               &record.year,
               record.date,
               record.weekday,
               record.country,
               record.commodity,
               record.transport_mode,
               record.measure,
               &record.value,
               &record.cumulative);

            check++;

            if(users_sort_choice==1)
                *root=insert_avl_node_by_date(&(*root), record);
            else
                *root=insert_avl_node_by_value(&(*root), record);
    }

    fclose(fp);
}

int insert_avl_root(AVL_NODE_PTR *root, RECORD rec)
{
	AVL_NODE_PTR new_node;

	if (*root!=NULL)
		return FALSE;

	new_node=(AVL_NODE *)malloc(sizeof(AVL_NODE));
	if (!new_node)
	{
		printf("Adynamia desmeusis mnimis");
		return FALSE;
	}
	new_node->data=rec;
	new_node->left=NULL;
	new_node->right=NULL;
	new_node->list=NULL;

	*root=new_node;
	return TRUE;
}

int delete_bst_node(AVL_NODE_PTR *root, element users_given_date)
{
	AVL_NODE_PTR current, parent, next_in_order;
	int plevra_ipodentrou;

	parent=NULL;
	current=*root;
	while (current!=NULL)
	{
		if (strcmp(users_given_date , current->data.date) == 0)
			break;
		else if (strcmp(users_given_date , current->data.date) < 0)
		{
			parent=current;
			plevra_ipodentrou=1;
			current=current->left;
		}
		else
		{
			parent=current;
			plevra_ipodentrou=2;
			current=current->right;
		}
	}
	if (current==NULL)
		return FALSE;

	if (current->left==NULL && current->right==NULL)
	{
		free(current);

		if (parent==NULL)
			*root=NULL;
		else
			if (plevra_ipodentrou==1)
				parent->left=NULL;
			else
				parent->right=NULL;
		return TRUE;
	}

	else if (current->left!=NULL && current->right==NULL)
	{
		if (parent==NULL)
			*root=current->left;
		else
			if (plevra_ipodentrou==1)
				parent->left=current->left;
			else
				parent->right=current->left;
		free(current);
		return TRUE;
	}

	else if (current->left==NULL && current->right!=NULL)
	{
		if (parent==NULL)
			*root=current->right;
		else
			if (plevra_ipodentrou==1)
				parent->left=current->right;
			else
				parent->right=current->right;
		free(current);
		return TRUE;
	}

	else
	{
		plevra_ipodentrou=1;
		next_in_order=current->right;

		while (next_in_order->left!=NULL)
		{
			parent=next_in_order;
			next_in_order=next_in_order->left;
			plevra_ipodentrou=2;
		}

        current->data=next_in_order->data;

		if (plevra_ipodentrou==1)
		{
			current->right=next_in_order->right;
			free(next_in_order);
		}
		else
		{
			parent->left=next_in_order->right;
			free(next_in_order);
		}
	}
}

AVL_NODE_PTR rotate_avl_right(AVL_NODE_PTR node)
{
	AVL_NODE_PTR previus_left_child = node->left;
	node->left = previus_left_child->right;
	previus_left_child->right = node;
	node->height = max(height(node->left), height(node->right))+1;
	previus_left_child->height = max(height(previus_left_child->left), height(previus_left_child->right))+1;
	return previus_left_child;
}

AVL_NODE_PTR rotate_avl_left(AVL_NODE_PTR node)
{
   AVL_NODE_PTR previus_right_child = node->right;
   node->right = previus_right_child->left;
   previus_right_child->left = node;
   node->height = max(height(node->left), height(node->right))+1;
   previus_right_child->height = max(height(previus_right_child->left), height(previus_right_child->right))+1;
   return previus_right_child;
}

AVL_NODE_PTR rotate_avl_left_right(AVL_NODE_PTR node)
{
   node->left = rotate_avl_left(node->left);

   return rotate_avl_right(node);
}

AVL_NODE_PTR rotate_avl_right_left(AVL_NODE_PTR node)
{
   node->right = rotate_avl_right(node->right);

   return rotate_avl_left(node);
}

AVL_NODE_PTR insert_avl_node_by_date(AVL_NODE_PTR *root, RECORD rec)
{
	if (*root == NULL)
    {
        insert_avl_root(root, rec);
        (*root)->height = 1;
        return *root;
    }
    else if (compare_dates(rec.date, (*root)->data.date) < 0)
    {
        (*root)->left = insert_avl_node_by_date(&((*root)->left), rec);
        if (height((*root)->left) - height((*root)->right) == 2)
        {
            if (compare_dates(rec.date, (*root)->left->data.date) < 0)
                (*root) = rotate_avl_right(*root);
            else
                (*root) = rotate_avl_left_right(*root);
        }
    }
    else if (compare_dates(rec.date, (*root)->data.date) > 0)
    {
        (*root)->right = insert_avl_node_by_date(&((*root)->right), rec);
        if (height((*root)->left) - height((*root)->right) == -2)
        {
            if (compare_dates(rec.date, (*root)->right->data.date) > 0)
                (*root) = rotate_avl_left(*root);
            else
                (*root) = rotate_avl_right_left(*root);
        }
    } else {
          LIST_NODE new_list_node;
          if ((*root)->list == NULL) {
          new_list_node = (LIST_NODE)malloc(sizeof(struct AVL_LIST_NODE));

        if (!new_list_node) {
            printf("Adynamia desmefsi mnimis gia komvo pou epanalamvanete\n\n");
            return *root;
        }
        (*root)->list = new_list_node;
        new_list_node->data = rec;
        new_list_node->next_list_node = NULL;
        } else {
            LIST_NODE current = (*root)->list;
            while (current->next_list_node != NULL) {
                current = current->next_list_node;
            }
            current->next_list_node = (LIST_NODE)malloc(sizeof(struct AVL_LIST_NODE));
        if (!current->next_list_node) {
            printf("Memory allocation failed for list node\n\n");
            return *root;
        }
        current = current->next_list_node;
        current->data = rec;
        current->next_list_node = NULL;
        }
    }

	(*root)->height = max(height((*root)->left), height((*root)->right))+1;
	return (*root);
}

AVL_NODE_PTR insert_avl_node_by_value(AVL_NODE_PTR *root, RECORD rec)
{
	if (*root == NULL)
    {
        insert_avl_root(root, rec);
        (*root)->height = 1;
        return *root;
    }
    else if (rec.value < (*root)->data.value)
    {
        (*root)->left = insert_avl_node_by_value(&((*root)->left), rec);
        if (height((*root)->left) - height((*root)->right) == 2)
        {
            if (rec.value < (*root)->left->data.value)
                (*root) = rotate_avl_right(*root);
            else
                (*root) = rotate_avl_left_right(*root);
        }
    }
    else if (rec.value > (*root)->data.value)
    {
        (*root)->right = insert_avl_node_by_value(&((*root)->right), rec);
        if (height((*root)->left) - height((*root)->right) == -2)
        {
            if (rec.value > (*root)->right->data.value)
                (*root) = rotate_avl_left(*root);
            else
                (*root) = rotate_avl_right_left(*root);
        }
    }else {
          LIST_NODE new_list_node;
          if ((*root)->list == NULL) {
          new_list_node = (LIST_NODE)malloc(sizeof(struct AVL_LIST_NODE));

        if (!new_list_node) {
            printf("Adynamia desmefsi mnimis gia komvo pou epanalamvanete\n\n");
            return *root;
        }
        (*root)->list = new_list_node;
        new_list_node->data = rec;
        new_list_node->next_list_node = NULL;
        } else {
            LIST_NODE current = (*root)->list;
            while (current->next_list_node != NULL) {
                current = current->next_list_node;
            }
            current->next_list_node = (LIST_NODE)malloc(sizeof(struct AVL_LIST_NODE));
        if (!current->next_list_node) {
            printf("Memory allocation failed for list node\n\n");
            return *root;
        }
        current = current->next_list_node;
        current->data = rec;
        current->next_list_node = NULL;
        }
    }

	(*root)->height = max(height((*root)->left), height((*root)->right))+1;
	return (*root);
}

int delete_avl_node(AVL_NODE_PTR *root, element users_given_date)
{
	AVL_NODE_PTR new_parent_node[DEPTH], new_root;
	int previous_parent_nodes[DEPTH];
	AVL_NODE_PTR current;
	int index=0,j;

	if (*root==NULL){
        printf("\n\nNOT DELETED. THE TREE IS EMPTY");
		return EMPTY_TREE;
	}

	current=*root;
	while(current!=NULL)
	{
		if (strcmp(users_given_date , current->data.date) == 0){
			break;  }
		else if (strcmp(users_given_date , current->data.date) < 0)
		{
			previous_parent_nodes[index]=0;
			new_parent_node[index++]=current;
			current=current->left;
		}
		else
		{
			previous_parent_nodes[index]=1;
			new_parent_node[index++]=current;
			current=current->right;
		}
	}
	if (current==NULL){
        printf("\n\nDEN IPARXI KOMVOS ME AFTI TIN IMEROMINIA");
		return FALSE;
	}

	if (current->left!=NULL && current->right!=NULL)
	{
		previous_parent_nodes[index]=1;
		new_parent_node[index++]=current;
		current=current->right;

		while (current->left!=NULL)
		{
			previous_parent_nodes[index]=0;
			new_parent_node[index++]=current;
			current=current->left;
		}
	}
	delete_bst_node(root, users_given_date);

	for (j=index-1; j>=0; j--)
	{
		if (height(new_parent_node[j]->left)-height(new_parent_node[j]->right)==2)
		{
			if(height(new_parent_node[j]->left->left)>height(new_parent_node[j]->left->right))
				new_root=rotate_avl_right(new_parent_node[j]);
			else
				new_root=rotate_avl_left_right(new_parent_node[j]);
		}
		else if (height(new_parent_node[j]->left)-height(new_parent_node[j]->right)==-2)
		{
			if(height(new_parent_node[j]->right->right)>height(new_parent_node[j]->right->left))
				new_root=rotate_avl_left(new_parent_node[j]);
			else
				new_root=rotate_avl_right_left(new_parent_node[j]);
		}
		else
			continue;

		if (j==0)
			*root = new_root;
		else
			if (previous_parent_nodes[index-1]==0)
				new_parent_node[index-1]->left=new_root;
			else
				new_parent_node[index-1]->right=new_root;
	}
	printf("\n\nSUCCESFULLY DELETED");
	return TRUE;
}

void print_avl_node(AVL_NODE_PTR root)
{
	if (root->left!=NULL)
	{
		print_avl_node(root->left);
	}

	printf("\n%s     %.2lf ", root->data.date, root->data.value);

    LIST_NODE current = root->list;
    while (current != NULL) {
        printf("\tDUPLICATE:     %.2lf\n", current->data.value);
        current = current->next_list_node;
    }
    printf("\n");

	if (root->right!=NULL)
	{
		print_avl_node(root->right);
	}
}

AVL_NODE_PTR search_avl_node(AVL_NODE_PTR root, element users_given_date)
{
	AVL_NODE_PTR current;

	current=root;

	while (current!=NULL)
	{
		if (compare_dates(users_given_date , current->data.date) == 0)
			return current;
		else if (compare_dates(users_given_date , current->data.date) < 0)
			current=current->left;
		else
			current=current->right;
	}
	return NULL;
}

int max(int x, int y)
{
	if (x>y)
		return x;
	else
		return y;
}

int height(AVL_NODE_PTR root)
{
	if (root==NULL)
		return 0;
	else
		return root->height;
}

AVL_NODE_PTR search_max_value(AVL_NODE_PTR tree){

if (tree == NULL)
        return NULL;

    AVL_NODE_PTR current = tree;
    while (current->right != NULL)
        current = current->right;

    return current;
}

AVL_NODE_PTR search_min_value(AVL_NODE_PTR tree){

if (tree == NULL)
        return NULL;

    AVL_NODE_PTR current = tree;
    while (current->left != NULL)
        current = current->left;

    return current;
}

void date_input_check(element* date) {
    int day, month, year;
    int valid_input = FALSE;

    do {
        printf("Enter the date in the format DD/MM/YYYY: ");
        if (scanf("%d/%d/%d", &day, &month, &year) != 3) {
            // Invalid input format
            while (getchar() != '\n'); // Clear input buffer
            printf("\n\nLanthasmeni eisodos! Dwse imerominia stin morfi DD/MM/YYYY\n");
        } else {
            // Check date validity
            if (day < 1 || year < 2015 || year > 2021) {
                printf("\n\nLanthasmeni eisodos! Dwse imerominia stin morfi DD/MM/YYYY\n");
            } else {
                switch (month) {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        if (day > 31) {
                            printf("\n\nLanthasmeni eisodos! Dwse imerominia stin morfi DD/MM/YYYY\n");
                        } else {
                            valid_input = TRUE;
                        }
                        break;

                    case 2:
                        if (day > 28) {
                            printf("\n\nLanthasmeni eisodos! Dwse imerominia stin morfi DD/MM/YYYY\n");
                        } else {
                            valid_input = TRUE;
                        }
                        break;

                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        if (day > 30) {
                            printf("\n\nLanthasmeni eisodos! Dwse imerominia stin morfi DD/MM/YYYY\n");
                        } else {
                            valid_input = TRUE;
                        }
                        break;
                }
            }
        }
    } while (!valid_input);

    // Store the validated date in the provided pointer
    sprintf(*date, "%02d/%02d/%04d", day, month, year);
}

int hash_function(element date[11]){

int sum = 0;
    for (int i = 0; i < 11; i++) {
        sum += (int)(date[i]);
 }
    return sum % HASH_TABLE_SIZE;

}

void insert_record_to_hashTable(HashTable* table, RECORD record){

int index = hash_function(record.date);

    Node* new_node = malloc(sizeof(Node));
    new_node->record = record;
    new_node->next = NULL;

    if (table->buckets[index] == NULL) {
        table->buckets[index] = new_node;
    } else {
        Node* current = table->buckets[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void load_data_to_hashTable(HashTable* table, const char* filename){

FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: could not open file '%s' for reading\n", filename);
        exit(0);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, fp);

    int check=0;
    printf("\n\nfile is loading...\n\n");
    while (fgets(line, MAX_LINE_LENGTH, fp) && check<=CHECK) {
        RECORD record;
        sscanf(line,  "%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lf,%lf",
               record.direction,
               &record.year,
               record.date,
               record.weekday,
               record.country,
               record.commodity,
               record.transport_mode,
               record.measure,
               &record.value,
               &record.cumulative);
            insert_record_to_hashTable(table, record);
            check++;
    }

    system("cls");

    fclose(fp);
}

Node* search_value_by_date(HashTable* table, element users_given_date) {
    int index = hash_function(users_given_date);
    Node* current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(current->record.date, users_given_date) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void delete_hashTable_record(HashTable* table, element users_given_date) {
    int index = hash_function(users_given_date);

    Node* current = table->buckets[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->record.date, users_given_date) == 0) {
            if (prev == NULL) {
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Record with date %s deleted.\n", users_given_date);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Record with date %s not found.\n", users_given_date);
}

int compare_dates(const char* new_date, const char* record_date)
{
    // Extract year, month, and day from date1
    int year1, month1, day1;
    sscanf(new_date, "%d/%d/%d", &day1, &month1, &year1);

    int year2, month2, day2;
    sscanf(record_date, "%d/%d/%d", &day2, &month2, &year2);

    // Compare year, month, and day in ascending order
    if (year1 != year2)
        return year1 - year2;
    else if (month1 != month2)
        return month1 - month2;
    else
        return day1 - day2;
}
