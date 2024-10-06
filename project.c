#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define False 0
#define True 1
#define NULL (void*)0
typedef unsigned char bool;

struct student{
	int id; 			//student id
	char name[50];		//student name
	int age;			//student age
	float gpa;			//student GPA
};

struct node{
	struct student data;
	struct node *next;
};

struct node *head=NULL;
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);



int main(void){
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	int choice;							//to choose the operation
	int checkId;						//used to compare the id entered by the user
	bool EXIT=False;					//used to exit the program

	while(!EXIT){
		printf("1. Add student\n"
				"2. Display students\n"
				"3. Search student by ID\n"
				"4. Update student informations\n"
				"5. Delete student\n"
				"6. Calculate Average GPA\n"
				"7. Search for student with highest grade\n"
				"8. Exit\n");

		printf("Enter choice: ");
		scanf("%d",&choice);

		switch (choice){
			case 1:
				struct student *information=(struct student*)malloc(sizeof(struct student));

				//test the allocation
				if(information==NULL){
					printf("Error, allocation failed\n");
					printf("------------------------------------------------------\n");
				}

				//take data from user
				printf("Enter student ID: ");
				scanf("%d",&information->id);

				printf("Enter name: ");
				scanf("%s",information->name);

				printf("Enter age: ");
				scanf("%d",&information->age);

				printf("Enter GPA: ");
				scanf("%f",&information->gpa);
				printf("------------------------------------------------------\n");

				addStudent(information);
				break;

			case 2:
				printf("------------------------------------------------------\n");
				displayStudents();
				break;

			case 3:
				printf("Enter student id to search:");
				scanf("%d",&checkId);
				printf("------------------------------------------------------\n");
				searchStudentByID(checkId);
				break;

			case 4:
				printf("Enter student's ID to update its information:");
				scanf("%d",&checkId);
				printf("------------------------------------------------------\n");
				updateStudent(checkId);
				break;

			case 5:
				printf("Enter student's ID to delete its data:");
				scanf("%d",&checkId);
				printf("------------------------------------------------------\n");
				deleteStudent(checkId);
				break;

			case 6:
				printf("Average GPA = %f\n",calculateAverageGPA());
				printf("------------------------------------------------------\n");
				break;

			case 7:
				searchHighestGPA();
				break;

			case 8:
				EXIT=True;
		}
	}
	return 0;
}


void addStudent(const struct student *const ptr){ 			//add a student at the end of the list
	struct node *current=head;
	struct node *assign=head;
	struct node *link=(struct node *)malloc(sizeof(struct node));

	//test the allocation
	if(link==NULL){
		printf("Error, allocation failed\n");
		return;
	}

	//if the list is empty
	if(current==NULL){
		link->data=*ptr;				//the data of the node points to the struct student
		head=link;						//assign the node
		link->next=NULL;
		return;
	}

	else{
		//loop on the linked list to check if the id already exists
		while(current!=NULL){
			if(current->data.id==ptr->id){
				printf("this ID is already reserved\n");
				printf("------------------------------------------------------\n");
				return;
			}
			current=current->next;
		}			//got out of the loop because the id doesn't exist


		//loop to the last node
		while(assign->next!=NULL){
			assign=assign->next;
		}

		//the data of the node points to the struct student
		link->data=*ptr;

		//Assign the new node at the end of the list
		assign->next=link;
		link->next=NULL;
		return;
	}
}


void displayStudents(void){				//shows a list of all stored student records
	struct node *ptr=head;

	if(ptr==NULL){						//check if the list is empty
		printf("No students are present\n");
		printf("------------------------------------------------------\n");
		return;
	}

	while(ptr!=NULL){					//loops on the list and print informations
		printf("[ ID: %d, Name: %s, Age: %d, GPA: %.1f ]\n",ptr->data.id,ptr->data.name,ptr->data.age,ptr->data.gpa);
		ptr=ptr->next;
	}
	printf("------------------------------------------------------\n");
}

void searchStudentByID(int id){			//find a specific student using their unique ID
	struct node *ptr=head;
	int checkId=id;						//used to compare the id entered

	while(ptr!=NULL){
		if(ptr->data.id==checkId){		//loops on the list and compare IDs
			printf("Student found: \n");
			printf("[ ID: %d, Name: %s, Age: %d, GPA: %.1f ]\n",ptr->data.id,ptr->data.name,ptr->data.age,ptr->data.gpa);
			printf("------------------------------------------------------\n");
			return;
		}
		ptr=ptr->next;
	}
	//no student have the entered ID
	printf("Student with ID %d not found\n",checkId);
	printf("------------------------------------------------------\n");
}

void updateStudent(int id){				//updates details for an existing student identified by their ID
	struct node *ptr=head;
	int checkId=id;						//used to compare the id entered

	while(ptr!=NULL){
		if(ptr->data.id==checkId){		//loops on the list until it finds the id
			printf("Enter the new details for the student with ID %d\n", checkId );

			printf("Enter new name: ");
			scanf("%s",ptr->data.name);

			printf("Enter new age: ");
			scanf("%d",&ptr->data.age);

			printf("Enter new GPA: ");
			scanf("%f",&ptr->data.gpa);

			printf("Student details updated successfully\n");
			printf("------------------------------------------------------\n");
			return;
		}
		ptr=ptr->next;
	}
	//no student have the entered ID
	printf("Student with ID %d not found\n",checkId);
	printf("------------------------------------------------------\n");
}

float calculateAverageGPA(void){		//computes and displays the average GPA of all students
	struct node *ptr=head;
	float sum=0;
	int count=0;

	if(ptr==NULL){						//check if the list is empty
		return 0;
	}

	while(ptr!=NULL){					//loops on the list
		count++;
		sum+=ptr->data.gpa;				//add the GPA of each student
		ptr=ptr->next;
	}

	return sum/count;
}

void searchHighestGPA(void){			//identifies and displays the student with the highest GPA
	struct node *ptr=head;
	int max=0;
	int checkId=0;						//to find the ID of the student with highest GPA


	if(ptr==NULL){						//list is empty
		printf("No students are present\n");
		printf("------------------------------------------------------\n");
		return;
	}

	max=ptr->data.gpa;					//assigning the GPA of first student as max
	checkId=ptr->data.id;

	while(ptr!=NULL){
		if(ptr->data.gpa>max){			//compares GPA
			max=ptr->data.gpa;
			checkId=ptr->data.id;
		}
		ptr=ptr->next;
	}

	printf("Student with the highest GPA:\n");


	ptr=head;							//pointer returns to the beginning of the list
	while(ptr!=NULL){
		if(ptr->data.id==checkId){		//loops on the list and compare IDs
			printf("[ ID: %d, Name: %s, Age: %d, GPA: %.1f ]\n",ptr->data.id,ptr->data.name,ptr->data.age,ptr->data.gpa);
			printf("------------------------------------------------------\n");
			return;
		}
		ptr=ptr->next;
	}
	printf("after the second while");
	return;
}

void deleteStudent(int id){				//removes a student's record based on their ID
	struct node *ptr=head;				//points to the node before the one to be deleted
	struct node *deleted=NULL;			//points to the node to be deleted
	int checkId=id;

	//if the list is empty
	if(ptr==NULL){
		printf("Student with ID %d not found\n",checkId);
		printf("------------------------------------------------------\n");
		return;
	}

	//if the student to be deleted is the first student
	if(ptr->data.id==checkId){
		head=ptr->next;					//head is moved to point to the second student
		free(ptr);

		printf("The student is deleted\n");
		printf("------------------------------------------------------\n");
		return;
	}

	while(ptr->next!=NULL){				//loops on the list
		if(ptr->next->data.id==checkId){
			deleted=ptr->next;
			ptr->next=ptr->next->next;	//the node before points to the node after
			free(deleted);

			printf("The student is deleted\n");
			printf("------------------------------------------------------\n");
			return;
		}
		ptr=ptr->next;
	}
	printf("Student with ID %d not found\n",checkId);
	printf("------------------------------------------------------\n");
	return;
}
