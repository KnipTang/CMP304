#include "openGA.hpp"

#include <iostream>

std::string valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.|!#$£%^&*()=+?@ 1234567890";
std::string target_string = "To be, or not to be.";


struct Chromosome
{
	std::string data;
};

struct Cost
{
	float cost;
};

typedef EA::Genetic < Chromosome, Cost> Genetic_Algorithm;
typedef EA::GenerationType < Chromosome, Cost> Generation_Type;

bool calculate_cost(const Chromosome& individual, Cost& cost)
{
	int score = 0;

	for (size_t i = 0; i < individual.data.length(); i++)
	{
		if (individual.data[i] != target_string[i])
			score++;
	}

	cost.cost = score;

	return true;
}

Chromosome mutation_function(const Chromosome& X_base, const std::function<double(void)>& rnd01, double shrink_scale)
{
	Chromosome newChromosome;
	newChromosome.data = X_base.data;

	int randomindex = rnd01() * newChromosome.data.length();
	int randomindexNew = rnd01() * valid_chars.length();

	newChromosome.data[randomindex] = valid_chars[randomindexNew];

	return newChromosome;
}

Chromosome crossover_function(const Chromosome& X1, const Chromosome& X2, const std::function<double(void)>& rnd01)
{
	Chromosome newChromosome;

	for (size_t i = 0; i < X1.data.length(); i++)
	{
		float randomindex = rnd01();

		if (randomindex > 0.5f)
			newChromosome.data.push_back(X1.data[i]);
		else
			newChromosome.data.push_back(X2.data[i]);
	}

	return newChromosome;
}

void report_generation(int generation_number, const Generation_Type& last_generation, const Chromosome& best_genes)
{
	std::cout << "Generation [" << generation_number << "], " << std::endl;

	std::cout << "Generation [" << last_generation.best_total_cost << "], " << std::endl;

	std::cout << "Generation [" << last_generation.average_cost << "], " << std::endl;

	std::cout << "Generation [" << last_generation.exe_time << "], " << std::endl;

	std::cout << "Generation [" << best_genes.data << "], " << std::endl;
}

char generate_random_character(const std::function<double(void)> &rnd01)
{
	return valid_chars[(int)(valid_chars.size() * rnd01())];
}

void shakespeare_init_genes(Chromosome& s, const std::function<double(void)> &rnd01)
{
	for (int i = 0; i < target_string.size(); i++)
	{
		s.data += generate_random_character(rnd01);
	}
}

double calculate_total_fitness(const Genetic_Algorithm::thisChromosomeType & X)
{
	return X.middle_costs.cost;
}

int main()
{
	EA::Chronometer timer;
	timer.tic();

	Genetic_Algorithm ga_obj;
	ga_obj.problem_mode = EA::GA_MODE::SOGA;	// State the Genetic Algorithm is aiming for a single objective.
	ga_obj.population = 200;
	ga_obj.generation_max = 1000;				// We want this to keep attempting for a long time.
	ga_obj.init_genes = shakespeare_init_genes;
	ga_obj.calculate_SO_total_fitness = calculate_total_fitness;
	ga_obj.eval_solution = calculate_cost;
	ga_obj.mutate = mutation_function;
	ga_obj.crossover = crossover_function;
	ga_obj.crossover_fraction = 1;
	ga_obj.SO_report_generation = report_generation;
	ga_obj.mutation_rate = 0.05;
	ga_obj.best_stall_max = 1000;
	ga_obj.average_stall_max = 1000;
	EA::StopReason reason = ga_obj.solve();

	std::cout << "The problem is optimized in " << timer.toc() << " seconds." << std::endl;

	std::cin.get();
}