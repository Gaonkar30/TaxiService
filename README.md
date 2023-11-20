# Ride-Sharing Service Simulation

This C program simulates a ride-sharing service with functionalities like adding drivers and passengers, requesting rides, completing rides, canceling rides, and calculating ride fares. The implementation includes the use of a queue to manage ride requests and structures to represent drivers, passengers, and ride requests.

## Program Structure

### Data Structures
- **Driver Structure**
  - `name`: Driver's name
  - `carDetails`: Details of the driver's car
  - `availability`: Availability status (1 for available, 0 for unavailable)
  - `latitude`, `longitude`: Location coordinates of the driver

- **Passenger Structure**
  - `name`: Passenger's name
  - `latitude`, `longitude`: Location coordinates of the passenger
  - `destinationLatitude`, `destinationLongitude`: Destination coordinates of the passenger

- **RideRequest Structure**
  - `passengerName`: Name of the passenger making the ride request
  - `latitude`, `longitude`: Location coordinates of the ride request
  - `destinationLatitude`, `destinationLongitude`: Destination coordinates of the ride request

- **Queue Structure**
  - `requests`: Array of ride requests
  - `front`, `rear`: Indices for tracking the front and rear of the queue

### Functions
- `initializeQueue`: Initializes a queue.
- `isQueueEmpty`: Checks if the queue is empty.
- `enqueue`: Enqueues a ride request.
- `dequeue`: Dequeues a ride request.
- `addDriver`: Adds a new driver to the system.
- `addPassenger`: Adds a new passenger to the system.
- `completeRide`: Completes a ride by updating the driver's availability.
- `haversine`: Calculates the Haversine distance between two points.
- `requestRide`: Handles ride requests and assigns the nearest available driver using a queue.
- `cancelRide`: Cancels a ride request.
- `calculateRideFare`: Calculates ride fare based on the distance.

## How to Use

1. **Adding a Driver**
   - Select option 1 from the menu.
   - Enter the driver's name, car details, latitude, and longitude.

2. **Adding a Passenger**
   - Select option 2 from the menu.
   - Enter the passenger's name.

3. **Requesting a Ride**
   - Select option 3 from the menu.
   - Enter the passenger's name, latitude, and longitude.
   - The ride request will be added to the queue, and a driver will be assigned shortly.

4. **Completing a Ride**
   - Select option 4 from the menu.
   - Enter the driver's name to mark the ride as completed.

5. **Canceling a Ride**
   - Select option 5 from the menu.
   - Enter the passenger's name to cancel a ride request.

6. **Calculating Ride Fare**
   - Select option 6 from the menu.
   - Enter the passenger's name to calculate the ride fare for completed rides.

7. **Exiting the Program**
   - Select option 7 from the menu to exit the program.

Note: Ensure to replace the placeholder fare and distance calculation logic with the desired logic for your ride-sharing service.

Feel free to customize the base fare and distance-based fare calculation according to your specific requirements.
