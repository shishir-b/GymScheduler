/*  Name : Shishir Nandkishor Bhalerao
    Enroll no. : BT20CSE023
    DSPD-II Assignment-1 Batch-1 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Program_List //List for Programs(Courses) and respective fees if for Member.
{
    char name[20]; // Course Name
    int fees; // Course Respective fees
    struct Program_List *next;
}Programs;

typedef struct Member_List // Member List with respective info.
{
    int member_id; // Randomly Generated 4-Digit Member ID
    char name[20]; // Member Name
    int age;      // Age
    char gender; // F for female and M for male.
    Programs *prog; //Program List for all courses for Member.
    int fees; //Total Fees (Summation of all program respective fees.)
    struct Member_List *next;
}Member;

typedef struct Trainer_List // Trainer List with respective info.
{
    int trainer_id; // Randomly Generated 4-Digit Trainer ID
    char name[20]; // Trainer Name
    char prog[20]; 
    Programs *programs; // Trainer Programs List same as Member
    int fees; // Remuneration Earned per Slot
    struct Trainer_List *next;
}Trainer;

typedef struct Per_Hour // Per Hour(Slot) Info List.
{
    int trainer_id; // Trainer ID for the slot
    int member_id;  // Member ID for the slot
    char program[20]; // Course Name
    int pref;
    struct Per_Hour *next;
}Per;

typedef struct Hour_list // Total 6:00 to 21:00 Slot Info List.
{
    int free; // No. of free slot Max 10 as (10 MAX members allowed).
    int start; // Time Slot Start Time
    Per *info; // Respective Hour Info 
    struct Hour_list *next;
}Hour;

/* Function to create program list for Member(k=1) as well as Trainer(k=0).*/ 
Programs* create_prog_list(Programs *ptr,int n,int k){ 
    ptr = (Programs*)malloc(sizeof(Programs)); //Creating List for n programs.(Input Course Name and Fees if k=1 as for Trainer Remuneration is fixed.)
    printf("Enter Courses Name:\n");
    char input[20];
    int fee=0;
    scanf("%s",input);
    if(k==1){
        printf("Enter Course Fee:\n");
        scanf("%d",&fee);
    }
    strcpy(ptr->name,input);
    ptr->fees=fee;
    ptr->next=NULL;
    n--;
    Programs *lptr = ptr;
    while (n>0) // Repeating for remaining courses.
    {
        Programs *nptr = (Programs*)malloc(sizeof(Programs));
        printf("Enter Courses Name:\n");
        scanf("%s",input);
        if(k==1){
            printf("Enter Course Fee:\n");
            scanf("%d",&fee);
        }
        strcpy(nptr->name,input);
        nptr->fees=fee;
        nptr->next=NULL;
        lptr->next=nptr;
        lptr=lptr->next;
        n--;
    }
    return ptr; // Returns Program pointer.
}

/* Q1. Add_member() takes Member Head and all info of Member except Courses Name and Returns Head of Member List.
*/
Member* add_member(Member* mem_head,char name[],int age,char gender,int n){
    Member *nptr = NULL;
    nptr = (Member*)malloc(sizeof(Member)); // Creating Node.
    strcpy(nptr->name,name);
    nptr->age = age;
    nptr->gender = gender;
    nptr->next = NULL;
    nptr->member_id = rand() % 9000 + 1000; // Generating Random 4-Digit ID.
    Programs *ptr = NULL;
    if(n!=0) ptr = create_prog_list(ptr,n,1); // Courses Info List from create_prog_list function with k=1.
    nptr->prog=ptr;
    Programs *pptr = ptr;
    nptr->fees=0;
    while (pptr!=NULL) // Calculating the total fees paid by traversing the Program List.
    {
        nptr->fees+=pptr->fees;
        pptr=pptr->next;
    }
    Member *lptr=mem_head;
    // Now inserting Member Node Sortingly by comparing Member-ID by travering member list.
    if(mem_head==NULL || mem_head->member_id>=nptr->member_id){ //If Head is NULL or Smallest Member ID.
        nptr->next=mem_head;
        mem_head = nptr;
    }else{
        while (lptr->next!=NULL && lptr->next->member_id<nptr->member_id) //Finding perfect Node as per ID.
        {
            lptr = lptr->next;
        }
        nptr->next=lptr->next;
        lptr->next=nptr;
    }
    printf("Member Added Succesfully.\n");
    printf("----------------------------------------------------------------------------------------\n");
    return mem_head; // Returning Member Head.
}

/* Q2. Add_trainer() takes Trainer Head and all info of trainer except Courses Name and Returns Head of Trainer List.
*/
Trainer* add_trainer(Trainer* tra_head,char name[],char prog[],int fees,int n){
    Trainer *nptr;
    nptr = (Trainer*)malloc(sizeof(Trainer)); // Creating Node.
    strcpy(nptr->name,name);
    nptr->next = NULL;
    strcpy(nptr->prog,prog);
    nptr->fees = fees;
    nptr->trainer_id = rand() % 9000 + 1000; // Generating Random 4-Digit ID.
    Programs *ptr = NULL;
    if(n!=0) ptr = create_prog_list(ptr,n,0); // Courses Info List from create_prog_list function with k=0.
    nptr->programs=ptr;
    Trainer *lptr=tra_head;
    // Now inserting Trainer Node Sortingly by comparing Trainer-ID by travering trainer list same as Add_member().
    if(tra_head==NULL || tra_head->trainer_id>=nptr->trainer_id){
        nptr->next=tra_head;
        tra_head = nptr;
    }else{
        while (lptr->next!=NULL && lptr->next->trainer_id<nptr->trainer_id)
        {
            lptr = lptr->next;
        }
        nptr->next=lptr->next;
        lptr->next=nptr;
    }
    printf("Trainer Added Succesfully.\n");
    printf("----------------------------------------------------------------------------------------\n");
    return tra_head; // Returns Trainer Head.
}

/* Q5. Delete_member() takes Member Head and ID and returns Member Head.
*/
Member* delete_member(Member* mem_head,int id){
    Member* lptr=mem_head;
    Member* prev=mem_head;
    int present=1;
    // Traversing the list with prev and list ptr and Deleting the member.
    if(lptr==NULL) present=0;
    else if(lptr!=NULL && lptr->member_id == id){
        mem_head = lptr->next;
        free(lptr); //Freeing the deleted.
    }
    else
    {
        while (lptr!=NULL && lptr->member_id != id)
        {
            prev = lptr;
            lptr = lptr->next;
        }
        if(lptr==NULL){
            present=0;
        }
        else{
            prev->next=lptr->next;
            free(lptr); //Freeing the deleted.
        }
    }
    if(present==0) printf("Member ID Not Found.\n");
    else printf("Member Deleted Succesfully.\n");
    printf("----------------------------------------------------------------------------------------\n");
    return mem_head; //Returns Member Head.
}

/* Q6. Delete_trainer() takes Trainer Head and ID and returns Trainer Head.
*/
Trainer* delete_trainer(Trainer* tra_head,int id){
    Trainer* lptr=tra_head;
    Trainer* prev=tra_head;
    // Traversing the list with prev and list ptr and Deleting the trainer.
    int present=1;
    if(lptr==NULL) present=0;
    else if(lptr!=NULL && lptr->trainer_id == id){
        tra_head = lptr->next;
        free(lptr); //Freeing the deleted.
    }
    else
    {
        while (lptr!=NULL && lptr->trainer_id != id)
        {
            prev = lptr;
            lptr = lptr->next;
        }
        if(lptr==NULL){
            present=0;
        }
        else{
            prev->next=lptr->next;
            free(lptr); //Freeing the deleted.
        }
    }
    if(present==0) printf("Trainer ID Not Found.\n");
    else printf("Trainer Deleted Succesfully.\n");
    printf("----------------------------------------------------------------------------------------\n");
    return tra_head; //Returns Trainer Head.
}

/* Q9. Print_member_list() takes Member Head.
*/
void print_member_list(Member* mem_head){
    Member *lptr=mem_head;
    // Traversing the Member List and Outputs.
    if(lptr==NULL){
        printf("The Member List is Empty.");
    }else{
        printf("The Member List:\n");
        printf("----------------------------------------------------------------------------------------\n");
        printf("ID\t\tName\t\tAge\t\tGender\t\tTotal Fees(Rs)\n");
        printf("----------------------------------------------------------------------------------------\n");
        while (lptr!=NULL)
        {
            printf("%d\t\t%s\t\t%d\t\t%c\t\t%d\n",lptr->member_id,lptr->name,lptr->age,lptr->gender,lptr->fees);
            Programs *temp = lptr->prog;
            printf("Courses\t\tFees(Rs)\n");
            while(temp!=NULL){
                printf("%s\t\t%d\n",temp->name,temp->fees);
                temp=temp->next;
            }
            printf("----------------------------------------------------------------------------------------\n");
            lptr=lptr->next;
        }
    }
    printf("\n");
}

/* Q10. Print_trainer_list() takes Trainer Head.
*/
void print_trainer_list(Trainer* tra_head){
    Trainer *lptr=tra_head;
    // Traversing the trainer List and Outputs.
    if(lptr==NULL){
        printf("The Trainer List is Empty.");
    }else{
        printf("The Trainer List:\n");
        printf("----------------------------------------------------------------------------------------\n");
        printf("ID\t\tName\t\tFees(Rs)\n");
        printf("----------------------------------------------------------------------------------------\n");
        while (lptr!=NULL)
        {
            printf("%d\t\t%s\t\t%d\n",lptr->trainer_id,lptr->name,lptr->fees);
            Programs *temp = lptr->programs;
            printf("Courses that can be Trained: \n");
            while(temp!=NULL){
                printf("%s\n",temp->name);
                temp=temp->next;
            }
            lptr=lptr->next;
            printf("----------------------------------------------------------------------------------------\n");
        }
    }
    printf("\n");
}

/* Q7. Search_member() takes Memory Head.
*/
void search_member(Member* mem_head){
    int option;
    /* Takes the input for Key Value and then Key.
       Then traverse the Member list and matches key and Outputs. */
    printf("Press 1)ID 2)Name 3)Age 4)Gender 5)Program\n");
    scanf("%d",&option);
    int found=0;
    Member* lptr=mem_head;
    if(option==1){
        int id;
        printf("Enter ID: \n");
        scanf("%d",&id);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        while(lptr!=NULL && found==0)
        {
            if(lptr->member_id==id){
                if(found==0) printf("ID\t\tName\t\tAge\t\tGender\t\tTotal Fees(Rs)\n");
                found=1;
                printf("%d\t\t%s\t\t%d\t\t%c\t\t%d\n",lptr->member_id,lptr->name,lptr->age,lptr->gender,lptr->fees);
                Programs *temp = lptr->prog;
                printf("Courses\t\tFees(Rs)\n");
                while(temp!=NULL){
                    printf("%s\t\t%d\n",temp->name,temp->fees);
                    temp=temp->next;
                }
                printf("----------------------------------------------------------------------------------------\n");
            }
            lptr=lptr->next;
        }
    }
    else if(option==2){
        char name[20];
        printf("Enter Name: \n");
        scanf("%s",name);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        while(lptr!=NULL)
        {
            if(strcmp(lptr->name,name)==0){
                if(found==0) printf("ID\t\tName\t\tAge\t\tGender\t\tTotal Fees(Rs)\n");
                found=1;
                printf("%d\t\t%s\t\t%d\t\t%c\t\t%d\n",lptr->member_id,lptr->name,lptr->age,lptr->gender,lptr->fees);
                Programs *temp = lptr->prog;
                printf("Courses\t\tFees(Rs)\n");
                while(temp!=NULL){
                    printf("%s\t\t%d\n",temp->name,temp->fees);
                    temp=temp->next;
                }
                printf("----------------------------------------------------------------------------------------\n");
            }
            lptr=lptr->next;
        }
    }
    else if(option ==3){
        int age;
        printf("Enter Age: \n");
        scanf("%d",&age);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        while(lptr!=NULL)
        {
            if(lptr->age==age){
                if(found==0) printf("ID\t\tName\t\tAge\t\tGender\t\tTotal Fees(Rs)\n");
                found=1;
                printf("%d\t\t%s\t\t%d\t\t%c\t\t%d\n",lptr->member_id,lptr->name,lptr->age,lptr->gender,lptr->fees);
                Programs *temp = lptr->prog;
                printf("Courses\t\tFees(Rs)\n");
                while(temp!=NULL){
                    printf("%s\t\t%d\n",temp->name,temp->fees);
                    temp=temp->next;
                }
                printf("----------------------------------------------------------------------------------------\n");
            }
            lptr=lptr->next;
        }
    }
    else if(option == 4){
        char gender;
        printf("Enter Gender: \n");
        fflush(stdin);
        scanf("%c",&gender);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        while(lptr!=NULL)
        {
            if(lptr->gender==gender){
                if(found==0) printf("ID\t\tName\t\tAge\t\tGender\t\tTotal Fees(Rs)\n");
                found=1;
                printf("%d\t\t%s\t\t%d\t\t%c\t\t%d\n",lptr->member_id,lptr->name,lptr->age,lptr->gender,lptr->fees);
                Programs *temp = lptr->prog;
                printf("Courses\t\tFees(Rs)\n");
                while(temp!=NULL){
                    printf("%s\t\t%d\n",temp->name,temp->fees);
                    temp=temp->next;
                }
                printf("----------------------------------------------------------------------------------------\n");
            }
            lptr=lptr->next;
        }
    }
    else{
        char prog[20];
        printf("Enter Program: \n");
        scanf("%s",prog);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        while(lptr!=NULL)
        {
            Programs *temp = lptr->prog;
            while(temp!=NULL){
                if(strcmp(prog,temp->name)==0){
                    if(found==0) printf("ID\t\tName\t\tAge\t\tGender\t\tTotal Fees(Rs)\n");
                    found=1;
                    printf("%d\t\t%s\t\t%d\t\t%c\t\t%d\n",lptr->member_id,lptr->name,lptr->age,lptr->gender,lptr->fees);
                    Programs *temp2 = lptr->prog;
                    printf("Courses\t\tFees(Rs)\n");
                    while(temp2!=NULL){
                        printf("%s\t\t%d\n",temp2->name,temp2->fees);
                        temp2=temp2->next;
                    }
                    printf("----------------------------------------------------------------------------------------\n");
                }
                temp=temp->next;
            }
            lptr=lptr->next;
        }
    }
    if(found==0){
        printf("None\n");
    }
    printf("----------------------------------------------------------------------------------------\n");
}

/* Q8. Search_trainer() takes trainer Head.
*/
void search_trainer(Trainer* tra_head){
    int option;
    /* Takes the input for Key Value and then Key.
       Then traverse the Trainer list and matches key and Outputs. */
    printf("Press 1)ID 2)Name 3)Program\n");
    scanf("%d",&option);
    int found=0;
    Trainer* lptr=tra_head;
    if(option==1){
        int id;
        printf("Enter ID: \n");
        scanf("%d",&id);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        while(lptr!=NULL && found==0)
        {
            if(lptr->trainer_id==id){
                if(found==0) printf("ID\t\tName\t\tRenumeration(Rs)\n");
                found=1;
                printf("%d\t\t%s\t\t%d\n",lptr->trainer_id,lptr->name,lptr->fees);
                Programs *temp2=lptr->programs;
                printf("Courses:\n");
                while (temp2!=NULL)
                {
                    printf("%s\n",temp2->name);
                    temp2=temp2->next;
                } 
                printf("----------------------------------------------------------------------------------------\n");
            }
            lptr=lptr->next;
        }
    }
    else if(option==2){
        char name[20];
        printf("Enter Name: \n");
        scanf("%s",name);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        while(lptr!=NULL)
        {
            if(strcmp(name,lptr->name)==0){
                if(found==0) printf("ID\t\tName\t\tRenumeration(Rs)\n");
                found=1;
                printf("%d\t\t%s\t\t%d\n",lptr->trainer_id,lptr->name,lptr->fees);
                Programs *temp2=lptr->programs;
                printf("Courses:\n");
                while (temp2!=NULL)
                {
                    printf("%s\n",temp2->name);
                    temp2=temp2->next;
                } 
                printf("----------------------------------------------------------------------------------------\n");
            }
            lptr=lptr->next;
        }
    }
    else if(option ==3){
        char prog[20];
        printf("Enter program: \n");
        scanf("%s",prog);
        printf("----------------------------------------------------------------------------------------\n");
        printf("Records matched on key:\n");
        while(lptr!=NULL)
        {
            Programs *temp = lptr->programs;
            while(temp!=NULL){
                if(strcmp(prog,temp->name)==0){
                    if(found==0) printf("ID\t\tName\t\tRenumeration(Rs)\n");
                    found=1;
                    printf("%d\t\t%s\t\t%d\n",lptr->trainer_id,lptr->name,lptr->fees);
                    Programs *temp2=lptr->programs;
                    printf("Courses:\n");
                    while (temp2!=NULL)
                    {
                        printf("%s\n",temp2->name);
                        temp2=temp2->next;
                    } 
                    printf("----------------------------------------------------------------------------------------\n");
                }
                temp=temp->next;
            }
            lptr=lptr->next;
        }
    }
    if(found==0){
        printf("None\n");
    }
    printf("----------------------------------------------------------------------------------------\n");
}

typedef struct schedule_member_tag //Schedule Member List
{
    int id; // Member ID
    char program[20]; // Program to be Scheduled
    int slot; // Preferred Slot
    int time_hr; // TimeStamps Hour
    int time_min; // TimeStamps Minutes
    int pref_id; // Preferred Trainer ID 
    int done; // 0 for NOT, 1 for DONE ,2 for DONE with prefferd trainer.
    struct schedule_member_tag *next;
}schedule_member;

typedef struct available_tra_tag // Available Member List
{
    int tra_id; // Trainer ID
    Programs *prog; // All Courses trainer can take when available.
    int start; //Available from start hour.
    int end; // Available to end hour.
    struct available_tra_tag *next;
}available_trainer;

schedule_member *initialize_schedule(schedule_member *sche_head){ // To intialize Schedule Member List as in Q.3 Input we get member info list.
    schedule_member *nptr;
    nptr=(schedule_member*)malloc(sizeof(schedule_member)); //Creating Node and Taking relevent Infos.
    printf("For Member in Schedule :\n");
    int id;
    printf("Enter Member ID: ");
    scanf("%d",&id);
    nptr->id=id;
    char prog[20];
    printf("Enter Program Name: ");
    scanf("%s",prog);
    strcpy(nptr->program,prog);
    int slot;
    printf("Enter Time Slot: ");
    scanf("%d",&slot);
    nptr->slot=slot;
    int hr,min;
    printf("Enter Timestamps Hr and Min: ");
    scanf("%d %d",&hr,&min);
    nptr->time_hr=hr;
    nptr->time_min=min;
    int pref_id;
    printf("Enter Preferd Trainer ID: ");
    scanf("%d",&pref_id);
    nptr->pref_id=pref_id;
    nptr->done=0;
    schedule_member *lptr=sche_head;
    /* Traversing the Schedule Member List and inserting the Node with respect to the Time Stamps
     such that the scheduling will be First Come First Serve.*/
    if(sche_head==NULL || sche_head->time_hr*60 + sche_head->time_min>=nptr->time_hr*60 + nptr->time_min){
        nptr->next=sche_head;
        sche_head = nptr;
    }else{
        while (lptr->next!=NULL && lptr->time_hr*60 + lptr->time_min<nptr->time_hr*60 + nptr->time_min)
        {
            lptr = lptr->next;
        }
        nptr->next=lptr->next;
        lptr->next=nptr;
    }
    printf("The member with ID %d added to schedule list.\n",id);
    printf("----------------------------------------------------------------------------------------\n");
    return sche_head; // Returing Schedule Member Head.
}

available_trainer *intialize_available(available_trainer *avail_head){ // To intialize Available trainer List as in Q3. Input we get trainer info.
    int id;
    printf("Enter Trainer ID: ");
    scanf("%d",&id);
    int n;
    printf("No of programs can train when available: ");
    scanf("%d",&n);
    Programs *ptr = NULL;
    if(n!=0) ptr = create_prog_list(ptr,n,0);
    int start,end;
    printf("Trainer available from start hour: \n");
    scanf("%d",&start);
    printf("Trainer available till end hour: \n");
    scanf("%d",&end);
    available_trainer* nptr=(available_trainer*)malloc(sizeof(available_trainer));
    nptr->tra_id=id; // Creating Node and taking relevant info.
    nptr->prog=ptr;
    nptr->start=start;
    nptr->end=end;
    Programs *llll=nptr->prog;
    nptr->next=avail_head;
    avail_head=nptr;
    nptr=avail_head;
    printf("The Trainer with ID %d added to available list.\n",id);
    printf("----------------------------------------------------------------------------------------\n");
    return avail_head; //Returns available head.
}

/* Q3. Schedule_slot() takes Hour Head,Schedule Member Head and Available Trainer Head .
    and returns Hour Head*/
Hour *schedule_slot(Hour* hour_head,schedule_member *sche_head,available_trainer *avail_head){
    schedule_member *temp_s=sche_head;
    // Traversing the Schedule Member List as we dealt with First-Come-First-Serve.
    while (temp_s!=NULL)
    {
        Hour *h_lptr=hour_head;
        int already=0;
        // Traversing the Hour List if the Member ID match we will disallow the request.
        while (h_lptr!=NULL && already==0)
        {
            Per *p_lptr=h_lptr->info;
            while (p_lptr!=NULL && already==0)
            {
                if(p_lptr->member_id==temp_s->id){
                    already=1;
                }
                p_lptr=p_lptr->next;
            }
            h_lptr=h_lptr->next;
        }
        if(already==1){ // Already present.
            printf("This Member ID %d already had a slot.\n",temp_s->id);
            printf("----------------------------------------------------------------------------------------\n");
        }
        else{
            int search=temp_s->slot;
            Hour* temp_h=hour_head;
            // Traversing to the Preferred Time Slot from Hour List.
            while (temp_h->start!=search && temp_h!=NULL)
            {
                temp_h=temp_h->next;
            }
            int tra_found=0;
            available_trainer* temp_a=avail_head;
            // Traversing the Available Trainer List if the preferred trainer is available.
            while (temp_a!=NULL && tra_found==0)
            {
                if(temp_a->tra_id==temp_s->pref_id){
                    tra_found=1;
                }
                else temp_a=temp_a->next;
            }

            if(tra_found==0){ //If preferred trainer not found.
                while (temp_h!=NULL && temp_s->done==0) //Finding free trainer and slot with preffered time and after it
                {
                    if(temp_h->free>0){ // If atleast one free is there out of 10 for max 10 member.
                        temp_a=avail_head;
                        while (temp_a!=NULL && temp_s->done==0)
                        {
                            int flag=1;
                            Per *temp_p=temp_h->info;
                            while (temp_p!=NULL && flag) //Checking if the free trainer is not on the slot.
                            {
                                if(temp_a->tra_id==temp_p->trainer_id){
                                    flag=0;
                                }
                                temp_p=temp_p->next;
                            }
                            int can=0;
                            Programs * temp_program=temp_a->prog;
                            while (temp_program!=NULL && can==0 && flag==1) // Checking if that trainer can teach the Course.
                            {
                                if(strcmp(temp_program->name,temp_s->program)==0){
                                    can=1;
                                }
                                temp_program=temp_program->next;
                            }
                            int avail=0;
                            if(temp_h->start < temp_a->end && temp_h->start >= temp_a->start){ //Checking if trainer available in that specific hour. 
                                avail=1;
                            }
                            if(flag==1 && can==1 && avail==1){ // If Available and Can teach course then Allocate and add in Hour list.
                                Per *add=(Per*)malloc(sizeof(Per));
                                add->trainer_id=temp_a->tra_id;
                                add->member_id=temp_s->id;
                                add->pref=0;
                                strcpy(add->program,temp_s->program);
                                add->next=temp_h->info; // Adding info list of per hour.
                                temp_h->info=add;
                                temp_s->done=1; // 1 for not prefferd trainer.
                                temp_h->free--; // Subtracting 1 from no. of free slot int that hour as one member is added.
                            }
                            temp_a=temp_a->next;
                        }
                    }
                    temp_h=temp_h->next;
                }
                // If Not free slot after the prefferd slot and after trying before it
                temp_h=hour_head;
                while (temp_h!=NULL && temp_s->done==0) 
                {
                    if(temp_h->free>0){ // If atleast one free is there out of 10 for max 10 member.
                        temp_a=avail_head;
                        // Doing the same as done if the above while iteration.
                        while (temp_a!=NULL && temp_s->done==0)
                        {
                            int flag=1;
                            Per *temp_p=temp_h->info;
                            while (temp_p!=NULL && flag)
                            {
                                if(temp_a->tra_id==temp_p->trainer_id){
                                    flag=0;
                                }
                                temp_p=temp_p->next;
                            }
                            int can=0;
                            Programs *temp_program=temp_a->prog;
                            while (temp_program!=NULL && can==0 && flag==1)
                            {
                                if(strcmp(temp_program->name,temp_s->program)==0){
                                    can=1;
                                }
                                temp_program=temp_program->next;
                            }
                            int avail=0;
                            if(temp_h->start < temp_a->end && temp_h->start >= temp_a->start){ //Checking if trainer available in that specific hour. 
                                avail=1;
                            }
                            if(flag==1 && can==1 && avail==1){
                                Per *add=(Per*)malloc(sizeof(Per));
                                add->trainer_id=temp_a->tra_id;
                                add->member_id=temp_s->id;
                                add->pref=0;
                                strcpy(add->program,temp_s->program);
                                add->next=temp_h->info;
                                temp_h->info=add;
                                temp_s->done=1; //1 for not prefferd tainer.
                                temp_h->free--; // Subtracting 1 from no. of free slot int that hour as one member is added.
                            }
                            temp_a=temp_a->next;
                        }
                    }
                    temp_h=temp_h->next;
                }
                
            }
            else{
                while (temp_h!=NULL && temp_s->done==0) //Finding prefferd trainer and slot with preffered time and after it
                {
                    if(temp_h->free>0){ // If atleast one free is there out of 10 for max 10 member.
                        int flag=1;
                        Per *temp_p=temp_h->info;
                        while (temp_p!=NULL && flag) //Checking if the preffered trainer is not on the slot.
                        {
                            if(temp_s->pref_id==temp_p->trainer_id){
                                flag=0;
                            }
                            temp_p=temp_p->next;
                        }
                        int can=0;
                        Programs * temp_program=temp_a->prog;
                        while (temp_program!=NULL && can==0 && flag==1) // Checking if that trainer can teach the Course.
                        {
                            if(strcmp(temp_program->name,temp_s->program)==0){
                                can=1;
                            }
                            temp_program=temp_program->next;
                        }
                        int avail=0;
                        if(temp_h->start < temp_a->end && temp_h->start >= temp_a->start){ //Checking if trainer available in that specific hour. 
                            avail=1;
                        }
                        if(flag==1 && can==1 && avail==1){ // If Available and Can teach course then Allocate and add in Hour list.
                            Per *add=(Per*)malloc(sizeof(Per));
                            add->trainer_id=temp_s->pref_id;
                            add->member_id=temp_s->id;
                            add->pref=1;
                            strcpy(add->program,temp_s->program);
                            add->next=temp_h->info;
                            temp_h->info=add;
                            temp_s->done=2; //Done 2 for prefferd trainer .
                            temp_h->free--; // Subtracting 1 from no. of free slot int that hour as one member is added.
                        }
                    }
                    temp_h=temp_h->next;
                }
                // If Not free slot after the prefferd slot and after trying before it
                temp_h=hour_head;
                while (temp_h!=NULL && temp_s->done==0) 
                {
                    if(temp_h->free>0){ // If atleast one free is there out of 10 for max 10 member.
                        int flag=1;
                        Per *temp_p=temp_h->info;
                        while (temp_p!=NULL && flag) //Checking if the preffered trainer is not on the slot.
                        {
                            if(temp_s->pref_id==temp_p->trainer_id){
                                flag=0;
                            }
                            temp_p=temp_p->next;
                        }
                        int can=0;
                        Programs * temp_program=temp_a->prog;
                        while (temp_program!=NULL && can==0 && flag==1) // Checking if that trainer can teach the Course.
                        {
                            if(strcmp(temp_program->name,temp_s->program)==0){
                                can=1;
                            }
                            temp_program=temp_program->next;
                        }
                        int avail=0;
                        if(temp_h->start < temp_a->end && temp_h->start >= temp_a->start){ //Checking if trainer available in that specific hour. 
                            avail=1;
                        }
                        if(flag==1 && can==1 && avail==1){ // If Available and Can teach course then Allocate and add in Hour list.
                            Per *add=(Per*)malloc(sizeof(Per));
                            add->trainer_id=temp_s->pref_id;
                            add->member_id=temp_s->id;
                            add->pref=1;
                            strcpy(add->program,temp_s->program);
                            add->next=temp_h->info;
                            temp_h->info=add;
                            temp_s->done=2; //Done 2 for prefferd trainer .
                            temp_h->free--; // Subtracting 1 from no. of free slot int that hour as one member is added.
                        }
                    }
                    temp_h=temp_h->next;
                }
            }
        }
        temp_s=temp_s->next;
    }
    // Traversing the Hour List and Outputs The Info of Assigned Members.
    Hour *h_lptr=hour_head;
    int any=1;
    printf("----------------------------------------------------------------------------------------\n");
    printf("Assigned Members with Time Slot and ID and trainer allocated ID.:\n");
    printf("Time Slot\t\tMember ID\t\tTrainer ID\n");
    printf("----------------------------------------------------------------------------------------\n");
    while (h_lptr!=NULL)
    {
        Per* p_lptr=h_lptr->info;
        while (p_lptr!=NULL)
        {
            printf("%d:00 to %d:00\t\t%d is assigned to \t%d.\n",h_lptr->start,h_lptr->start+1,p_lptr->member_id,p_lptr->trainer_id);
            any=0;
            p_lptr=p_lptr->next;
        }
        h_lptr=h_lptr->next;
    }
    if(any==1) printf("None.\n");
    printf("----------------------------------------------------------------------------------------\n");
    // Traversing the Schedule List and Outputs The Info of Not-Assigned Members.
    temp_s=sche_head;
    any=1;
    printf("Not Assigned Members with ID:\n");
    printf("----------------------------------------------------------------------------------------\n");
    while (temp_s!=NULL)
    {
        if(temp_s->done==0){
            printf("The Member with %d is not Assigned.\n",temp_s->id);
            any=0;
        }
        temp_s=temp_s->next;
    }
    if(any==1) printf("None.\n");
    printf("----------------------------------------------------------------------------------------\n");
    return hour_head;
}

/* Q4. Print_hour_wise_list() takes Hour Head as Input and Outputs Info.
*/
void print_hour_wise_list(Hour* hour_head){
    Hour* lptr=hour_head;
    // Outputing for all Slots and grouped by programs.
    printf("----------------------------------------------------------------------------------------\n");
    printf("Hour Wise List:\n");
    while (lptr!=NULL)
    {
        printf("For %d:00 to %d:00 Slot:\n",lptr->start,lptr->start+1);
        if(lptr->free==5){
            printf("None.\n");
        }
        else{
            printf("For Yoga:\n");
            int found=0;
            char Yoga[]="Yoga";
            Per *temp=lptr->info;
            while (temp!=NULL)
            {
                if(strcmp(temp->program,Yoga)==0){
                    found=1;
                    printf("The Member Id %d with Trainer Id %d for Yoga.\n",temp->member_id,temp->trainer_id);
                }
                temp=temp->next;
            }
            if(found==0) printf("None.\n");
            found=0;
            printf("For Cardio:\n");
            char Cardio[]="Cardio";
            temp=lptr->info;
            while (temp!=NULL)
            {
                if(strcmp(temp->program,Cardio)==0){
                    found=1;
                    printf("The Member Id %d with the Trainer Id %d for Cardio.\n",temp->member_id,temp->trainer_id);
                }
                temp=temp->next;
            }
            if(found==0) printf("None.\n");
            found=0;
            printf("For Zumba:\n");
            char Zumba[]="Zumba";
            temp=lptr->info;
            while (temp!=NULL)
            {
                if(strcmp(temp->program,Zumba)==0){
                    found=1;
                    printf("The Member Id %d with the Trainer Id %d for Zumba.\n",temp->member_id,temp->trainer_id);
                }
                temp=temp->next;
            }
            if(found==0) printf("None.\n");
            found=0;
            printf("For Weight Lifting:\n");
            char Weight[]="WeightLifting";
            temp=lptr->info;
            while (temp!=NULL)
            {
                if(strcmp(temp->program,Weight)==0){
                    found=1;
                    printf("The Member Id %d with the Trainer Id %d for Weight Lifting.\n",temp->member_id,temp->trainer_id);
                }
                temp=temp->next;
            }
            if(found==0) printf("None.\n");
        }
        lptr=lptr->next;
    }
    printf("----------------------------------------------------------------------------------------\n");
}

typedef struct Remuneration //List for Remuneration Earned by trainer.
{
    int id; //Trainer ID
    int earned; //Total Earned in a day.
    struct Remuneration *next;
}Earn;

/* Q11. Print_sorted_remuneration_list() takes Hour Head and Trainer Head
*/
void print_sorted_remuneration_list(Hour* hour_head,Trainer *tra_head){
    Hour* h_lptr=hour_head;
    Trainer *t_ptr=tra_head;
    Earn *earn_head=NULL;
    // Traversing the Trainer List and Hour List to find total earned.
    while (t_ptr!=NULL)
    {
        h_lptr=hour_head;
        int earned=0;
        while (h_lptr!=NULL)
        {
            Per *p_lptr=h_lptr->info;
            while (p_lptr!=NULL)
            {
                if(p_lptr->trainer_id==t_ptr->trainer_id){ //If same ID trainer is there adding the earned.
                    earned+=t_ptr->fees;
                }
                p_lptr=p_lptr->next;
            }
            h_lptr=h_lptr->next;
        }
        Earn *lptr=earn_head;
        Earn *nptr=(Earn*)malloc(sizeof(Earn)); //Create Node and adding relevant info.
        nptr->id=t_ptr->trainer_id;
        nptr->earned=earned;
        // Inserting the earned Node sortingly in decrease for Highest to Lowest.
        if(earn_head==NULL || earn_head->earned<=nptr->earned){
            nptr->next=earn_head;
            earn_head = nptr;
        }else{
            while (lptr->next!=NULL && lptr->next->earned>nptr->earned)
            {
                lptr = lptr->next;
            }
            nptr->next=lptr->next;
            lptr->next=nptr;
        }
        t_ptr=t_ptr->next;
    }
    // Printing the Output.
    Earn *e_lptr=earn_head;
    int any=1;
    printf("----------------------------------------------------------------------------------------\n");
    printf("Remuneration List(Highest to Lowest):\n");
    printf("Trainer ID\t\tEarned(Rs)\n");
    printf("----------------------------------------------------------------------------------------\n");
    while (e_lptr!=NULL)
    {
        printf("The Trainer with ID %d has Remuneration of %d.\n",e_lptr->id,e_lptr->earned);
        any=0;
        printf("----------------------------------------------------------------------------------------\n");
        e_lptr=e_lptr->next;
    }
    if(any==1) printf("None.\n");
    printf("----------------------------------------------------------------------------------------\n");
}

/* Q12. print_intersection_list() takes schedule member head and outputs.
*/
void print_intersection_list(schedule_member *sche_head){
    schedule_member *lptr=sche_head;
    /*Traversing the Schedule List and if the done==2 as implemented
    and then output the respective Member and Trainer ID.*/
    printf("----------------------------------------------------------------------------------------\n");
    printf("The Intersection List:");
    printf("The Member(ID) with preferred the trianer(ID).\n");
    int any=1;
    printf("----------------------------------------------------------------------------------------\n");
    while (lptr!=NULL)
    {
        if(lptr->done==2){
            printf("Member %d with Trainer %d.\n",lptr->id,lptr->pref_id);
            any=0;
            printf("----------------------------------------------------------------------------------------\n");
        }
        lptr=lptr->next;
    }
    if(any==1) printf("None.\n");
    printf("----------------------------------------------------------------------------------------\n");
}

/* Function to save the DATA in .txt files for each trainer list,member list and hour list.*/
void save_data(Member *mem_head,Trainer *tra_head,Hour *hour_head){
    // First for Member List
    FILE *mptr;
    mptr = fopen("Member_List.txt","w");
    Member *lptr=mem_head;
    // Traversing the Member List and Outputs in file.
    if(lptr==NULL){
        fprintf(mptr,"The Member List is Empty.\n");
    }else{
        fprintf(mptr,"The Member List:\n");
        fprintf(mptr,"----------------------------------------------------------------------------------------\n");
        fprintf(mptr,"ID\t\tName\t\tAge\t\tGender\t\tTotal Fees(Rs)\n");
        fprintf(mptr,"----------------------------------------------------------------------------------------\n");
        while (lptr!=NULL)
        {
            fprintf(mptr,"%d\t\t%s\t\t%d\t\t%c\t\t%d\n",lptr->member_id,lptr->name,lptr->age,lptr->gender,lptr->fees);
            Programs *temp = lptr->prog;
            fprintf(mptr,"Courses\t\tFees(Rs)\n");
            while(temp!=NULL){
                fprintf(mptr,"%s\t\t%d\n",temp->name,temp->fees);
                temp=temp->next;
            }
            fprintf(mptr,"----------------------------------------------------------------------------------------\n");
            lptr=lptr->next;
        }
    }
    fprintf(mptr,"\n");
    fclose(mptr);

    // Now for Trainer List.
    FILE *tptr;
    tptr = fopen("Trainer_List.txt","w");
    Trainer *t_lptr=tra_head;
    // Traversing the trainer List and Outputs in File.
    if(t_lptr==NULL){
        fprintf(tptr,"The Trainer List is Empty.");
    }else{
        fprintf(tptr,"The Trainer List:\n");
        fprintf(tptr,"----------------------------------------------------------------------------------------\n");
        fprintf(tptr,"ID\t\tName\t\tFees(Rs)\n");
        fprintf(tptr,"----------------------------------------------------------------------------------------\n");
        while (t_lptr!=NULL)
        {
            fprintf(tptr,"%d\t\t%s\t\t%d\n",t_lptr->trainer_id,t_lptr->name,t_lptr->fees);
            Programs *temp = t_lptr->programs;
            fprintf(tptr,"Courses that can be Trained: \n");
            while(temp!=NULL){
                fprintf(tptr,"%s\n",temp->name);
                temp=temp->next;
            }
            t_lptr=t_lptr->next;
            fprintf(tptr,"----------------------------------------------------------------------------------------\n");
        }
    }
    fprintf(tptr,"\n");
    fclose(tptr);

    //Last one Schedule list Hour Wise.
    FILE *hptr;
    hptr = fopen("Schedule_List.txt","w");
    Hour* h_lptr=hour_head;
    // Saving for all Slots and grouped by programs.
    fprintf(hptr,"----------------------------------------------------------------------------------------\n");
    fprintf(hptr,"Hour Wise List:\n");
    while (h_lptr!=NULL)
    {
        fprintf(hptr,"For %d:00 to %d:00 Slot:\n",h_lptr->start,h_lptr->start+1);
        if(h_lptr->free==5){
            fprintf(hptr,"None.\n");
        }
        else{
            fprintf(hptr,"For Yoga:\n");
            int found=0;
            char Yoga[]="Yoga";
            Per *temp=h_lptr->info;
            while (temp!=NULL)
            {
                if(strcmp(temp->program,Yoga)==0){
                    found=1;
                    fprintf(hptr,"The Member Id %d with Trainer Id %d for Yoga.\n",temp->member_id,temp->trainer_id);
                }
                temp=temp->next;
            }
            if(found==0) fprintf(hptr,"None.\n");
            found=0;
            fprintf(hptr,"For Cardio:\n");
            char Cardio[]="Cardio";
            temp=h_lptr->info;
            while (temp!=NULL)
            {
                if(strcmp(temp->program,Cardio)==0){
                    found=1;
                    fprintf(hptr,"The Member Id %d with the Trainer Id %d for Cardio.\n",temp->member_id,temp->trainer_id);
                }
                temp=temp->next;
            }
            if(found==0) fprintf(hptr,"None.\n");
            found=0;
            fprintf(hptr,"For Zumba:\n");
            char Zumba[]="Zumba";
            temp=h_lptr->info;
            while (temp!=NULL)
            {
                if(strcmp(temp->program,Zumba)==0){
                    found=1;
                    fprintf(hptr,"The Member Id %d with the Trainer Id %d for Zumba.\n",temp->member_id,temp->trainer_id);
                }
                temp=temp->next;
            }
            if(found==0) fprintf(hptr,"None.\n");
            found=0;
            fprintf(hptr,"For Weight Lifting:\n");
            char Weight[]="WeightLifting";
            temp=h_lptr->info;
            while (temp!=NULL)
            {
                if(strcmp(temp->program,Weight)==0){
                    found=1;
                    fprintf(hptr,"The Member Id %d with the Trainer Id %d for Weight Lifting.\n",temp->member_id,temp->trainer_id);
                }
                temp=temp->next;
            }
            if(found==0) fprintf(hptr,"None.\n");
        }
        h_lptr=h_lptr->next;
    }
    fprintf(hptr,"----------------------------------------------------------------------------------------\n");
    fclose(hptr);
}


int main(){
    Member *mem_head=NULL; // Initialize Member List Head.
    Trainer *tra_head=NULL; // Initialize Trainer List Head.
    schedule_member *sche_head=NULL; // Initialize Schedule Member List Head.
    available_trainer *avail_head=NULL; // Initialize Available Trainer List Head.
    Hour *hour_head=(Hour*)(malloc(sizeof(Hour))); // Initialize Hour List and Creating all Nodes from 6 to 8 slots.
    hour_head->free=10; // All 10 slots free for max 10 members at a time.
    hour_head->start=6;
    Hour *lptr=hour_head;
    for(int i=7;i<21;i++){
        Hour* nptr=(Hour*)(malloc(sizeof(Hour)));
        nptr->free=10;
        nptr->start=i;
        nptr->info=NULL;
        nptr->next=NULL;
        lptr->next=nptr;
        lptr=lptr->next;
    }
    lptr=hour_head;
    
    int option;
    int condition=1;
    printf("----------------------------------------------------------------------------------------\n\n");
    printf("***Instruction***!!!!\n\n***Use Camel Case For Name or Program with more than two words.***\n");
    printf("---Example for Weight Lifting use WeightLifting.---\n");
    printf("***The functioning is Case Sensitive so provide Case Sensetive Input.***\n");
    printf("***The four programs:Yoga,Cardio,Zumba and WeightLifting. Select these(Case Sensitive)***\n");
    printf("***The time used is 24hr Format. For a schedule slot provide starting hr of the slot.***\n");
    printf("***The data structure used for storing data and maintaining is Linked List(Singly).***\n");
    printf("***The data then stored in text file through file handling.***\n");
    printf("***For functioning please read comments and readme file attached.***\n");
    printf("***Enter 0 to exit the program and Enter 100 to save the data collected.***\n\n");
    printf("----------------------------------------------------------------------------------------\n");
    while(condition){
        printf("Enter Option::\n1)Add Member 2)Add Trainer 3)Schedule Slot 4)Hour List 5)Delete Member 6)Delete Trainer\n7)Search Member 8)Search Trainer 9)Member List 10)Trainer List 11)Renumeration 12)Intersection\n");
        scanf("%d",&option);
        if(option==1){
            char name[20];
            printf("Enter Member Name: ");
            scanf("%s",&name);
            int age;
            printf("Enter Age: ");
            scanf("%d",&age);
            char gender;
            printf("Enter Gender(F for Female and M for Male): ");
            fflush(stdin);
            scanf("%c",&gender);
            int n;
            printf("Enter Number of program: ");
            scanf("%d",&n);
            mem_head=add_member(mem_head,name,age,gender,n);
            printf("Updated Member List:\n");
            print_member_list(mem_head);
        }
        else if(option==2){
            char name[20];
            printf("Enter Trainer Name: ");
            scanf("%s",&name);
            char program[20]="Nothing";
            int fees;
            printf("Enter Renumeration: ");
            scanf("%d",&fees);
            int n;
            printf("Enter Number of program they can train: ");
            scanf("%d",&n);
            tra_head=add_trainer(tra_head,name,program,fees,n);
            printf("Updated Trainer List:\n");
            print_trainer_list(tra_head);
        }
        else if(option==3){
            printf("Enter the info of member to schedule and trainers available from above Member List and Trainer List Data.\n");
            print_member_list(mem_head);
            print_trainer_list(tra_head);
            int no_of_member;
            printf("Enter no of member in list\n");
            scanf("%d",&no_of_member); //Taking input as the input of schedule memeber and aailable trainer list is given.
            while(no_of_member--){
                sche_head=initialize_schedule(sche_head);
            }
            int no_of_trainer;
            printf("Enter no of trainer available.\n");
            scanf("%d",&no_of_trainer);
            while(no_of_trainer--){
                avail_head=intialize_available(avail_head);
            }
            hour_head=schedule_slot(hour_head,sche_head,avail_head);
        }
        else if(option==4){
            print_hour_wise_list(hour_head);
        }
        else if(option==5){
            int id;
            printf("Enter Member ID to delete: ");
            scanf("%d",&id);
            mem_head=delete_member(mem_head,id);
            printf("Updated Member List:\n");
            print_member_list(mem_head);
        }
        else if(option==6){
            int id;
            printf("Enter Trainer ID to delete: ");
            scanf("%d",&id);
            tra_head=delete_trainer(tra_head,id);
            printf("Updated Trainer List:\n");
            print_trainer_list(tra_head);
        }
        else if(option==7){
            printf("For Searching Member:\n");
            search_member(mem_head);
        }
        else if(option==8){
            printf("For Searching Trainer:\n");
            search_trainer(tra_head);
        }
        else if(option==9){
            print_member_list(mem_head);
        }
        else if(option==10){
            print_trainer_list(tra_head);
        }
        else if(option==11){
            print_sorted_remuneration_list(hour_head,tra_head);
        }
        else if(option==12){
            print_intersection_list(sche_head);
        }
        else if (option==100)
        {
            save_data(mem_head,tra_head,hour_head);
            printf("----------------------------------------------------------------------------------------\n");
            printf("Data saved successfully.\nMember_List.txt for Member.\nTrainer_List.txt for Trainers.\n");
            printf("Schedule_List.txt for Schedule Slots.\n");
            printf("All txt files are saved in current directory.\n");
            printf("----------------------------------------------------------------------------------------\n");
        }
        else if(option==0){
            printf("----------------------------------------------------------------------------------------\n");
            printf("Thank You For Using.\n");
            printf("----------------------------------------------------------------------------------------\n");
            condition=0;
        }
        else{
            printf("Please Select a Valid Option from above and 0 for exit and 100 to save data.\n");
            printf("----------------------------------------------------------------------------------------\n");
        }
    }
    return 0;
}