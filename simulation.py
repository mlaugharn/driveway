import random
import math
import os

def simulate(observation_period = 31556926, max_driveway_length = 10, average_arrival_rate = 90, average_service_rate = 60, average_meal_cost = 3, per_meal_cost = .25):
	total_cars = 0
	cars_rejected = 0
	seconds_waited = 0
	seconds_passed = 0
	meals_served = 0
	profit = 0
	driveway = [0] * max_driveway_length
	driveway_states = [0] * (max_driveway_length + 1) #0 through incl. 10
	rand = random.random
	numcars = 0
	print("starting simulation...")
	while seconds_passed < observation_period:
		car_leaves = numcars > 0 and driveway[0] <= 0
		if car_leaves:
			driveway.pop(0)
			driveway.append(0)
			numcars -= 1
			driveway_states[numcars] += 1
		car_shows_up = rand() <= (1 / average_arrival_rate)
		if car_shows_up:
			total_cars += 1
			car_enters = numcars < max_driveway_length
			if car_enters:
				driveway[numcars] = average_service_rate
				numcars += 1
				driveway_states[numcars] += 1
				meals_served += 1
				profit += average_meal_cost - per_meal_cost
			else:
				cars_rejected += 1
		for index, car in enumerate(driveway):
			if car > 0:
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
	print("driveway_states:", driveway_states)
	return profit
