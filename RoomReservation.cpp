// #include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include <curses.h>
#include <string.h>

#pragma warning(disable:4996)

struct newRoom
{
	char x[20];
	char ID[20];
	char typeA[20], typeB[20];
	char adultLimit[20], kidLimit[20];
};

struct Reservation
{
	char UserID[20];
	char RoomID[20];
	char typeA[20];
	char typeB[20];
	char adults[20];
	char kids[20];
};

void Signup(void);
int Login(void);
void Booking(void);
void ViewAll(void);
void Cancel(void);
void Modify(void);
void Upload(void);
void ViewReservation(void);
void Search(void);
void ViewCancel(void);
void ModifyRoom(void);

int main()
{
	int role;
	int admin;
	int cOption;
	int customer;

	printf("========== Hotel Room Reservation System ==========\n\n");

Role:

	printf("Press 1 for Admin\n");
	printf("Press 2 for Customer\n");
	printf("Press 0 to Exit\n");
	scanf("%d", &role);

	switch (role)
	{
	case 1:

	administrator:

		printf("\n- Press 1 to upload room details\n");
		printf("- Press 2 to view the reservations\n");
		printf("- Press 3 to search reservations\n");
		printf("- Press 4 to view the cancellations\n");
		printf("- Press 5 to modify room details\n");
		printf("- Press 6 to log out\n\n");
		scanf("%d", &admin);

		switch (admin)
		{
		case 1:
			Upload();
			goto administrator;
			break;
		case 2:
			ViewReservation();
			goto administrator;
			break;
		case 3:
			Search();
			goto administrator;
			break;
		case 4:
			ViewCancel();
			goto administrator;
			break;
		case 5:
			ModifyRoom();
			goto administrator;
			break;
		case 6:
			goto Role;
			break;
		default:
			printf("\nIncorrect Input, try again\n");
			scanf("%c");
			goto administrator;
			break;
		}

		break;

	case 2:

	customerOption:

		printf("\nPress 1 to Signup\n");
		printf("\nPress 2 to Login\n");
		scanf("%d", &cOption);

		if (cOption == 1)
		{
			Signup();
			goto customerOption;
		}
		else if (cOption == 2)
		{
			if (Login() == 1)
			{

			Customer:

				printf("- Press 1 to Book a room\n");
				printf("- Press 2 to Cancel a booking\n");
				printf("- Press 3 to Modify a booking\n");
				printf("- Press 4 to view the status of the rooms\n");
				printf("- Press 5 to log out\n\n");
				scanf("%d", &customer);

				switch (customer)
				{
				case 1:
					ViewAll();
					Booking();
					goto Customer;
					break;

				case 2:
					Cancel();
					goto Customer;
					break;

				case 3:
					Modify();
					goto Customer;
					break;

				case 4:
					ViewAll();
					goto Customer;
					break;

				case 5:
					goto Role;
					break;

				default:
					printf("\nIncorrect Input, try again\n");
					scanf("%c");;
					goto Customer;
					break;
				}
			}
			else
			{
				goto Role;
			}
		}
		else
		{
			printf("\nIncorrect Input\n");
			goto Role;
		}
		break;
	case 0:
		system("exit");
		break;
	default:
		printf("\nIncorrect input, try again\n");
		scanf("%c");;
		goto Role;
		break;
	}

	system("pause");
}

void Signup()
{
	char username[20], password[20];
	char scan[20];

	FILE *fp;
	fp = fopen("UserData.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	printf("\nEnter Username: \n");
	scanf("%s", &username);

	printf("\nEnter Password: \n");
	scanf("%s", &password);

	while (!feof(fp))
	{
		fscanf(fp, "%s", scan);

		if (strcmp(scan, username) == 0)
		{
			printf("\nUsername already exist. \n");
			printf("Please try a new username or login if you are already a user. \n");
			scanf("%c");;
			break;
		}
	}

	if (strcmp(scan, username) != 0)
	{
		printf("\nUser added! \n");
		fprintf(fp, "\n%s\t", username);
		fprintf(fp, "%s", password);
		scanf("%c");;
	}
	fclose(fp);
}

int Login()
{
	int result;
	char username[20], password[20];
	char inputUsername[20], inputPassword[20];

	FILE *fp;

	fp = fopen("UserData.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	printf("\nEnter Username: \n");
	scanf("%s", &inputUsername);

	printf("\nEnter Password: \n");
	scanf("%s", &inputPassword);

	if (strcmp(inputUsername, "Admin") == 0 && strcmp(inputPassword, "12345") == 0)
	{
		result = 2;
		printf("\nAdmin logged in Successfully\n");
		goto end;
	}

	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s", username);

			if (strcmp(inputUsername, username) == 0)
			{
				fscanf(fp, "%s", password);

				if (strcmp(inputPassword, password) != 0)
				{
					printf("Incorrect Password");
					result = 0;
					rewind(fp);
					break;
				}

				else
				{
					printf("\nSuccessfully Logged in! \n\n");
					result = 1;
					break;
				}
			}
		}
	}

	if (strcmp(inputUsername, username) != 0)
	{
		printf("\nIncorrect Username");
		result = 0;
		scanf("%c");;
	}
end:
	return result;
}

void Booking()
{
	struct newRoom Room;

	char RoomID[20];
	char UserID[20];
	int adults, kids;

	int a, b;

	FILE *fp, *fp2, *fp3;

	fp = fopen("Rooms.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	fp2 = fopen("Reservations.txt", "a+");

	if (fp2 == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

choose:

	printf("\nEnter User ID: \n");
	scanf("%s", &UserID);
	printf("\nEnter desired Room ID: \n");
	scanf("%s", &RoomID);
	printf("\nEnter the number of Adults: \n");
	scanf("%d", &adults);
	printf("\nEnter the number of Kids: \n");
	scanf("%d", &kids);

	while (!feof(fp))
	{
		fscanf(fp, "%s", Room.x);

		if (strcmp(Room.x, "#") == 0)
		{
			fscanf(fp, "%s", Room.ID);
			fscanf(fp, "%s", Room.typeA);
			fscanf(fp, "%s", Room.typeB);
			fscanf(fp, "%s", Room.adultLimit);
			fscanf(fp, "%s", Room.kidLimit);

			if (strcmp(Room.ID, RoomID) == 0)
			{
				a = atoi(Room.adultLimit);
				b = atoi(Room.kidLimit);

				if (adults > a && kids > b)
				{
					printf("\nLimt for kids or adults exceeded, please choose a different room\n");
					goto choose;
				}
				else
				{
					printf("\nRoom reserved successfully\n");
					printf("\nUser ID: %s", UserID);
					printf("\nRoom ID: %s", Room.ID);
					printf("\nRoom Type: %s %s", Room.typeA, Room.typeB);
					printf("\nNumber of Adults: %d", adults);
					printf("\nNumber of Kids: %d\n", kids);

					fprintf(fp2, "\n%s\t", UserID);
					fprintf(fp2, "%s\t", Room.ID);
					fprintf(fp2, "%s\t", Room.typeA);
					fprintf(fp2, "%s\t", Room.typeB);
					fprintf(fp2, "%d\t", adults);
					fprintf(fp2, "%d", kids);

					scanf("%c");;
					break;
				}
			}
		}
		rewind(fp);
	}

	if (strcmp(Room.ID, RoomID) != 0)
	{
		printf("\nIncorrect Room Id\n");
		goto choose;
	}

	fclose(fp);
	fclose(fp2);
}

void ViewAll()
{
	struct newRoom Room;

	FILE *fp;

	fp = fopen("Rooms.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	printf("\n\n---------------------- Displaying All Available Rooms ----------------------\n\n");

	while (!feof(fp))
	{
		fscanf(fp, "%s", Room.x);
		fscanf(fp, "%s", Room.ID);
		fscanf(fp, "%s", Room.typeA);
		fscanf(fp, "%s", Room.typeB);
		fscanf(fp, "%s", Room.adultLimit);
		fscanf(fp, "%s", Room.kidLimit);

		printf("Room ID: %s\n", Room.ID);
		printf("Room Type: %s %s\n", Room.typeA, Room.typeB);
		printf("Adults Limit: %s\n", Room.adultLimit);
		printf("Kids Limit: %s\n\n", Room.kidLimit);
	}
	fclose(fp);
}

void Cancel()
{
	char inputID[20];

	struct Reservation a;

	FILE *fp, *fp2, *fp3;

	fp = fopen("Reservations.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	fp2 = fopen("temp.txt", "a+");

	if (fp2 == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	fp3 = fopen("Cancellation.txt", "a+");

	if (fp3 == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	printf("\nEnter the User ID\n");
	scanf("%s", &inputID);

	while (!feof(fp))
	{
		fscanf(fp, "%s", a.UserID);

		if (strcmp(inputID, a.UserID) == 0)
		{
			fscanf(fp, "%s", a.RoomID);
			fscanf(fp, "%s", a.typeA);
			fscanf(fp, "%s", a.typeB);
			fscanf(fp, "%s", a.adults);
			fscanf(fp, "%s", a.kids);

			printf("\nUser ID: %s", a.UserID);
			printf("\nRoom ID: %s", a.RoomID);
			printf("\nRoom Type: %s %s", a.typeA, a.typeB);
			printf("\nNumber of Adults: %s", a.adults);
			printf("\nNumber of Kids: %s\n", a.kids);
			printf("\n------------- Reservation Canceled Successfully -------------\n");

			fprintf(fp3, "\n%s\t", a.UserID);
			fprintf(fp3, "%s\t", a.RoomID);
			fprintf(fp3, "%s\t", a.typeA);
			fprintf(fp3, "%s\t", a.typeB);
			fprintf(fp3, "%s\t", a.adults);
			fprintf(fp3, "%s", a.kids);

			rewind(fp);
			scanf("%c");;

			while (!feof(fp))
			{
				fscanf(fp, "%s", a.UserID);
				fscanf(fp, "%s", a.RoomID);
				fscanf(fp, "%s", a.typeA);
				fscanf(fp, "%s", a.typeB);
				fscanf(fp, "%s", a.adults);
				fscanf(fp, "%s", a.kids);

				if (strcmp(inputID, a.UserID) != 0)
				{
					fprintf(fp2, "\n%s\t", a.UserID);
					fprintf(fp2, "%s\t", a.RoomID);
					fprintf(fp2, "%s\t", a.typeA);
					fprintf(fp2, "%s\t", a.typeB);
					fprintf(fp2, "%s\t", a.adults);
					fprintf(fp2, "%s", a.kids);
				}
			}
			break;
			goto exit;
		}
	}

	if (strcmp(inputID, a.UserID) != 0)
	{
		printf("\nUser ID not found\n\n");
		scanf("%c");;
	}

exit:

	fclose(fp);
	fclose(fp2);
	fclose(fp3);

	remove("Reservations.txt");
	rename("temp.txt", "Reservations.txt");
}

void Modify()
{
	char inputID[20];

	struct Reservation a;
	struct Reservation b;

	FILE *fp, *fp2;

	fp = fopen("Reservations.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	fp2 = fopen("temp.txt", "a+");

	if (fp2 == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	printf("\nEnter the User ID\n");
	scanf("%s", &inputID);

	while (!feof(fp))
	{
		fscanf(fp, "%s", a.UserID);

		if (strcmp(inputID, a.UserID) == 0)
		{
			fscanf(fp, "%s", a.RoomID);
			fscanf(fp, "%s", a.typeA);
			fscanf(fp, "%s", a.typeB);
			fscanf(fp, "%s", a.adults);
			fscanf(fp, "%s", a.kids);

			printf("\nReservation Found\n");

			printf("\nEnter desired Room ID: \n");
			scanf("%s", &a.RoomID);
			printf("\nEnter the number of Adults: \n");
			scanf("%s", &a.adults);
			printf("\nEnter the number of Kids: \n");
			scanf("%s", &a.kids);

			printf("\nReservation Modified\n");

			fprintf(fp2, "\n%s\t", a.UserID);
			fprintf(fp2, "%s\t", a.RoomID);
			fprintf(fp2, "%s\t", a.typeA);
			fprintf(fp2, "%s\t", a.typeB);
			fprintf(fp2, "%s\t", a.adults);
			fprintf(fp2, "%s", a.kids);

			rewind(fp);

			while (!feof(fp))
			{
				fscanf(fp, "%s", b.UserID);
				fscanf(fp, "%s", b.RoomID);
				fscanf(fp, "%s", b.typeA);
				fscanf(fp, "%s", b.typeB);
				fscanf(fp, "%s", b.adults);
				fscanf(fp, "%s", b.kids);

				if (strcmp(a.UserID, b.UserID) != 0)
				{
					fprintf(fp2, "\n%s\t", b.UserID);
					fprintf(fp2, "%s\t", b.RoomID);
					fprintf(fp2, "%s\t", b.typeA);
					fprintf(fp2, "%s\t", b.typeB);
					fprintf(fp2, "%s\t", b.adults);
					fprintf(fp2, "%s", b.kids);
				}
			}
			break;
		}
	}

	if (strcmp(inputID, a.UserID) != 0)
	{
		printf("\nReservation not found\n\n");
		fclose(fp);
		fclose(fp2);
		remove("temp.txt");
		goto exit;
	}

	fclose(fp);
	fclose(fp2);

	remove("Reservations.txt");
	rename("temp.txt", "Reservations.txt");

exit:
	printf("Press any key to return to the main menu");
	scanf("%c");;
}

void Upload()
{
	int type;
	int ID;
	int adultsLimit, kidsLimit;
	char x[50], y[10], z[10], a[10];

	FILE *fp;

	fp = fopen("Rooms.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

Room:

	printf("\nPlease Enter Room ID: \n");
	scanf("%d", &ID);

	itoa(ID, z, 10);

	while (!feof(fp))
	{
		fscanf(fp, "%s", y);

		if (strcmp(y, "#") == 0)
		{
			fscanf(fp, "%s", a);

			if (strcmp(z, a) == 0)
			{
				printf("\nID already exists, Press any key to try again\n");
				scanf("%c");;
				goto Room;
			}
		}
	}

	if (strcmp(z, a) != 0)
	{
		printf("\n\nPlease choose the room type: \n");
		printf("- Enter 1 for Single Room\n");
		printf("- Enter 2 for Double Room\n");
		printf("- Enter 3 for Queen size Room\n");
		printf("- Enter 4 for King size Room\n");
		scanf("%d", &type);

		printf("\n\nEnter the limit of Adults: \n");
		scanf("%d", &adultsLimit);

		printf("\n\nEnter the limit of Kids: \n");
		scanf("%d", &kidsLimit);

		if (type == 1)
		{
			strcpy(x, "Single Room");
		}
		else if (type == 2)
		{
			strcpy(x, "Double Room");
		}
		else if (type == 3)
		{
			strcpy(x, "QueenSize Room");
		}
		else if (type == 4)
		{
			strcpy(x, "KingSize Room");
		}

		printf("\n\nRoom uploaded successfully\n");
		printf("Room ID: %d\n", ID);
		printf("Room Type: %s\n", x);
		printf("Adults: %d\n", adultsLimit);
		printf("Kids: %d\n", kidsLimit);
		printf("Press any key to continue\n");
		scanf("%c");;

		fprintf(fp, "\n#\t%d\t", type);
		fprintf(fp, "%s\t", x);
		fprintf(fp, "%d\t", adultsLimit);
		fprintf(fp, "%d", kidsLimit);
	}

	fclose(fp);
}

void ViewReservation()
{
	char UserID[20];
	char RoomID[20];
	char typeA[20];
	char typeB[20];
	char adults[20];
	char kids[20];

	FILE *fp;

	fp = fopen("Reservations.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	printf("\n\n---------------------- Displaying All Reservations ----------------------\n\n");

	while (!feof(fp))
	{
		fscanf(fp, "%s", UserID);
		fscanf(fp, "%s", RoomID);
		fscanf(fp, "%s", typeA);
		fscanf(fp, "%s", typeB);
		fscanf(fp, "%s", adults);
		fscanf(fp, "%s", kids);

		printf("\nUser ID: %s", UserID);
		printf("\nRoom ID: %s", RoomID);
		printf("\nRoom Type: %s %s", typeA, typeB);
		printf("\nNumber of Adults: %s", adults);
		printf("\nNumber of Kids: %s\n", kids);
	}

	printf("\nPress any key to contiue\n");
	scanf("%c");;

	fclose(fp);
}

void Search()
{
	char inputID[20];

	char UserID[20];
	char RoomID[20];
	char typeA[20];
	char typeB[20];
	char adults[20];
	char kids[20];

	FILE *fp;

	fp = fopen("Reservations.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

start:

	printf("\nEnter the User ID\n");
	scanf("%s", &inputID);

	while (!feof(fp))
	{
		fscanf(fp, "%s", UserID);

		if (strcmp(inputID, UserID) == 0)
		{
			fscanf(fp, "%s", RoomID);
			fscanf(fp, "%s", typeA);
			fscanf(fp, "%s", typeB);
			fscanf(fp, "%s", adults);
			fscanf(fp, "%s", kids);

			printf("\nUser ID: %s", UserID);
			printf("\nRoom ID: %s", RoomID);
			printf("\nRoom Type: %s %s", typeA, typeB);
			printf("\nNumber of Adults: %s", adults);
			printf("\nNumber of Kids: %s\n", kids);
			scanf("%c");;
			break;
		}
	}

	if (strcmp(inputID, UserID) != 0)
	{
		printf("\nIncorrect ID, press any key to try again\n");
		scanf("%c");;
		goto start;
	}

	fclose(fp);
}

void ViewCancel()
{
	char UserID[20];
	char RoomID[20];
	char typeA[20];
	char typeB[20];
	char adults[20];
	char kids[20];

	FILE *fp;

	fp = fopen("Cancellation.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	printf("\n\n---------------------- Displaying All Cancellations ----------------------\n\n");

	while (!feof(fp))
	{
		fscanf(fp, "%s", UserID);
		fscanf(fp, "%s", RoomID);
		fscanf(fp, "%s", typeA);
		fscanf(fp, "%s", typeB);
		fscanf(fp, "%s", adults);
		fscanf(fp, "%s", kids);

		printf("\nUser ID: %s", UserID);
		printf("\nRoom ID: %s", RoomID);
		printf("\nRoom Type: %s %s", typeA, typeB);
		printf("\nNumber of Adults: %s", adults);
		printf("\nNumber of Kids: %s\n", kids);
	}

	printf("\nPress any key to contiue\n");
	scanf("%c");;

	fclose(fp);
}

void ModifyRoom()
{
	char inputID[20];

	struct newRoom room;
	struct newRoom delroom;

	FILE *fp, *fp2;

	fp = fopen("Rooms.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	fp2 = fopen("temp.txt", "a+");

	if (fp2 == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	printf("\nEnter the Room ID\n");
	scanf("%s", &inputID);

	while (!feof(fp))
	{
		fscanf(fp, "%s", room.x);

		if (strcmp(room.x, "#") == 0)
		{
			fscanf(fp, "%s", room.ID);

			if (strcmp(inputID, room.ID) == 0)
			{
				fscanf(fp, "%s", room.typeA);
				fscanf(fp, "%s", room.typeB);
				fscanf(fp, "%s", room.adultLimit);
				fscanf(fp, "%s", room.kidLimit);

				printf("\nRoom Found\n");

				printf("\n\nEnter the new limit of Adults: \n");
				scanf("%s", &room.adultLimit);

				printf("\n\nEnter the new limit of Kids: \n");
				scanf("%s", &room.kidLimit);

				printf("\nReservation Modified\n");

				fprintf(fp2, "\n#\t%s\t", room.ID);
				fprintf(fp2, "%s\t", room.typeA);
				fprintf(fp2, "%s\t", room.typeB);
				fprintf(fp2, "%s\t", room.adultLimit);
				fprintf(fp2, "%s", room.kidLimit);

				rewind(fp);

				while (!feof(fp))
				{
					fscanf(fp, "%s", delroom.x);
					fscanf(fp, "%s", delroom.ID);
					fscanf(fp, "%s", delroom.typeA);
					fscanf(fp, "%s", delroom.typeB);
					fscanf(fp, "%s", delroom.adultLimit);
					fscanf(fp, "%s", delroom.kidLimit);

					if (strcmp(room.ID, delroom.ID) != 0)
					{
						fprintf(fp2, "\n#\t%s\t", delroom.ID);
						fprintf(fp2, "%s\t", delroom.typeA);
						fprintf(fp2, "%s\t", delroom.typeB);
						fprintf(fp2, "%s\t", delroom.adultLimit);
						fprintf(fp2, "%s", delroom.kidLimit);
					}
				}
				break;
			}
		}
	}

	if (strcmp(inputID, room.ID) != 0)
	{
		printf("\nRoom not found\n\n");
		fclose(fp);
		fclose(fp2);
		remove("temp.txt");
		goto exit;
	}

	fclose(fp);
	fclose(fp2);

	remove("Rooms.txt");
	rename("temp.txt", "Rooms.txt");

exit:
	printf("Press any key to return to the main menu");
	scanf("%c");;
}