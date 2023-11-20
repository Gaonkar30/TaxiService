#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_DRIVERS 50
#define MAX_PASSENGERS 50
#define MAX_QUEUE_SIZE 50

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

struct RideRequest
{
    char passengerName[50];
    double latitude;
    double longitude;
    double destinationLatitude;
    double destinationLongitude;
};

struct Queue
{
    struct RideRequest requests[MAX_QUEUE_SIZE];
    int front, rear;
};

// Function to initialize a queue
void initializeQueue(struct Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue *q)
{
    return (q->front == -1 && q->rear == -1);
}

// Function to enqueue a ride request
void enqueue(struct Queue *q, struct RideRequest request)
{
    if (isQueueEmpty(q))
    {
        q->front = 0;
        q->rear = 0;
    }
    else
    {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    }

    q->requests[q->rear] = request;
}

// Function to dequeue a ride request
struct RideRequest dequeue(struct Queue *q)
{
    struct RideRequest dequeuedRequest = q->requests[q->front];

    if (q->front == q->rear)
    {
        // Last element in the queue
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }

    return dequeuedRequest;
}

// Function to add a new driver to the system
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

// Function to add a new passenger to the system
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

// Function to complete a ride by updating driver availability
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

// Function to handle ride requests and assign the nearest available driver using a queue
void requestRide(struct Driver drivers[], int numDrivers, struct Passenger passengers[], int numPassengers, struct Queue *rideQueue)
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

            // Enqueue the ride request
            struct RideRequest newRequest;
            strcpy(newRequest.passengerName, passName);
            newRequest.latitude = passengers[i].latitude;
            newRequest.longitude = passengers[i].longitude;
            newRequest.destinationLatitude = passengers[i].destinationLatitude;
            newRequest.destinationLongitude = passengers[i].destinationLongitude;

            enqueue(rideQueue, newRequest);

            printf("Ride request added to the queue. A driver will be assigned shortly.\n");
            return;
        }
        else
        {
            printf("Passenger not found in the database\n");
        }
    }
}

// Function to cancel a ride request
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

// Function to calculate ride fare based on distance
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
    struct Queue rideQueue;
    initializeQueue(&rideQueue);

    int numDrivers = 0;
    int numPassengers = 0;
    int choice;

    do
    {
        printf("\n** Ride-Sharing Service Simulation Menu **\n");
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
            requestRide(drivers, numDrivers, passengers, numPassengers, &rideQueue);
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
