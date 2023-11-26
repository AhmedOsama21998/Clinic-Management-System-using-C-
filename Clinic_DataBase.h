/*
 * Clinic_DataBase.h
 *
 * Clinic Management System
 *
 *  Created on: Jun 23, 2023
 *      Author: Ahmed Osama Metwally
 */
#ifndef CLINIC_DATABASE_H_INCLUDED
#define CLINIC_DATABASE_H_INCLUDED

#define MAX_PATIENTS 3
#define RESERVATIONS 5
#define PASS         1234
typedef struct
{
    u8 name  [50];
    u8 age;
    u8 gender[10];
    u32 id;
} Patient_t;

typedef struct
{
    u8 slot;
    u32 patientID;
} Reservation;

Reservation reservations[RESERVATIONS];
Patient_t   Patients[MAX_PATIENTS];

#endif // CLINIC_DATABASE_H_INCLUDED
