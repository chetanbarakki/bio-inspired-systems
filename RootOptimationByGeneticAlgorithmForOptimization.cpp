#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

struct Individual {
    double x;
    double fitness;
};

// Calculate fitness
double calculateFitness(double x, double target) {
    double error = abs(x * x - target);

    return 1.0 / (1.0 + error);
}

int main() {

    double target;
    cout << "Enter number: ";
    cin >> target;

    double lower = 0;
    double upper = max(1.0, target);

    const int POP_SIZE = 100;
    const int GENERATIONS = 1000;
    const double MUTATION_RATE = 0.1;

    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<double> initialDist(lower, upper);
    uniform_real_distribution<double> probability(0.0, 1.0);

    vector<Individual> population;

    for (int i = 0; i < POP_SIZE; i++) {

        double x = initialDist(gen);

        population.push_back({
            x,
            calculateFitness(x, target)
        });
    }

    for (int generation = 0;
         generation < GENERATIONS;
         generation++) {

        for (auto &individual : population) {
            individual.fitness =
                calculateFitness(individual.x, target);
        }
        sort(population.begin(),
             population.end(),
             [](const Individual &a,
                const Individual &b) {

                 return a.fitness > b.fitness;
             });

        double bestX = population[0].x;

        // Stop if sufficiently accurate
        if (abs(bestX * bestX - target) < 1e-10) {
            break;
        }

        vector<Individual> newPopulation;

        int eliteCount = POP_SIZE * 0.2;

        for (int i = 0; i < eliteCount; i++) {
            newPopulation.push_back(population[i]);
        }


        uniform_int_distribution<int> parentDist(
            0,
            eliteCount - 1
        );

        while (newPopulation.size() < POP_SIZE) {

            double parent1 =
                population[parentDist(gen)].x;

            double parent2 =
                population[parentDist(gen)].x;


            double alpha = probability(gen);

            double child =
                alpha * parent1 +
                (1 - alpha) * parent2;


            if (probability(gen) < MUTATION_RATE) {

                // Mutation amount
                double mutation =
                    (probability(gen) * 2 - 1)
                    * (upper - lower)
                    * 0.05;

                child += mutation;
            }

            child = max(lower, min(upper, child));

            newPopulation.push_back({
                child,
                calculateFitness(child, target)
            });
        }

        population = newPopulation;
    }


    sort(population.begin(),
         population.end(),
         [](const Individual &a,
            const Individual &b) {

             return a.fitness > b.fitness;
         });

    double answer = population[0].x;

    cout << "\nApproximate square root = "
         << answer << endl;

    cout << "Square of answer = "
         << answer * answer << endl;

    cout << "Error = "
         << abs(answer * answer - target)
         << endl;

    return 0;
}
