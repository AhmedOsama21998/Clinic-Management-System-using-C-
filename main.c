/*
 * main.c
 *
 *Clinic Management System
 *
 *  Created on: Jun 23, 2023
 *      Author: Ahmed Osama Metwally
 */
#include <stdio.h>
#include <stdlib.h>
#include "Std_Types.h"
#include "Clinic_DataBase.h"

void AdminMode(u8 pressed);
void UserMode (u8 pressed);
// Global variables
u8 numPatients      = 0;
u8 numReservations  = 0;

int main(void)
{
u8 mode=0;

while(mode!=3)
 {
Mode:
system("cls");
printf("\nWelcome To my Clinic Management System\n");
printf("***************************\n");
printf("choose between TWO Modes\n");
printf("Admin Mode    press (1)\n");
printf("User Mode     press (2)\n");
printf("Exit Program  Press (3)\n");
printf("***************************\n");
scanf("%d",&mode);
    switch(mode)
         {
        case 1:/*Admin Mode*/
                printf("\n**********Admin Mode**********\n");
                printf("\nEnter The PassWord\n");
                for (u8 i=0 ; i < 3 ; i++ )
                 {
                 u32 pass;
                 scanf("%ld",&pass);
                 if(pass == PASS)
                     {
                        u8 pressed;
                        admin:
                        printf("\n**********Welcome Admin**********\n");
                        printf(" Add New Patient Record             Press(1)\n");
                        printf(" Edit Patient Record                Press(2)\n");
                        printf(" Reserve a Slot with the Doctor     Press(3)\n");
                        printf(" Cancel Reservation                 Press(4)\n");
                        printf(" Return to the previous list        Press(5)\n");
                        scanf("%d",&pressed);
                        if((pressed==1)|(pressed==2)|(pressed==3)|(pressed==4))
                         {
                            AdminMode(pressed);
                            goto admin;
                         }else if((pressed==5))
                         {
                           goto Mode;
                         }else
                         {
                            printf("\nWrong Choice\n");
                            goto admin;
                         }
                     }else
                     {
                        printf("Wrong PassWord\n");
                        printf("Try Again!!\n");
                     }
                 }
               goto Mode;
            break;
        case 2:/*User Mode*/
                User:

                printf("**********Welcome User**********\n");
                printf(" View Patient Record                Press(1)\n");
                printf(" View Todays Reservations           Press(2)\n");
                printf(" Return to the previous list        Press(3)\n");
                u8 pressed;
                scanf("%d",&pressed);
                if((pressed==1)|(pressed==2))
                 {
                  UserMode(pressed);
                  goto User;
                 }else if((pressed==3))
                 {
                  goto Mode;
                 }else
                 {
                  printf("Wrong Choice\n");
                  goto User;
                 }
            break;
         }
 }
 return 0;
}
void AdminMode(u8 pressed)
{

switch(pressed)
    {
    case 1:/*Add New Patient Record */
            if(numPatients == MAX_PATIENTS)
            {
            printf("Maximum number of patients reached. Cannot add more patients.\n");
            return;
            }
            Patient_t newPatient;
            printf("\nAdd New Patient\n");
            printf("----------------\n");
            printf("Enter patient name: ");
            scanf("%s", newPatient.name);
            printf("Enter patient age: ");
            scanf("%d", &newPatient.age);
            printf("Enter patient gender: ");
            scanf("%s", newPatient.gender);
            printf("Enter patient ID: ");
            scanf("%ld", &newPatient.id);

            // Check if ID already exists
            for (u8 i = 0; i < numPatients; i++)
            {
            if (Patients[i].id == newPatient.id)
                {
                    printf("Patient ID already exists. Cannot add patient.\n");
                    return;
                }
            }
            Patients[numPatients] = newPatient;
            numPatients++;
            printf("Patient record added successfully.\n");
        break;
    case 2:/*Edit Patient Record*/
            printf("\nEdit Patient Record\n");
            printf("-------------------\n");
            printf("Enter patient ID: ");
            u32 patientID;
            s8 flage = -1;
            scanf("%ld", &patientID);

            for (u8 i = 0; i < numPatients; i++)
            {
                if (Patients[i].id == patientID)
                {
                    flage = i;
                    break;
                }
            }
            if (flage == -1)
                {
                printf("Patient ID not found. Cannot edit patient record.\n");
                return;
                }
            Patient_t *patient = &Patients[flage];
            printf("Patient found. Enter new details:\n\n");
            printf("Enter patient name: ");
            scanf("%s", patient->name);
            printf("Enter patient age: ");
            scanf("%d", &patient->age);
            printf("Enter patient gender: ");
            scanf("%s", patient->gender);
            printf("\nPatient record updated successfully.\n");
        break;
    case 3:/*Reserve a Slot with the Doctor*/
            if (numReservations == 5)
            {
            printf("All slots are reserved. Cannot make a new reservation.\n");
            return;
            }
            printf("\nReserve a Slot\n");
            printf("---------------------------------------\n");
            printf("Available slots:\n\n");
            printf("2pm    to 2:30pm    Press(1)\n");
            printf("2:30pm to 3pm       Press(2)\n");
            printf("3pm    to 3:30pm    Press(3)\n");
            printf("4pm    to 4:30pm    Press(4)\n");
            printf("4:30pm to 5pm       Press(5)\n");
            printf("---------------------------------------\n\n");
            printf("Enter patient ID: ");
            u32 id;
            u8 slot;
            s8 ind = -1;
            scanf("%ld", &id);
            for (u8 i = 0; i < numPatients; i++)
            {
            if (Patients[i].id == id)
                {
                ind = i;
                break;
                }
            }
            if (ind == -1)
            {
            printf("Patient ID not found. Cannot make a reservation.\n");
            return;
            }
            printf("Enter slot number Press(1)to(5) : ");
            scanf("%d", &slot);

            if ((slot < 1)|(slot > 5))
            {
            printf("Invalid slot number. Cannot make a reservation.\n");
            return;
            }
            // Check if slot is already reserved
            for (u8 i = 0; i < numReservations; i++)
            {
                if (reservations[i].slot == slot)
                {
                printf("Slot is already reserved. Cannot make a reservation.\n");
                return;
                }
            }

            Reservation newReservation;
            newReservation.slot = slot;
            newReservation.patientID = patientID;
            reservations[numReservations] = newReservation;
            numReservations++;
            printf("Reservation made successfully.\n\n");
        break;
    case 4:/*Cancel Reservation*/
            printf("\nCancel Reservation\n");
            printf("------------------\n");
            printf("Enter patient ID: ");
            u32 pat_ID;
            u8  iex = -1;
            scanf("%ld", &pat_ID);
            // Find reservation index based on patient ID
            for (u8 i = 0; i < numReservations; i++)
                {
                if (reservations[i].patientID == pat_ID)
                    {
                        iex = i;
                        break;
                    }
                }
            if (iex == -1)
            {
                printf("Patient ID not found. Cannot cancel reservation.\n");
                return;
            }

          // Remove reservation from the list
            for (int i = iex; i < numReservations - 1; i++) {
                reservations[i] = reservations[i + 1];
            }
            numReservations--;
            printf("Reservation cancelled successfully.\n");
        break;
    }
}
void UserMode (u8 pressed)
{
    switch(pressed)
    {
    case 1:/*View Patient Record */
            printf("\nView Patient Record\n");
            printf("-------------------\n");
            printf("Enter patient ID: ");
            u32 patientID;
            u8  index = -1;
            scanf("%ld", &patientID);
            // Find patient index based on ID
            for (u8 i = 0; i < numPatients; i++)
            {
                if (Patients[i].id == patientID)
                {
                    index = i;
                    break;
                }
            }

            if (index == -1)
            {
            printf("Patient ID not found. Cannot view patient record.\n");
            return;
            }

            Patient_t *patient = &Patients[index];
            printf("Patient Name: %s\n", patient->name);
            printf("Patient Age: %d\n", patient->age);
            printf("Patient Gender: %s\n", patient->gender);
        break;
    case 2:/*View Todays Reservations*/
            printf("\nToday's Reservations\n");
            printf("--------------------\n");
            if (numReservations == 0)
                {
                printf("No reservations for today.\n");
                return;
                }

            for (int i = 0; i < numReservations; i++) {
                printf("Slot %d: Patient ID %d\n", reservations[i].slot, Patients[i].id);
            }
        break;
    }
}

/*
            for(u8 i=0;i<numReservations;i++)
            {
                if(iex == reservations[i].patientID)
                {
                    reservations[i] = reservations[i+1];
                }
            }*/
            /*
            for (int i = iex; i < numReservations - 1; i++)
            {
                reservations[i] = reservations[i + 1];
            }*/
