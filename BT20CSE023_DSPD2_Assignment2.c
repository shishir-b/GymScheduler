/*  Name : Shishir Nandkishor Bhalerao
    Enroll no. : BT20CSE023
    DSPD-II Assignment-2 Batch-1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

typedef struct Program_Tree // AVL Tree for Programs(Courses).
{
    int key;       // Key as per the progarms 1 to 4
    char name[20]; // Course Name
    int height;
    struct Program_Tree *left;
    struct Program_Tree *right;
} Programs;

int height_p(Programs *N) // Height Finding function for Program AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}
Programs *new_program_node(int key) // To create a new program node.
{
    Programs *node = (Programs *)malloc(sizeof(Programs));
    char name[20];
    // As per the keys they are stored respectively.
    if (key == 1)
        strcpy(name, "Yoga");
    else if (key == 2)
        strcpy(name, "Cardio");
    else if (key == 3)
        strcpy(name, "Zumba");
    else if (key == 4)
        strcpy(name, "WeightLifting");
    strcpy(node->name, name);
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Programs *rightRotate_p(Programs *y) // Function to rotate right for program Tree.
{
    Programs *x = y->left;
    Programs *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_p(y->left), height_p(y->right)) + 1;
    x->height = max(height_p(x->left), height_p(x->right)) + 1;

    return x;
}
Programs *leftRotate_p(Programs *x) // Function to rotate left for program Tree.
{
    Programs *y = x->right;
    Programs *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_p(x->left), height_p(x->right)) + 1;
    y->height = max(height_p(y->left), height_p(y->right)) + 1;

    return y;
}
int get_p_Balance(Programs *N) // Function to count balance factor for Program Tree.
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_p(N->left) - height_p(N->right);
    return ret_val;
}
Programs *add_programs(Programs *node, int key) // Function to add program to the Program Tree in AVL Insertion.
{
    // Find the correct position to add_programs the node and add_programs it
    Programs *ret_val = node;
    if (node == NULL)
        ret_val = (new_program_node(key));
    else
    {
        if (key < node->key)
            node->left = add_programs(node->left, key);
        else if (key > node->key)
            node->right = add_programs(node->right, key);

        // Uodating the balance factor and balancing the Tree to make AVL again.
        node->height = 1 + max(height_p(node->left), height_p(node->right));

        int balance = get_p_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_p(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_p(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_p(node->left);
            ret_val = rightRotate_p(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_p(node->right);
            ret_val = leftRotate_p(node);
        }
        return ret_val;
    }
}
void print_programs_list(Programs *root) // To print the program List. Traversing in In-Order.
{
    if (root != NULL)
    {
        print_programs_list(root->left);
        printf("%s.\n", root->name);
        print_programs_list(root->right);
    }
}
// For Member Programs Tree
typedef struct Program_Member // AVL Tree for Programs_Mem(Courses).
{
    int key;       // Key as per the progarms 1 to 4
    char name[20]; // Course Name
    int fees;      // Course Fees
    int height;
    struct Program_Member *left;
    struct Program_Member *right;
} Programs_Mem;

int height_p_m(Programs_Mem *N) // Height Finding function for Program Member AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}
Programs_Mem *new_program_mem_node(int key, int *fee_tot) // To create a new program Member node.
{
    Programs_Mem *node = (Programs_Mem *)malloc(sizeof(Programs_Mem));
    char name[20];
    // As per the keys they are stored respectively.
    if (key == 1)
        strcpy(name, "Yoga");
    else if (key == 2)
        strcpy(name, "Cardio");
    else if (key == 3)
        strcpy(name, "Zumba");
    else if (key == 4)
        strcpy(name, "WeightLifting");
    strcpy(node->name, name);
    int fees;
    printf("Enter Fees:\n");
    scanf("%d", &fees);
    *fee_tot += fees;
    node->fees = fees;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Programs_Mem *rightRotate_p_m(Programs_Mem *y) // Function to rotate right for program member Tree.
{
    Programs_Mem *x = y->left;
    Programs_Mem *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_p_m(y->left), height_p_m(y->right)) + 1;
    x->height = max(height_p_m(x->left), height_p_m(x->right)) + 1;

    return x;
}
Programs_Mem *leftRotate_p_m(Programs_Mem *x) // Function to rotate left for program member Tree.
{
    Programs_Mem *y = x->right;
    Programs_Mem *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_p_m(x->left), height_p_m(x->right)) + 1;
    y->height = max(height_p_m(y->left), height_p_m(y->right)) + 1;

    return y;
}
int get_p_m_Balance(Programs_Mem *N) // Function to count balance factor for Program member Tree.
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_p_m(N->left) - height_p_m(N->right);
    return ret_val;
}
Programs_Mem *add_Programs_Mem(Programs_Mem *node, int key, int *fees) // Function to add program to the Program Mem Tree in AVL Insertion.
{
    // Find the correct position to add_Programs_Mem the node and add_Programs_Mem it
    Programs_Mem *ret_val = node;
    if (node == NULL)
        ret_val = (new_program_mem_node(key, fees));
    else
    {
        if (key < node->key)
            node->left = add_Programs_Mem(node->left, key, fees);
        else if (key > node->key)
            node->right = add_Programs_Mem(node->right, key, fees);

        // Uodating the balance factor and balancing the Tree to make AVL again.
        node->height = 1 + max(height_p_m(node->left), height_p_m(node->right));

        int balance = get_p_m_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_p_m(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_p_m(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_p_m(node->left);
            ret_val = rightRotate_p_m(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_p_m(node->right);
            ret_val = leftRotate_p_m(node);
        }
        return ret_val;
    }
}
void print_Programs_Mem_list(Programs_Mem *root) // To print the program member List. Traversing in In-Order.
{
    if (root != NULL)
    {
        print_Programs_Mem_list(root->left);
        printf("%s\t%d.\n", root->name, root->fees);
        print_Programs_Mem_list(root->right);
    }
}

typedef struct Member_Tree // AVL Tree for Member.
{
    int key;            // Works as Member ID Too
    char name[20];      // Member Name
    int age;            // Age
    char gender;        // F for female and M for male.
    Programs_Mem *prog; // Program List for all courses for Member.
    int fees;
    struct Member_Tree *left;
    struct Member_Tree *right;
    int height;
} Member;

typedef struct Trainer_Tree
{
    int key;        // Works as Trainer ID Too
    char name[20];  // Trainer Name
    Programs *prog; // Program List for all courses for Trainer. Yet to be done
    int fees;       // Fees
    struct Trainer_Tree *left;
    struct Trainer_Tree *right;
    int height;
} Trainer;

int height_m(Member *N) // Height Finding function for Member AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}

int height_t(Trainer *N) // Height Finding function for Trainer AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}

// Member Starts Here for AVL Insertion deletion.

Member *new_member_node(int key) // To create a new Member node.
{
    Member *node = (Member *)malloc(sizeof(Member));
    printf("Enter Member Name: ");
    scanf("%s", node->name);
    printf("Enter Gender: ");
    fflush(stdin);
    scanf("%c", &node->gender);
    printf("Enter Age: ");
    scanf("%d", &node->age);
    int total_fees = 0;
    int no;
    printf("Enter Number of program: ");
    scanf("%d", &no);
    printf("Choose:\n1. Yoga 2. Cardio 3. Zumba 4. WeightLifting\n");
    Programs_Mem *p_ptr = NULL;
    while (no--)
    {
        int choice;
        printf("Enter : ");
        scanf("%d", &choice);
        p_ptr = add_Programs_Mem(p_ptr, choice, &total_fees);
    }
    node->fees = total_fees;
    node->prog = p_ptr;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Member *rightRotate_m(Member *y) // Function to rotate right for Member Tree.
{
    Member *x = y->left;
    Member *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_m(y->left), height_m(y->right)) + 1;
    x->height = max(height_m(x->left), height_m(x->right)) + 1;

    return x;
}

Member *leftRotate_m(Member *x) // Function to rotate left for Member Tree.
{
    Member *y = x->right;
    Member *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_m(x->left), height_m(x->right)) + 1;
    y->height = max(height_m(y->left), height_m(y->right)) + 1;

    return y;
}

int get_m_Balance(Member *N) // Function to count balance factor for Member Tree.
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_m(N->left) - height_m(N->right);
    return ret_val;
}

// Q1. Add_member()
// For adding member it take random generated key for id and Member Tree Root and Add with respect to AVL properties.
// And returns root.
Member *add_member(Member *node, int key) // Function to add Member to the Member Tree in AVL Insertion.
{
    // Find the correct position to add_member the node and add_member it
    Member *ret_val = node;
    if (node == NULL)
        ret_val = (new_member_node(key));
    else
    {
        if (key < node->key)
            node->left = add_member(node->left, key);
        else if (key > node->key)
            node->right = add_member(node->right, key);

        // Updating the balance factor and balancing the Tree to make AVL again.
        node->height = 1 + max(height_m(node->left), height_m(node->right));

        int balance = get_m_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_m(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_m(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_m(node->left);
            ret_val = rightRotate_m(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_m(node->right);
            ret_val = leftRotate_m(node);
        }
        return ret_val;
    }
}

Member *min_value_m_node(Member *node) // To find minimum node to join when Member Node deleted.
{
    Member *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Q5. delete_member() to delete the member with key as id.
Member *delete_member(Member *root, int key, int *yes)
{
    // Finding Node and deleting it.
    Member *ret_val = root;
    if (root == NULL)
        ret_val = root;
    else
    {
        if (key < root->key)
            root->left = delete_member(root->left, key, yes);

        else if (key > root->key)
            root->right = delete_member(root->right, key, yes);

        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                Member *temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
                *yes = 1;
            }
            else
            {
                Member *temp = min_value_m_node(root->right);

                root->key = temp->key;

                root->right = delete_member(root->right, temp->key, yes);
            }
        }

        if (root == NULL)
            ret_val = root;

        // Updating the balance factor and balancing the Tree to make AVL again.
        else
        {
            root->height = 1 + max(height_m(root->left), height_m(root->right));

            int balance = get_m_Balance(root);
            if (balance > 1 && get_m_Balance(root->left) >= 0)
                ret_val = rightRotate_m(root);

            if (balance > 1 && get_m_Balance(root->left) < 0)
            {
                root->left = leftRotate_m(root->left);
                ret_val = rightRotate_m(root);
            }

            if (balance < -1 && get_m_Balance(root->right) <= 0)
                ret_val = leftRotate_m(root);

            if (balance < -1 && get_m_Balance(root->right) > 0)
            {
                root->right = rightRotate_m(root->right);
                ret_val = leftRotate_m(root);
            }
        }
    }
    return ret_val;
}

// Printing the Member Tree
void print_member_tree(Member *root)
{
    if (root != NULL)
    {
        print_member_tree(root->left);
        printf("%d\t\t%s\t\t%d\t\t%c\t\t%d\n", root->key, root->name, root->age, root->gender, root->fees);
        Programs_Mem *pptr = root->prog;
        printf("Courses\tFees:\n");
        print_Programs_Mem_list(pptr);
        printf("-----------------------------------------------------------------------------\n");
        print_member_tree(root->right);
    }
}
// To call print tree for member.
// Q8. print_member_list() to display all members record.
void print_member_list(Member *root)
{
    if (root == NULL)
    {
        printf("-----------------------------------------------------------------------------\n");
        printf("The Member List is Empty.\n");
        printf("-----------------------------------------------------------------------------\n");
    }
    else
    {
        printf("The Member List:\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("ID\t\tName\t\tAge\t\tGender\t\tTotal Fees(Rs)\n");
        printf("-----------------------------------------------------------------------------\n");
        print_member_tree(root);
    }
    printf("\n");
}

// Trainer Starts Here

Trainer *new_trainer_node(int key) // To create a new Trainer node.
{
    Trainer *node = (Trainer *)malloc(sizeof(Trainer));
    printf("Enter Trainer Name: ");
    scanf("%s", node->name);
    printf("Enter Fees: ");
    scanf("%d", &node->fees);
    int no;
    printf("Enter Number of program: ");
    scanf("%d", &no);
    printf("Choose:\n1. Yoga 2. Cardio 3. Zumba 4. WeightLifting\n");
    Programs *p_ptr = NULL;
    while (no--)
    {
        int choice;
        printf("Enter : ");
        scanf("%d", &choice);
        p_ptr = add_programs(p_ptr, choice);
    }
    node->prog = p_ptr;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Trainer *rightRotate_t(Trainer *y) // Function to rotate right for Trainer Tree.
{
    Trainer *x = y->left;
    Trainer *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_t(y->left), height_t(y->right)) + 1;
    x->height = max(height_t(x->left), height_t(x->right)) + 1;

    return x;
}

Trainer *leftRotate_t(Trainer *x) // Function to rotate left for Trainer Tree.
{
    Trainer *y = x->right;
    Trainer *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_t(x->left), height_t(x->right)) + 1;
    y->height = max(height_t(y->left), height_t(y->right)) + 1;

    return y;
}

// Function to count balance factor for Trainer Tree.
int get_t_Balance(Trainer *N)
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_t(N->left) - height_t(N->right);
    return ret_val;
}

// Function to add Trainer to the Trainer Tree in AVL Insertion.
// Q2. Add_trainer()
// For adding trainer it take random generated key for id and Trainer Tree Root and Add with respect to AVL properties.
// And returns root.
Trainer *add_trainer(Trainer *node, int key)
{
    // Find the correct position to add_trainer the node and add_trainer it
    Trainer *ret_val = node;
    if (node == NULL)
        ret_val = (new_trainer_node(key));
    else
    {
        if (key < node->key)
            node->left = add_trainer(node->left, key);
        else if (key > node->key)
            node->right = add_trainer(node->right, key);

        // Updating the balance factor and balancing the Tree to make AVL again.
        node->height = 1 + max(height_t(node->left), height_t(node->right));

        int balance = get_t_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_t(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_t(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_t(node->left);
            ret_val = rightRotate_t(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_t(node->right);
            ret_val = leftRotate_t(node);
        }
        return ret_val;
    }
}

Trainer *min_value_t_node(Trainer *node) // To find minimum node to join when Trainer Node deleted.
{
    Trainer *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Q6. delete_trainer() to delete the trainer with key.
Trainer *delete_trainer(Trainer *root, int key, int *yes)
{
    // Find the node and deleting it.
    Trainer *ret_val = root;
    if (root == NULL)
        ret_val = root;
    else
    {
        if (key < root->key)
            root->left = delete_trainer(root->left, key, yes);

        else if (key > root->key)
            root->right = delete_trainer(root->right, key, yes);

        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                Trainer *temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
                *yes = 1;
            }
            else
            {
                Trainer *temp = min_value_t_node(root->right);

                root->key = temp->key;

                root->right = delete_trainer(root->right, temp->key, yes);
            }
        }

        if (root == NULL)
            ret_val = root;

        // Updating the balance factor and balancing the Tree to make AVL again.
        else
        {
            root->height = 1 + max(height_t(root->left), height_t(root->right));

            int balance = get_t_Balance(root);
            if (balance > 1 && get_t_Balance(root->left) >= 0)
                ret_val = rightRotate_t(root);

            if (balance > 1 && get_t_Balance(root->left) < 0)
            {
                root->left = leftRotate_t(root->left);
                ret_val = rightRotate_t(root);
            }

            if (balance < -1 && get_t_Balance(root->right) <= 0)
                ret_val = leftRotate_t(root);

            if (balance < -1 && get_t_Balance(root->right) > 0)
            {
                root->right = rightRotate_t(root->right);
                ret_val = leftRotate_t(root);
            }
        }
    }
    return ret_val;
}

// Printing the tariner tree
void print_trainer_tree(Trainer *root)
{
    if (root != NULL)
    {
        print_trainer_tree(root->left);
        printf("%d\t\t%s\t\t%d\n", root->key, root->name, root->fees);
        Programs *pptr = root->prog;
        printf("Courses that can be Trained: \n");
        print_programs_list(pptr);
        printf("-----------------------------------------------------------------------------\n");
        print_trainer_tree(root->right);
    }
}
// To call print trainer tree.
// Q10. print_trainer_list() displays trainer records.
void print_trainer_list(Trainer *root)
{
    if (root == NULL)
    {
        printf("-----------------------------------------------------------------------------\n");
        printf("The Trainer List is Empty.\n");
        printf("-----------------------------------------------------------------------------\n");
    }
    else
    {
        printf("The Trainer List:\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("ID\t\tName\t\tFees(Rs)\n");
        printf("-----------------------------------------------------------------------------\n");
        print_trainer_tree(root);
    }
    printf("\n");
}

// For Member Search

// To Search Member ID
Member *s_m_id(Member *root, int id)
{
    Member *ret_val;
    if (root == NULL || root->key == id)
    {
        ret_val = root;
    }
    else if (root->key < id)
    {
        ret_val = s_m_id(root->right, id);
    }
    else
    {
        ret_val = s_m_id(root->left, id);
    }
    return ret_val;
}
// To Search Member Name
void s_m_name(Member *root, int *found, char name[])
{
    if (root != NULL)
    {
        s_m_name(root->left, found, name);
        if (strcmp(root->name, name) == 0)
        {
            *found = 1;
            printf("ID : %d\tName : %s\tGender : %c\tAge : %d\tFees : %d.\n", root->key, root->name, root->gender, root->age, root->fees);
            Programs_Mem *pptr = root->prog;
            printf("Courses\tFees :\n");
            print_Programs_Mem_list(pptr);
        }
        s_m_name(root->right, found, name);
    }
}
// To Search Member Age
void s_m_age(Member *root, int *found, int age)
{
    if (root != NULL)
    {
        s_m_age(root->left, found, age);
        if (root->age == age)
        {
            *found = 1;
            printf("ID : %d\tName : %s\tGender : %c\tAge : %d\tFees : %d.\n", root->key, root->name, root->gender, root->age, root->fees);
            Programs_Mem *pptr = root->prog;
            printf("Courses\tFees :\n");
            print_Programs_Mem_list(pptr);
        }
        s_m_age(root->right, found, age);
    }
}
// To Search Member Gender
void s_m_gender(Member *root, int *found, char gender)
{
    if (root != NULL)
    {
        s_m_gender(root->left, found, gender);
        if (root->gender == gender)
        {
            *found = 1;
            printf("ID : %d\tName : %s\tGender : %c\tAge : %d\tFees : %d.\n", root->key, root->name, root->gender, root->age, root->fees);
            Programs_Mem *pptr = root->prog;
            printf("Courses\tFees :\n");
            print_Programs_Mem_list(pptr);
        }
        s_m_gender(root->right, found, gender);
    }
}
// To Search any Programs for Trainer
void s_programs(Programs *root, int *present, char name[])
{
    if (root != NULL)
    {
        s_programs(root->left, present, name);
        if (strcmp(root->name, name) == 0)
        {
            *present = 1;
        }
        s_programs(root->right, present, name);
    }
}
// To Search any Programs for Trainer
void s_programs_mem(Programs_Mem *root, int *present, char name[])
{
    if (root != NULL)
    {
        s_programs_mem(root->left, present, name);
        if (strcmp(root->name, name) == 0)
        {
            *present = 1;
        }
        s_programs_mem(root->right, present, name);
    }
}
// To Search Member Program
void s_m_program(Member *root, int *found, char name[])
{
    if (root != NULL)
    {
        s_m_program(root->left, found, name);
        int present = 0;
        s_programs_mem(root->prog, &present, name);
        if (present == 1)
        {
            *found = 1;
            printf("ID : %d\tName : %s\tGender : %c\tAge : %d\tFees : %d.\n", root->key, root->name, root->gender, root->age, root->fees);
            Programs_Mem *pptr = root->prog;
            printf("Courses\tFees:\n");
            print_Programs_Mem_list(pptr);
        }
        s_m_program(root->right, found, name);
    }
}

// Q7. search_member() to search member tree as per key and key value.
void search_member(Member *root_m)
{
    int option;
    printf("Press 1)ID 2)Name 3)Age 4)Gender 5)Program\n");
    scanf("%d", &option);
    int found = 0;
    Member *lptr = root_m;
    if (option == 1)
    {
        int id;
        printf("Enter ID: \n");
        scanf("%d", &id);
        printf("-----------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        // Do on basis of binary search
        Member *id_node = s_m_id(lptr, id);
        if (id_node != NULL)
        {
            found = 1;
            printf("ID : %d\tName : %s\tGender : %c\tAge : %d\tFees : %d.\n", id_node->key, id_node->name, id_node->gender, id_node->age, id_node->fees);
            Programs_Mem *pptr = id_node->prog;
            print_Programs_Mem_list(pptr);
        }
    }
    else if (option == 2)
    {
        char name[20];
        printf("Enter Name: \n");
        scanf("%s", name);
        printf("-----------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        s_m_name(lptr, &found, name);
    }
    else if (option == 3)
    {
        int age;
        printf("Enter Age: \n");
        scanf("%d", &age);
        printf("-----------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        s_m_age(lptr, &found, age);
    }
    else if (option == 4)
    {
        char gender;
        printf("Enter Gender: \n");
        fflush(stdin);
        scanf("%c", &gender);
        printf("-----------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        s_m_gender(lptr, &found, gender);
    }
    else
    {
        char prog[20];
        printf("Enter Program: \n");
        scanf("%s", prog);
        printf("-----------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        s_m_program(lptr, &found, prog);
    }
    if (found == 0)
    {
        printf("None\n");
    }
    printf("-----------------------------------------------------------------------------\n");
}

// Search Trainer

// To Search Trainer ID
Trainer *s_t_id(Trainer *root, int id)
{
    Trainer *ret_val;
    if (root == NULL || root->key == id)
    {
        ret_val = root;
    }
    else if (root->key < id)
    {
        ret_val = s_t_id(root->right, id);
    }
    else
    {
        ret_val = s_t_id(root->left, id);
    }
    return ret_val;
}
// To Search Trainer Name
void s_t_name(Trainer *root, int *found, char name[])
{
    if (root != NULL)
    {
        s_t_name(root->left, found, name);
        if (strcmp(root->name, name) == 0)
        {
            *found = 1;
            printf("ID : %d\tName : %s.\n", root->key, root->name);
            Programs *pptr = root->prog;
            printf("Courses :\n");
            print_programs_list(pptr);
        }
        s_t_name(root->right, found, name);
    }
}
// To Search Trainer Program
void s_t_program(Trainer *root, int *found, char name[])
{
    if (root != NULL)
    {
        s_t_program(root->left, found, name);
        int present = 0;
        s_programs(root->prog, &present, name);
        if (present == 1)
        {
            *found = 1;
            printf("ID : %d\tName : %s.\n", root->key, root->name);
            Programs *pptr = root->prog;
            printf("Courses :\n");
            print_programs_list(pptr);
        }
        s_t_program(root->right, found, name);
    }
}

// Q8. search_trainer() to search trainer tree as per key and key value.
void search_trainer(Trainer *root_m)
{
    int option;
    printf("Press 1)ID 2)Name 3)Program\n");
    scanf("%d", &option);
    int found = 0;
    Trainer *lptr = root_m;
    if (option == 1)
    {
        int id;
        printf("Enter ID: \n");
        scanf("%d", &id);
        printf("-----------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        // Do on basis of binary search
        Trainer *id_node = s_t_id(lptr, id);
        if (id_node != NULL)
        {
            found = 1;
            printf("ID : %d\tName : %s.\n", id_node->key, id_node->name);
            Programs *pptr = id_node->prog;
            print_programs_list(pptr);
        }
    }
    else if (option == 2)
    {
        char name[20];
        printf("Enter Name: \n");
        scanf("%s", name);
        printf("-----------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        s_t_name(lptr, &found, name);
    }
    else
    {
        char prog[20];
        printf("Enter Program: \n");
        scanf("%s", prog);
        printf("-----------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        s_t_program(lptr, &found, prog);
    }
    if (found == 0)
    {
        printf("None\n");
    }
    printf("-----------------------------------------------------------------------------\n");
}

// For the Schedule List
typedef struct schedule_member_tag // AVL Tree for Schedules.
{
    int key;          // Hour + Min  will work as key
    int id;           // Member ID
    char program[20]; // Program to be Scheduled
    int slot;         // Preferred Slot
    int pref_id;      // Preferred Trainer ID
    int done;         // 0 for NOT, 1 for DONE ,2 for DONE with prefferd trainer.
    struct schedule_member_tag *left;
    struct schedule_member_tag *right;
    int height;
} schedule_member;

int height_sche(schedule_member *N) // Height Finding function for Schedule AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}

schedule_member *new_sche_node(int key) // To create a new Schedule node.
{
    schedule_member *nptr = (schedule_member *)malloc(sizeof(schedule_member));
    printf("For Member in Schedule :\n");
    int id;
    printf("Enter Member ID: ");
    scanf("%d", &id);
    nptr->id = id;
    char prog[20];
    printf("Enter Program Name: ");
    scanf("%s", prog);
    strcpy(nptr->program, prog);
    int slot;
    printf("Enter Time Slot: ");
    scanf("%d", &slot);
    nptr->slot = slot;
    int pref_id;
    printf("Enter Preferd Trainer ID: ");
    scanf("%d", &pref_id);
    nptr->pref_id = pref_id;
    nptr->done = 0;
    nptr->key = key;
    nptr->left = NULL;
    nptr->right = NULL;
    nptr->height = 1;
    return (nptr);
}

schedule_member *rightRotate_sche(schedule_member *y) // Function to rotate right for Schedule Tree.
{
    schedule_member *x = y->left;
    schedule_member *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_sche(y->left), height_sche(y->right)) + 1;
    x->height = max(height_sche(x->left), height_sche(x->right)) + 1;

    return x;
}

schedule_member *leftRotate_sche(schedule_member *x) // Function to rotate left for Schedule Tree.
{
    schedule_member *y = x->right;
    schedule_member *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_sche(x->left), height_sche(x->right)) + 1;
    y->height = max(height_sche(y->left), height_sche(y->right)) + 1;

    return y;
}

// Function to count balance factor for Schedule Tree.
int get_sche_Balance(schedule_member *N)
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_sche(N->left) - height_sche(N->right);
    return ret_val;
}

// Function to add Schedule to the Schedule Tree in AVL Insertion.
schedule_member *add_sche(schedule_member *node, int key)
{
    // Find the correct position to add_hour the node and add_hour it
    schedule_member *ret_val = node;
    if (node == NULL)
        ret_val = (new_sche_node(key));
    else
    {
        if (key < node->key)
            node->left = add_sche(node->left, key);
        else if (key > node->key)
            node->right = add_sche(node->right, key);

        // Updating the balance factor and balancing the Tree to make AVL again.
        node->height = 1 + max(height_sche(node->left), height_sche(node->right));

        int balance = get_sche_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_sche(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_sche(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_sche(node->left);
            ret_val = rightRotate_sche(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_sche(node->right);
            ret_val = leftRotate_sche(node);
        }
        return ret_val;
    }
}
// For Available Trainer
typedef struct available_tra_tag // AVL Tree for Availables.
{
    int key;        // As per entry random.
    int tra_id;     // Trainer ID
    Programs *prog; // All Courses trainer can take.
    int earned;     // Total Earned
    int fees;       // Fees
    struct available_tra_tag *left;
    struct available_tra_tag *right;
    int height;
} available_trainer;

int height_avai(available_trainer *N) // Height Finding function for Available AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}

available_trainer *new_avai_node(int key) // To create a new Available node.
{
    available_trainer *nptr = (available_trainer *)malloc(sizeof(available_trainer));
    char prog[20];
    int tra;
    printf("Enter Trainer ID: ");
    scanf("%d", &tra);
    int no;
    int fees = 0;
    printf("Enter Trainer Fees: ");
    scanf("%d", &fees);
    printf("Enter Number of program: ");
    scanf("%d", &no);
    printf("Choose:\n1. Yoga 2. Cardio 3. Zumba 4. WeightLifting\n");
    Programs *p_ptr = NULL;
    while (no--)
    {
        int choice;
        printf("Enter : ");
        scanf("%d", &choice);
        p_ptr = add_programs(p_ptr, choice);
    }
    nptr->fees = fees;
    nptr->earned = 0;
    nptr->prog = p_ptr;
    nptr->key = key;
    nptr->tra_id = tra;
    nptr->left = NULL;
    nptr->right = NULL;
    nptr->height = 1;
    return (nptr);
}

available_trainer *rightRotate_avai(available_trainer *y) // Function to rotate right for Available Tree.
{
    available_trainer *x = y->left;
    available_trainer *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_avai(y->left), height_avai(y->right)) + 1;
    x->height = max(height_avai(x->left), height_avai(x->right)) + 1;

    return x;
}

available_trainer *leftRotate_avai(available_trainer *x) // Function to rotate left for Available Tree.
{
    available_trainer *y = x->right;
    available_trainer *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_avai(x->left), height_avai(x->right)) + 1;
    y->height = max(height_avai(y->left), height_avai(y->right)) + 1;

    return y;
}

// Function to count balance factor for Available Tree.
int get_avai_Balance(available_trainer *N)
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_avai(N->left) - height_avai(N->right);
    return ret_val;
}

// Function to add Available to the Available Tree in AVL Insertion.
available_trainer *add_avai(available_trainer *node, int key)
{
    // Find the correct position to add_hour the node and add_hour it
    available_trainer *ret_val = node;
    if (node == NULL)
        ret_val = (new_avai_node(key));
    else
    {
        if (key < node->key)
            node->left = add_avai(node->left, key);
        else if (key > node->key)
            node->right = add_avai(node->right, key);

        // Update the balance factor of each node and
        // Balance the tree
        node->height = 1 + max(height_avai(node->left), height_avai(node->right));

        int balance = get_avai_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_avai(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_avai(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_avai(node->left);
            ret_val = rightRotate_avai(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_avai(node->right);
            ret_val = leftRotate_avai(node);
        }
        return ret_val;
    }
}
// For Per Hour List

typedef struct Per_Hour // AVL Tree for Per Hours.
{
    int key;          // Will used as no of free slots as key
    int trainer_id;   // Trainer ID for the slot
    int member_id;    // Member ID for the slot
    char program[20]; // Course Name
    int pref;
    struct Per_Hour *right;
    struct Per_Hour *left;
    int height;
} Per;

int height_hp(Per *N) // Height Finding function for Per Hour AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}

Per *new_per_node(int key, int mem_id, int tra_id, char prog_n[], int pref) // To create a new Per Hour node.
{
    Per *node = (Per *)malloc(sizeof(Per));
    node->member_id = mem_id;
    node->trainer_id = tra_id;
    node->pref = pref;
    strcpy(node->program, prog_n);
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Per *rightRotate_hp(Per *y) // Function to rotate right for Per Hour Tree.
{
    Per *x = y->left;
    Per *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_hp(y->left), height_hp(y->right)) + 1;
    x->height = max(height_hp(x->left), height_hp(x->right)) + 1;

    return x;
}

Per *leftRotate_hp(Per *x) // Function to rotate left for Per Hour Tree.
{
    Per *y = x->right;
    Per *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_hp(x->left), height_hp(x->right)) + 1;
    y->height = max(height_hp(y->left), height_hp(y->right)) + 1;

    return y;
}

// Function to count balance factor for Per Hour Tree.
int get_hp_Balance(Per *N)
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_hp(N->left) - height_hp(N->right);
    return ret_val;
}

// Function to add Per Hour to the Per Hour Tree in AVL Insertion.
Per *add_per(Per *node, int key, int mem_id, int tra_id, char prog_n[], int pref)
{
    // Find the correct position to add_hour the node and add_hour it
    Per *ret_val = node;
    if (node == NULL)
        ret_val = (new_per_node(key, mem_id, tra_id, prog_n, pref));
    else
    {
        if (key < node->key)
            node->left = add_per(node->left, key, mem_id, tra_id, prog_n, pref);
        else if (key > node->key)
            node->right = add_per(node->right, key, mem_id, tra_id, prog_n, pref);

        /// Updating the balance factor and balancing the Tree to make AVL again.
        node->height = 1 + max(height_hp(node->left), height_hp(node->right));

        int balance = get_hp_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_hp(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_hp(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_hp(node->left);
            ret_val = rightRotate_hp(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_hp(node->right);
            ret_val = leftRotate_hp(node);
        }
        return ret_val;
    }
}
// To print per hour
void print_per_list(Per *root, char name[])
{
    if (root != NULL)
    {
        print_per_list(root->left, name);
        if (strcmp(root->program, name) == 0)
        {
            printf("The Member Id %d with Trainer Id %d for %s.\n", root->member_id, root->trainer_id, name);
        }
        print_per_list(root->right, name);
    }
}
// For Hour List
typedef struct Hour_list // Total 6:00 to 21:00 Slot Info AVL Tree.
{
    int free;  // No. of free slot Max 10 as (10 MAX members allowed).
    int key;   // Time Slot Start Time // Start will act as Key
    Per *info; // Respective Hour Info  Yet to be done
    struct Hour_list *left;
    struct Hour_list *right;
    int height;
} Hour;

int height_h(Hour *N) // Height Finding function for Hour AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}

Hour *new_hour_node(int key) // To create a new Hour node.
{
    Hour *node = (Hour *)malloc(sizeof(Hour));
    node->free = 10;
    node->key = key;
    node->info = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Hour *rightRotate_h(Hour *y) // Function to rotate right for Hour Tree.
{
    Hour *x = y->left;
    Hour *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_h(y->left), height_h(y->right)) + 1;
    x->height = max(height_h(x->left), height_h(x->right)) + 1;

    return x;
}

Hour *leftRotate_h(Hour *x) // Function to rotate left for Hour Tree.
{
    Hour *y = x->right;
    Hour *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_h(x->left), height_h(x->right)) + 1;
    y->height = max(height_h(y->left), height_h(y->right)) + 1;

    return y;
}

// Function to count balance factor for Hour Tree.
int get_h_Balance(Hour *N)
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_h(N->left) - height_h(N->right);
    return ret_val;
}

// Function to add Hour to the Hour Tree in AVL Insertion
Hour *add_hour(Hour *node, int key)
{
    // Find the correct position to add_hour the node and add_hour it
    Hour *ret_val = node;
    if (node == NULL)
        ret_val = (new_hour_node(key));
    else
    {
        if (key < node->key)
            node->left = add_hour(node->left, key);
        else if (key > node->key)
            node->right = add_hour(node->right, key);

        // Updating the balance factor and balancing the Tree to make AVL again.
        node->height = 1 + max(height_h(node->left), height_h(node->right));

        int balance = get_h_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_h(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_h(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_h(node->left);
            ret_val = rightRotate_h(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_h(node->right);
            ret_val = leftRotate_h(node);
        }
        return ret_val;
    }
}

// Q4. print_hour_wise_list() takes argument of hour root and prints schedule.
void print_hour_wise_list(Hour *root)
{
    if (root != NULL)
    {
        print_hour_wise_list(root->left);
        printf("-----------------------------------------------------------------------------\n");
        printf("For Slot Hour: %d:00 to %d:00 (Free slots are : %d) :\n", root->key, root->key + 1, root->free);
        Per *temp = root->info;
        printf("For Yoga:\n");
        print_per_list(temp, "Yoga");
        printf("For Cardio:\n");
        print_per_list(temp, "Cardio");
        printf("For Zumba:\n");
        print_per_list(temp, "Zumba");
        printf("For Weight Lifting:\n");
        print_per_list(temp, "WeightLifting");
        print_hour_wise_list(root->right);
    }
}
// For printing Assign Node Per Hour
void print_per_assign_list(Per *root, int opt, int slot)
{
    if (root != NULL)
    {
        print_per_assign_list(root->left, opt, slot);
        if (opt == root->pref)
        {
            printf("Member ID : %d\tTrainer ID: %d form slot %d:00 to %d:00.\n", root->member_id, root->trainer_id, slot, slot + 1);
        }
        print_per_assign_list(root->right, opt, slot);
    }
}
// For printing Assign Node of Day
void print_assign(Hour *root, int opt) // 1 for non-pref 2 for pref
{
    if (root != NULL)
    {
        print_assign(root->left, opt);
        if (root->free != 10)
        {
            print_per_assign_list(root->info, opt, root->key);
        }
        print_assign(root->right, opt);
    }
}
// Main Q3
void trav_per(Per *root, int *found, int id)
{
    if (root != NULL)
    {
        trav_per(root->left, found, id);
        if (root->member_id == id || root->trainer_id == id)
            *found = 1;
        trav_per(root->right, found, id);
    }
}
void trav_hour(Hour *root, int *found, int id)
{
    if (root != NULL)
    {
        trav_hour(root->left, found, id);
        trav_per(root->info, found, id);
        trav_hour(root->right, found, id);
    }
}

void trav_avail_mem(available_trainer *root, int *found, int id, Programs **prog, available_trainer **temp_a)
{
    if (root != NULL)
    {
        trav_avail_mem(root->left, found, id, prog, temp_a);
        if (root->tra_id == id)
        {
            *found = 1;
            *prog = root->prog;
            *temp_a = root;
        }
        trav_avail_mem(root->right, found, id, prog, temp_a);
    }
}

void trav_per_alloc(Per *root, int *found, int id)
{
    if (root != NULL)
    {
        trav_per_alloc(root->left, found, id);
        if (root->member_id == id || root->trainer_id == id)
            *found = 1;
        trav_per_alloc(root->right, found, id);
    }
}
void trav_hour_alloc(Hour *root, int *found, int id, schedule_member *sche)
{
    if (root != NULL)
    {
        trav_hour_alloc(root->left, found, id, sche);
        if (root->free > 0 && sche->slot <= root->key)
        {
            int is_trainer = 0;
            trav_per(root->info, &is_trainer, id);
            if (*found == 0 && is_trainer == 0)
            {
                if (id == sche->pref_id)
                    *found = 2;
                else
                    *found = 1;
                root->info = add_per(root->info, root->free, sche->id, id, sche->program, *found);
                root->free--;
            }
        }
        trav_hour_alloc(root->right, found, id, sche);
    }
}

void trav_avail_non_trai(available_trainer *root, int *found, char prog[], Hour *root_h, schedule_member *sche)
{
    if (root != NULL)
    {
        trav_avail_non_trai(root->left, found, prog, root_h, sche);
        int can_prog = 0;
        s_programs(root->prog, &can_prog, prog);
        if (can_prog == 1 && *found == 0)
        {
            int done = 0;
            *found = 1;
            for (int i = sche->slot; i < 22 && done == 0; i++)
            {
                trav_hour_alloc(root_h, &done, root->tra_id, sche);
            }
            if (done == 1)
            {
                root->earned += root->fees;
                sche->done = 1;
            }
        }
        trav_avail_non_trai(root->right, found, prog, root_h, sche);
    }
}
void trav_sche(schedule_member *sche_root, available_trainer *avai_root, Hour *hour_root)
{
    if (sche_root != NULL)
    {
        trav_sche(sche_root->left, avai_root, hour_root);
        int found = 0;
        int found_store;
        trav_hour(hour_root, &found, sche_root->id);
        found_store = found;
        if (found == 1)
        {
            printf("%d Member Already Exists so Cannot be Allocated.\n", sche_root->id);
        }
        else
        {
            int pref_trainer = sche_root->pref_id;
            Programs *tra_avail_prog = NULL;
            available_trainer *temp_a;
            trav_avail_mem(avai_root, &found, pref_trainer, &tra_avail_prog, &temp_a);
            int can_prog = 0;
            s_programs(tra_avail_prog, &can_prog, sche_root->program);

            if (can_prog == 1 && found == 1)
            { // Found set if trainer is available and Can if trainer can teach that program
                int done = 0;
                for (int i = sche_root->slot; i < 22 && done == 0; i++)
                {
                    trav_hour_alloc(hour_root, &done, sche_root->pref_id, sche_root); // Calling function to allocate slot for time from that slot to upto last slot with pref trainer.
                }
                if (done == 2)
                {
                    temp_a->earned += temp_a->fees;
                    sche_root->done = 2;
                }
            }
            else
            {
                trav_avail_non_trai(avai_root, &found, sche_root->program, hour_root, sche_root);
                // This for trainer non-pref trainer from slot to end slot if a trainer can teach that program.
            }
        }
        // Even if the member is not allocated a slot trying to allocate from start slot with prefered and non-pref trainer.
        if (sche_root->done == 0 && found_store == 0)
        {
            int pref_trainer = sche_root->pref_id;
            Programs *tra_avail_prog = NULL;
            available_trainer *temp_a;
            trav_avail_mem(avai_root, &found, pref_trainer, &tra_avail_prog, &temp_a);
            int can_prog = 0;
            s_programs(tra_avail_prog, &can_prog, sche_root->program);
            int upto = sche_root->slot;
            sche_root->slot = 6;
            if (can_prog == 1 && found == 1)
            { // Found set if trainer is available and Can if trainer can teach that program
                int done = 0;
                for (int i = 6; i < upto && done == 0; i++)
                {
                    trav_hour_alloc(hour_root, &done, sche_root->pref_id, sche_root); // Calling function to allocate slot for time start.
                }
                if (done == 2)
                {
                    temp_a->earned += temp_a->fees;
                    sche_root->done = 2;
                }
            }
            else
            {
                trav_avail_non_trai(avai_root, &found, sche_root->program, hour_root, sche_root);
                // This for trainer non-pref trainer from start if a trainer can teach that program.
            }
        }
        trav_sche(sche_root->right, avai_root, hour_root);
    }
}

void print_non_assign(schedule_member *root)
{
    if (root != NULL)
    {
        print_non_assign(root->left);
        if (root->done == 0)
        {
            printf("Member with ID %d.\n", root->id);
        }
        print_non_assign(root->right);
    }
}
// Test
void print_sche(schedule_member *root)
{
    if (root != NULL)
    {
        print_sche(root->left);
        printf("%d ID\n", root->id);
        print_sche(root->right);
    }
}

// Q3. Schedule_Slot() For Scheduling the Slot.
void schedule_slot(schedule_member **sche_root, available_trainer **avai_root, Hour *hour_root)
{
    // schedule_member *temp_s = sche_root;
    printf("Enter no of member for member list \n");
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int h, m;
        printf("Enter Time stamps in hr and min.\n");
        scanf("%d %d", &h, &m);
        *sche_root = add_sche(*sche_root, h * 60 + m);
    }
    // print_sche(*sche_root);
    int no_tra = 0;
    printf("Enter no of available trainers \n");
    scanf("%d", &no_tra);
    for (int i = 1; i <= no_tra; i++)
    {
        *avai_root = add_avai(*avai_root, i);
    }
    trav_sche(*sche_root, *avai_root, hour_root);
    printf("After the Scheduling as per the time : : \n\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("The Assigned Members : \n\n");
    printf("With Preferred Trainer : \n");
    printf("-----------------------------------------------------------------------------\n");
    print_assign(hour_root, 2);
    printf("With Non-Preferred Trainer : \n");
    print_assign(hour_root, 1);
    printf("-----------------------------------------------------------------------------\n");
    printf("The Non Assigned Member: \n");
    print_non_assign(*sche_root);
}

// Remuneration
typedef struct Remuneration // AVL Tree for Remunerations Earned by trainer.
{
    int id; // Trainer ID
    int height;
    int key; // Key here is negative of earned as then it will be added as highest to lowest if we take mod.
    int earned;
    struct Remuneration *left;
    struct Remuneration *right;
} Earn;

int height_e(Earn *N) // Height Finding function for Remuneration AVL Tree
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = N->height;
    return ret_val;
}
Earn *new_earn_node(int key, int id) // To create a new Remuneration node.
{
    Earn *node = (Earn *)malloc(sizeof(Earn));
    char name[20];
    node->id = id;
    node->key = key;
    node->earned = -1 * key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Earn *rightRotate_e(Earn *y) // Function to rotate right for Remuneration Tree.
{
    Earn *x = y->left;
    Earn *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height_e(y->left), height_e(y->right)) + 1;
    x->height = max(height_e(x->left), height_e(x->right)) + 1;

    return x;
}
Earn *leftRotate_e(Earn *x) // Function to rotate left for Remuneration Tree.
{
    Earn *y = x->right;
    Earn *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height_e(x->left), height_e(x->right)) + 1;
    y->height = max(height_e(y->left), height_e(y->right)) + 1;

    return y;
}
int get_e_Balance(Earn *N) // Function to count balance factor for Remuneration Tree.
{
    int ret_val;
    if (N == NULL)
        ret_val = 0;
    else
        ret_val = height_e(N->left) - height_e(N->right);
    return ret_val;
}
Earn *add_earn(Earn *node, int key, int id) // Function to add Remuneration to the Remuneration Tree in AVL Insertion.
{
    // Find the correct position to add_earn the node and addearn it
    Earn *ret_val = node;
    if (node == NULL)
        ret_val = (new_earn_node(key, id));
    else
    {
        if (key < node->key)
            node->left = add_earn(node->left, key, id);
        else if (key > node->key)
            node->right = add_earn(node->right, key, id);

        // Updating the balance factor and balancing the Tree to make AVL again.
        node->height = 1 + max(height_e(node->left), height_e(node->right));

        int balance = get_e_Balance(node);
        if (balance > 1 && key < node->left->key)
            ret_val = rightRotate_e(node);

        else if (balance < -1 && key > node->right->key)
            ret_val = leftRotate_e(node);

        else if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate_e(node->left);
            ret_val = rightRotate_e(node);
        }

        else if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate_e(node->right);
            ret_val = leftRotate_e(node);
        }
        return ret_val;
    }
}

// Q11. print_sorted_remuneration_list() to print highest to lowest in Trainer Remuneration.
void print_sorted_remuneration_list(Earn *root) // To print in Highest to Lowest
{
    if (root != NULL)
    {
        print_sorted_remuneration_list(root->left);
        printf("Trainer ID : %d Earned :%d.\n", root->id, root->earned);
        print_sorted_remuneration_list(root->right);
    }
}
// To traverse and find the correct
void trav_avail_for_earn(available_trainer *root, Earn **earn_h)
{
    if (root != NULL)
    {
        trav_avail_for_earn(root->left, earn_h);
        int pass_earned = -1 * root->earned; // So it will be added highest to lowest.
        *earn_h = add_earn(*earn_h, pass_earned, root->tra_id);
        trav_avail_for_earn(root->right, earn_h);
    }
}

// Member ID Range Search
// Q12. range_search() to seacrh in range of member id.
void range_search(Member *root, int l, int r, int *yes)
{
    if (root != NULL)
    {
        if (l < root->key)
            range_search(root->left, l, r, yes);
        if (root->key >= l && root->key <= r)
        {
            printf("ID %d \n", root->key);
            *yes = 1;
        }
        if (root->key < r)
            range_search(root->right, l, r, yes);
    }
}
int main()
{
    // Initializing all avl tree nodes sto NULL
    Member *root_m = NULL;
    Trainer *root_t = NULL;
    schedule_member *root_sche = NULL;
    available_trainer *root_avai = NULL;
    Hour *root_h = NULL;
    Earn *root_e = NULL;
    for (int i = 6; i < 22; i++) // Setting all the nodes for Hour list for  6 to 21 (24hr format).
    {
        root_h = add_hour(root_h, i);
    }
    int a = rand() % 9000 + 1000; // For random 4 digits

    printf("-----------------------------------------------------------------------------\n");
    printf("***Instruction***!!!!\n***Use Camel Case For Name or Program with more than two words.***\n");
    printf("Example for Weight Lifting use WeightLifting.\n");
    printf("***The functioning is Case Sensitive so provide Case Sensetive Input.***\n");
    printf("***The time used is 24hr Format. For a schedule slot provide starting hr of the slot.***\n");
    printf("***Enter 0 to exit the program.***\n");
    printf("-----------------------------------------------------------------------------\n");
    
    int option;
    int condition = 1;
    while (condition)
    {
        printf("Enter Option::\n1)Add Member 2)Add Trainer 3)Schedule Slot 4)Hour List 5)Delete Member 6)Delete Trainer\n7)Search Member 8)Search Trainer 9)Member List 10)Trainer List 11)Renumeration 12)Range Search(Members)\n");
        scanf("%d", &option);
        if (option == 1)
        {
            a = rand() % 9000 + 1000;
            root_m = add_member(root_m, a);
            printf("Member Added Succesfully.\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("Updated Member List:\n");
            print_member_list(root_m);
        }
        else if (option == 2)
        {
            a = rand() % 9000 + 1000;
            root_t = add_trainer(root_t, a);
            printf("Trainer Added Succesfully.\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("Updated Trainer List:\n");
            print_trainer_list(root_t);
        }
        else if (option == 3)
        {
            schedule_slot(&root_sche, &root_avai, root_h);
        }
        else if (option == 4)
        {
            print_hour_wise_list(root_h);
            printf("-----------------------------------------------------------------------------\n");
        }
        else if (option == 5)
        {
            int id;
            printf("Enter Member ID to delete: ");
            scanf("%d", &id);
            int yes = 0;
            root_m = delete_member(root_m, id, &yes);
            printf("-----------------------------------------------------------------------------\n");
            if (yes == 0)
                printf("Member ID Not Found.\n");
            else
                printf("Member Deleted Succesfully.\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("Updated Member List:\n");
            print_member_list(root_m);
        }
        else if (option == 6)
        {
            int id;
            printf("Enter Trainer ID to delete: ");
            scanf("%d", &id);
            int yes = 0;
            root_t = delete_trainer(root_t, id, &yes);
            printf("-----------------------------------------------------------------------------\n");
            if (yes == 0)
                printf("Trainer ID Not Found.\n");
            else
                printf("Trainer Deleted Succesfully.\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("Updated Trainer List:\n");
            print_trainer_list(root_t);
        }
        else if (option == 7)
        {
            printf("For Searching Member:\n");
            search_member(root_m);
        }
        else if (option == 8)
        {
            printf("For Searching Trainer:\n");
            search_trainer(root_t);
        }
        else if (option == 9)
        {
            print_member_list(root_m);
        }
        else if (option == 10)
        {
            print_trainer_list(root_t);
        }
        else if (option == 11)
        {
            root_e = NULL; // Every time the earned chnages so Fresh Tree.
            trav_avail_for_earn(root_avai, &root_e);
            printf("-----------------------------------------------------------------------------\n");
            printf("The Renumeration List (From Largest to Smallest).\n");
            printf("-----------------------------------------------------------------------------\n");
            print_sorted_remuneration_list(root_e);
            printf("-----------------------------------------------------------------------------\n");
        }
        else if (option == 12)
        {
            int l, r;
            printf("For Range Search in Member enter Limits L and R: \n");
            scanf("%d %d", &l, &r);
            int yes = 0;
            printf("-----------------------------------------------------------------------------\n");
            printf("The Member with ID in range of [%d,%d] are :\n", l, r);
            range_search(root_m, l, r, &yes);
            if (yes == 0)
                printf("None.\n");
            printf("-----------------------------------------------------------------------------\n");
        }
        else if (option == 0)
        {
            printf("-----------------------------------------------------------------------------\n");
            printf("Thank You For Using.\n");
            printf("-----------------------------------------------------------------------------\n");
            condition = 0;
        }
        else
        {
            printf("Please Select a Valid Option from above and 0 for exit.\n");
            printf("-----------------------------------------------------------------------------\n");
        }
        printf("\n");
    }
    return 0;
}