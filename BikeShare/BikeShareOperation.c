#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define N 4000



/**
 * Trip Structure.
 */
typedef struct Trip_struct{
    char membershipType[12];
    int startStationId,
            endStationId,
            bikeId,
            duration,
            startHr,
            startMin;
}Trip;
/**
 * Busy Station Structure.
 */
typedef struct busyStation{
    int stationId,count;
}busyStation;
/**
 * Bike Structure
 */
typedef struct Bike_struct{
    char maintenanceFlag  ;
    int bikeId, endStationId;
    int numTrips, totalDuration;
    float totalMinutes;
}Bike;
/**
 * Small Trip Structure.
 */
typedef struct smallTrip_struct{
    int startStationId,
            numTrips,
            bikeId;
}SmallTrips;




/**Prototypes for the Menus*/
void tripMetricMenu();
void displayMainMenu();
void metricDisplayOptionList();
void displayPrintMenu();
void tripMetricControl(int numOfRows,Trip *tripPtr,Bike *bikeIdPtr);
void printMenuControl(int numOfRows,Trip *tripPtr,Bike *bikePtr);

/**Prototypes for Metric Functions*/
Trip *readTripData(int *numOfRows);
Bike  *bikesInfo(int numOfRows,Trip *tripPtr);
void averageNumTrips(int numOfRows);
int averageNumTripsCal(int numOfRows);
void hourLargestTrip(int numOfRows, Trip *tripPtr);
int hourLargestTripCal(int numOfRows, Trip *tripPtr);
void reportTripsCountEachHour(int numOfRows, Trip *tripPtr);
void reportTripsCountEachHourCal(int numOfRows, Trip *tripPtr,int *dup);
void averageTripsDuration(int numOfRows,Trip *tripPtr);
void averageTripsDurationCal(int numOfRows,Trip *tripPtr,long double *a, long double  *b);
void longestTripDuration(int numOfRows,Trip *tripPtr);
void longestTripDurationCal(int numOfRows,Trip *tripPtr,int *durationMs,int *durationMin);
void busiestSS(int numOfRows,Trip *tripPtr);
void busiestSSCal(int numOfRows, Trip *tripPtr,busyStation *stationPtr);
void busiestES(int numOfRows, Trip *tripPtr);
void busiestESCal(int numOfRows, Trip *tripPtr, busyStation *stationPtr);
void percentageTrips(int numOfRows,Trip *tripPtr);
void percentageTripCal(int numOfRows,Trip *tripPtr,double *p1, double *p2);
void bikesLongestDuration(Bike *bikeIdPtr);
void bikesEndStation(Bike *bikePtr);
void bikeMostTrips(Bike *bikeIdPtr);
void bikeSmallTrips(Bike *bikeIdPtr);
int bikeSmallTripsCal(Bike *bikeIdPtr);
void listSmallTrips(int numOfRows,Trip *tripPtr,Bike *bikeIdPtr);
void smallList(int numOfRows,Trip *tripPtr,Bike *bikeIdPtr,SmallTrips *smallTripsPtr);
void smallListTripsPrint(int numOfRows,Bike *bikeIdPtr,SmallTrips *smallTripsPtr);

/**Prototypes for functions set Bike values*/
void setBikesTotalDuration(int numOfRows, Trip *tripPtr, Bike *bikeIdPtr);
void setBikeEndStationId(int numOfRows, Trip *tripPtr, Bike *bikeIdPtr);
void setBikeTrips(int numOfRows, Trip *tripPtr, Bike *bikeIdPtr);

/**Prototypes for initialize functions*/
void initializeSmallTripsList(int numOfRows,SmallTrips *smallTripsPtr);
void initializePtrValues(busyStation *stationPtr);
void initializeBikeIds(Bike *bikePtr);
void emptyBikeValues(Bike *bikePtr);

/**Prototypes for output to file functions for Run Metrics*/
void outputToFile1(int toOutPut);
void outputToFile(int  toOutPut);
void outputToFile3(int numOfRows, Trip *tripPtr,int *result);
void outputToFile4(long double a, long double b );
void outputToFile5(int a, int b);
void outputToFile6(busyStation *busiestStartPtr);
void outputToFile7(busyStation *busiestEndPtr);
void outputToFile8(const double p1, const double p2);
void outputToFile9(Bike *bikeIdPtr);
void outputToFile10(Bike *bikeIdPtr);
void outputToFile11(Bike *bikeIdPtr);
void outputToFile12(int result);
void outputToFile13(int numOfRows,Bike *bikeIdPtr,SmallTrips *smallTripsPtr);

/**Prototypes for qsort() functions*/
int comparatorDescending(const void *p, const void *q);
int startStationDescendingComparator(const void *p, const void *q);
int busiestStartStationDescending(const void *p, const void *q);
int endStationDescendingComparator(const void *p, const void *q);
int memberTypeDescending(const void *p, const void *q);
int bikeIdComparator(const void *p, const void *q);
int bikeTotalDurationDescendingComparator(const void *p, const void *q);
int bikeNumTripsDescendingComparator(const void *p, const void *q);
int bikeNumTripsAscendingComparator(const void *p, const void *q);
int bikeIdDescending(const void *p, const void *q);

/**Prototypes for Print All Trip Data functions*/
void printTripData(int numOfRows, Trip *tripPtr);
void tripDataToScreen(int numOfRows,Trip *tripPtr);
void tripDataToOutput(int numOfRows, Trip *tripPtr);

/**Prototypes for Print All the Bike Inventory*/
void printBikeInventory(Bike *bikePtr);
void bikeInventoryOutput(Bike *bikePtr);
void setBikesAttributes(int numOfRows,Trip *tripPtr,Bike *bikePtr);
void printBikeInventoryToScreen(Bike *bikePtr);




/** Prototypes for CEO Report functions*/
void printCEOReport(int numOfRows, Trip *tripPtr,Bike *bikePtr);
void printMetric3(int numOfRows,Trip *tripPtr,FILE **filePtr);
void printMetric4(int numOfRows,Trip *tripPtr,FILE **filePtr);
void printMetric5(int numOfRows,Trip *tripPtr,FILE **filePtr);
void printMetrics6(int numOfRows,Trip *tripPtr,FILE **filePtr);
void printMetric7(int numOfRows,Trip *tripPtr,FILE **filePtr);
void printMetric8(int numOfRows,Trip *tripPtr,FILE **filePtr);
void printMetric9(Bike *bikeIdPtr,FILE **filePtr);
void printMetric10(Bike *bikeIdPtr,FILE **filePtr);
void printMetric11(Bike *bikeIdPtr,FILE **filePtr);
void printMetric12(Bike *bikeIdPtr,FILE **filePtr);
void printMetric13(int numOfRows,Trip *tripPtr,Bike *bikeIdPtr,FILE **filePtr);

/**Prototypes for Print one bike functions*/
int bikeContainCheck(Bike *bikePtr,int userInPut);
void printOneBike(Bike *bikePtr);
void printOneBikeCal(int userInPut, Bike *bikePtr);
void printOneBikeOutput(Bike *bikePtr, int userInput);

/**Prototypes for Bikes flag for maintenance function*/
void bikesForMaintenance(Bike *bikePtr);

/** Prototypes for Update Bike inventory functions*/
void updateBikePrompt();
void updateBike(Bike *bikePtr);
void addBike(Bike *bikePtr);
void addBikeCal(int bikeID,Bike *bikePtr);
int bikeId();
int endStationId();
int numTrips();
int totalDuration();
void removeBike(Bike *bikePtr);
void removeBikeCal(int position, Bike *bikePtr);




/**
 * Display main menu.
 * Main function control the flow of the program.
 * @param argc command line arguments.
 * @param argv command line arguments.
 * @return 0
 */
int main(int argc, char* argv[]) {
    int  numOfRows,userChoice,readInputValid=0;
    char inBuf[20];
    Trip *tripPtr;
    Bike *bikePtr;
    do{
        displayMainMenu();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                printf("Reading Trip Data: \n");
                tripPtr=readTripData(&numOfRows);
                bikePtr = bikesInfo(numOfRows,tripPtr);
                setBikesAttributes(numOfRows,tripPtr,bikePtr);
                readInputValid=1;
                break;
            case 2:
                if(readInputValid==0){printf("Please choose option 1 before continuing\n");}
                else{
                    tripMetricControl(numOfRows,tripPtr,bikePtr);
                }
                break;
            case 3:
                if(readInputValid==0){printf("Please choose option 1 before continuing\n");}
                else{
                    printf("Print menu\n");
                    printMenuControl(numOfRows,tripPtr,bikePtr);}
                break;
            case 4:
                if(readInputValid==0){printf("Please choose option 1 before continuing\n");}
                else{
                    printf("Flag Bikes for Maintenance\n");
                    bikesForMaintenance(bikePtr); }
                break;
            case 5:
                if(readInputValid==0){printf("Please choose option 1 before continuing\n");}
                else{
                    printf("Updating Bike Inventory:\n");
                    updateBike(bikePtr);}
                break;
            case 6:
                printf("EXIT.\n");
                free(tripPtr);
                free(bikePtr);
                exit(0);
            default:
                printf("Please choose the right choice.\n");
        }
        printf("\n-----------------------------------------------------\n\n");
    }while(userChoice != 6);
    return 0;
}
/**
 * Prompt messages for the when open the program.
 */
void displayMainMenu(){
    printf("Main menu: \n");
    printf("1 - Read Trip Data\n");
    printf("2 - Run Metrics Menu\n");
    printf("3 - Print menu\n");
    printf("4 - Flag Bikes for Maintenance\n");
    printf("5 - Update Bike Inventory\n");
    printf("6 - Quit\n");
    printf("Enter the number for the choice you want to open: \n");
}
/**
 * Prompt messages for Run Metrics.
 */
void tripMetricMenu(){
    printf("\n\n");
    printf("\n----------------Trip--------------------\n");
    printf("1  - Average number of trips per hour\n");
    printf("2  - The hour with largest number of trips\n");
    printf("3  - A report of the count of trips in each hour\n");
    printf("4  - Average duration of the trips (in both milliseconds and minutes)\n");
    printf("5  - The trip with the longest duration (in both milliseconds and minutes)\n");
    printf("6  - The 5 busiest starting stations (that had the largest number of trips in the day)\n");
    printf("7  - The 5 busiest ending stations (that had the largest number of trips in the day)\n");
    printf("8  - The percentage of trips in each membership type\n");
    printf("\n----------------Bike--------------------\n");
    printf("9  - The 10 bikes with the longest duration in minutes\n");
    printf("10 - Where the 10 bikes above are located at the end of the day\n");
    printf("11 - The 10 bikes with the most trips\n");
    printf("12 - How many bikes were only used for 2 or less trips\n");
    printf("13 - For the bikes with 2 or less trips, make a list of the start station IDs and the number of trips for each of these stations\n");
}
/**
 * Prompt messages for Metrics Menu.
 */
void metricDisplayOptionList(){
    printf("1 - To print the metric results on screen\n");
    printf("2 - To write the metric results to an output file\n");
    printf("Please choose 1 or 2\n");
}
/**
 * Prompt messages for print menu.
 */
void displayPrintMenu(){
    printf("1 - Print All the Trip Data\n");
    printf("2 - Print All the Bike Inventory\n");
    printf("3 - Print the CEO Report\n");
    printf("4 - Print one Bike\n");
    printf("Enter the number for the choice you want to open:\n");
}


/**
 * This function will set the values in struct station array to 0.
 * @param *stationPtr is the pointer that point to the station array passing in.
 */
void initializePtrValues(busyStation *stationPtr){
    int i=0;
    for(i=0;i<N;i++){
        stationPtr[i].stationId=0;
        stationPtr[i].count=0;
    }
}


/**
 *This function will read in the input file.
 */
Trip *readTripData(int *numOfRows){
    Trip *tripPtr;
    FILE *inputPt;
    int i;
    char inBuf[100],inputFileName[25], fileName[25];
    printf("Please enter the name of your's input file\n");
    fgets(inputFileName,25,stdin);
    sscanf(inputFileName,"%s",fileName);

    if((inputPt = fopen(fileName,"r"))== NULL){
        printf("Invalid Input File.\n");
        exit(0);
    }else{printf("Valid Input File.\n");}

    fgets(inBuf,100,inputPt);
    sscanf(inBuf, "%d", numOfRows);


    tripPtr  =(Trip*) malloc(*numOfRows * sizeof(Trip));

    for( i =0;i<*numOfRows;++i){
        fgets(inBuf,100,inputPt);
        sscanf(inBuf,"%s %d %d %d %d %d %d",tripPtr[i].membershipType, &tripPtr[i].startStationId, &tripPtr[i].endStationId, &tripPtr[i].bikeId, &tripPtr[i].duration, &tripPtr[i].startHr, &tripPtr[i].startMin);
    }

    fclose(inputPt);
    return tripPtr;
}
/**
 *Sorting unique bike IDs into bike struct.
 * @param numOfRows is total number of bike IDs.
 * @param tripPtr is use to access bikeID in Trip struct.
 * @return bikePtr that point to the unique bikeId.
 */
Bike  *bikesInfo(int numOfRows,Trip *tripPtr){
    int i,j=0;
    Bike *bikePtr;
    bikePtr=malloc(N* sizeof(Bike));
    initializeBikeIds(bikePtr);
    qsort(tripPtr,numOfRows, sizeof(Trip),bikeIdComparator);
    for(i=0;i<numOfRows-1;i++){
        if(tripPtr[i].bikeId != tripPtr[i+1].bikeId){
            bikePtr[j].bikeId=tripPtr[i].bikeId;
            j++;
        }
    }
    bikePtr[j].bikeId=tripPtr[numOfRows-1].bikeId;
    return bikePtr;
}

/**
 * This function control the flow of Run Metrics Menu.
 */
void tripMetricControl(int numOfRows,Trip *tripPtr,Bike *bikeIdPtr){
    int  userChoice=0,valid=0;
    char inBuf[20];
    do{
        tripMetricMenu();
        printf("Enter your choice here \n");
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);

        switch (userChoice){
            case 1:
                printf("\nAverage number of trips per hour: \n");
                averageNumTrips(numOfRows);
                valid=1;
                break;
            case 2:
                printf("\nThe hour with largest number of trips:\n");
                hourLargestTrip(numOfRows,tripPtr);
                valid=1;
                break;
            case 3:
                printf("\nA report of the count of trips in each hour:\n");
                reportTripsCountEachHour(numOfRows,tripPtr);
                valid=1;
                break;
            case 4:
                printf("\nAverage duration of the trips (in both milliseconds and minutes)\n");
                averageTripsDuration(numOfRows,tripPtr);
                valid=1;
                break;
            case 5:
                printf("\nThe trip with the longest duration (in both milliseconds and minutes)\n");
                longestTripDuration(numOfRows,tripPtr);
                valid=1;
                break;
            case 6:
                printf("\nThe 5 busiest starting stations (that had the largest number of trips in the day)\n");
                busiestSS(numOfRows,tripPtr);
                valid=1;
                break;
            case 7:
                printf("\nThe 5 busiest ending stations (that had the largest number of trips in the day)\n");
                busiestES(numOfRows, tripPtr);
                valid=1;
                break;
            case 8:
                printf("\nThe percentage of trips in each membership type\n");
                percentageTrips(numOfRows,tripPtr);
                valid=1;
                break;
            case 9:
                printf("\nThe 10 bikes with the longest duration in minutes\n");
                bikesLongestDuration(bikeIdPtr);
                valid =1;
                break;
            case 10:
                printf("\nWhere the 10 bikes above are located at the end of the day\n");
                bikesEndStation(bikeIdPtr);
                valid =1;
                break;
            case 11:
                printf("\nThe 10 bikes with the most trips\n");
                bikeMostTrips(bikeIdPtr);
                valid =1;
                break;
            case 12:
                printf("\nHow many bikes were only used for 2 or less trips\n");
                bikeSmallTrips(bikeIdPtr);
                valid =1;
                break;
            case 13:
                printf("\nBikes with 2 or less trips\n");
                listSmallTrips(numOfRows,tripPtr,bikeIdPtr);
                valid=1;
                break;
            default:
                printf("Invalid input\n");
        }}while(valid == 0);
}


/***************************Functions of Metrics for Trip****************************************/

/**
 * This function control the flow of fiding out the average number of trips per hour.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 */
void averageNumTrips(int numOfRows) {
    int userChoice=0,valid=0;
    char inBuf[20];
    int avgTripsPerHour= averageNumTripsCal(numOfRows);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                printf("Average number of trips per hour is: %d\n", avgTripsPerHour);
                valid =1;
                break;
            case 2:
                outputToFile1(avgTripsPerHour);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}



/**
 * This function will calculate the average number of trips per hour.
 * @param numOfRows is the total number of trips
 * @return the average number of trips
 */
int averageNumTripsCal(int numOfRows){
    int avgTripsPerHour= numOfRows /24;
    return avgTripsPerHour;
}

/**
 * This function control the flow of finding out which hour has the largest number of trips.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 */
void hourLargestTrip(int numOfRows, Trip *tripPtr){
    int result=0,userChoice=0,valid=0;
    char inBuf[20];
    result=hourLargestTripCal(numOfRows,tripPtr);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                printf("The hour with largest number of trips is: %d\n", result);
                valid =1;
                break;
            case 2:
                outputToFile(result);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}

/**
 * This function will calculate the see which hour has the largest number of trips.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 * @return hour with largest trip number of trips.
 */
int hourLargestTripCal(int numOfRows, Trip *tripPtr){
    int i,j,hourLargestTrip,count,tempHour,tempCount;
    int *arrHours;
    arrHours = malloc(numOfRows*sizeof(int));
    /**Storing the trip hours into the array*/
    for(i=0;i<numOfRows;i++){
        arrHours[i]=tripPtr[i].startHr;
    }
    hourLargestTrip=0;
    count=0;
    for( i=0;i<numOfRows;i++){
        tempHour=arrHours[i];
        tempCount=0;
        for( j=0; j<numOfRows;j++){
            if(arrHours[j]==tempHour){
                tempCount++;}
        }
        if(tempCount>count){
            hourLargestTrip=tempHour;
            count=tempCount;
        }
    }
    free(arrHours);
    return hourLargestTrip;
}

/**
 * This function control the flow of finding out the count of trips in each hour.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 */
void reportTripsCountEachHour(int numOfRows, Trip *tripPtr){
    int userChoice=0,valid=0,i,*result;
    char inBuf[20];
    result= malloc(numOfRows*sizeof(int));
    reportTripsCountEachHourCal(numOfRows,tripPtr,result);

    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                printf("Report of Trips Count in Each Hour:\n");
                for(i=0;i<numOfRows;i++){
                    if(result[i] != 0)
                    {
                        printf("Hour : %d - %d Trips\n", tripPtr[i].startHr, result[i]);
                    }
                }
                valid =1;
                break;
            case 2:
                outputToFile3(numOfRows,tripPtr,result);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
    free(result);
}
/**
 * This function will calculate the count of trips in each hour.
 * @param numOfRows is the total number of trips
 * @param tripPtr is pointing to the data in trip list.
 * @param dup is a list that will store the counts of each trips
 */
void reportTripsCountEachHourCal(int numOfRows, Trip *tripPtr,int *dup){
    int i,j,count=0;
    int *hours;
    hours = malloc(numOfRows*sizeof(int));
    /**Storing the trip hours into the array*/
    for(i=0;i<numOfRows;i++){
        hours[i]=tripPtr[i].startHr;
    }
    for(i=0;i<numOfRows;i++){
        dup[i]=-1;
    }
    for(i = 0 ; i < numOfRows;i++){
        count=1;
        for(j=i+1;j<numOfRows;j++){
            if(hours[i]==hours[j]){
                count=count+1;
                dup[j]=0;
            }
        }
        if(dup[i]!=0){
            dup[i]=count;
        }
    }
    free(hours);
}

/**
 * This function control the flow of finding out the average duration of the trips (in both milliseconds and minutes).
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 */
void averageTripsDuration(int numOfRows,Trip *tripPtr){
    int userChoice=0,valid=0;
    long double a,b;
    char inBuf[20];
    averageTripsDurationCal(numOfRows,tripPtr,&a,&b);

    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                printf("Average Trips Duration in Millisecond: %.0Lf  ms\n",a);
                printf("Average Trips Duration in Minutes    : %9.0Lf  min\n",b);
                valid =1;
                break;
            case 2:
                outputToFile4(a,b);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}

/**
 * This function will calculate to see the average duration of the trips (in both milliseconds and minutes).
 * @param numOfRows is total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 * @param a is pointing to value that will be modify with the result of average duration of trips in ms.
 * @param b is pointing to value that will be modify with the result of average duration of trips in min.
 */
void averageTripsDurationCal(int numOfRows,Trip *tripPtr,long double *a, long double  *b){
    long double sumDuration=0;
    int i;
    for(i=0;i<numOfRows;i++){
        sumDuration=sumDuration+tripPtr[i].duration;
    }
    *a=(long double)(sumDuration/numOfRows)*1000;
    *b=(*a/60000)*10;

}
/**
 * This function control the flow of finding the trip with the longest duration (in both milliseconds and minutes).
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 */
void longestTripDuration(int numOfRows,Trip *tripPtr){
    int userChoice=0,valid=0,durationMs,durationMin;
    char inBuf[20];
    longestTripDurationCal(numOfRows,tripPtr,&durationMs,&durationMin);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                printf("Trip with longest Duration: \n");
                printf("\nDuration in MS:\t\t%8d ms\nDuration in Minutes:\t%8d min\n ",durationMs,durationMin);
                valid =1;
                break;
            case 2:
                outputToFile5(durationMs,durationMin);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);

}
/**
 * This function will calculate to see the trip with the longest duration (in both milliseconds and minutes).
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 * @param durationMs is pointing value that will be modify with the result of trip with longest duration in ms.
 * @param durationMin is pointing value that will be modify with the result of trip with longest duration in min.
 */
void longestTripDurationCal(int numOfRows,Trip *tripPtr,int *durationMs,int *durationMin){
    qsort(tripPtr, numOfRows, sizeof(Trip), comparatorDescending);
    *durationMs=tripPtr[0].duration;
    *durationMin=(*durationMs/60000);

}

/**
 * This function will print out the 5 busiest starting stations.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 */
void busiestSS(int numOfRows,Trip *tripPtr){
    int i,userChoice=0,valid=0;
    char inBuf[20];
    busyStation *station = malloc(sizeof(busyStation ) * N );
    initializePtrValues(station);
    busiestSSCal(numOfRows, tripPtr,station);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                for( i =0;i<5;i++){
                    printf("Station ID: %d\tTrips: %3d\n",station[i].stationId,station[i].count);
                }
                valid =1;
                break;
            case 2:
                outputToFile6(station);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
    free(station);
}
/**
 * This function will calculate to see which starting station ID is the busiest.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 * @param stationPtr is pointing to a list that will be store the Start Station Ids & the Number of Trips.
 */
void busiestSSCal(int numOfRows, Trip *tripPtr,busyStation *stationPtr){
    int j=0, i=0,count=0,t,k=0;
    qsort(tripPtr,numOfRows,sizeof(Trip),startStationDescendingComparator);
    for(i=0;i<numOfRows;i++){
        for(j=0;j<numOfRows;j++){
            if(tripPtr[i].startStationId==tripPtr[j].startStationId)
            {
                count =count+1;
            }
        }
        t=i;
        stationPtr[k].stationId=tripPtr[t].startStationId;
        stationPtr[k].count=count;
        i=i+count;
        count = 0;
        k++;
    }
    qsort(stationPtr,N, sizeof(busyStation),busiestStartStationDescending);
}

/**
 * This function will print out the 5 busiest ending stations.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 */
void busiestES(int numOfRows, Trip *tripPtr){
    int i,userChoice=0,valid=0;
    char inBuf[20];
    busyStation *station = malloc(sizeof(busyStation ) * N );
    initializePtrValues(station);
    busiestESCal(numOfRows, tripPtr, station);
    qsort(station,N, sizeof(busyStation),busiestStartStationDescending);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                for( i =0;i<5;i++){
                    printf("End Station ID: %d\tTrips: %3d\n",station[i].stationId,station[i].count);
                }
                valid =1;
                break;
            case 2:
                outputToFile7(station);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
    free(station);
}

/**
 * This function will calculate to see which ending station ID is the busiest.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 * @param stationPtr is pointing to a list that will be store the End Station Ids & the Number of Trips.
 */
void busiestESCal(int numOfRows, Trip *tripPtr, busyStation *stationPtr){
    int j=0, i=0,count=0,t,k=0;
    qsort(tripPtr,numOfRows,sizeof(Trip),endStationDescendingComparator);

    for(i=0;i<numOfRows;i++){
        for(j=0;j<numOfRows;j++){
            if(tripPtr[i].endStationId==tripPtr[j].endStationId)
            {
                count =count+1;
            }
        }
        t=i;
        stationPtr[k].stationId=tripPtr[t].endStationId;
        stationPtr[k].count=count;
        i=i+count;
        count = 0;
        k++;
    }
}

/**
 * This function control the flow of finding the percentage of trips in each membership type.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 */
void percentageTrips(int numOfRows,Trip *tripPtr){
    double percent1,percent2;
    int userChoice=0,valid=0;
    char inBuf[20];
    percentageTripCal(numOfRows,tripPtr,&percent1,&percent2);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                printf("\nCasual:     %.2f%%\n",percent1);
                printf("Registered: %.2f%%\n",percent2);
                valid =1;
                break;
            case 2:
                outputToFile8(percent1,percent2);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}
/**
 * This function calculate the percentage of trips in each membership type.
 * @param numOfRows is total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 * @param p1 is the pointer that will be store the percentage of membership type 1.
 * @param p2 is the pointer that will be store the percentage of membership type 2.
 */
void percentageTripCal(int numOfRows,Trip *tripPtr,double *p1, double *p2){
    int i=0,j,count=0;
    qsort(tripPtr,numOfRows, sizeof(Trip),memberTypeDescending);
    for(j=0;j<numOfRows;j++){
        if(strcmp(tripPtr[i].membershipType,tripPtr[j].membershipType)== 0){
            count++;
        }
    }

    *p1=((double)count/numOfRows)*100;
    *p2=((double)numOfRows-count)/numOfRows*100;
}

/***************************Functions of Metrics for Bike****************************************/

/**
 * This function control the flow of finding out the 10 bikes with the longest duration in minutes.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param bikeIdPtr is pointing to the data in bike list.
 */
void bikesLongestDuration(Bike *bikeIdPtr){
    int i;
    int userChoice=0,valid=0;
    char inBuf[20];

    qsort(bikeIdPtr,N, sizeof(Bike),bikeTotalDurationDescendingComparator);


    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                for(i=0;i<10;i++){
                    printf("Bike ID:  %5d\t\tDuration: %4d minutes\n",bikeIdPtr[i].bikeId,(int)bikeIdPtr[i].totalMinutes);
                }
                valid =1;
                break;
            case 2:
                outputToFile9(bikeIdPtr);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}
/**
 * This function will calculate to see which bikes has the longest trip duration.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 * @param bikeIdPtr is pointing to the data in bike list.
 */
void setBikesTotalDuration(int numOfRows, Trip *tripPtr, Bike *bikeIdPtr){
    int i=0,j=0,durations=0;
    for(i=0;i<N;i++){
        bikeIdPtr[j].totalDuration=0;
        bikeIdPtr[j].totalMinutes=0;
    }
    qsort(bikeIdPtr,N,sizeof(Bike),bikeIdDescending);
    qsort(tripPtr,numOfRows,sizeof(Trip),bikeIdComparator);
    for(i=0;i<numOfRows;i++){
        if(bikeIdPtr[j].bikeId==tripPtr[i].bikeId){
            durations += tripPtr[i].duration;
            bikeIdPtr[j].totalDuration=durations;
            bikeIdPtr[j].totalMinutes=(float)durations/60000;
        }else{
            bikeIdPtr[j].totalDuration=durations;
            bikeIdPtr[j].totalMinutes=(float)durations/60000;
            durations=tripPtr[i].duration;
            j++;}
    }
    emptyBikeValues(bikeIdPtr);
}


/**
 * This function control the flow of finding out where the 10 bikes above are located at the end of the day.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param bikePtr is pointing to the data in bike list.
 */
void bikesEndStation(Bike *bikePtr){
    int i,userChoice=0,valid=0;
    char inBuf[20];
    qsort(bikePtr, N, sizeof(Bike), bikeTotalDurationDescendingComparator);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                for(i=0;i<10;i++){
                    printf("Bike ID: %8d\tLocated At End ID Station: %8d\n", bikePtr[i].bikeId, bikePtr[i].endStationId);}
                valid =1;
                break;
            case 2:
                outputToFile10(bikePtr);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}
/**
 * This function will set the EndStationId for bikes.
 * @param numOfRows is total number of trips
 * @param tripPtr is pointing to the data in trip list.
 * @param bikeIdPtr is pointing to the data in bike list.
 */
void setBikeEndStationId(int numOfRows, Trip *tripPtr, Bike *bikeIdPtr) {
    int i=0, j = 0, tempHour=0, tempMinutes=0 ;
    setBikesTotalDuration(numOfRows, tripPtr, bikeIdPtr);
    qsort(bikeIdPtr,N, sizeof(Bike),bikeTotalDurationDescendingComparator);
    /**Sort out only the top 10 longest duration trips**/
    for(i=0;i<N;i++){
        tempHour=0;
        tempMinutes=0;
        for(j=0;j<numOfRows;j++){
            if(tripPtr[j].bikeId == bikeIdPtr[i].bikeId){
                if(tempHour<tripPtr[j].startHr){
                    tempHour=tripPtr[j].startHr;
                    tempMinutes=tripPtr[j].startMin;
                    bikeIdPtr[i].endStationId=tripPtr[j].endStationId;
                }
                else
                {
                    if(tempHour == tripPtr[i].startHr){
                        if(tempMinutes<tripPtr[j].startMin){
                            bikeIdPtr[i].endStationId=tripPtr[j].endStationId;
                        }}}}
        }
    }
}

/**
 *This function control the flow of finding the 10 bikes with the most trips.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param bikeIdPtr is pointing to the data in bike list.
 */
void bikeMostTrips(Bike *bikeIdPtr){
    int i;
    int userChoice=0,valid=0;
    char inBuf[20];
    qsort(bikeIdPtr,N, sizeof(Bike),bikeNumTripsDescendingComparator);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                for(i=0;i<10;i++){
                    printf("Bike ID:%8d\tNum Trips:%8d\n",bikeIdPtr[i].bikeId,bikeIdPtr[i].numTrips);
                }
                valid =1;
                break;
            case 2:
                outputToFile11(bikeIdPtr);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}
/**
 *This function set the trips for the bikes.
 * @param numOfRows is total number of trips.
 * @param tripPtr is pointing to the data in trip list.
 * @param bikeIdPtr is pointing to the data in bike list.
 */
void setBikeTrips(int numOfRows, Trip *tripPtr, Bike *bikeIdPtr){
    int i,j=0,count=0;
   for(i=0;i<N;i++){
        count=0;
        for(j=0;j<numOfRows;j++){
            if(bikeIdPtr[i].bikeId==tripPtr[j].bikeId){
                count++;
            }
        }
        bikeIdPtr[i].numTrips=count;
    }}


/**
 * This function control the flow of finding how many bikes were only used for 2 or less trips.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is total number of trips
 * @param tripPtr is pointing to the data in trip list.
 * @param bikeIdPtr is pointing to the data in bike list.
 */
void bikeSmallTrips(Bike *bikeIdPtr){
    int result=0, userChoice=0,valid=0;
    char inBuf[20];
    result=bikeSmallTripsCal(bikeIdPtr);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                printf("\nTotal of %d bikes were only used for 2 or less trips\n",result);
                valid =1;
                break;
            case 2:
                outputToFile12(result);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}
/**
 * This function will calculate how many bikes were only used for 2 or less trips.
 * @param numOfRows is the total number of trips
 * @param tripPtr is pointing to the data in trip list.
 * @param bikeIdPtr is pointing to the data in bike list.
 * @return the number of trips with 2 or less trips
 */
int bikeSmallTripsCal(Bike *bikeIdPtr){
    int i,count=0;
    /**tripPtr and bikePtr already in descending order for bikeId*/
    qsort(bikeIdPtr,N, sizeof(Bike),bikeNumTripsAscendingComparator);
    for(i=0;i<N;i++){
        if(bikeIdPtr[i].bikeId != 0 && bikeIdPtr[i].numTrips<=2) {
            count++;
        }
    }
    return count;
}

/**
 * This function control the flow of making a list of start station Ids with 2 or less trips.
 * The user has the option to choose to either display the results on screen or to an output file.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the trip list.
 * @param bikeIdPtr is poiting to the bike list.
 */
void listSmallTrips(int numOfRows,Trip *tripPtr,Bike *bikeIdPtr){
    int userChoice=0,valid=0;
    char inBuf[20];
    SmallTrips *smallTripsPtr=malloc(numOfRows * sizeof(SmallTrips));
    initializeSmallTripsList(numOfRows,smallTripsPtr);
    smallList(numOfRows,tripPtr,bikeIdPtr,smallTripsPtr);
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                smallListTripsPrint(numOfRows,bikeIdPtr,smallTripsPtr);
                valid =1;
                break;
            case 2:
                outputToFile13(numOfRows,bikeIdPtr,smallTripsPtr);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
    free(smallTripsPtr);
}

/**
 * This function will find the start station ID for each bike ID and store it in another list.
 * @param numOfRows is the total number of trips.
 * @param tripPtr is pointing to the trip data, use to get the start station IDs from this.
 * @param bikeIdPtr is pointing to bikes data, use this pointer to get the unique bike Ids.
 * @param smallTripsPtr is list that will contain the Bikes Ids and the Start Station Ids for that bike Bike Id.
 */
void smallList(int numOfRows,Trip *tripPtr,Bike *bikeIdPtr,SmallTrips *smallTripsPtr){
    int i,j,k=0;
    qsort(bikeIdPtr,N, sizeof(Bike),bikeNumTripsDescendingComparator);
    for(i=0;i<N;i++){
        for(j=0;j<numOfRows;j++){
            if(bikeIdPtr[i].bikeId==tripPtr[j].bikeId){
                smallTripsPtr[k].bikeId=tripPtr[j].bikeId;
                smallTripsPtr[k].startStationId=tripPtr[j].startStationId;
                k++;
            }
        }
    }
}

/**
 * This function will display the number of trips,bike Id, start station Id for bikes with 2 orl ess trips.
 * @param numOfRows is total number of bike IDs.
 * @param bikeIdPtr is use to access bikeID in Trip struct.
 * @param smallTripsPtr is pointing to the list of small trips that will be modify in this function.
 */
void smallListTripsPrint(int numOfRows,Bike *bikeIdPtr,SmallTrips *smallTripsPtr){
    int i,j;
    for(i=0;i<N;i++){
        if(bikeIdPtr[i].bikeId != 0 && bikeIdPtr[i].numTrips<=2){
            smallTripsPtr[i].numTrips=bikeIdPtr[i].numTrips;
            printf("\nBike ID: %d Num trips: %d\n",bikeIdPtr[i].bikeId, smallTripsPtr[i].numTrips);
            for(j=0;j<numOfRows;j++){
                if(bikeIdPtr[i].bikeId == smallTripsPtr[j].bikeId){
                    printf("Start Station id: %d\n",smallTripsPtr[j].startStationId);
                }
            }
        }
    }
}

/**
 * This function will initialize the values for smallTrips list to 0
 * @param numOfRows is the total number of trips.
 * @param smallTripsPtr is the data to initialize.
 */
void initializeSmallTripsList(int numOfRows,SmallTrips *smallTripsPtr){
    int i;
    for(i=0;i<numOfRows;i++){
        smallTripsPtr[i].numTrips=0;
        smallTripsPtr[i].bikeId=0;
        smallTripsPtr[i].startStationId=0;
    }
}
/**
 * This function will initialize the values for Bike list to 0.
 * @param bikePtr is the data to initialize.
 */
void initializeBikeIds(Bike *bikePtr){
    int i = 0;
    for(i=0;i<N;i++){
        bikePtr[i].bikeId=0;
        bikePtr[i].endStationId=0;
        bikePtr[i].numTrips=0;
        bikePtr[i].totalDuration=0;
        bikePtr[i].totalMinutes=0;
        bikePtr[i].maintenanceFlag='0';
    }
}



/**
 * This function will let the user choose an option in Print Menu .
 * @param numOfRows is number of trips
 * @param tripPtr is pointing to trips data
 * @param bikePtr is pointing to bikes data
 */
void printMenuControl(int numOfRows, Trip *tripPtr,Bike *bikePtr){
    int userChoice,valid=0;
    char inBuf[10];
    do{
        displayPrintMenu();
        fgets(inBuf,10,stdin);
        sscanf(inBuf,"%d",&userChoice);

        switch(userChoice){
            case 1:
                printf("\nPrint All the Trip Data\n");
                printTripData(numOfRows, tripPtr);
                valid =1;
                break;
            case 2:
                printf("\nPrint All the Bike Inventory\n");

                printBikeInventory(bikePtr);
                valid =1;
                break;
            case 3:
                printf("\nPrint the CEO Report\n");
                printCEOReport(numOfRows,tripPtr,bikePtr);
                valid =1;
                break;
            case 4:
                printf("\nPrint one Bike\n");
                printOneBike(bikePtr);
                valid =1;
                break;
            default:
                printf("Please choose the right choice.\n");
        }
    }while(valid==0);
}
/**
 * This function will print all of trips data to screen or to an outputfile.
 * @param numOfRows is number of trips
 * @param tripPtr is pointing to trips data
 */
void printTripData(int numOfRows, Trip *tripPtr)
{
    int userChoice=0,valid=0;
    char inBuf[20];
    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                tripDataToScreen(numOfRows,tripPtr);
                valid =1;
                break;
            case 2:
                tripDataToOutput(numOfRows,tripPtr);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}

/**
 * This function will display the trip data to screen.
 * @param numOfRows is the total number of trips to loop through.
 * @param tripPtr is pointing to the trip list to display on screen.
 */
void tripDataToScreen(int numOfRows,Trip *tripPtr){
    int i=0;
    for(i=0;i<numOfRows;i++){
        printf("\nMembership Type: %10s\t\tStart Station Id: %-5d\t\tEnd Station Id: %-5d\t\tBike Id: %-5d\n",tripPtr[i].membershipType, tripPtr[i].startStationId, tripPtr[i].endStationId, tripPtr[i].bikeId);
        printf("Duration: %15d ms\t\tHour: %2d\t\t\tMinute: %2d\n\n", tripPtr[i].duration, tripPtr[i].startHr, tripPtr[i].startMin);
    }

}


/**
 * This function will print out all the bike in the inventory.
 * @param bikePtr is pointing to the bike inventory that ill be printed out.
 */
void printBikeInventory(Bike *bikePtr){
    int userChoice=0,valid=0;
    char inBuf[20];

    do{
        metricDisplayOptionList();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:

                printBikeInventoryToScreen(bikePtr);
                valid =1;
                break;
            case 2:
                bikeInventoryOutput(bikePtr);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}


/**
 * This function will set the value for Bike Inventory before it's print
 * @param numOfRows total number of trips that is use to pass into sub functions.
 * @param tripPtr is point to the data for trip list.
 * @param bikePtr is point to the data for bike list.
 */
void setBikesAttributes(int numOfRows,Trip *tripPtr,Bike *bikePtr){
    /**Setting total duration, total minutes, end station id for bikes*/
    setBikeEndStationId(numOfRows, tripPtr, bikePtr);
    /**Setting the num trips count for bikes*/
    setBikeTrips(numOfRows, tripPtr, bikePtr);
}
/**
 * This function will display the bike inventory on screen.
 * @param bikePtr is use to access the the data for bikes
 */
void printBikeInventoryToScreen(Bike *bikePtr){
    int i=0;
    printf("\n\t\tBike Inventory:\n");
    for(i=0;i<N;i++) {
        if (bikePtr[i].bikeId != 0) {
            printf("\nBike ID: %5d\tBike EndStation:%d\tNumber of Trips:%d\tTotal Duration: %7d\n",
                   bikePtr[i].bikeId, bikePtr[i].endStationId, bikePtr[i].numTrips,
                   bikePtr[i].totalDuration);
            printf("Total minutes:%7.2f                           \t\tMaintenance Flag: %c\n\n",
                   bikePtr[i].totalMinutes, bikePtr[i].maintenanceFlag);
        }
    }
}


/**
 * This function will display all the metrics for the trips and the bikes to the output file.
 * @param numOfRows is the number of trips.
 * @param tripPtr is pointing to the data for the trips.
 * @param bikeIdPtr is pointing to the data for the bikes.
 */
void printCEOReport(int numOfRows, Trip *tripPtr,Bike *bikePtr){
    FILE *filePtr;
    int metric1=averageNumTripsCal(numOfRows);
    int metric2=hourLargestTripCal(numOfRows,tripPtr);
    char inBuf[20],outputFileName[50];
  
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
  
    fprintf(filePtr,"Metric 1:\n Average number of trips per hour: %d\n",metric1);
    fprintf(filePtr,"Metric 2:\n The hour with largest number of trips: %d\n",metric2);
    printMetric3(numOfRows,tripPtr,&filePtr);
    printMetric4(numOfRows,tripPtr,&filePtr);
    printMetric5(numOfRows,tripPtr,&filePtr);
    printMetrics6(numOfRows,tripPtr,&filePtr);
    printMetric7(numOfRows,tripPtr,&filePtr);
    printMetric8(numOfRows,tripPtr,&filePtr);
    printMetric9(bikePtr,&filePtr);
    printMetric10(bikePtr,&filePtr);
    printMetric11(bikePtr,&filePtr);
    printMetric12(bikePtr,&filePtr);
    printMetric13(numOfRows,tripPtr,bikePtr,&filePtr);
	
    fclose(filePtr);
}
 /**
  * This function will print the results of metric 3 to the CEO report output file.
  * @param numOfRows is the number of trips to be use.
  * @param tripPtr is pointing to the data for the trips.
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric3(int numOfRows,Trip *tripPtr,FILE **filePtr){
    int i=0;
    int   *result = malloc(numOfRows*sizeof(int));
    reportTripsCountEachHourCal(numOfRows,tripPtr,result);
    fprintf(*filePtr,"Metric 3:\n      Report of Trips Count in Each Hour:\n");
    for(i = 0 ; i < numOfRows; i++) {
        if (result[i] != 0) { fprintf(*filePtr,"                Hour : %2d - %7d Trips\n", tripPtr[i].startHr, result[i]); }
    }
    free(result);
}
/**
  * This function will print the results of metric 4 to the CEO report output file.
  * @param numOfRows is the number of trips to be use.
  * @param tripPtr is pointing to the data for the trips.
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric4(int numOfRows,Trip *tripPtr,FILE **filePtr){
    long double a=0,b=0;
    averageTripsDurationCal(numOfRows,tripPtr,&a,&b);
    fprintf(*filePtr,"Metric 4:\n 	Average Trips Duration in Millisecond: %.0Lf  ms\n",a);
    fprintf(*filePtr," 	Average Trips Duration in Minutes    : %9.0Lf  min\n",b);
}
/**
  * This function will print the results of metric 5 to the CEO report output file.
  * @param numOfRows is the number of trips to be use.
  * @param tripPtr is pointing to the data for the trips.
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric5(int numOfRows,Trip *tripPtr,FILE **filePtr){
    int durationMs,durationMin;
    longestTripDurationCal(numOfRows,tripPtr,&durationMs,&durationMin);
    fprintf(*filePtr,"Metric 5:\n	        Trip with longest Duration:\n");
    fprintf(*filePtr,"	Duration in MS:\t\t%8d ms\n	Duration in Minutes:\t%8d min\n ",durationMs,durationMin);
}
/**
  * This function will print the results of metric 6 to the CEO report output file.
  * @param numOfRows is the number of trips to be use.
  * @param tripPtr is pointing to the data for the trips.
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetrics6(int numOfRows,Trip *tripPtr,FILE **filePtr){
    int i=0;
    busyStation *station = malloc(sizeof(busyStation ) * N );
    initializePtrValues(station);
    busiestSSCal(numOfRows, tripPtr,station);
    fprintf(*filePtr,"Metric 6:\n	        The 5 Busiest Starting Stations:\n");
    for( i =0;i<5;i++){
        fprintf(*filePtr,"         Start Station ID: %d\tTrips: %3d\n",station[i].stationId,station[i].count);
    }
    free(station);
}
/**
  * This function will print the results of metric 7 to the CEO report output file.
  * @param numOfRows is the number of trips to be use.
  * @param tripPtr is pointing to the data for the trips.
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric7(int numOfRows,Trip *tripPtr,FILE **filePtr){
    int i=0;
    busyStation *station = malloc(sizeof(busyStation ) * N );
    initializePtrValues(station);
    busiestESCal(numOfRows, tripPtr, station);
    qsort(station,N, sizeof(busyStation),busiestStartStationDescending);
    fprintf(*filePtr,"Metric 7:\n	        The 5 Busiest Ending Stations:\n");
    for( i =0;i<5;i++){
        fprintf(*filePtr,"         End Station ID: %d\tTrips: %3d\n",station[i].stationId,station[i].count);
    }
    free(station);
}
/**
  * This function will print the results of metric 8 to the CEO report output file.
  * @param numOfRows is the number of trips to be use.
  * @param tripPtr is pointing to the data for the trips.
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric8(int numOfRows,Trip *tripPtr,FILE **filePtr){
    double percent1,percent2;
    percentageTripCal(numOfRows,tripPtr,&percent1,&percent2);
    fprintf(*filePtr,"Metric 8:\n	        The percentage of trips in each membership type:\n");
    fprintf(*filePtr,"          Casual:     %.2f%%\n",percent1);
    fprintf(*filePtr,"          Registered: %.2f%%\n",percent2);
}
/**
  * This function will print the results of metric 9 to the CEO report output file.
  * @param bikeIdPtr is pointing to the data for the bikes
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric9(Bike *bikeIdPtr,FILE **filePtr){
    int i=0;
    qsort(bikeIdPtr,N, sizeof(Bike),bikeTotalDurationDescendingComparator);
    fprintf(*filePtr,"Metric 9:\n	        The 10 bikes with the longest duration in minutes:\n");
    for(i=0;i<10;i++){
        fprintf(*filePtr,"	  Bike ID:  %5d\t\tDuration:%10.2f minutes\n",bikeIdPtr[i].bikeId,bikeIdPtr[i].totalMinutes);
    }

}
/**
  * This function will print the results of metric 10 to the CEO report output file.
  * @param bikeIdPtr is pointing to the data for the bikes
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric10(Bike *bikeIdPtr,FILE **filePtr){
    int i=0;
    qsort(bikeIdPtr,N, sizeof(Bike),bikeTotalDurationDescendingComparator);
    fprintf(*filePtr,"Metric 10:\n	        Where the 10 bikes above are located at the end of the day:\n\n");
    for(i=0;i<10;i++){
        fprintf(*filePtr,"	  Bike ID: %8d\tLocated At End Station ID: %8d\n",bikeIdPtr[i].bikeId,bikeIdPtr[i].endStationId);}
}
/**
  * This function will print the results of metric 11 to the CEO report output file.
  * @param bikeIdPtr is pointing to the data for the bikes
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric11(Bike *bikeIdPtr,FILE **filePtr){
    int i=0;
    qsort(bikeIdPtr,N, sizeof(Bike),bikeNumTripsDescendingComparator);
    fprintf(*filePtr,"Metric 11:\n	        The 10 bikes with the most trips:\n\n");
    for(i=0;i<10;i++){
        fprintf(*filePtr,"	  Bike ID:%8d\tNum Trips:%8d\n",bikeIdPtr[i].bikeId,bikeIdPtr[i].numTrips);
    }
}
/**
  * This function will print the results of metric 12 to the CEO report output file.
  * @param bikeIdPtr is pointing to the data for the bikes
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric12(Bike *bikeIdPtr,FILE **filePtr){
    int result;
    result=bikeSmallTripsCal(bikeIdPtr);
    fprintf(*filePtr,"Metric 12:\n	     How many bikes were only used for 2 or less trips:\n\n");
    fprintf(*filePtr,"	  Total of %d bikes were only used for 2 or less trips\n",result);
}
/**
  * This function will print the results of metric 13 to the CEO report output file.
  * @param numOfRows is the number of trips to be use.
  * @param tripPtr is pointing to the data for the trips.
  * @param bikeIdPtr is pointing to the data for the bikes
  * @param filePtr is pointing to the pointer that is pointing to the file that the CEO results will be written to.
  */
void printMetric13(int numOfRows,Trip *tripPtr,Bike *bikeIdPtr,FILE **filePtr){
    int i,j;
    SmallTrips *smallTripsPtr=malloc(numOfRows * sizeof(SmallTrips));
    initializeSmallTripsList(numOfRows,smallTripsPtr);
    smallList(numOfRows,tripPtr,bikeIdPtr,smallTripsPtr);
    fprintf(*filePtr,"Metric 13:\n	        List of the start station IDs and the number of trips for the bikes with 2 or less trips:\n\n");
    for(i=0;i<N;i++){
        if(bikeIdPtr[i].bikeId != 0 && bikeIdPtr[i].numTrips<=2){
            smallTripsPtr[i].numTrips=bikeIdPtr[i].numTrips;
            fprintf(*filePtr,"\nBike ID: %d Number of trips: %d\n",bikeIdPtr[i].bikeId, smallTripsPtr[i].numTrips);
            for(j=0;j<numOfRows;j++){
                if(bikeIdPtr[i].bikeId == smallTripsPtr[j].bikeId){
                    fprintf(*filePtr,"Start Station id: %d\n",smallTripsPtr[j].startStationId);
                }
            }
        }
    }
    free(smallTripsPtr);
}


/**
 * This function will check to see if the bike Id is in the list or not.
 * @param bikePtr is pointing to the data for the bikes
 * @param userInPut is the bike ID that the user is looking for.
 * @return 1 if Bike Id is in the list else return 0.
 */
int bikeContainCheck(Bike *bikePtr,int userInPut){
    int i,contain=0;
    for(i=0;i<N;i++){
        if(userInPut == bikePtr[i].bikeId){
            contain=1;
            break;
        }
    }
    return contain;
}
/**
 * This function will print the information for 1 Bike out to screen or to output file.
 * @param bikePtr is pointing to the data for the bikes
 */
void printOneBike(Bike *bikePtr){
    int userChoice=0,valid=0,userInPut=0,contain=0;
    char inBuf[20];
    printf("Enter a bike ID:\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%d",&userInPut);
    contain =bikeContainCheck(bikePtr,userInPut);
    if(contain==1) {
        do {
            metricDisplayOptionList();
            fgets(inBuf, 20, stdin);
            sscanf(inBuf, "%d", &userChoice);
            switch (userChoice) {
                case 1:
                    printOneBikeCal(userInPut,bikePtr);
                    valid = 1;
                    break;
                case 2:
                    printOneBikeOutput(bikePtr, userInPut);
                    valid = 1;
                    break;
                default:
                    printf("Invalid input please enter your choice again\n");
            }
        } while (valid == 0);
    }else{
        printf("Cannot find the Bike to display:\n");
    }
}
/**
 * This function will find the information of a bike and print it information out to screen.
 * @param userInPut is the Bike looking for.
 * @param bikePtr  is the list of bikes to look for.
 */
void printOneBikeCal(int userInPut, Bike *bikePtr){
    int i=0;
    for (i = 0; i < N; i++) {
        if (userInPut == bikePtr[i].bikeId) {
            printf("\nBike ID: %5d\tBike EndStation:%d\tNum Trips:%d\tTotal Duration: %7d\n",
                   bikePtr[i].bikeId, bikePtr[i].endStationId, bikePtr[i].numTrips,
                   bikePtr[i].totalDuration);
            printf("Total minutes:%7.2f                           \tMaintenance Flag: %c\n\n",
                   bikePtr[i].totalMinutes, bikePtr[i].maintenanceFlag);
            break;
        }
    }
}


/**
 * This function will flag 10 bikes with longest duration for maintenance.
 * @param bikePtr is pointing to bikes data.
 */
void bikesForMaintenance(Bike *bikePtr){
    int i;
      for (i = 0;  i< N; i++) {
        bikePtr[i].maintenanceFlag='0';
    }
    qsort(bikePtr,N, sizeof(Bike),bikeTotalDurationDescendingComparator);
    printf("Bikes flagged for maintenance:\n");
    for(i=0;i<10;i++){
        bikePtr[i].maintenanceFlag='1';
        printf("Bike Id: %5d Flag: %c\n",bikePtr[i].bikeId,bikePtr[i].maintenanceFlag);
    }
}


/**
 * Prompt messages of Update Bike option.
 */
void updateBikePrompt(){
    printf("\n1 - Add a Bike\n");
    printf("2 - Remove a Bike\n");
}
/**
 * This function will let the user choose if if they want to add or remove a bike from the bie list.
 * @param bikePtr is the data of bikes that will be pass to addBike or removeBike function to use.
 */
void updateBike(Bike *bikePtr){
    int userChoice=0,valid=0;
    char inBuf[20];
    do{
        updateBikePrompt();
        fgets(inBuf,20,stdin);
        sscanf(inBuf,"%d",&userChoice);
        switch(userChoice){
            case 1:
                addBike(bikePtr);
                valid =1;
                break;
            case 2:
                removeBike(bikePtr);
                valid =1;
                break;
            default:
                printf("Invalid input please enter your choice again\n");
        }}while(valid==0);
}


/**
 * This function will add one bike of user choice to the bike list.
 * @param bikePtr is pointing the bike list that the new bike to be added to.
 */
void addBike(Bike *bikePtr){
    int i=0,bikeID,choice=0,valid=0;
    do{
        bikeID=bikeId();
        for (i=0;i<N;i++){
            if(bikeID == bikePtr[i].bikeId){
                printf("Bike already in the list try again.\n");
                choice =1;
                break;
            }
        }
        if(choice !=1){
            choice =2;
        }
        switch(choice)  {
            case 1:
                printf("Enter Again\n");
                choice =0;
                break;
            case 2:
                addBikeCal(bikeID,bikePtr);
                valid=1;
                break;
        }
    }while(valid==0);
}
/**
 * This function will add the new bike to the bike list.
 * @param bikeID is the new bike ID
 * @param bikePtr is pointing to the bike list where the new bike will be added in.
 */
void addBikeCal(int bikeID,Bike *bikePtr){
    int i=0;
    for (i=0;i<N;i++){
        if(bikePtr[i].bikeId == 0){
            printf("Enter the info for the bike that you want in to add here: \n");
            bikePtr[i].bikeId=bikeID;
            bikePtr[i].endStationId= endStationId();
            bikePtr[i].numTrips=numTrips();
            bikePtr[i].totalDuration=totalDuration();
            bikePtr[i].totalMinutes=(float)bikePtr[i].totalDuration/60000;
            break;}
    }
}


/**
 * This function get the bike ID of user choice.
 * @return the user ID back to addBike() function.
 */
int bikeId(){
    int bikeId;
    char inBuff[20];
    printf("Enter your Bike ID:\n");
    fgets(inBuff,20,stdin);
    sscanf(inBuff,"%d",&bikeId);
    return bikeId;
}
/**
 * This function get the bike end station ID of user choice.
 * @return the ID back to addBike() function.
 */
int endStationId(){
    int endStationId;
    char inBuff[20];
    printf("EndStation ID:\n");
    fgets(inBuff,20,stdin);
    sscanf(inBuff,"%d",&endStationId);
    return endStationId;
}
/**
 * This function get the number of trips of the new bike.
 * @return the number of trips to be add to the inventory.
 */
int numTrips(){
    int numTrips;
    char inBuff[20];
    printf("Total Number of Trips:\n");
    fgets(inBuff,20,stdin);
    sscanf(inBuff,"%d",&numTrips);
    return numTrips;
}
/**
 * This function get the total duration of the new bike.
 * @return the totalDuration of the new bike.
 */
int totalDuration(){
    int totalDuration;
    char inBuff[20];
    printf("Total Duration:\n");
    fgets(inBuff,20,stdin);
    sscanf(inBuff,"%d",&totalDuration);
    return totalDuration;
}

/**
 * This function will remove one bike of user choice from the bike list.
 * @param bikePtr is the bike list.
 */
void removeBike(Bike *bikePtr){
    int i=0,bikeId=0,position=0;
    char inBuff[20];
    printf("Enter the Bike ID to remove:\n");
    fgets(inBuff,20,stdin);
    sscanf(inBuff,"%d",&bikeId);

    /**Finding position of Bike*/
    for(i = 0 ; i < N ;i++){
        if(bikePtr[i].bikeId == bikeId) {
            position=i;
            break;
        }
    }
    if(position == 0){
        printf("Cannot Find the Bike Id to Remove.");
    }else {
	    removeBikeCal(position,bikePtr);
    }
}
/**
 * This function will remove the chosen bike from the inventory.
 * @param position is the position of the bike to be remove.
 * @param bikePtr is the inventory the remove from.
 */
void removeBikeCal(int position, Bike *bikePtr){
    int i;
    printf("Bike ID: %d is removed form the list\n",bikePtr[position].bikeId);
    for (i = position; i < N; i++) {
        bikePtr[i].bikeId = bikePtr[i + 1].bikeId;
        bikePtr[i].numTrips=bikePtr[i+1].numTrips;
        bikePtr[i].totalDuration=bikePtr[i+1].totalDuration;
        bikePtr[i].totalMinutes=bikePtr[i+1].totalMinutes;
        bikePtr[i].endStationId=bikePtr[i+1].endStationId;
        bikePtr[i].maintenanceFlag=bikePtr[i+1].maintenanceFlag;
    }
}

/**
 * This function setting all of the bikes data to 0.
 * @param bikePtr is pointing to the bikes data
 */
void emptyBikeValues(Bike *bikePtr){
    int i =0;
    for( i = 0 ; i< N; i++){
        if(bikePtr[i].bikeId==0){
            bikePtr[i].bikeId =0;
            bikePtr[i].numTrips=0;
            bikePtr[i].totalDuration=0;
            bikePtr[i].totalMinutes=0;
            bikePtr[i].endStationId=0;
            bikePtr[i].maintenanceFlag=0;
        }
    }
}

/**output the result to file for metric 1*/
void outputToFile1(int  toOutPut) {
    FILE *filePtr;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"Average number of trips per hour: %3d\n", toOutPut);
    fclose(filePtr);}
/**output the result to file for metric 2*/
void outputToFile(int  toOutPut) {
    FILE *filePtr;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"The hour with largest number of trips: %d\n", toOutPut);
    fclose(filePtr);}
/**output the result to file for metric 3*/
void outputToFile3(int numOfRows, Trip *tripPtr,int *result){
    int i;
    FILE *filePtr;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n      Report of Trips Count in Each Hour:\n");
    for(i=0;i<numOfRows;i++){
        if(result[i] != 0)
        {
            fprintf(filePtr,"Hour : %d  =%7d  Trips\n", tripPtr[i].startHr, result[i]);
        }
    }
    fclose(filePtr);

}
/**output the result to file for metric 4*/
void outputToFile4(long double a, long double b ){
    FILE *filePtr;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"Average Trips Duration in Millisecond: %.0Lf ms\n",a);
    fprintf(filePtr,"Average Trips Duration in Minutes    : %9.0Lf min\n",b);
    fclose(filePtr);
}
/**output the result to file for metric 5*/
void outputToFile5(int a, int b) {
    FILE *filePtr;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	        Trip with longest Duration:\n");
    fprintf(filePtr,"\nDuration in MS:\t\t%8d ms\nDuration in Minutes:\t%8d min\n ",a,b);
    fclose(filePtr);
}
/**output the result to file for metric 6*/
void outputToFile6(busyStation *busiestStartPtr){
    FILE *filePtr;
    int i;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	        The 5 Busiest Starting Stations:\n");
    for(i=0; i<5; ++i){
        fprintf(filePtr,"\nStart Station ID: %d\tTrips: %3d\n", busiestStartPtr[i].stationId,busiestStartPtr[i].count);}

    fclose(filePtr);
}
/**output the result to file for metric 7*/
void outputToFile7(busyStation *busiestEndPtr){
    FILE *filePtr;
    int i;
    char inBuf[20],outputFileName[50];

    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	        The 5 Busiest Ending Stations:\n");
    for(i=0; i<5; ++i){
        fprintf(filePtr,"\nEnd Station ID: %d\tTrips: %3d\n", busiestEndPtr[i].stationId,busiestEndPtr[i].count);}
    fclose(filePtr);
}
/**output the result to file for metric 8*/
void outputToFile8(const double p1, const double p2){
    FILE *filePtr;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	        The percentage of trips in each membership type:\n");
    fprintf(filePtr,"Casual:     %.2f%%\n",p1);
    fprintf(filePtr,"Registered: %.2f%%\n",p2);
    fclose(filePtr);}
/**output the result to file for metric 9*/
void outputToFile9(Bike *bikeIdPtr){
    FILE *filePtr;
    int i;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	        The 10 bikes with the longest duration in minutes:\n");
    for(i=0;i<10;i++){
        fprintf(filePtr,"Bike ID:  %5d\t\tDuration:%10d minutes\n",bikeIdPtr[i].bikeId,bikeIdPtr[i].totalDuration/60000);
    }
    fclose(filePtr);
}
/**output the result to file for metric 10*/
void outputToFile10(Bike *bikeIdPtr){
    FILE *filePtr;
    int i;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	        Where the 10 bikes above are located at the end of the day:\n\n");
    for(i=0;i<10;i++){
        fprintf(filePtr,"Bike ID: %8d\tLocated At End ID Station: %8d\n",bikeIdPtr[i].bikeId,bikeIdPtr[i].endStationId);}
    fclose(filePtr);
}
/**output the result to file for metric 11*/
void outputToFile11(Bike *bikeIdPtr){
    FILE *filePtr;
    int i;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	        The 10 bikes with the most trips:\n\n");
    for(i=0;i<10;i++){
        fprintf(filePtr,"Bike ID:%8d\tNum Trips:%8d\n",bikeIdPtr[i].bikeId,bikeIdPtr[i].numTrips);
    }
    fclose(filePtr);
}
/**output the result to file for metric 12*/
void outputToFile12(int result){
    FILE *filePtr;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	     How many bikes were only used for 2 or less trips:\n\n");
    fprintf(filePtr,"\nTotal of %d bikes were only used for 2 or less trips\n",result);
    fclose(filePtr);
}
/**output the result to file for metric 13*/
void outputToFile13(int numOfRows,Bike *bikeIdPtr,SmallTrips *smallTripsPtr){
    FILE *filePtr;
    int i=0,j=0;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n	       List of the start station IDs and the number of trips for the bikes with 2 or less trips:\n\n");
    for(i=0;i<N;i++){
        if(bikeIdPtr[i].bikeId != 0 && bikeIdPtr[i].numTrips<=2){
            smallTripsPtr[i].numTrips=bikeIdPtr[i].numTrips;
            fprintf(filePtr,"\nBike ID: %d Num trips: %d\n",bikeIdPtr[i].bikeId, smallTripsPtr[i].numTrips);
            for(j=0;j<numOfRows;j++){
                if(bikeIdPtr[i].bikeId == smallTripsPtr[j].bikeId){
                    fprintf(filePtr,"Start Station id: %d\n",smallTripsPtr[j].startStationId);
                }
            }
        }
    }
    fclose(filePtr);
}
/**output the result to file for Trip Data*/
void tripDataToOutput(int numOfRows, Trip *tripPtr){
    FILE *filePtr;
    int i=0;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    for(i=0;i<numOfRows;i++){
        for(i=0;i<numOfRows;i++){
            fprintf(filePtr,"\nMembership Type: %10s\t\tStart Station Id: %-5d\t\tEnd Station Id: %-5d\t\tBike Id: %-5d\n",tripPtr[i].membershipType, tripPtr[i].startStationId, tripPtr[i].endStationId, tripPtr[i].bikeId);
            fprintf(filePtr,"Duration: %15d ms\t\tHour: %2d\t\t\tMinute: %2d\n\n", tripPtr[i].duration, tripPtr[i].startHr, tripPtr[i].startMin);
        }
    }
    fclose(filePtr);
}
/**output the result to file for Bike Inventory*/
void bikeInventoryOutput(Bike *bikePtr){
    FILE *filePtr;
    int i=0;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    fprintf(filePtr,"\n\t\tBike Inventory:\n");
    for(i=0;i<N;i++) {
        if (bikePtr[i].bikeId != 0) {
            fprintf(filePtr,"\nBike ID: %5d\tBike EndStation:%d\tNumber of Trips:%d\tTotal Duration: %7d\n",
                   bikePtr[i].bikeId, bikePtr[i].endStationId, bikePtr[i].numTrips,
                   bikePtr[i].totalDuration);
            fprintf(filePtr,"Total minutes:%7.2f                           \t\tMaintenance Flag: %c\n\n",
                   bikePtr[i].totalMinutes, bikePtr[i].maintenanceFlag);
        }
    }
    fclose(filePtr);
}
/**output the result to file for Print One Bike*/
void printOneBikeOutput(Bike *bikePtr,int userInput){
    FILE *filePtr;
    int i=0;
    char inBuf[20],outputFileName[50];
    printf("Enter the name of your output file\n");
    fgets(inBuf,20,stdin);
    sscanf(inBuf,"%s",outputFileName);
    filePtr = fopen(outputFileName, "w");
    for(i=0;i<N;i++){
        if(userInput == bikePtr[i].bikeId){
            fprintf(filePtr,"\nBike ID: %5d\tBike EndStation:%d\tNum Trips:%d\tTotal Duration: %7d\n", bikePtr[i].bikeId,bikePtr[i].endStationId,bikePtr[i].numTrips,bikePtr[i].totalDuration);
            fprintf(filePtr,"Total minutes:%7.2f                           \tMaintenance Flag: %c\n\n",bikePtr[i].totalMinutes,bikePtr[i].maintenanceFlag);
            break;
        }
    }
    fclose(filePtr);
}






/**comparator for descending order for trip struct based on the duration.*/
int comparatorDescending(const void *p, const void *q){
    int l = ((Trip *)p)->duration;
    int r = ((Trip *)q)->duration;
    return (r) - (l);
}
/**comparator for descending order for Trip struct based on startStationId.*/
int startStationDescendingComparator(const void *p, const void *q){
    int l = ((Trip *)p)->startStationId;
    int r = ((Trip *)q)->startStationId;
    return (r) - (l);
}
/**comparator for descending order for Trip struct based on endStationId.*/
int endStationDescendingComparator(const void *p, const void *q){
    int l = ((Trip *)p)->endStationId;
    int r = ((Trip *)q)->endStationId;
    return (r) - (l);
}
/**comparator for descending order for busyStation based on count*/
int busiestStartStationDescending(const void *p, const void *q){
    int l = ((busyStation *)p)->count;
    int r = ((busyStation *)q)->count;
    return (r-l) ;
}
/**comparator for the membershipType in descending order, since its s string we use strcmp to compare the 2 strings*/
int memberTypeDescending(const void *p, const void *q){
    const Trip *pp = p;
    const Trip *qq = q;
    return strcmp(pp->membershipType,qq->membershipType);
}
/**comparator for descending order for Trip struct based on  bikeId.*/
int bikeIdComparator(const void *p, const void *q){
    int l = ((Trip *)p)->bikeId;
    int r = ((Trip *)q)->bikeId;
    return (r-l);
}
/**comparator for descending order for Bike struct based on  bikeId.*/
int bikeIdDescending(const void *p, const void *q){
    int l = ((Bike *)p)->bikeId;
    int r = ((Bike *)q)->bikeId;
    return (r-l);
}
/**comparator for descending order for Bike struct based on  totalDuration.*/
int bikeTotalDurationDescendingComparator(const void *p, const void *q){
    int l = ((Bike *)p)->totalDuration;
    int r = ((Bike *)q)->totalDuration;
    return (r-l);
}
/**comparator for descending order for Bike struct based on  numTrips.*/
int bikeNumTripsDescendingComparator(const void *p, const void *q){
    int l = ((Bike *)p)->numTrips;
    int r = ((Bike *)q)->numTrips;
    return (r -l);
}
/**comparator for ascending order for Bike struct based on  numTrips.*/
int bikeNumTripsAscendingComparator(const void *p, const void *q){
    int l = ((Bike *)p)->numTrips;
    int r = ((Bike *)q)->numTrips;
    return (l-r);
}
