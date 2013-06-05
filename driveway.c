#include "stdbool.h"
#include <stdio.h>
#include <time.h>

void simulate(__int32 observation_period, int max_driveway_length, int average_arrival_rate, int average_service_rate, float average_meal_cost, float per_meal_cost);

int main(void){
	simulate(31556926, 10, 90, 45, 3, .25);
	return 0;
}

void simulate(__int32 observation_period, int max_driveway_length, int average_arrival_rate, int average_service_rate, float average_meal_cost, float per_meal_cost){
	int total_cars = 0;
	int cars_rejected = 0;
	int seconds_waited = 0;
	int seconds_passed = 0;
	int meals_served = 0;
	int profit = 0;
	int driveway[max_driveway_length];
	int driveway_states[max_driveway_length + 1];
	memset(driveway, 0, max_driveway_length * sizeof(int));
	memset(driveway_states, 0, (max_driveway_length + 1) * sizeof(int));
	int numcars = 0;
	srand(time(NULL));
	printf("starting simulation...\n");
	while (seconds_passed < observation_period){
		bool car_leaves = (numcars > 0 && driveway[0] <= 0);
		if (car_leaves){
			int i;
			for (i = 0; i < max_driveway_length; i++){
				if (i == max_driveway_length - 1){
					driveway[i] = 0;
				}
				else {
					driveway[i] = driveway[i + 1];
				}
			}
			numcars--;
			driveway_states[numcars]++;
		}
		bool car_shows_up = rand() < 1.0 / average_arrival_rate;
		if (car_shows_up){
			total_cars++;
			bool car_enters = (numcars < max_driveway_length);
			if (car_enters){
				int i;
				for (i = max_driveway_length; i > 0; i--){
					if (driveway[i] == 0){
						driveway[i] = average_service_rate;
						break;
					}
				}
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
	printf("\n");
	printf("total_cars: %d\n", total_cars);
	printf("cars_rejected: %d\n", cars_rejected);
	printf("seconds_waited: %d\n", seconds_waited);
	printf("seconds_passed: %d\n", seconds_passed);
	printf("meals_served: %d\n", meals_served);
	printf("profit: %d\n", profit);
	int i = 0;
	printf("driveway_states:\n");
	for (i = 0; i < max_driveway_length + 1; i++){
		printf("%d: %d\n", i, driveway_states[i]);
	}
}