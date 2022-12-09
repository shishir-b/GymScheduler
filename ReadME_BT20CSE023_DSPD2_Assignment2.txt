/* Name: Shishir N Bhalerao | Enroll no: BT20CSE023 | DSPD-II Assignment-2 Batch-1 */

// So as all the data is stored in AVL tree, so the algorithm for adding and deleting node is same for all by maintaining balance factor
   and the BST properties and while deleting the tree is rearranged as the minimum root replacement and balance factor adjusting. 
   For each tree we have height count, balance factor count , left rotate , right rotate function and for member and trainer tree
   we have also minimum node function to apply all the transformation to keep tree AVL balanced.
// For traversing In-Order Traversal is used for all recursively so all multiple trees are traversed with multiple recursions.

// All AVL Trees to store data with their elements and Key.

// Program AVL Tree -> Contains Course Name for Trainer. (Key is 1 to 4)
// Program_Mem AVL Tree ->Contains Course Name for Member with respective fees.(Key is 1 to 4)
// Member AVL Tree -> Contains Member Name,ID,Age,Gender,Program_Mem AVL Tree for programs and total fees.(Key is Member ID).
// Trainer AVL Tree -> Contains Trainer Name,ID,Program AVL Tree. (Key is Trainer ID).
// Per Hour AVL Tree -> Contains Member and Trainer ID and programs.(Key is Free Slots so distinct.).
// Hour AVL Tree -> Contains Schedule is Per Hour AVL Tree, free and start of slot. (Key is Slot start point).
// Earn AVL Tree -> Contains Member Remuneration in highest to lowest and Member ID .(Key is Total Remuneration in negative).

// For Q1. Add_member()
--> For adding the member first we took all the info of the member and then add to the member AVL tree according to the ID,
    so the tree is mainted AVL whenever we insert a member Node and it remains AVL after every insertion and    
    returns the member tree root.

// For Q2. Add_trainer()
--> For adding the trainer first we took all the info of the trainer and then add to the trainer AVL tree according to the ID
    same as the Add_Member, so the tree is AVL whenever we insert a member Node and it remains AVL after every  
    insertion and returns the trainer tree root.

// For Q3. Schedule_slot()
--> First we take the input for member to schedule along with the preffered slot,ID and timestamps of request, and to store 
    this schedule member a schedule member tree is created which stores the request accordingly to the timestamps such that 
    whenever the sceduling is done the First-Come-First-Done format is respected by direct traversing the schedule tree in-order.
    Then to store the Member available we take the input ID and the time from when they are available and store it in the 
    available membertree. After storing these both input we traverse through the Hour AVL Tree and if the Member is already allocated,
    we will return with message already allocated.If not the we will traverse and then first find the slot prefferd
    and if the member prefferd is available and the slot is free for max 10 members and allocate it. If the preferred slot
    is already allocated, finds the next free slot in the tree whole cycle. If the prefferd ID is not available then we do the  
    same traversing with a free member. After allocation we will traverse the hour tree and print the record of the assigned member 
    with slot, ID and trainer ID. And we will traverse the schedule tree to print all the non assigned members.

// For Q4. Print_hour_wise_list()
--> Traversing the Hour AVL Tree and prints the all information of scheduled member ID , Time Slot and Trainer Allocated grouped by the
    different programs.

// For Q5. Delete_member()
--> Traversing the Member AVL Tree if the member ID is matched we will delete the Member Node and returns the Member AVL Tree root of the
    rearranged member tree by deleting AVL node algorithm with message of deleted succesfully otherwise if the member ID not matched returns the message of member
    not found and returns member root.

// For Q6. Delete_trainer()
--> Traversing the Member AVL Tree if the trainer ID is matched we will delete the Trainer Node and returns the Trainer AVL Tree root of the
    rearranged trainer tree by deleting AVL node algorithm with message of deleted succesfully otherwise if the trainer ID not matched returns the message of member
    not found and returns trainer root.

// For Q7. Search_member()
--> First we will take the input for key of either ID,Name,Programs,Age or Gender of member and then traverse the whole member tree
    and when the take the key value and match the records if the member is found with matching we will print if else will print None.
    When searched with ID we take use of the BST properties as ID is key in Member Tree.

// For Q8. Search_trainer()
--> First we will take the input for key of either ID,Name,Programs of Trainer and then traverse the whole trainer tree and when 
    the take the key value and match the records if the trainer is found with matching we will print if else will print None.
    When searched with ID we take use of the BST properties key as ID is key in Trainer Tree.

// For Q9. Print_member_list()
--> We will traverse the whole member tree print the records is nothing is present we will print None.

// For Q10. Print_trainer_list()
--> We will traverse the whole trainer tree print the records is nothing is present we will print None.

// For Q11. Print_sorted_remuneration_list()
--> We will traverse the trainer tree and for each member we will calculate the total slots taken and increase the remuneration of 
    that trainer from the whole Hour Tree and then we will add the Trainer Remuneration Node to Trainer Renumeration AVL Tree with 
    respect to the renumeration in descending order as the key stored is negative of total remuneration and then will print the whole
    renumeration tree it will be in highest to lowest as in-order traversal prints sorted so with modulus we can get correct ans
    if no trainer is present we will print None.

// For Q12. Range_Search()
--> We travese the member tree in In-order but we saves the recursion overhead by applying the BST properties with range mention.
    And if the member id(key) is matched with the range we print it. 

/* Functions defintion in source file:
   Q1. Add_member() -> Line no. 381
   Q2. Add_trainer() -> Line no. 608
   Q3. Schedule_slot() -> Line no. 1795
   Q4. Print_hour_wise_list()-> Line no. 1559
   Q5. Delete_member() -> Line no. 430
   Q6. Delete_trainer() -> Line no. 657
   Q7. Search_member() -> Line no. 881
   Q8. Search_trainer()-> Line no. 1007
   Q9. Print_member_list()-> Line no. 517
   Q10. Print_trainer_list() -> Line no. 744
   Q11. Print_sorted_remuneration_list() -> Line no. 1938
   Q12. Range_Search() -> Line no. 1961
*/
/********Thanks a lot for reading.********/