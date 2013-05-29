import random
import math
def simulate(observation_period = 31556926, max_driveway_length = 10, average_arrival_rate = 90, average_service_rate = 45, average_meal_cost = 3, per_meal_cost = .25):
	total_cars = 0
	cars_rejected = 0
	seconds_waited = 0
	seconds_passed = 0
	meals_served = 0
	profit = 0
	driveway = []
	print("starting simulation...")
	while seconds_passed < observation_period:
		if len(driveway) > 0 and driveway[0] <= 0:
			driveway.pop(0)
		car_shows_up = random.random() <= (1 / average_arrival_rate)
		if car_shows_up:
			total_cars += 1
			car_enters = len(driveway) < max_driveway_length
			if car_enters:
				driveway.append(average_service_rate)
				meals_served += 1
				profit += average_arrival_rate - per_meal_cost
			else:
				cars_rejected += 1
		for index, car in enumerate(driveway):
			driveway[index] = car - 1
			seconds_waited += 1
		seconds_passed += 1
	print()
	print("total_cars:", total_cars)
	print("cars_rejected:", cars_rejected)
	print("seconds_waited:", seconds_waited)
	print("seconds_passed:", seconds_passed)
	print("meals_served:", meals_served)
	print("profit:", profit)
	print("driveway:", driveway)
	return profit