#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void shift_over_one_left(int array[], size_t length);
float simulate(long observation_period, int max_driveway_length, int average_arrival_rate, int average_service_rate, float average_meal_cost, float per_meal_cost);

int main(void){
	simulate(31556926, 11, 90, 45, 3, .25);
	return 0;
}

float simulate(long observation_period, int max_driveway_length, int average_arrival_rate, int average_service_rate, float average_meal_cost, float per_meal_cost){
	float inv_arrival_rate = 1.0 / average_arrival_rate;
	int total_cars = 0;
	int cars_left = 0;
	int cars_rejected = 0;
	int seconds_waited = 0;
	int seconds_passed = 0;
	int meals_served = 0;
	float profit = 0;
	int driveway[max_driveway_length];
	int driveway_states[max_driveway_length];
	memset(driveway, 0, (max_driveway_length + 1) * sizeof(int));
	memset(driveway_states, 0, (max_driveway_length + 1) * sizeof(int));
	int numcars = 0;
	srand(time(NULL));
	printf("starting simulation...\n");
	while (seconds_passed < observation_period){
		bool car_leaves = (numcars > 0 && driveway[0] <= 0);
		cars_left++;
		if (car_leaves){
			shift_over_one_left(driveway, max_driveway_length);
			numcars--;
			driveway_states[numcars]++;
		}
		bool car_shows_up = (float)(rand()) / RAND_MAX <= inv_arrival_rate;
		if (car_shows_up){
			total_cars++;
			bool car_enters = (numcars < max_driveway_length);
			if (car_enters){
				driveway[numcars] = average_service_rate;
				numcars++;
				driveway_states[numcars]++;
				meals_served++;
				profit += average_meal_cost - per_meal_cost;
			}
			else {
				cars_rejected++;
			}
		}
		int i;
		for (i = 0; i < max_driveway_length; i++){
			if (driveway[i] > 0){
				driveway[i]--;				
				seconds_waited++;
			}
		}
		seconds_passed++;
	}
	float percent_cars_served = meals_served / total_cars;
	printf("\n");
	printf("total_cars: %d\n", total_cars);
	printf("percent_cars_served: %f\n", percent_cars_served);
	printf("cars_left: %d\n", cars_left);
	printf("cars_rejected: %d\n", cars_rejected);
	printf("seconds_waited: %d\n", seconds_waited);
	printf("seconds_passed: %d\n", seconds_passed);
	printf("meals_served: %d\n", meals_served);
	printf("profit: %f\n", profit);
	int i = 0;
	printf("driveway_states:\n");
	for (i = 0; i < max_driveway_length + 1; i++){
		printf("%d: %d\n", i, driveway_states[i]);
	}
	return profit;
}

void shift_over_one_left(int array[], size_t length){
	int i;
	for (i = 0; i < length; i++){
		if (i == length - 1){
			*(array + i) = 0;
		}
		else {
			*(array + i) = *(array + i + 1);
		}
	}
	return;
}