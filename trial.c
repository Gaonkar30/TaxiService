#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// including all the necessary libra
#define MAX_DRIVERS 50
#define MAX_PASSENGERS 50

struct Driver
{
    char name[50];
    char carDetails[50];
    int availability;
    double latitude;
    double longitude;
};

struct Passenger
{
    char name[50];
    double latitude;
    double longitude;
    double destinationLatitude;
    double destinationLongitude;
};

void addDriver(struct Driver drivers[], int *numDrivers)
{
    if (*numDrivers < MAX_DRIVERS)
    {
        printf("Enter driver name: ");
        scanf("%s", drivers[*numDrivers].name);
        printf("Enter car details: ");
        scanf("%s", drivers[*numDrivers].carDetails);
        printf("Enter driver latitude: ");
        scanf("%lf", &drivers[*numDrivers].latitude);
        printf("Enter driver longitude: ");
        scanf("%lf", &drivers[*numDrivers].longitude);
        drivers[*numDrivers].availability = 1; // 1 indicates the driver is available
        (*numDrivers)++;
        printf("Driver added successfully!\n");
    }
    else
    {
        printf("Maximum number of drivers reached.\n");
    }
}

void addPassenger(struct Passenger passengers[], int *numPassengers)
{
    if (*numPassengers < MAX_PASSENGERS)
    {
        printf("Enter passenger name: ");
        scanf("%s", passengers[*numPassengers].name);
        (*numPassengers)++;
        printf("Passenger added successfully!\n");
    }
    else
    {
        printf("Maximum number of passengers reached.\n");
    }
}

void completeRide(struct Driver drivers[], int numDrivers, struct Passenger passengers[], int numPassengers)
{
    if (numDrivers == 0 || numPassengers == 0)
    {
        printf("Cannot complete a ride. Insufficient drivers or passengers.\n");
        return;
    }

    printf("Enter driver name: ");
    char driverName[50];
    scanf("%s", driverName);

    for (int i = 0; i < numDrivers; i++)
    {
        if (strcmp(drivers[i].name, driverName) == 0 && drivers[i].availability == 0)
        {
            printf("Ride completed successfully!\n");
            drivers[i].availability = 1;
            return;
        }
    }

    printf("Driver not found or the ride is not completed.\n");
}

// Function to calculate the Haversine distance between two points
double haversine(double lat1, double lon1, double lat2, double lon2)
{
    // Radius of the Earth in kilometers
    double R = 6371.0;

    // Convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Calculate differences
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Haversine formula
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Calculate distance
    double distance = R * c;

    return distance;
}

void requestRide(struct Driver drivers[], int numDrivers, struct Passenger passengers[], int numPassengers)
{
    if (numDrivers == 0 || numPassengers == 0)
    {
        printf("Cannot request a ride. Insufficient drivers or passengers.\n");
        return;
    }

    printf("Enter the passenger name who requires a ride: \n");
    char passName[80];
    scanf("%s", passName);
    int driverAssigned = 0;

    for (int i = 0; i < numPassengers; i++)
    {
        if (strcmp(passengers[i].name, passName) == 0)
        {
            printf("Passenger found\n");
            printf("Enter passenger latitude: \n");
            scanf("%lf", &passengers[i].latitude);
            printf("Enter passenger longitude: \n");
            scanf("%lf", &passengers[i].longitude);
            printf("Enter passenger destination latitude: \n");
            scanf("%lf", &passengers[i].destinationLatitude);
            printf("Enter passenger destination longitude: \n");
            scanf("%lf", &passengers[i].destinationLongitude);

            for (int j = 0; j < numDrivers; j++)
            {
                if (drivers[j].availability == 1)
                {
                    double distance = haversine(passengers[i].latitude, passengers[i].longitude,
                                                drivers[j].latitude, drivers[j].longitude);

                    printf("Distance between passenger and driver %s: %.2lf km\n", drivers[j].name, distance);

                    // You can adjust the distance threshold as needed
                    if (distance < 10.0) // Assuming a threshold of 10 km
                    {
                        printf("Ride request successful!\n");
                        printf("Assigned driver: %s\n", drivers[j].name);
                        drivers[j].availability = 0;
                        driverAssigned = 1;
                        break;
                    }
                }
            }

            if (driverAssigned == 0)
            {
                printf("No driver available within the specified distance at this moment.\n");
            }
        }
        else
        {
            printf("Passenger not found in the database\n");
        }
    }
}

void cancelRide(struct Driver drivers[], int numDrivers, struct Passenger passengers[], int numPassengers)
{
    printf("Enter passenger name: ");
    char passengerName[50];
    scanf("%s", passengerName);

    for (int i = 0; i < numPassengers; i++)
    {
        if (strcmp(passengers[i].name, passengerName) == 0)
        {
            if (passengers[i].destinationLongitude == 0)
            {
                printf("Ride request canceled successfully!\n");
            }
            else
            {
                printf("Cannot cancel the ride. The ride is already in progress.\n");
            }
            passengers[i].destinationLongitude = 0;
            passengers[i].destinationLongitude = 0;
            return;
        }
    }

    printf("Passenger not found or no ride request to cancel.\n");
}

void calculateRideFare(struct Driver drivers[], int numDrivers, struct Passenger passengers[], int numPassengers)
{
    printf("Enter passenger name: ");
    char passengerName[50];
    scanf("%s", passengerName);

    for (int i = 0; i < numPassengers; i++)
    {
        if (strcmp(passengers[i].name, passengerName) == 0 && passengers[i].destinationLongitude != 0)
        {
            double distance = haversine(passengers[i].latitude, passengers[i].longitude,
                                        passengers[i].destinationLatitude, passengers[i].destinationLongitude);
                    double baseFare = 40.0; // Replace with your base fare logic
            double fare = baseFare + (distance * 7.0); // Replace with your distance-based fare logic
            printf("Ride fare for %s: Rs.%.2lf\n", passengerName, fare);
            return;
        }
    }

    printf("Passenger not found or no completed ride to calculate fare.\n");
}

int main()
{
    struct Driver drivers[MAX_DRIVERS];
    struct Passenger passengers[MAX_PASSENGERS];
    int numDrivers = 0;
    int numPassengers = 0;
    int choice;

    do
    {
        printf("\n*** Ride-Sharing Service Simulation Menu ***\n");
        printf("1. Add a Driver\n");
        printf("2. Add a Passenger\n");
        printf("3. Request a Ride\n");
        printf("4. Complete a Ride\n");
        printf("5. Cancel a Ride\n");
        printf("6. Calculate Ride Fare\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addDriver(drivers, &numDrivers);
            break;
        case 2:
            addPassenger(passengers, &numPassengers);
            break;
        case 3:
            requestRide(drivers, numDrivers, passengers, numPassengers);
            break;
        case 4:
            completeRide(drivers, numDrivers, passengers, numPassengers);
            break;
        case 5:
            cancelRide(drivers, numDrivers, passengers, numPassengers);
            break;
        case 6:
            calculateRideFare(drivers, numDrivers, passengers, numPassengers);
            break;
        case 7:
            printf("Exiting the program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 7);

    return 0;
}
