/* Name: Shishir N Bhalerao | Enroll no: BT20CSE023 | DSPD-II Assignment-1 Batch-1 */

// Program List -> Contains Course Name and Respective fees if for member.
// Member List -> Contains Member Name,ID,Age,Gender,Program List for programs and total fees.
// Trainer List -> Contains Trainer Name,ID,Program List and Remuneration. 
// Per Hour List -> Contains Member and Trainer ID and programs.
// Hour List -> Contains Schedule is Per Hour List, free and start of slot.

// For Q1. Add_member()
--> For adding the member first we took all the info of the member and then add to the member list according to the ID,
    so the list is sorted whenever we insert a member Node and it remains sorted after every insertion and    
    returns the member head.

// For Q2. Add_trainer()
--> For adding the trainer first we took all the info of the trainer and then add to the trainer list according to the ID
    same as the Add_Member, so the list is sorted whenever we insert a member Node and it remains sorted after every  
    insertion and returns the trainer head.

// For Q3. Schedule_slot()
--> First we take the input for member to schedule along with the preffered slot,ID and timestamps of request, and to store 
    this schedule member a schedule member list is created which stores the request accordingly to the timestamps such that 
    whenever the sceduling is done the First-Come-First-Done format is respected by direct traversing the schedule list.
    Then to store the Member available we take the input ID and the time from when they are available and store it in the 
    available member list. After storing these both input we traverse through the Hour List and if the Member is already allocated,
    we will return with message already allocated.If not the we will traverse and then first find the slot prefferd
    and if the member prefferd is available and the slot is free for max 10 members and alllocate it. If the preferred slot
    is already allocated, finds the next free slot in the list whole cycle. If the prefferd ID is not available then we do the  
    same traversing with a free member. After allocation we will traverse the hour list and print the record of the assigned member 
    with slot, ID and trainer ID. And we will traverse the schedule list to print all the non assigned members.

// For Q4. Print_hour_wise_list()
--> Traversing the Hour List and prints the all information of scheduled member ID , Time Slot and Trainer Allocated grouped by the
    different programs.

// For Q5. Delete_member()
--> Traversing the Member List if the member ID is matched we will delete the Member Node and returns the Member List head of the
    arranged member list with message of deleted succesfully otherwise if the member ID not matched returns the message of member
    not found and returns member head.

// For Q6. Delete_trainer()
--> Traversing the trainer List if the trainer ID is matched we will delete the trainer Node and returns the trainer List head of the
    arranged trainer list with message of deleted succesfully otherwise if the trainer ID not matched returns the message of trainer
    not found and returns trainer head.

// For Q7. Search_member()
--> First we will take the input for key of either ID,Name,Programs,Age or Gender of member and then traverse the whole member list 
    and when the take the key value and match the records if the member is found with matching we will print if else will print None.

// For Q8. Search_trainer()
--> First we will take the input for key of either ID,Name,Programs of Trainer and then traverse the whole trainer list and when 
    the take the key value and match the records if the trainer is found with matching we will print if else will print None.

// For Q9. Print_member_list()
--> We will traverse the whole member list print the records is nothing is present we will print None.

// For Q10. Print_trainer_list()
--> We will traverse the whole trainer list print the records is nothing is present we will print None.

// For Q11. Print_sorted_remuneration_list()
--> We will traverse the trainer list and for each member we will calculate the total slots taken and increase the remuneration of 
    that trainer from the whole Hour list and then we will add the Trainer Remuneration Node to Trainer Renumeration List with 
    respect to the renumeration in descending order and then will print the whole renumeration list it will be in highest to lowest
    as node is added descendingly if no trainer is present we will print None.

// For Q12. Print_intersection_list()
--> We will traverse the schedule list and then according to the preffered variable saved for done(0 for None,1 for Done,
    2 for preferred trainer Done) and if the done is 2 we will print the Member and trainer who are assigned preferrably
    and if nothing is in record we will output None.

// For saving the data of the list function is also added which will be print the all list data in respective text file.

/********Thanks a lot for reading.********/