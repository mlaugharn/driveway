import simulation

if __name__ == '__main__':
	simulation.simulate(int(input("observation_period (s): \n")),
int(input("max_driveway_length (cars): \n")),
int(input("average_arrival_rate (s): \n")),
int(input("average_service_rate (s): \n")),
int(input("average_meal_price ($): \n")),
float(input("per_meal_cost ($): \n")))